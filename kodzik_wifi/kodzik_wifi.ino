#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
//#include <ISADefinitions.h>

ESP8266WiFiMulti WiFiMulti;

volatile int counter = 0;

void count(){
  counter++;
  //Serial.print("counter jest");
}

void setup() {
  Serial.begin(9600);
  pinMode(D2, INPUT);
  pinMode(D1, OUTPUT);
  
  delay(500);
  int i;
  for(i = 0; i < 10; ++i){
    digitalWrite(D1, !!(i%2));
    delay(500);
  }

  attachInterrupt(digitalPinToInterrupt(D2), count, RISING);
  
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("SKN_SERVER", "masloorzechowe");
}

void loop() {
  
  if((WiFiMulti.run() == WL_CONNECTED)) {
     //Serial.print("O_O");

      HTTPClient http;
      //counter = digitalRead(D2);

      //delay(1000*10);

      
      //Serial.print(counter);

      //delay(1000 * 60 * 1);

      if(counter == 0){
         http.begin("http://192.168.1.100/index.php?status=0");
         digitalWrite(D1, LOW);
         delay(500);

         int httpCode = http.GET();

         if(httpCode == HTTP_CODE_OK) {
             Serial.println(http.getString());
         } 
      }
      else{
         //http.begin("http://192.168.1.100/index.php?status=0");
         digitalWrite(D1, HIGH);
         //delay(1000 * 60 * 2);
         counter = 0;
         for(int i = 0; i < 4; ++i){
            http.begin("http://192.168.1.100/index.php?status=1");
            delay(1000 * 60);
             
            int httpCode = http.GET();

            if(httpCode == HTTP_CODE_OK) {
            Serial.println(http.getString());
            }   
         }
      }

  
    http.end();
  }
  //Serial.print(digitalRead(D2));

}

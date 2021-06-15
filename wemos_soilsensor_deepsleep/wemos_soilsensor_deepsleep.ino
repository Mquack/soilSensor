#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

int PWR = D5;
String sensorName = "Sensor1";                                        //Name it something unique, the name will be sent along with the data

void setup() {
  pinMode(PWR, OUTPUT);
  //Serial.begin(115200);
  WiFi.begin("SSID", "password");                                     //Connect to Wifi

  while (WiFi.status() != WL_CONNECTED){                              //Wait for the WiFI to connect
    delay(500);
    //Serial.println("Waiting for connection");
  }
  digitalWrite(PWR, HIGH);
  delay(500);
  int sensorValue = analogRead(A0);
  delay(500);
  digitalWrite(PWR, LOW);

  Serial.println(sensorValue);

  if(WiFi.status() == WL_CONNECTED){                                 //Check WiFi connection status
   HTTPClient http;                                                  //Declare object of class HTTPClient
   http.begin("http://ip.of.your.server:5000/soilstatushandler");    //Set request destination, port 5000 used in server example code.
   http.addHeader("Content-Type", "text/plain");                     //Set content-type header

   String packet = String(sensorValue) + sensorName;
   int httpCode = http.POST(packet);                                //Send request
   //Serial.println("Packet sent to server...");
   http.end();                                                      //Close connection

  }else{
   //Serial.println("Error in WiFi connection");
   delay(200);
  }
  //ESP.deepSleep(30e6 * 10);                                       // 30 seconds.
  //ESP.deepSleep(36e7 * 10);                                       // one hour.
  ESP.deepSleep(36e8 * 3);                                          // three hour.
  //ESP.deepSleep(36e8 * 6);                                        // six hour.
}

void loop() {
                                                                    //empty loop, we will be going to deepsleep at the end of setup()
}

#include <Arduino.h>
#include <SoftwareSerial.h>
//Dougyd
#define ab true
#define tankID int(5)

SoftwareSerial esp(10, 11); // RX | TX

int getWaterLevel();
String sendData(String command, const int timeout, boolean debug);

void setup()
{
  Serial.begin(9600);
  Serial.begin(9600);
  esp.begin(9600); //Baud Rate for command Mode.
  
  sendData("AT+RST\r\n", 10000, ab);
  sendData("AT+CWJAP=\"Digicel_WiFi_U957\",\"\"\r\n", 5000, ab);
}

void loop()
{
  //sendData("AT+CIPSTART=\"TCP\",\"192.168.100.67\",\"5000\"", 3000, ab);
  // String post = "POST /tank HTTP/1.1\r\nHost: 192.168.100.67:5000\r\nContent-Type: application/json\r\nContent-Length: 44\r\n\r\n{  \"tank_id\": \"" + String(tankID) + String("\", \"water_level\": ") + getWaterLevel() + " }";
  // sendData("AT+CIPSEND=160\r\n", 2000, ab);
  // sendData(post, 10000, st);
  //delay(5000);

  // Feed any data from esp to Terminal.
  if (esp.available())
    Serial.write(esp.read());

  // Feed all data from termial to esp
  if (Serial.available())
    esp.write(Serial.read());
}

int getWaterLevel()
{
  return random(10, 201);
}

String sendData(String command, const int timeout, boolean debug)
{
  String response = "";

  esp.print(command); // send the read character to the esp8266

  unsigned long int time = millis();

  while ((time + timeout) > millis())
  {
    while (esp.available())
    {

      // The esp has data so display its output to the serial window
      char c = esp.read(); // read the next character.
      response += c;
    }
  }

  if (debug)
  {
    Serial.print(response);
  }

  return response;
}
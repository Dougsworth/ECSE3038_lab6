# ECSE3038_lab6

Aim
This lab is meant to get students more accustomed to the technologies used in designing and implementing an embedded module as part of an IoT system and RESTful API server. As such, the system should consists of an embedded client as well as a server. A detailed outline of the requirements of the lab can be found here.

Client
For the final part of the system you're meant to build, you'll have to send status updates from each tank's location. You'll have to design a circuit that consists of an atmega based microcontroller (eg. Atmega328p) and an ESP8266 WiFi module.
Your goal is to continuously send POST requests to your server from the embedded circuit. 
Your POST request should send a JSON object as payload.

Server
You'll have to add a new route handler to your API. The route handler function should accept a POST request on the path "/tank": `POST /tank`.

The function should also take the `water_level` value from the request body and calculate the `percentage_full` by converting the `water_level` value to a percentage. As specified before, a `water_level` value of 10 should evaluate to a `percentage_full` of 100 and a `water_level`of 200 should evaluate to a `percentage_full` of 0.

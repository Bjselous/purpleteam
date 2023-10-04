#include <Arduino.h>
#include <WiFi.h>
#include <DNSServer.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "soc/soc.h"             // disable brownout problems
#include "soc/rtc_cntl_reg.h"    // disable brownout problems
#include "purpleconstants.h"
#include "movementcommands.h"
#include "ui.h"
#include <ESP32Servo.h>

// Set web server port number to 80
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
IPAddress local_IP(192,168,201,200);
IPAddress gateway(192, 168, 1, 4);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8); 
IPAddress secondaryDNS(8, 8, 4, 4);

/// @brief Connects to the wifi network using the passed ssid and pwd
/// @param ssid 
/// @param pwd 
void connectToWiFi(const char * ssid, const char * pwd)
{
    
  //  Serial.println("Scanning WIFI Network: " + String(ssid));
  //  int numberOfNetworks = WiFi.scanNetworks(); 
  //  Serial.println("Number of networks dount: " + String(numberOfNetworks));
  
  // for(int i =0; i<numberOfNetworks; i++)
  // { 
  //     Serial.print("Network name: ");
  //     Serial.println(WiFi.SSID(i));
  //     Serial.print("Signal strength: ");
  //     Serial.println(WiFi.RSSI(i));
  //     Serial.println("-----------------------"); 
  // }
  
  Serial.println("Connecting to WiFi network: " + String(ssid));

  //set up static IP address so that we can enter known ip addresses on devices 
  if(!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) 
  {
    Serial.println("STA Failed to configure");
  }

  WiFi.begin(ssid, pwd);

  int connectionAttemptCycles =0;

  while (WiFi.status() != WL_CONNECTED) 
  {
    // Blink LED while we're connecting:
    //digitalWrite(GREENLED_PIN, HIGH);
    delay(500);
    //digitalWrite(GREENLED_PIN, LOW);
    delay(500);
    Serial.println(WiFi.status());
    connectionAttemptCycles++;

    //If we havent connected in 5 cycles restart
    if(connectionAttemptCycles>5)
    {
      //digitalWrite(REDLED_PIN, LOW);
      //digitalWrite(GREENLED_PIN, LOW);
      Serial.println("Restarting ESP");
      Serial.println();
      Serial.println();
      Serial.println();
      ESP.restart();
    }
  }

  //digitalWrite(GREENLED_PIN, HIGH);
  //digitalWrite(REDLED_PIN, LOW);

  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

/// @brief Displays the rootpage
/// @param request 
void displayRoot(AsyncWebServerRequest *request) 
{
  request->send_P(200, "text/html", htmlHomePage);
}

/// @brief Displays feedback for page not found
/// @param request 
void displayPageNotFound(AsyncWebServerRequest *request) 
{
    request->send(404, "text/plain", "File Not Found");
}

void processMovementCommand(String inputValue)
{

  switch(inputValue.toInt())
  {

      case STOP_ALL:
        handleStopAll();                       
      break;

    case FORWARD:
        handleForward();                       
      break;

    case CREEP_FORWARD:
        handleCreepForward();                       
      break;
  
    case REVERSE:
        handleReverse();
      break;

    case CREEP_REVERSE:
      handleCreepReverse();
    break;
  
    case STOPACCELERATION:
        handleStopAcceleration();
      break;
  
    case ELEVATE_TURRET:
        handleElevateTurret();
      break;

    case SLOW_ELEVATE_TURRET:
        handleSlowElevateTurret();
      break;
  
    case DEPRESS_TURRET:
        handleDepressTurret();
      break;

    case SLOW_DEPRESS_TURRET:
        handleSlowDepressTurret();
      break;
  
    case STOP_TURRET_ELEVATION_CHANGE:
        handleStopTurretElevationChange();
      break;
  
    case TRAVERSE_TURRET_ANTICLOCKWISE:
        handleTraverseTurretAnticlockwise();
      break;
  
    case TRAVERSE_TURRET_CLOCKWISE:
        handleTraverseTurretClockwise();  
      break;
  
    case STOP_TURRET_TRAVERSE_CHANGE:
        handleStopTurretTraverseChange();
      break;
  
    case WATER_START:
        handleWaterStart();  
      break;
  
    case WATER_STOP:
        handleWaterStop();      
      break;

    case LINEAR_ACTUATOR_UP:
        handleLinearActuatorUp();      
      break;
  
    case LINEAR_ACTUATOR_DOWN:
        handleLinearActuatorDown();      
      break;

    case LINEAR_ACTUATOR_STOP:
        handleLinearActuatorStop();      
      break;

    default:
      Serial.println("Unkown Websocket event code");    
      break;
  }
}

void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) 
{                 
  switch (type) 
  {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      //client->text(getRelayPinsStatusJson(ALL_RELAY_PINS_INDEX));
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      processMovementCommand("0");
      break;
    case WS_EVT_DATA:
      AwsFrameInfo *info;
      info = (AwsFrameInfo*)arg;
      if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) 
      {
        std::string myData = "";
        myData.assign((char *)data, len);
        processMovementCommand(myData.c_str());       
      }
      break;
    case WS_EVT_PONG:
      Serial.println("Websocket pong");
    case WS_EVT_ERROR:
      Serial.println("Websocket error");
      break;
    default:
      break;  
  }
}

void setup() 
{
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector

  pinMode(SERVO_ELEVATION_PIN, OUTPUT);
  pinMode(SERVO_TRAVERSE_PIN, OUTPUT);
 
  pinMode(MD_ENABLE, OUTPUT);
  pinMode(MD_IN_3, OUTPUT);
  pinMode(MD_IN_4, OUTPUT);

  pinMode(PD_ENABLE, OUTPUT);
  pinMode(PD_IN_1, OUTPUT);
  pinMode(PD_IN_2, OUTPUT);

  pinMode(LA_ENABLE, OUTPUT);
  pinMode(LA_IN_1, OUTPUT);
  pinMode(LA_IN_2, OUTPUT);
  
  digitalWrite(LA_IN_1, LOW);
  digitalWrite(LA_IN_2, LOW);

  Serial.begin(115200); // Starts the serial communication // Setup serial object and define transmission speed
  Serial.println("");
  Serial.println("");// Clear some space in serial monitor
   
  // Connect to the WiFi network (see function below loop)
  connectToWiFi(networkName, networkPswd);
  
  WiFi.softAP(networkName, networkPswd);
 
  server.on("/", HTTP_GET, displayRoot);
  server.onNotFound(displayPageNotFound);
  
  ws.onEvent(onWebSocketEvent);
  server.addHandler(&ws);
 

  server.begin();
  Serial.println("HTTP server started");
  
  ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	elevation_servo.setPeriodHertz(50);    // standard 50 hz servo
  elevation_servo.attach(SERVO_ELEVATION_PIN,500, 2400);
  elevation_servo.write(90);
  delay(20);
  traverse_servo.setPeriodHertz(50);    // standard 50 hz servo
  traverse_servo.attach(SERVO_TRAVERSE_PIN,500, 2400);
  traverse_servo.write(90);
  delay(20);

  Serial.println("Setup() Complete");
}

void loop() 
{
  //Remove any old clients to improve performance
  ws.cleanupClients(); 
}

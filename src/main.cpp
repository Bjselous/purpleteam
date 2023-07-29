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

// Set web server port number to 80
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

/// @brief Connects to the wifi network using the passed ssid and pwd
/// @param ssid 
/// @param pwd 
void connectToWiFi(const char * ssid, const char * pwd)
{
    
  // Serial.println("Scanning WIFI Network: " + String(ssid));
  // int numberOfNetworks = WiFi.scanNetworks(); 
  // Serial.println("Number of networks dount: " + String(numberOfNetworks));
  
  // for(int i =0; i<numberOfNetworks; i++)
  // { 
  //     Serial.print("Network name: ");
  //     Serial.println(WiFi.SSID(i));
  //     Serial.print("Signal strength: ");
  //     Serial.println(WiFi.RSSI(i));
  //     Serial.println("-----------------------"); 
  // }
  
  Serial.println("Connecting to WiFi network: " + String(ssid));
  WiFi.begin(ssid, pwd);

  int connectionAttemptCycles =0;

  while (WiFi.status() != WL_CONNECTED) 
  {
    // Blink LED while we're connecting:
    digitalWrite(GREENLED_PIN, HIGH);
    delay(1000);
    digitalWrite(GREENLED_PIN, LOW);
    delay(1000);
    Serial.println(WiFi.status());
    connectionAttemptCycles++;

    //If we havent connected in 5 cycles restart
    if(connectionAttemptCycles>5)
    {
      digitalWrite(REDLED_PIN, LOW);
      digitalWrite(GREENLED_PIN, LOW);
      Serial.println("Restarting ESP");
      Serial.println();
      Serial.println();
      Serial.println();
      ESP.restart();
    }
  }

  digitalWrite(REDLED_PIN, LOW);
  digitalWrite(GREENLED_PIN, HIGH);
  delay(250);
  digitalWrite(GREENLED_PIN, LOW);
  delay(250);
  digitalWrite(GREENLED_PIN, HIGH);
  delay(250);
  digitalWrite(GREENLED_PIN, LOW);
  delay(250);
  digitalWrite(GREENLED_PIN, HIGH);
  delay(250);
  digitalWrite(GREENLED_PIN, LOW);

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
        handleForward();                       
      break;

    case FORWARD:
        handleForward();                       
      break;
  
    case REVERSE:
        handleReverse();
      break;
  
    case STOPACCELERATION:
        handleStopAcceleration();
      break;
  
    case ELEVATE_TURRET:
        handleElevateTurret();
      break;
  
    case DEPRESS_TURRET:
        handleDepressTurret();
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

  pinMode(REDLED_PIN, OUTPUT);
  pinMode(GREENLED_PIN, OUTPUT);

  Serial.begin(115200); // Starts the serial communication // Setup serial object and define transmission speed
  Serial.println("");
  Serial.println("");// Clear some space in serial monitor

  //Red LED on so know there is power
  digitalWrite(REDLED_PIN, HIGH);

  // Connect to the WiFi network (see function below loop)
  connectToWiFi(networkName, networkPswd);
  
  WiFi.softAP(networkName, networkPswd);
 
  server.on("/", HTTP_GET, displayRoot);
  server.onNotFound(displayPageNotFound);
  
  ws.onEvent(onWebSocketEvent);
  server.addHandler(&ws);
  

  server.begin();
  Serial.println("HTTP server started");
  Serial.println("Setup() Complete");
}

void loop() 
{
  ws.cleanupClients(); 
}

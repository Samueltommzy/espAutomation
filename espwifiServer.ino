#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

MDNSResponder mdns;

// Replace with your network credentials
const char* ssid = "Connectify-SAM";
const char* password = "BFORBALL";

ESP8266WebServer server(80);

String webPage = "";

int gpio13_pin = 13;
int gpio4_pin = 4;
int gpio5_pin = 5;

void setup(void){
  webPage += "<h1>My Web Server</h1><p>LED #1 <a href=\"LED1On\"><button>ON</button></a>&nbsp;<a href=\"LED1Off\"><button>OFF</button></a></p>";
  webPage += "<p>LED #2 <a href=\"LED2On\"><button>ON</button></a>&nbsp;<a href=\"LED2Off\"><button>OFF</button></a></p>";
  webPage += "<p> Fan Control <a href =\"FanHigh\"><button>HIGH</a>&nbsp;<a href=\"FanMedium\"><button>Medium</button></a>&nbsp;<a href=\"FanLow\"><button>Low</button></a></p>";

  
  // preparing GPIOs
  //pinMode(LED_BUILTIN, OUTPUT);
  //digitalWrite(LED_BUILTIN, LOW);
  pinMode(gpio4_pin, OUTPUT);
  digitalWrite(gpio4_pin, LOW);
  pinMode(gpio13_pin, OUTPUT);
  digitalWrite(gpio13_pin, LOW);
  pinMode(gpio5_pin,OUTPUT);
  analogWrite(gpio5_pin,0);
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid,password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
  
  server.on("/", [](){
    server.send(200, "text/html", webPage);
  });
  
  server.on("/LED1On", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio4_pin, HIGH);
    Serial.println("ook");
    delay(1000);
  });
  server.on("/LED1Off", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio4_pin, LOW);
    Serial.println("ok");
    delay(1000); 
  });
  server.on("/LED2On", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio13_pin, HIGH);
    delay(1000);
  });
  server.on("/LED2Off", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio13_pin, LOW);
    delay(1000); 
  });
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void){
  server.handleClient();
} 

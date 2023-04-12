#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <PulseSensorPlayground.h>

// Replace with your network credentials
const char* ssid = "OnePlus Nord2 5G";
const char* password = "vi3iq4y8";
int PulseSensorPurplePin = A0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int Signal; 
int a;               // holds the incoming raw data. Signal value can range from 0-1024        // Determine which Signal to "count as a beat", and which to ingore.


// Initialize Telegram BOT
#define BOTtoken "6220196984:AAGS7Xm_PZ0JX8-QYjziIyRxq1FKh4LJf7Q"  // your Bot Token (Get from Botfather)

// Use @myidbot to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
#define CHAT_ID "2034883649"

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);


void setup() {
  Serial.begin(115200);
  configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
  client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org


  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Bot started up \nHeart Beat detected!!");
  bot.sendMessage(CHAT_ID, "Bot started up\nThis Bot was created by Gokul for his IoT project \nHeart Beat detected!!", "");
}

void loop() {
   a = analogRead(PulseSensorPurplePin)/10;  // Read the PulseSensor's value.
    Signal = round(a);                                         // Assign this value to the "Signal" variable.
     if(Signal>80){
     Serial.println(Signal);                    // Send the Signal value to Serial Plotter.
     const String data1 = String(Signal);
     bot.sendMessage(CHAT_ID, data1, "");
     Serial.println(data1);
     }
}
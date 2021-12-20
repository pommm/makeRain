#include <NTPClient.h>
// change next line to use with another board/shield
#include <WiFi.h>
#include <Arduino.h>
#include <M5Stack.h>
const char *ssid     = "aaaa";
const char *password = "xxxx";
const long utcOffsetInSeconds = 25200;

int transformer = 2;
int valveOff = 25;
int valveOn = 5;
int pump = 26;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void setup(){
  Serial.begin(115200);
 M5.begin();
  WiFi.begin(ssid, password);
  M5.Power.begin();

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();

  pinMode(transformer, OUTPUT);
  pinMode(valveOff, OUTPUT);
  pinMode(valveOn, OUTPUT);
  pinMode(pump, OUTPUT);
}


void makeRain(){
  Serial.println("Its time!!");
  Serial.println("Turn on transformer");
  digitalWrite(transformer, HIGH);
  Serial.println("Wait for flux");
  delay(1000);
  Serial.println("Turn valve on");
  digitalWrite(valveOn, HIGH);
  delay(15000);
  digitalWrite(valveOn, LOW);
  Serial.println("Valve is on");
  delay(1000);
  
  Serial.println("Turn pump on for 3 minite");
  digitalWrite(pump, HIGH);
  delay(180000);
  Serial.println("Turn pump off");
  digitalWrite(pump, LOW);

  Serial.println("Turn valve off");
  digitalWrite(valveOff, HIGH);
  delay(15000);
  digitalWrite(valveOff, LOW);
  Serial.println("Valve is off");
  delay(1000);
  Serial.println("Turn off transformer");
  digitalWrite(transformer, LOW);
}

void loop() {
  M5.update();
  timeClient.update();
  Serial.println(timeClient.getFormattedTime());
  M5.Lcd.setCursor(30,30);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);
  M5.Lcd.print(timeClient.getFormattedTime());
  delay(200);
  M5.Lcd.clear();
  //M5.Lcd.fillScreen(TFT_BLACK);
  if(timeClient.getHours() == 9 && timeClient.getMinutes() == 00){
    makeRain();
  }
  else if (timeClient.getHours() == 12 && timeClient.getMinutes() == 00){
    makeRain();
  }
  else if (timeClient.getHours() == 15 && timeClient.getMinutes() == 00){
    makeRain();
  }
  else if (timeClient.getHours() == 18 && timeClient.getMinutes() == 33){
    makeRain();
  }
  else if (M5.BtnA.wasReleased()) {
    makeRain();
  }
  
}

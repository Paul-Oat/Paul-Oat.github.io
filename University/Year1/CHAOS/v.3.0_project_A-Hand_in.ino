//Paul Oates
//WeMos: v3.0_project_A
//14/12/2020
/////////////////////////
////////////////////////
// Importing Libaries for WeMos----------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <TM1638.h>
#include <Wire.h>
#include "RTClib.h"
#include <SPI.h>
#include <TM1638plus.h> 
#include <ESP8266WiFi.h>
 
//Setup GPIO I/O pins for strobe, clock, data-------------------------------------------------------------------------------------------------------------------------------------------------
#define  STROBE_TM 14 // strobe = D5
#define  CLOCK_TM 12  // clock =  D6
#define  DIO_TM 13 // data = D7
#define MAX 100

//wifi ssid password for WiFI server 
const char* ssid = "WIFI";
const char* password = "Password";
bool high_freq = false; //default false, If using a high freq CPU > ~100 MHZ set to true. 

//Define and start functions-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Start Wifi server 
WiFiServer server(80); 
// assigning LED and KEY cluster libary as ledKey.
TM1638plus ledKey(STROBE_TM, CLOCK_TM , DIO_TM, high_freq);
// assigining OLED Addr found in I2c BUS SCAN
#define OLED_Address 0x3C
// assigning sensor cluster libary as sensor.
Adafruit_BME280 sensor;
// assigining OLED screen size 128 x 32  
Adafruit_SSD1306 oled = Adafruit_SSD1306(128, 32, &Wire);
// assigning RTC libary as rtc
RTC_DS3231 rtc;

//Global Variables----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
float temperature, humidity, pressure;
int iBval = 1;
bool dispVal = false;

//Clear OLED display function----------------------------------------------------------------------------------------------------------------------------------------------------------------
void clear_oled(){
  // clear the display 
  oled.clearDisplay();
  oled.display();
  oled.setCursor(0, 0);
}

//Display Set Time Instructions to OLED function------------------------------------------------------------------------------------------------------------------------------------------------
void set_time_oled_info(){
    clear_oled();
    oled.println("In Time Set Mode");
    oled.println("Press S6 to decrease");
    oled.println("Press S7 to increase");
    oled.println("Press S1 to confirm");
      //send to display
    oled.display();
}

//UpdateTime Function-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void updateTime(){
  
   //Get time form RTC
  DateTime now = rtc.now();
  int h = now.hour();
  int m = now.minute();
  int s = now.second();

  //clear the display
  clear_oled();
   
  //writing the time to the display 
  oled.print("Time : ");
  
  //appending zeros if the number is less than 10 
  if (h<10) {
    oled.print("0");
  }
  
  oled.print(h);
  oled.print(":");
  
  //appending zeros if the number is less than 10 
  if (m<10) {
    oled.print("0");
  }

  oled.print(m);
  oled.print(":");
  
  //appending zeros if the number is less than 10 
  if (s<10) {
    oled.print("0");
  }
  //alternating between information to display on OLED
  oled.println(s);
  if(dispVal == false){
    oled.println("Button S1 = Temp");
    oled.println("Button S2 = Humidity");
    oled.println("Button S3 = Pressure");
    //send to display
    oled.display();
    dispVal = true;
  }
  else{
    oled.println("Button S2 = Humidity");
    oled.println("Button S3 = Pressure");
    oled.println("Button S4 = Set time");
    //send to display
    oled.display();
    dispVal = false;
  }
}

//Set Hour function------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
char set_hour(){
byte buttons;
int iHr = 12;
char stHr[2];

do {
    //Service the Watchdog
    ESP.wdtFeed();
        if (iHr < 10) {
          sprintf(stHr, "Hour  0%d", iHr);
        } else{
          sprintf(stHr, "Hour  %d", iHr);
        }
        ledKey.displayText(stHr);
        buttons =ledKey.readButtons();
        
        if (buttons == 64){ // button S6
          iHr++;
          ledKey.setLED(5,1);
          delay(500);
          ledKey.setLED(5,0);
        } else if (buttons == 32){ // button S5
          iHr--;
          ledKey.setLED(4,1);
          delay(500);
          ledKey.setLED(4,0);
        }
        if (iHr < 0) {
          iHr = 23;
        } else if (iHr > 23){
          iHr = 0;
        }
  }
      while (buttons != 1);
      return (iHr);
}


//Set Min function-----------------------------------Set Minunite-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
char set_min(){
byte buttons;
int iMin = 59;
char stMin[2];

do {
    //Service the Watchdog
    ESP.wdtFeed();
        if (iMin < 10) {
          sprintf(stMin, "Min   0%d", iMin);
        } else{
          sprintf(stMin, "Min   %d", iMin);
        }
        ledKey.displayText(stMin);
        buttons =ledKey.readButtons();

        if (buttons == 64){ // button S6
          iMin++;
          ledKey.setLED(5,1);
          delay(500);
          ledKey.setLED(5,0);
        } else if (buttons == 32){ // button S5
          iMin--;
          ledKey.setLED(4,1);
          delay(500);
          ledKey.setLED(4,0);
        }
        if (iMin < 0) {
          iMin = 59;
        } else if (iMin > 59){
          iMin = 0;
        }
  }
      while (buttons != 1);
      return (iMin);
}


//Set Second function-----------------------------------------Set Seconds-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
char set_sec(){
byte buttons;
int iSec = 59;
char stSec[2];

do {
    //Service the Watchdog
    ESP.wdtFeed();
        if (iSec < 10) {
          sprintf(stSec, "Sec   0%d", iSec);
        } else{
          sprintf(stSec, "Sec   %d", iSec);
        }
        ledKey.displayText(stSec);
        buttons =ledKey.readButtons();

        if (buttons == 64){ // button S6
          iSec++;
          ledKey.setLED(5,1);
          delay(500);
          ledKey.setLED(5,0);
        } else if (buttons == 32){ // button S5
          iSec--;
          ledKey.setLED(4,1);
          delay(500);
          ledKey.setLED(4,0);
        }
        if (iSec < 0) {
          iSec = 59;
        } else if (iSec > 59){
          iSec = 0;
        }
  }
      while (buttons != 1);
      return (iSec);
}

//Set Time function
void set_time(){//-----------------------------------------Set Time-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

byte buttons;
int iHr = 12;
int iMin = 59;
int iSec = 59;
char stTime[8];
char stHr[2];
char stMin[2];
char stSec[2];
bool blHr = true;
bool blMin = false;
bool blSec = false;

do {
  ESP.wdtFeed();
  buttons =ledKey.readButtons();
  if ((buttons == 8) && (blHr == true)) {
    
    // Display set time instruction on OLED.
    set_time_oled_info();
    
    iHr = set_hour();
    blHr = false;
    blMin = true;
    delay(500);
  }
  
  if ((buttons == 8) && (blMin == true)) {
    iMin = set_min();
    blMin = false;
    blSec = true;
    delay(500);
  }
  
  if ((buttons == 8) && (blSec == true)) {
    iSec = set_sec();
    blSec = false;
  }
}
  while (buttons != 1);
  rtc.adjust(DateTime(2020, 12, 14, iHr, iMin, iSec));
}


//Update LCD display with sensor data and option to set clock function-------------------------------------------------------------------------------------------------------------------------
void update_lcd(){
byte buttons;
char buf[MAX];
char stTemp[10];
char stHum[10];
char stPres[10];
 
  // Feed the watchdog
  ESP.wdtFeed();

  //read sensor measurements.
  temperature = sensor.readTemperature();
  humidity = sensor.readHumidity();
  pressure = sensor.readPressure() / 100.0F;
  
  // read button input.
  buttons =ledKey.readButtons();

  //display temp pressure and humidity 
  sprintf(stTemp, "T= %.1f", temperature);
  sprintf(stHum, "H= %.1f", humidity);
  sprintf(stPres, "P= %.1f", pressure);

  //serial print tempature 
  Serial.print("Temp:");
  Serial.println(stTemp); 
    //serial print Humidity 
  Serial.print("Humidity:");
  Serial.println(stHum);
  //serial print Pressure 
  Serial.print("Pressure:");
  Serial.println(stPres);
  
  if (buttons == 1){
    iBval = 1;
  }else if (buttons == 2){
    iBval = 2;
  }else if (buttons == 4){
    iBval = 4;
  }else if (buttons == 8){
    iBval = 8;
  }
  
//display the desired button press
  if (iBval== 1){ // display temperature measurement
    ledKey.reset();
    //set the correct LED on 
    ledKey.setLED(0,1);
    ledKey.setLED(1,0);
    ledKey.setLED(2,0);
    ledKey.setLED(3,0);
    ledKey.setLED(4,0);
    //display temp 
    ledKey.displayText(stTemp);
  }else if (iBval == 2){ // display humidity measurement
    ledKey.reset();
    //set the correct LED on 
    ledKey.setLED(0,0);
    ledKey.setLED(1,1);
    ledKey.setLED(2,0);
    ledKey.setLED(3,0);
    ledKey.setLED(4,0);
    //display humidity 
    ledKey.displayText(stHum);
  }else if (iBval == 4){ // display pressure measurement
    ledKey.reset();
    //set the correct LED on 
    ledKey.setLED(0,0);
    ledKey.setLED(1,0);
    ledKey.setLED(2,1);
    ledKey.setLED(3,0);
    ledKey.setLED(4,0);
    //display Pressure 
    ledKey.displayText(stPres);
  }else if (iBval == 8){ // set clock
    ledKey.setLED(0,0);
    ledKey.setLED(1,0);
    ledKey.setLED(2,0);
    ledKey.setLED(3,1);
    ledKey.setLED(4,0);
    set_time();
    //reset iBval = 1 to display temperature on lcd as default after clock set.
    iBval = 1;
  }
}

//write data to webserver function  
void webserver() {//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
 //Get time form RTC and convert to string 
  DateTime now = rtc.now();
  int h = now.hour();
  int m = now.minute();
  int s = now.second();
  char stHr[10];
  char stMin[10];
  char stSec[10];
  
 //appending zeros if the number is less than 10 
  if (h<10) {
    sprintf(stHr, "0%i", h);
  }else{
    sprintf(stHr, "%i", h);
  }
  
  //appending zeros if the number is less than 10 
  if (m<10) {
    sprintf(stMin, "0%i", m);
  }else{
    sprintf(stMin, "%i", m);
  }
  
  //appending zeros if the number is less than 10 
  if (s<10) {
    sprintf(stSec, "0%i", s);
  }else{
    sprintf(stSec, "%i", s);
  }
  
  //if a device is created 
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request from the client 
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Build web page for web server.
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  //all html prior to the RTC time  
  client.println("<!DOCTYPE html><head><meta http-equiv='refresh' content='5' ><title>Wemos Weather</title><style>td, th {border: 1px solid black text-align: left;padding: 8px;}</style></head><body><table class=MsoTableGrid border=1 cellspacing=0 cellpadding=0 style='border-collapse:collapse;border:none'><tr><th colspan='2'>WeMos Weather Status</th></tr><tr><td>Current Time</td><td>");
  client.print(stHr);
  client.print(":");
  client.print(stMin);
  client.print(":");
  client.print(stSec);
  //all html prior to the tempature variable
  client.println("</td></tr><tr><td>Temperature (C)</td><td>");
  client.println(temperature);
  //all html prior to the Humidity variable
  client.println("</td></tr><tr><td>Humidity (%)</td><td>");
  client.println(humidity);
  //all html prior to pressure 
  client.println("</td></tr><tr><td>Pressure (mb)</td><td>");
  client.println(pressure);
  client.println("</td></tr></table></body>");
  Serial.println("Client disconnected");
  Serial.println("");
}


// Main Setup Function function--------------------------------------------setup---------------------------------------------------------------------------------------------------------------------
void setup() {
  // Send LedKey startup command
  ledKey.displayBegin(); 

  // Define sensor I2C address
  sensor.begin(0x77);   

  // send adafruit startup comand 
  oled.begin(SSD1306_SWITCHCAPVCC, OLED_Address);
  Serial.begin(9600);

  //wifi start
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
   }
   
   Serial.println("");
   Serial.println("WiFi connected");
   
   // Start the server
   server.begin();
   Serial.println("Server started");

   // Print the IP address to the Serial port 
   Serial.print("Use this URL : ");
   Serial.print("http://");
   Serial.print(WiFi.localIP());
   Serial.println("/");
 
   // Display addafruit image for one second on powerup
   oled.display();
   delay(1000);
  
   // clear the display 
   oled.clearDisplay();
   oled.display();

   // set OLED Text size
   oled.setTextSize(1);
  
   //set text colour to white
   oled.setTextColor(WHITE);
}

// Main Loop Function.
void loop() {//---------------------------------------------------------------MAIN_LOOP---------------------------------------------------------------------------------------------------------------
  //call update time function
  updateTime();
  //build webserver
  webserver();
  //Delay one second
  delay(1000);
  //update lcd with sensor measurements.
  update_lcd();
 }

/* 
 *  LCD SHIELD PROGRAM v0.9 - MK 
 */
 
#include <time.h>
#include <NewPing.h>  //NEWPING-ECHO
#define TRIGGER_PIN A1
#define ECHO_PIN A2
#define MAX_DISTANCE 400

NewPing sonar(TRIGGER_PIN,ECHO_PIN,MAX_DISTANCE); //NEWPING HC-SR04

#include <LCD4Bit_mod.h>
#include <LiquidCrystal.h>
LCD4Bit_mod lcd = LCD4Bit_mod(2); //SCREEN-R2

#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 RTC;  //TIMER

#include <OneWire.h>
#include <DS18B20.h>
#define ONEWIRE_PIN 2
byte address[8] = {��������������������������������������0x28, 0xFF, 0x39, 0x4F, 0xC0, 0x16, 0x4, 0x31};
OneWire onewire(ONEWIRE_PIN);
DS18B20 sensors(&onewire);  //TERMOMETR


//Z
int b=16; int TIME=600; int add; int af; 
extern int s=1; extern int w=0; 
int k=2; int liczba; int dlug;
int g=16, h=16, j=13; int v=13; int vv; int vj=1;
int countt; char outputCountt[16]; 
int count; char outputCount[16]; 
int counttt; char outputCounttt[16]; 

int lcd_key     = 0;  //KEYS
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5


int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // 1st option will be the most likely result
 if (adc_key_in < 50)   return btnRIGHT; 
 if (adc_key_in < 195)  return btnUP;
 if (adc_key_in < 380)  return btnDOWN;
 if (adc_key_in < 555)  return btnLEFT;
 if (adc_key_in < 790)  return btnSELECT;  
 return btnNONE;  // when all others fail, return this...
}

/* /////////// */

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); //INIC.DIODY
  lcd.init(); //INIC.LCD    
  lcd.clear();
  lcd.printIn(" WELCOME TO"); lcd.cursorTo(2,0);
  lcd.printIn("  <LCD SHIELD> "); delay(TIME);
  lcd.cursorTo(1,0); lcd.printIn("DESIGNED BY");
  lcd.cursorTo(2,0); lcd.printIn("Syndicate CORP.");
 delay(TIME); 
 
  for(int a=0;a<16;a++){ 
 b--; lcd.cursorTo(1,0);
lcd.cursorTo(1,a); lcd.printIn("/");
lcd.cursorTo(2,b); lcd.printIn("\\");
  }  
lcd.clear();
delay(200);

Wire.begin();
 RTC.begin(); //TIMER
 RTC.adjust(DateTime(__DATE__, __TIME__)); 

 sensors.begin();  //TERMO.
  sensors.request(address);
}

/* /////////// */

void loop() {
  digitalWrite(LED_BUILTIN, HIGH); 
    lcd_key = read_LCD_buttons();
// OS

if(w==3){ //TIMER
lcd.cursorTo(1,0); lcd.printIn("Time:");        
 lcd.cursorTo(1,6); itoa(count, outputCount, 10); //int -> char (USNG10)
  lcd.printIn(outputCount); count++; lcd.printIn("     "); //STOPER
   DateTime now = RTC.now(); lcd.cursorTo(2,0); //CZAS GLOBALNY
   int m=now.minute(); int g=now.hour(); int d=now.day(); int mo=now.month(); int y=now.year();
  char mi[16]; itoa(m, mi, 10); char go[16]; itoa(g, go, 10); 
  char di[16]; itoa(d, di, 10); char moo[16]; itoa(mo, moo, 10);
  char yy[16]; itoa(y, yy, 10);
  
    lcd.printIn( go ); lcd.printIn(":"); lcd.printIn( mi ); 
    lcd.printIn("-"); lcd.printIn( di ); lcd.printIn( moo ); 
    lcd.cursorTo(1,12); lcd.printIn( yy );    
    
    if (sensors.available())
  {
    int temperature = sensors.readTemperature(address);
    char te[16]; itoa(temperature, te, 10);
    
    lcd.cursorTo(2,11); lcd.printIn( te ); lcd.printIn( "'C" );

    sensors.request(address);
  }
    
  delay(1000); switch (lcd_key) {case btnLEFT:{lcd.clear();w=0;count=0; break;}}  }

if(w==2){ //TEXT
  if(k==2){char a[16]="Stalo sie. Moze "; char bb[16]="nie w tak spekta"; lcd.cursorTo(1,0); lcd.printIn(a); lcd.cursorTo(2,0); lcd.printIn(bb);} 
  if(k==3){char a[16]="nie w tak spekta"; char bb[16]="kularny sposob j"; lcd.cursorTo(1,0); lcd.printIn(a); lcd.cursorTo(2,0); lcd.printIn(bb);} if(k<2){k=2;} 
  if(k==4){char a[16]="kularny sposob j"; char bb[16]="ak zapowiadaly t"; lcd.cursorTo(1,0); lcd.printIn(a); lcd.cursorTo(2,0); lcd.printIn(bb);}    
  if(k==5){char a[16]="ak zapowiadaly t"; char bb[16]="o filmy i gry..."; lcd.cursorTo(1,0); lcd.printIn(a); lcd.cursorTo(2,0); lcd.printIn(bb);} 
switch (lcd_key) {
  case btnLEFT:{lcd.clear();w=0; break;} 
  case btnDOWN:{ k++; if(w==2){break;}} 
  case btnUP:{ k--; if(w==2){break;}}
  case btnNONE:{if(w==2){break;}}}}

if(w==1){ //GAME
//g=16; h=16; j=13=v; 
//srand(time(NULL));
  liczba = rand()%100+1;

if(liczba<=50) {lcd.cursorTo(1,g); lcd.printIn("-"); g--; 
if(g<=j) { lcd.cursorTo(1,h); lcd.printIn(" "); h--;}
if(g==0){g=16; j=v; lcd.clear(); h=16;}}

lcd.cursorTo(1,0); itoa(countt, outputCountt, 10); //int -> char (USNG10)
 lcd.printIn(outputCountt); countt++; //delay(1000); 

if(vv==1) {lcd.cursorTo(1,4); lcd.printIn("<UFO>"); lcd.cursorTo(2,4); lcd.printIn("     ");}
if(vv==0) {lcd.cursorTo(2,4); lcd.printIn("<UFO>"); lcd.cursorTo(1,4); lcd.printIn("     ");}  

if(vv==1 && g==9 || dlug>=15){lcd.clear(); lcd.cursorTo(1,3); lcd.printIn("GAME OVER!"); delay(2000); w=0; countt=0;}

 
switch (lcd_key) {
  case btnNONE:{ dlug=0; vv=1; if(w==1){break;}} 
  case btnDOWN:{ dlug++; vv=0; if(w==1){break;}}
  case btnLEFT:{if(w==1){lcd.clear(); w=0; countt=0; vj=1; break;}}}
  if(countt==330) {lcd.clear(); lcd.cursorTo(1,4); lcd.printIn("YOU WON!!"); delay(3000); w=0; countt=0;}}  

if(w==0){ //MENU
lcd.cursorTo(1,0); lcd.printIn("v0.9"); lcd.cursorTo(1,12); lcd.printIn("MENU");
if(s==1) {lcd.cursorTo(2,0); lcd.printIn(">GAME TEXT TIMER");}
if(s==2) {lcd.cursorTo(2,0); lcd.printIn(" GAME>TEXT TIMER");} 
if(s==3) {lcd.cursorTo(2,0); lcd.printIn(" GAME TEXT>TIMER");}

if(sonar.ping_cm()>=1){ 
counttt = sonar.ping_cm(); 
itoa(counttt, outputCounttt, 10);
lcd.cursorTo(1,4); lcd.printIn("|"); lcd.cursorTo(1,6); lcd.printIn("  "); 
lcd.cursorTo(1,9); lcd.printIn("cm"); lcd.cursorTo(1,11); lcd.printIn("|");
lcd.cursorTo(1,5); lcd.printIn(outputCounttt); } //DISTANCE 

switch (lcd_key)               // depending on which button was pushed, we perform an action
 {
   case btnRIGHT:
     {
     if(s==1) {s=2; break;}
     if(s==2) {s=3; break;}
     if(s==3) {s=3; break;}
     }
   case btnLEFT:
     {
     if(s==3 && w==0) {s=2; break;}
     if(s==2 && w==0) {s=1; break;}
     if(s==1 && w==0) {s=1; break;}
     }
   //case btnUP:
   //case btnDOWN:
   //case btnNONE:  
   
   case btnSELECT:
     {
//---
if(s==3) {w=3; lcd.clear(); break;}
if(s==2) {w=2; lcd.clear(); break;}
if(s==1) {w=1; lcd.clear(); break;}
//---    
     }
  
 }

}}

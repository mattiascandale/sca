#include <DS1302.h>
#include <Wire.h> 
#include <PCF8574_HD44780_I2C.h>
#include <SPI.h>
#include <RFID.h> //RFID
#include <SD.h> //microSD
PCF8574_HD44780_I2C lcd(0x27,20,4); //LCD
#define SDA_DIO 10  // Pin 53 per Arduino Mega
#define RESET_DIO 9
#define delayRead 1000 // Tempo 
#define delayLed 2000 
#define V 28 //led verde
#define R 27 //led rosso
#define B 26 //buzzer
#define RE 25 //relè+led giallo
#define CS 2
#include <RTClib.h>
DS1302 rtc(8, 7, 6);
int h;
int m;
int s;
int E=0;
int Z=0;
int contatore;
int state=0;
RFID RC522(SDA_DIO, RESET_DIO);
File ingressi;
char ora;




//_________________________________________________________________//
//______________________________MODALITA' C.A._____________________//
 
String codiceAutorizzato1 = "4694F7486D";
String codiceAutorizzato2 = "ESEMPIO479";
String codiceAutorizzato3 = "ESEMPIO480";
String codicesd;
char orario[20];
char data[20];
char s_orario[20];
byte readCard[4];

void inizio()
{
  lcd.setCursor(0,0);
  lcd.print(" AVVICINARE TESSERA");
  lcd.setCursor(0,1);
  lcd.print("     PER ENTRARE    ");
  lcd.setCursor(5,3);
  lcd.print("ORE");
  lcd.print(" ");
  
}


void tessera_no()
{
  int i;
      Serial.println("Tessera non autorizzata");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.setCursor(0,0);// Set the cursor to col 0, row 0
      lcd.print("TESSERA NON");
      lcd.setCursor(0,1);
      lcd.print("AUTORIZZATA");
      delay(1000);
      for (i=0; i<4; i++){
      digitalWrite(R,HIGH);
      delay(50);
      digitalWrite(R,LOW);
      tone(B,1000,50);
      delay(50);
      noTone(B);
      delay(50);
      }lcd.clear(); }
      
void tessera_si()
{
      digitalWrite(V, HIGH);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("TESSERA AUTORIZZATA");
      lcd.setCursor(1,2);
      lcd.print("ACCESSO CONSENTITO");
      lcd.setCursor(5,3);
      lcd.print(orario);
      tone(B,1000,1000);
      delay(1000);
      noTone(B);
      digitalWrite(V, LOW);
      digitalWrite(RE, HIGH);
      delay(2000);
      digitalWrite(RE, LOW);
      lcd.clear();
}

boolean verificaCodice(String codiceLetto, String codiceAutorizzato){
  if(codiceLetto.equals(codiceAutorizzato)){
    return true;
  }else{
    return false;
  }  
}    



//_______________FINE VOIDs_________________________//

//__________INIZIO ESECUZIONE______________________//

void setup(){ 
  pinMode(SS, OUTPUT);
  pinMode(CS, OUTPUT);
  pinMode(6, INPUT_PULLUP);
  Serial.println("initialization done.");
  Serial.begin(9600);
  Wire.begin();
  SPI.begin(); 
  RC522.init();
  Serial.println("Setup");
  pinMode(V,OUTPUT);
  pinMode(R,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(RE, OUTPUT);
  lcd.init();           
  lcd.backlight();      
  lcd.clear();
  rtc.halt(false);
  rtc.writeProtect(false);
  Wire.begin();

  }

byte x=0;

  
  void loop()
{
inizio();
 int i=0;
  if (RC522.isCard())
  {
  Wire.beginTransmission(8);
    RC522.readCardSerial();
    String codiceLetto ="";
    for(i = 0; i < 5; i++)
    {
      readCard[i] = RC522.serNum[i];
      codiceLetto+= String (RC522.serNum[i],HEX);
      Wire.write(readCard[i]);
      codiceLetto.toUpperCase();
    }
    Wire.endTransmission();
    delay(100);
    if(digitalRead(6)){
      tessera_si();
    }else{
     
      tessera_no();
    }  
  } 
  }



  
 








#define SD_CS_PIN SS
byte code[4];
char codice [15];
char codesd [18];
String completo;
String completo2;
#define E 6
#include <SPI.h>
#include <SdFat.h>
#include <Wire.h>
int state=0;
File myFile;
SdFat SD;

void setup() {
 pinMode(6, OUTPUT);
 Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(ricezione); // register event
  Serial.begin(9600);           // start serial for output
}

void loop() {
  while(state==1)
  {
    check();
    state=0;
  }
}

void ricezione(int howMany)
{
while (1 < Wire.available()) { // loop through all but the last
  int i;
  completo=("");
  for(i=0; i<5;i++)
  {
    byte c = Wire.read(); // receive byte as a character
    code[i]=c;
    completo+= String(code[i], HEX);
    completo.toUpperCase();
  }
 Serial.println(completo);  
 completo.toCharArray(codice,15);
 Serial.println(codice);
 sprintf(codesd, "%s.txt", codice);
 Serial.println(codesd);
 state=1;
}}

void check()
{
  if (SD.begin(SD_CS_PIN)) {
    Serial.println("initialization failed!");
  }
  Serial.println("initialization done.");
  if(SD.exists(codesd))
  {
  digitalWrite(6, HIGH);
  delay(500);
  digitalWrite(6,LOW);
  Serial.println("esiste");
  scrittura();
  }
  else{
    Serial.println("n.e.");
  }
}




void scrittura()
{

  // Open serial communications and wait for port to open:
 Serial.print("Initializing SD card...");

  if (SD.begin(SD_CS_PIN)) {
    Serial.println("initialization failed!");
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println(completo);
    myFile.println("_________");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}


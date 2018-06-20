#define SD_CS_PIN SS
byte code[4];
char* codice;
String completo;
#include <SPI.h>
#include <SdFat.h>
#include <Wire.h>
int state=0;
File myFile;
SdFat SD;

void setup() {
 Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(ricezione); // register event
  Serial.begin(9600);           // start serial for output
}

void loop() {
  while(state==1)
  {
    controllo();
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
    completo+= String(code[i], OCT);
    completo.toUpperCase();
  }
 Serial.println(completo);  
 state=1;
}}

void controllo()
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

  // re-open the file for reading:
  myFile = SD.open("datalog.txt");
  if (myFile) {
    
    Serial.println("datalog.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}


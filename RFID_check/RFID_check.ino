// This code was developed on the basis of https://funduino.de/nr-18-rfid-kit

//Include packages
#include <SPI.h> // add SPI library
#include <MFRC522.h> //add RFID library
#define SS_PIN 10 // define pin 10 as SS (slave select)
#define RST_PIN 9 // define pin 9 as RST (reset pin)
MFRC522 mfrc522(SS_PIN, RST_PIN); // name RFID reader

// setup section:
void setup()
{
Serial.begin(9600); //sets data rate in bits per second (baud) for serial data communication
SPI.begin(); //Initializes the SPI bus by setting SCK, MOSI, and SS to outputs, pulling SCK and MOSI low, and SS high
mfrc522.PCD_Init(); //Initialize RFID Reader
pinMode (2, OUTPUT); // Der Pin 2 ist jetzt ein Ausgang (Hier wird eine LED angeschlossen)
pinMode (3, OUTPUT); // Der Pin 3 ist jetzt ein Ausgang (Hier wird eine LED angeschlossen)

}

void loop()
{
if ( ! mfrc522.PICC_IsNewCardPresent()) // if there is a RFIC Card present..
{
return; // ...go on
}

if ( ! mfrc522.PICC_ReadCardSerial()) //if a RFID card was chosen...
{
return; //... go on
}

byte code[4]={0,0,0,0}; //define a byte array to save Chip ID lateron

//Code to read and save Card ID
for (byte i = 0; i < mfrc522.uid.size; i++)
{
code[i]=mfrc522.uid.uidByte[i];
}
//Code to print Card ID as HEX number
Serial.print("Die KartenID lautet:");
for (byte i = 0; i < sizeof(code); i++)
{
Serial.print(code[i],HEX);
Serial.print(" ");
}

// Initialize a new variable to control whether a led is on or off:
bool LEDPin2 = 0; // Value 0 means LED off
bool LEDPin3 = 0; // Value 0 means LED off

if (digitalRead (2)==HIGH) {LEDPin2=1;}else{LEDPin2=0;} //Transfer Pin state to boolean
if (digitalRead (3)==HIGH) {LEDPin3=1;}else{LEDPin3=0;}


if (code[0]==0xA5 && code[1]==0xDC && code[2]==0x1C && code[3]==0xA6) // IF the ChipID is A5 DC 1C A6 ...
{ // 
if (LEDPin2 ==0) {//
  digitalWrite (2, HIGH); LEDPin2 = 1 ;delay(1000); // ...Turn on LED 2 if it is off...
}else {digitalWrite (2, LOW); LEDPin2 = 0;delay(1000);} // Turn off LED 2 if it is on
} // 

if (code[0]==0x8E && code[1]==0xE3 && code[2]==0xC2 && code[3]==0x20) // IF the ChipID is A5 DC 1C A6 ...
{ // 
if (LEDPin3 ==0) {digitalWrite (3, HIGH); LEDPin3 = 1;delay(1000); // ...Turn on LED 3 if it is off...
}else {digitalWrite (3, LOW); LEDPin3 = 0;delay(1000);} // Turn off LED 3 if it is on
} //
} // Close Sketch

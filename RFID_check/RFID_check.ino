#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup()
{
Serial.begin(9600);
SPI.begin();
mfrc522.PCD_Init();
pinMode (2, OUTPUT); // Der Pin 2 ist jetzt ein Ausgang (Hier wird eine LED angeschlossen)
pinMode (3, OUTPUT); // Der Pin 3 ist jetzt ein Ausgang (Hier wird eine LED angeschlossen)
}

void loop()
{
if ( ! mfrc522.PICC_IsNewCardPresent())
{
return;
}

if ( ! mfrc522.PICC_ReadCardSerial())
{
return;
}

byte code[4]={0,0,0,0};

for (byte i = 0; i < mfrc522.uid.size; i++)
{
code[i]=mfrc522.uid.uidByte[i];
}
Serial.print("Die KartenID lautet:");
for (byte i = 0; i < sizeof(code); i++)
{
Serial.print(code[i],HEX);
Serial.print(" ");
}

// Ab hier erfolgt die erweiterung des Programms.

if (code[0]==0xA5 && code[1]==0xDC && code[2]==0x1C && code[3]==0xA6) // Wenn der Zahlencode 1031720 lautet... {165,220,28,166}

{ // Programmabschnitt öffnen

digitalWrite (2, HIGH); // ...dann soll die LED an Pin 2 leuchten...

delay (5000); // für 5 Sekunden

digitalWrite (2, LOW); // … und danach wieder aus gehen.

} // Programmabschnitt schließen

if (code[0]==0x8E && code[1]==0xE3 && code[2]==0xC2 && code[3]==0x20) // HEX Code eingeben; beachte Präfix "0x"...

{ // Programmabschnitt öffnen

digitalWrite (3, HIGH); // ...dann soll die LED an Pin 2 leuchten...

delay (5000); // für 5 Sekunden

digitalWrite (3, LOW); // … und danach wieder aus gehen.

} // Programmabschnitt schließen


} // Sketch abschließen

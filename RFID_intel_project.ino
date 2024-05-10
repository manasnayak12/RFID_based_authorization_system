//Card UID: 30 3C 53 59
 
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
#define GREEN_LED_PIN 3
#define RED_LED_PIN 4
#define BUZZER_PIN 2

MFRC522 mfrc522(SS_PIN, RST_PIN);

int grledState = LOW;
int redledState = LOW;
int buzzerState = LOW;

void setup() 
{
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

}
void loop()
{
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "30 3C 53 59") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("ACCESS GRANTED");
    Serial.println();
    for (int i = 0; i < 1; i++) {
        digitalWrite(BUZZER_PIN, HIGH);
        digitalWrite(GREEN_LED_PIN, HIGH);
        delay(250);
        digitalWrite(BUZZER_PIN, LOW);
        digitalWrite(GREEN_LED_PIN, LOW);
        delay(350);
        
        
        
      }
    } 
    else {
      Serial.println("!!! UNAUTHOTIZED ENTRY! ACCESS DENIED !!!");
      Serial.println();
      // Red LED blinks and buzzer sounds for 5 seconds
      for (int i = 0; i < 4; i++) {
        digitalWrite(RED_LED_PIN, HIGH);
        digitalWrite(BUZZER_PIN, HIGH);
        delay(350);
        digitalWrite(RED_LED_PIN, LOW);
        digitalWrite(BUZZER_PIN, LOW);
        delay(350);
       }
   }
}   

    

#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>
LiquidCrystal_I2C lcd(0x27,16,2);
SoftwareSerial SIM900(7, 8);

#define SS_PIN 10
#define RST_PIN 9
#define LED_G 5 //define green LED pin
#define LED_R 4 //define red LED
#define RELAY 3 //relay pin
#define BUZZER 2 //buzzer pin
#define ACCESS_DELAY 2000
#define DENIED_DELAY 1000
MFRC522 mfrc522(SS_PIN, RST_PIN);   // MFRC522 instance.

int *aux;
int card1[4];
int flag = 0;
int led = 13;
int cnt =0;
 
void setup() 
{
  pinMode(led, OUTPUT);

  lcd.init();
  lcd.backlight();
  SPI.begin();          // Initiate  SPI bus
  SIM900.begin(19200);
  mfrc522.PCD_Init();   // Initiate MFRC522
    
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  digitalWrite(RELAY, HIGH);
  lcd.clear();
  lcd.print("  Welcome TO");
  lcd.setCursor(0,1);
  lcd.print("   Room - 27");
  delay(5000);
  lcd.clear();
  lcd.print("Scan Your Card ");
  lcd.setCursor(0,1);
  lcd.print(" To the Reader");

}
void loop() 
{
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
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  if (content.substring(1) == "D0 A3 5C 32")
  {
    lcd.clear();
    lcd.print("Your Card is");
    lcd.setCursor(0,1);
    lcd.print("Scanning");
    delay(2000);
    lcd.clear();
    lcd.print("ACCESS PERMIS");
    digitalWrite(LED_G, HIGH);
    lcd.clear();
    lcd.print("Welcome Back");
    lcd.setCursor(0,1);
    lcd.print("  Keirishan");
    delay(3000);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    sendSMS();
    digitalWrite(RELAY, HIGH);
    digitalWrite(LED_G, LOW);
    lcd.clear();
    lcd.print("  Welcome TO");
    lcd.setCursor(0,1);
    lcd.print("   Room - 27");
    delay(5000);
    lcd.clear();
    lcd.print("Scan Your Card ");
    lcd.setCursor(0,1);
    lcd.print(" To the Reader");
  }

else if (content.substring(1) == "B9 1B 2C C2")
  {
    lcd.clear();
    lcd.print("Your Card is");
    lcd.setCursor(0,1);
    lcd.print("Scanning");
    delay(2000);
    lcd.clear();
    lcd.print("ACCESS PERMIS");
    digitalWrite(LED_G, HIGH);
    lcd.clear();
    lcd.print("Welcome Back");
    lcd.setCursor(0,1);
    lcd.print("  Mithurshan");
    delay(3000);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    sendSMS2();
    digitalWrite(RELAY, HIGH);
    digitalWrite(LED_G, LOW);
    lcd.clear();
    lcd.print("  Welcome TO");
    lcd.setCursor(0,1);
    lcd.print("   Room - 27");
    delay(5000);
    lcd.clear();
    lcd.print("Scan Your Card ");
    lcd.setCursor(0,1);
    lcd.print(" To the Reader");
  }

 else if (content.substring(1) == "0C BC CD 22")
  {
    lcd.clear();
    lcd.print("Your Card is");
    lcd.setCursor(0,1);
    lcd.print("Scanning");
    delay(2000);
    lcd.clear();
    lcd.print("ACCESS PERMIS");
    digitalWrite(LED_G, HIGH);
    lcd.clear();
    lcd.print("Welcome Back");
    lcd.setCursor(0,1);
    lcd.print("  Nirushan");
    delay(3000);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    sendSMS3();
    digitalWrite(RELAY, HIGH);
    digitalWrite(LED_G, LOW);
    lcd.clear();
    lcd.print("  Welcome TO");
    lcd.setCursor(0,1);
    lcd.print("   Room - 27");
    delay(5000);
    lcd.clear();
    lcd.print("Scan Your Card ");
    lcd.setCursor(0,1);
    lcd.print(" To the Reader");
  }
 
 else   {
    lcd.clear();
    lcd.print("Your Card is");
    lcd.setCursor(0,1);
    lcd.print("Scanning");
    delay(2000);
    lcd.clear();
    lcd.print("Invalid Card");
    digitalWrite(LED_R, HIGH);
    delay(2000);
    lcd.clear();
    lcd.print("Better Luck");
    lcd.setCursor(0,1);
    lcd.print("Next Time");
    delay(3000);
    digitalWrite(LED_R, LOW);
    sendSMS4();
    lcd.clear();
    lcd.print("  Welcome TO");
    lcd.setCursor(0,1);
    lcd.print("   Room - 27");
    delay(5000);
    lcd.clear();
    lcd.print("Scan Your Card ");
    lcd.setCursor(0,1);
    lcd.print(" To the Reader");
    
  }
}
void sendSMS() {
  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  SIM900.println("AT+CMGS=\"+94770688841\""); 
  delay(100);
  
  // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
  SIM900.println("Keirishan has just opened the Door"); 
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26); 
  delay(100);
  SIM900.println();
  // Give module time to send SMS
  delay(5000); 
}
void sendSMS2() {
  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  SIM900.println("AT+CMGS=\"+94770688841\""); 
  delay(100);
  
  // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
  SIM900.println("Mithurshan has just opened the Door"); 
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26); 
  delay(100);
  SIM900.println();
  // Give module time to send SMS
  delay(5000); 
}
void sendSMS3() {
  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  SIM900.println("AT+CMGS=\"+94770688841\""); 
  delay(100);
  
  // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
  SIM900.println("Nirushan has just opened the Door"); 
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26); 
  delay(100);
  SIM900.println();
  // Give module time to send SMS
  delay(5000); 
}
void sendSMS4() {
  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  SIM900.println("AT+CMGS=\"+94770688841\""); 
  delay(100);
  
  // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
  SIM900.println("Unknown Person Try to Open the door"); 
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26); 
  delay(100);
  SIM900.println();
  // Give module time to send SMS
  delay(5000); 
}

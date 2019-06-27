#include <SPI.h>
#include <MFRC522.h>
#include <Keyboard.h>

#define SS_PIN 10
#define RST_PIN 9
#define KEY_RETURN 0xB0

MFRC522 rfid(SS_PIN, RST_PIN);

char Enter = KEY_RETURN;
String readid;
String card = "6d158a5";

void setup() {
  Serial.begin(9600);
  SPI.begin();
  Keyboard.begin();
  
  rfid.PCD_Init();

  Serial.println("UID de leitura de RFID");
}

void loop() {
  if (rfid.PICC_IsNewCardPresent()) {
    if (rfid.PICC_ReadCardSerial()) {
      Serial.print("TAG UID: ");

      readid = "";

      for (byte i = 0; i < rfid.uid.size; i++) {
        // Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
        // Serial.print(rfid.uid.uidByte[i], HEX);

        readid = readid + String(rfid.uid.uidByte[i], HEX);
      }

      Serial.println(readid);

      rfid.PICC_HaltA();

      if (readid == card) {
        Keyboard.press(KEY_LEFT_GUI);              //Pressione a tecla esquerda do Windows.
        Keyboard.press('l');                       //Pressione a tecla "l".
        Keyboard.releaseAll();                     //Solte todas as chaves.
        delay (100);
        Keyboard.press(Enter);                     //Pressione a tecla Enter.
        Keyboard.release(Enter);                   //Solte a tecla Enter.
        delay(100);
        Keyboard.print("PASSWORD");                    // Altere este valor para seu PIN / senha do Windows.
        Keyboard.releaseAll();
        delay(100);
        Keyboard.press(Enter);
        Keyboard.releaseAll();
      } else {
        return;
      }
    }
  }
}

#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <SoftwareSerial.h>
#include <DFPlayerMini_Fast.h>

// NFCチップのMifair UIDを記入
#define UID_01 "15 A3 C5 EF"
#define UID_02 "04 1A 86 B2 BA 5D 81"
#define UID_03 "00 00 00 00 00 00 00"
#define UID_04 "04 EF 5C B2 BA 5D 80"
#define UID_05 "04 61 5C B2 BA 5D 80"
#define UID_06 "04 91 5c b2 ba 5d 80"
#define UID_07 "00 00 00 00 00 00 00"
#define UID_08 "00 00 00 00 00 00 00"
#define UID_09 "04 92 8a b2 ba 5d 81"
#define UID_10 "00 00 00 00 00 00 00"
#define UID_11 "04 0a 61 b2 ba 5d 81"
#define UID_12 "00 00 00 00 00 00 00"
#define UID_13 "04 a0 81 b2 ba 5d 80"
#define UID_14 "00 00 00 00 00 00 00"
#define UID_15 "04 7e 81 b2 ba 5d 80"
#define UID_16 "04 78 5e b2 ba 5d 81"
#define UID_17 "04 83 67 b2 ba 5d 80"

// 再生時のNFC再読取待機
int AC_WAIT = 3000;

// 停止後のNFC再読取待機
int ST_WAIT = 2000;

// ボリューム調整
int VOL = 25;

// RC522 RST/SS アサイン設定
#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

// DFPlayer RX/TX アサイン設定
SoftwareSerial mySerial(5, 6); // RX, TX

DFPlayerMini_Fast myMP3;
String STOP_UID = "0";

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
MFRC522::MIFARE_Key key;

void setup() {
  Serial.begin(9600);   // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

  dump_byte_array(key.keyByte, MFRC522::MF_KEY_SIZE);

  mySerial.begin(9600);

  myMP3.begin(mySerial);
  myMP3.volume(VOL); 
  myMP3.wakeUp();
  Serial.println("Standby OK");
}

void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // あとで削除 
  // Dump debug info about the card; PICC_HaltA() is automatically called
  // mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  
    Serial.println("start into strBuf");
    String strBuf[mfrc522.uid.size];
    String strUID = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      strBuf[i] =  String(mfrc522.uid.uidByte[i], HEX);  // (E)using a constant integer
      if(strBuf[i].length() == 1){  // 1桁の場合は先頭に0を追加
        strBuf[i] = "0" + strBuf[i];
      }
    }

    Serial.println("start for");
    Serial.println(mfrc522.uid.size);
    Serial.println(sizeof(strBuf));
    
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      if(mfrc522.uid.size != i+1){
        strUID += strBuf[i] + " ";
      } else {
        strUID += strBuf[i]; //UIDの最後に半角スペースを入力しないようにする。
      }
    }

//    String strUID = strBuf[0] + " " + strBuf[1] + " " + strBuf[2] + " " + strBuf[3] + " " + strBuf[4] + " " + strBuf[5] + " " + strBuf[6];
    Serial.println("strUID :" + strUID);

   
    if ( strUID == STOP_UID ){
        Serial.println("Stop");
        myMP3.pause();
        STOP_UID = "0";
        delay(ST_WAIT);
    }
    else if ( strUID.equalsIgnoreCase(UID_01) ){
        Serial.println("PlayNow - 001 / UID: " + strUID);
        myMP3.playFolder(1, 1);
        delay(AC_WAIT);
        STOP_UID = strUID;
    }
    else if ( strUID.equalsIgnoreCase(UID_02) ){
        Serial.println("PlayNow - 002 / UID: " + strUID);
        myMP3.playFolder(1, 2);
        delay(AC_WAIT);
        STOP_UID = strUID;
    }
    else if ( strUID.equalsIgnoreCase(UID_03) ){
        Serial.println("PlayNow - 003 / UID: " + strUID);
        myMP3.playFolder(1, 3);
        delay(AC_WAIT);
        STOP_UID = strUID;
    }
    else if ( strUID.equalsIgnoreCase(UID_04) ){
        Serial.println("PlayNow - 001 / UID: " + strUID);
        myMP3.playFolder(1, 4);
        delay(AC_WAIT);
        STOP_UID = strUID;
    }
    else if ( strUID.equalsIgnoreCase(UID_05) ){
        Serial.println("PlayNow - 002 / UID: " + strUID);
        myMP3.playFolder(1, 5);
        delay(AC_WAIT);
        STOP_UID = strUID;
    }
    else if ( strUID.equalsIgnoreCase(UID_06) ){
        Serial.println("PlayNow - 003 / UID: " + strUID);
        myMP3.playFolder(1, 6);
        delay(AC_WAIT);
        STOP_UID = strUID;
    }
    else if ( strUID.equalsIgnoreCase(UID_07) ){
        Serial.println("PlayNow - 003 / UID: " + strUID);
        myMP3.playFolder(1, 7);
        delay(AC_WAIT);
        STOP_UID = strUID;
    }
    else if ( strUID.equalsIgnoreCase(UID_08) ){
        Serial.println("PlayNow - 003 / UID: " + strUID);
        myMP3.playFolder(1, 8);
        delay(AC_WAIT);
        STOP_UID = strUID;
    }
    else if ( strUID.equalsIgnoreCase(UID_09) ){
        Serial.println("PlayNow - 003 / UID: " + strUID);
        myMP3.playFolder(1, 9);
        delay(AC_WAIT);
        STOP_UID = strUID;
    }
    else if ( strUID.equalsIgnoreCase(UID_10) ){
        Serial.println("PlayNow - 003 / UID: " + strUID);
        myMP3.playFolder(1, 10);
        delay(AC_WAIT);
        STOP_UID = strUID;
    }
    else if ( strUID.equalsIgnoreCase(UID_11) ){
        Serial.println("PlayNow - 003 / UID: " + strUID);
        myMP3.playFolder(1, 11);
        delay(AC_WAIT);
        STOP_UID = strUID;
    }
    else if ( strUID.equalsIgnoreCase(UID_12) ){
        Serial.println("PlayNow - 003 / UID: " + strUID);
        myMP3.playFolder(1, 12);
        delay(AC_WAIT);
        STOP_UID = strUID;
    }
    else if ( strUID.equalsIgnoreCase(UID_13) ){
        Serial.println("PlayNow - 003 / UID: " + strUID);
        myMP3.playFolder(1, 13);
        delay(AC_WAIT);
        STOP_UID = strUID;
    }
    else if ( strUID.equalsIgnoreCase(UID_14) ){
        Serial.println("PlayNow - 003 / UID: " + strUID);
        myMP3.playFolder(1, 14);
        delay(AC_WAIT);
        STOP_UID = strUID;
    }
    else if ( strUID.equalsIgnoreCase(UID_15) ){
        Serial.println("PlayNow - 003 / UID: " + strUID);
        myMP3.playFolder(1, 15);
        delay(AC_WAIT);
        STOP_UID = strUID;
    }
    else if ( strUID.equalsIgnoreCase(UID_16) ){
        Serial.println("PlayNow - 003 / UID: " + strUID);
        myMP3.playFolder(1, 16);
        delay(AC_WAIT);
        STOP_UID = strUID;
    }
    else if ( strUID.equalsIgnoreCase(UID_17) ){
        Serial.println("PlayNow - 003 / UID: " + strUID);
        myMP3.playFolder(1, 17);
        delay(AC_WAIT);
        STOP_UID = strUID;
    }
    else {
        Serial.println("Unregistered / UID: " + strUID);
        delay(AC_WAIT);
    }
}

/**
 * Helper routine to dump a byte array as hex values to Serial.
 */
void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
    Serial.println("");
}
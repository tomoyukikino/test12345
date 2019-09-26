// Nefry BT Board Setting
// 1.0.7 --> OK (Works)
// 1.0.8 --> OK (Works)
// 1.1.0 --> NG (Stacked)
// 1.1.1 --> NG (Stacked)
// 1.1.3 --> NG (Compile Error)

#include <Arduino.h>
#include <Nefry.h>
#include "DFRobotDFPlayerMini.h"

HardwareSerial mySoftwareSerial(1);
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

void setup() {
  Serial.begin(115200);
  mySoftwareSerial.begin(9600, SERIAL_8N1, 19, 18);  // speed, type, RX:D3=19, TX:D4=18);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini"));
  Serial.println(F("Initializing DFPlayer ..."));

  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println(myDFPlayer.readType(),HEX);
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));

// Set serial communictaion time out 500ms
  myDFPlayer.setTimeOut(500);

//----Set volume----
  myDFPlayer.volume(2);
//  myDFPlayer.volumeUp();
//  myDFPlayer.volumeDown();

//----Set different EQ----
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
//  myDFPlayer.EQ(DFPLAYER_EQ_POP);
//  myDFPlayer.EQ(DFPLAYER_EQ_ROCK);
//  myDFPlayer.EQ(DFPLAYER_EQ_JAZZ);
//  myDFPlayer.EQ(DFPLAYER_EQ_CLASSIC);
//  myDFPlayer.EQ(DFPLAYER_EQ_BASS);

  //----Set device we use SD as default----
//  myDFPlayer.outputDevice(DFPLAYER_DEVICE_U_DISK);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
//  myDFPlayer.outputDevice(DFPLAYER_DEVICE_AUX);
//  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SLEEP);
//  myDFPlayer.outputDevice(DFPLAYER_DEVICE_FLASH);

  //----Mp3 control----
//  myDFPlayer.sleep();     //sleep
//  myDFPlayer.reset();     //Reset the module
//  myDFPlayer.enableDAC();  //Enable On-chip DAC
//  myDFPlayer.disableDAC();  //Disable On-chip DAC
//  myDFPlayer.outputSetting(true, 15); //output setting, enable the output and set the gain to 15

  //----Mp3 play----
  /*
  Serial.println(F("myDFPlayer.next()"));
  myDFPlayer.next();  //Play next mp3
  delay(delayms);
  Serial.println(F("myDFPlayer.previous()"));
  myDFPlayer.previous();  //Play previous mp3
  delay(delayms);
  Serial.println(F("myDFPlayer.play(1)"));
  myDFPlayer.play(1);  //Play the first mp3
  delay(delayms);
  Serial.println(F("myDFPlayer.loop(1)"));
  myDFPlayer.loop(1);  //Loop the first mp3
  delay(delayms);
  Serial.println(F("myDFPlayer.pause()"));
  myDFPlayer.pause();  //pause the mp3
  delay(delayms);
  Serial.println(F("myDFPlayer.start()"));
  myDFPlayer.start();  //start the mp3 from the pause
  delay(delayms);
  Serial.println(F("myDFPlayer.playFolder(15, 4)"));
  myDFPlayer.playFolder(15, 4);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  delay(delayms);
  Serial.println(F("myDFPlayer.enableLoopAll()"));
  myDFPlayer.enableLoopAll(); //loop all mp3 files.
  delay(delayms);
  Serial.println(F("myDFPlayer.disableLoopAll()"));
  myDFPlayer.disableLoopAll(); //stop loop all mp3 files.
  delay(delayms);
  Serial.println(F("myDFPlayer.playMp3Folder(4)"));
  myDFPlayer.playMp3Folder(4); //play specific mp3 in SD:/MP3/0004.mp3; File Name(0~65535)
  delay(delayms);
  Serial.println(F("myDFPlayer.advertise(3)"));
  myDFPlayer.advertise(3); //advertise specific mp3 in SD:/ADVERT/0003.mp3; File Name(0~65535)
  delay(delayms);
  Serial.println(F("myDFPlayer.stopAdvertise()"));
  myDFPlayer.stopAdvertise(); //stop advertise
  delay(delayms);
  Serial.println(F("myDFPlayer.playLargeFolder(2,999)"));
  myDFPlayer.playLargeFolder(2, 999); //play specific mp3 in SD:/02/004.mp3; Folder Name(1~10); File Name(1~1000)
  delay(delayms);
  Serial.println(F("myDFPlayer.loopFolder(5)"));
  myDFPlayer.loopFolder(5); //loop all mp3 files in folder SD:/05.
  delay(delayms);
  Serial.println(F("myDFPlayer.randomAll()"));
  myDFPlayer.randomAll(); //Random play all the mp3.
  delay(delayms);
  Serial.println(F("myDFPlayer.enableLoop()"));
  myDFPlayer.enableLoop(); //enable loop.
  delay(delayms);
  Serial.println(F("myDFPlayer.disableLoop()"));
  myDFPlayer.disableLoop(); //disable loop.
  delay(delayms);
  */

  //----Read imformation----
  Serial.println(F("--- readState ---"));
  Serial.println(myDFPlayer.readState()); //read mp3 state
  Serial.println(F("--- readVolume ---"));
  Serial.println(myDFPlayer.readVolume()); //read current volume
  //Serial.println(F("readEQ--------------------"));
  //Serial.println(myDFPlayer.readEQ()); //read EQ setting
  Serial.println(F("--- readFileCounts ---"));
  Serial.println(myDFPlayer.readFileCounts()); //read all file counts in SD card
  Serial.println(F("--- readCurrentFileNumber ---"));
  Serial.println(myDFPlayer.readCurrentFileNumber()); //read current play file number
  Serial.println(F("--- readFileCountsInFolder ---"));
  Serial.println(myDFPlayer.readFileCountsInFolder(3)); //read fill counts in folder SD:/03
  Serial.println(F("--------------------"));

  Serial.println(F("--- play(1) ---"));
  myDFPlayer.play(1);  // Play the first mp3
  Nefry.setLed(0,0,255);  // set BLUE in playing music

  // DFPlayer HTML page
  Nefry.getWebServer()->on("/DFPlayer", handleRoot);
  Nefry.getWebServer()->on("/DFPlayer_next", handleNext);
  Nefry.getWebServer()->on("/DFPlayer_prev", handlePrev);
  Nefry.getWebServer()->on("/DFPlayer_+", handleVup);
  Nefry.getWebServer()->on("/DFPlayer_-", handleVdown);
  Nefry.getWebServer()->on("/DFPlayer_pause", handlePause);
  Nefry.getWebServer()->on("/DFPlayer_start", handleStart);
  Nefry.getWebServer()->onNotFound(handleNotFound);
  Nefry.getWebServer()->begin();

  // add URL link to top page
  Nefry.setIndexLink("DFPlayer","/DFPlayer");
}

void handleNotFound(){
  String message = "File Not Found\n\n\n\n";
  Nefry.getWebServer()->send(404, "text/plain", message);
}

void handleNext() {
  Serial.println(F("--- next ---"));
  myDFPlayer.next();
  delay(200);
  if (myDFPlayer.readType()==DFPlayerPlayFinished) {
    Serial.println(F("--- Finished ---"));
    Serial.println(F("--- next ---"));
    myDFPlayer.next();
  }
  Serial.println(myDFPlayer.readCurrentFileNumber()); //read current play file number
      String content = F(
      "<!DOCTYPE HTML><html><head><meta charset=\"UTF-8\">"
      "<title>DFPlayer</title>"
      "</head><body><div><h1>DFPlayer</h1></div>");
    content += F("Current Volume: ");
    content += String(myDFPlayer.readVolume());
    content += F(" [0-30]</br>");
    content += F("Current File Number: ");
    content += String(myDFPlayer.readCurrentFileNumber());
    content += F(" [/");
    content += String(myDFPlayer.readFileCounts());
    content += F("]");
    content += F("</br></br>");
    content += F("<a href=\"/DFPlayer_prev\">prev</a> ");
    content += F("<a href=\"/DFPlayer_next\">next</a> ");
    content += F("<a href=\"/DFPlayer_+\">+</a> ");
    content += F("<a href=\"/DFPlayer_-\">-</a> ");
    content += F("<a href=\"/DFPlayer_pause\">pause</a> ");
    content += F("<a href=\"/DFPlayer_start\">start</a> ");
    content += F("</br></br>");
    content += F("<a href=\"/\">Back to top</a></body></html>");
    Nefry.getWebServer()->send(200, "text/html", content);
}

void handlePrev() {
  Serial.println(F("--- previous ---"));
  myDFPlayer.previous();
  delay(200);
  Serial.println(myDFPlayer.readCurrentFileNumber()); //read current play file number
      String content = F(
      "<!DOCTYPE HTML><html><head><meta charset=\"UTF-8\">"
      "<title>DFPlayer</title>"
      "</head><body><div><h1>DFPlayer</h1></div>");
    content += F("Current Volume: ");
    content += String(myDFPlayer.readVolume());
    content += F(" [0-30]</br>");
    content += F("Current File Number: ");
    content += String(myDFPlayer.readCurrentFileNumber());
    content += F(" [/");
    content += String(myDFPlayer.readFileCounts());
    content += F("]");
    content += F("</br></br>");
    content += F("<a href=\"/DFPlayer_prev\">prev</a> ");
    content += F("<a href=\"/DFPlayer_next\">next</a> ");
    content += F("<a href=\"/DFPlayer_+\">+</a> ");
    content += F("<a href=\"/DFPlayer_-\">-</a> ");
    content += F("<a href=\"/DFPlayer_pause\">pause</a> ");
    content += F("<a href=\"/DFPlayer_start\">start</a> ");
    content += F("</br></br>");
    content += F("<a href=\"/\">Back to top</a></body></html>");
    Nefry.getWebServer()->send(200, "text/html", content);
}

void handleVup() {
  Serial.println(F("--- up ---"));
  myDFPlayer.volumeUp();
  delay(200);
  Serial.println(myDFPlayer.readVolume()); //read current play file number
      String content = F(
      "<!DOCTYPE HTML><html><head><meta charset=\"UTF-8\">"
      "<title>DFPlayer</title>"
      "</head><body><div><h1>DFPlayer</h1></div>");
    content += F("Current Volume: ");
    content += String(myDFPlayer.readVolume());
    content += F(" [0-30]</br>");
    content += F("Current File Number: ");
    content += String(myDFPlayer.readCurrentFileNumber());
    content += F(" [/");
    content += String(myDFPlayer.readFileCounts());
    content += F("]");
    content += F("</br></br>");
    content += F("<a href=\"/DFPlayer_prev\">prev</a> ");
    content += F("<a href=\"/DFPlayer_next\">next</a> ");
    content += F("<a href=\"/DFPlayer_+\">+</a> ");
    content += F("<a href=\"/DFPlayer_-\">-</a> ");
    content += F("<a href=\"/DFPlayer_pause\">pause</a> ");
    content += F("<a href=\"/DFPlayer_start\">start</a> ");
    content += F("</br></br>");
    content += F("<a href=\"/\">Back to top</a></body></html>");
    Nefry.getWebServer()->send(200, "text/html", content);
}

void handleVdown() {
  Serial.println(F("--- down ---"));
  myDFPlayer.volumeDown();
  delay(200);
  Serial.println(myDFPlayer.readVolume()); //read current play file number
      String content = F(
      "<!DOCTYPE HTML><html><head><meta charset=\"UTF-8\">"
      "<title>DFPlayer</title>"
      "</head><body><div><h1>DFPlayer</h1></div>");
    content += F("Current Volume: ");
    content += String(myDFPlayer.readVolume());
    content += F(" [0-30]</br>");
    content += F("Current File Number: ");
    content += String(myDFPlayer.readCurrentFileNumber());
    content += F(" [/");
    content += String(myDFPlayer.readFileCounts());
    content += F("]");
    content += F("</br></br>");
    content += F("<a href=\"/DFPlayer_prev\">prev</a> ");
    content += F("<a href=\"/DFPlayer_next\">next</a> ");
    content += F("<a href=\"/DFPlayer_+\">+</a> ");
    content += F("<a href=\"/DFPlayer_-\">-</a> ");
    content += F("<a href=\"/DFPlayer_pause\">pause</a> ");
    content += F("<a href=\"/DFPlayer_start\">start</a> ");
    content += F("</br></br>");
    content += F("<a href=\"/\">Back to top</a></body></html>");
    Nefry.getWebServer()->send(200, "text/html", content);
}

void handlePause() {
  Serial.println(F("--- pause ---"));
  myDFPlayer.pause();
  delay(200);
  Nefry.setLed(255,0,0);  // set RED in playing music
      String content = F(
      "<!DOCTYPE HTML><html><head><meta charset=\"UTF-8\">"
      "<title>DFPlayer</title>"
      "</head><body><div><h1>DFPlayer</h1></div>");
    content += F("Current Volume: ");
    content += String(myDFPlayer.readVolume());
    content += F(" [0-30]</br>");
    content += F("Current File Number: ");
    content += String(myDFPlayer.readCurrentFileNumber());
    content += F(" [/");
    content += String(myDFPlayer.readFileCounts());
    content += F("]");
    content += F("</br></br>");
    content += F("<a href=\"/DFPlayer_prev\">prev</a> ");
    content += F("<a href=\"/DFPlayer_next\">next</a> ");
    content += F("<a href=\"/DFPlayer_+\">+</a> ");
    content += F("<a href=\"/DFPlayer_-\">-</a> ");
    content += F("<a href=\"/DFPlayer_pause\">pause</a> ");
    content += F("<a href=\"/DFPlayer_start\">start</a> ");
    content += F("</br></br>");
    content += F("<a href=\"/\">Back to top</a></body></html>");
    Nefry.getWebServer()->send(200, "text/html", content);
}

void handleStart() {
  Serial.println(F("--- start ---"));
  myDFPlayer.start();
  delay(200);
  Nefry.setLed(0,0,255);  // set BLUE in playing music
      String content = F(
      "<!DOCTYPE HTML><html><head><meta charset=\"UTF-8\">"
      "<title>DFPlayer</title>"
      "</head><body><div><h1>DFPlayer</h1></div>");
    content += F("Current Volume: ");
    content += String(myDFPlayer.readVolume());
    content += F(" [0-30]</br>");
    content += F("Current File Number: ");
    content += String(myDFPlayer.readCurrentFileNumber());
    content += F(" [/");
    content += String(myDFPlayer.readFileCounts());
    content += F("]");
    content += F("</br></br>");
    content += F("<a href=\"/DFPlayer_prev\">prev</a> ");
    content += F("<a href=\"/DFPlayer_next\">next</a> ");
    content += F("<a href=\"/DFPlayer_+\">+</a> ");
    content += F("<a href=\"/DFPlayer_-\">-</a> ");
    content += F("<a href=\"/DFPlayer_pause\">pause</a> ");
    content += F("<a href=\"/DFPlayer_start\">start</a> ");
    content += F("</br></br>");
    content += F("<a href=\"/\">Back to top</a></body></html>");
    Nefry.getWebServer()->send(200, "text/html", content);
}

void handleRoot() {
    String content = F(
      "<!DOCTYPE HTML><html><head><meta charset=\"UTF-8\">"
      "<title>DFPlayer</title>"
      "</head><body><div><h1>DFPlayer</h1></div>");
    content += F("Current Volume: ");
    content += String(myDFPlayer.readVolume());
    content += F(" [0-30]</br>");
    content += F("Current File Number: ");
    content += String(myDFPlayer.readCurrentFileNumber());
    content += F(" [/");
    content += String(myDFPlayer.readFileCounts());
    content += F("]");
    content += F("</br></br>");
    content += F("<a href=\"/DFPlayer_prev\">prev</a> ");
    content += F("<a href=\"/DFPlayer_next\">next</a> ");
    content += F("<a href=\"/DFPlayer_+\">+</a> ");
    content += F("<a href=\"/DFPlayer_-\">-</a> ");
    content += F("<a href=\"/DFPlayer_pause\">pause</a> ");
    content += F("<a href=\"/DFPlayer_start\">start</a> ");
    content += F("</br></br>");
    content += F("<a href=\"/\">Back to top</a></body></html>");
    Nefry.getWebServer()->send(200, "text/html", content);
}

void loop() {
  // static unsigned long timer = millis();
 Nefry.getWebServer()->handleClient();

 if (Serial.available()) {
    String inData = "";
    inData = Serial.readStringUntil('\n');
    if (inData.startsWith("n")) {
      Serial.println(F("--- next ---"));
      myDFPlayer.next();
      delay(100);
      Serial.println(myDFPlayer.readCurrentFileNumber()); //read current play file number
    } else if (inData.startsWith("p")) {
      Serial.println(F("--- previous ---"));
      myDFPlayer.previous();
      delay(100);
      Serial.println(myDFPlayer.readCurrentFileNumber()); //read current play file number
    } else if (inData.startsWith("+")) {
      Serial.println(F("--- up ---"));
      myDFPlayer.volumeUp();
      delay(100);
      Serial.println(myDFPlayer.readVolume()); //read current volume
    } else if (inData.startsWith("-")) {
      Serial.println(F("--- down ---"));
      myDFPlayer.volumeDown();
      delay(100);
      Serial.println(myDFPlayer.readVolume()); //read current volume
    } else if (inData.startsWith("*")) {
      Serial.println(F("--- pause ---"));
      myDFPlayer.pause();
    } else if (inData.startsWith(">")) {
      Serial.println(F("--- start ---"));
      myDFPlayer.start();
    }
 }

 if (myDFPlayer.available()) {
  if (myDFPlayer.readType()==DFPlayerPlayFinished) {
    Serial.println(F("--- Finished ---"));
//   Serial.println(myDFPlayer.read());
    Serial.println(F("--- next ---"));
    myDFPlayer.next();
//   Serial.println(F("--- readCurrentFileNumber ---"));
//   Serial.println(myDFPlayer.readCurrentFileNumber()); //read current play file number
    delay(100);
  }
 }  
 // if (myDFPlayer.available()) {
 //   printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
 // }
}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
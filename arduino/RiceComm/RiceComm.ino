#include <SoftwareSerial.h>
#include <ROI.h>

void setup() 
{
  Serial.begin(9600);
  Roomba.begin(115200);
  sendPacket("Sending start command...");
  delay (1000);
   // set up ROI to receive commands  
  start();
  delay(150);
  sendPacket("Sending Safe Mode command...");
  delay (1000);
  safe();  // CONTROL
  delay(150);
  sendPacket ("Setup Finished");
  delay (500);
}

//temporary string that is the incoming bytes
String incString="";
char incBuf[2] = {};

//complete packet that is to be processed
String incomingPacket="";
unsigned char PACKET_END_CHAR = 0x03;

void sendPacket(char* str)
{
  Serial.write(str);
  Serial.write(PACKET_END_CHAR);
}

void sendPacket(String str)
{
  Serial.print(str);
  Serial.write(PACKET_END_CHAR);
}

void loop() { 
  while (Serial.available())
  {
    byte c = (char)Serial.read();
    if (c==PACKET_END_CHAR)
    {
      incomingPacket = incString;
      incString="";
      break;
    }
    incBuf[0] =c;
    String s = String(incBuf);
    incString+=s;
  }
  
  if (incomingPacket.length()>0)
  {
    //Process incoming packet
    if (incomingPacket== "CLEAN")
    {
      sendPacket("Clean Command Sent");
      clean();
      delay (500);
    }
    if (incomingPacket== "DOCK")
    {
      sendPacket("Dock Command Sent");
      dock();
      delay (500);
    }
    //Clear incoming packet
    incomingPacket ="";
  }
}

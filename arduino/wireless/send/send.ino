#include <SoftwareSerial.h>
#include <VirtualWire.h>
char *controller;

void setup() 
{
  //Setup tx
   pinMode(13,OUTPUT);
   //pinMode(12,OUTPUT);
   
vw_set_ptt_inverted(true); //
vw_set_tx_pin(12);
vw_setup(4000);// speed of data transfer Kbps
  
  Serial.begin(9600);
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

void sendCommandToRX(uint8_t command){
  uint8_t c[1] ={};
  c[0]=command; 
  vw_send(c, 1);
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(13,1);
}
void start() 
{
  sendCommandToRX(128);
}

void safe() 
{
  sendCommandToRX(131);
}

void full() 
{
  sendCommandToRX(132);
}

void clean() 
{
  sendCommandToRX(135);
}

void spot() 
{
  sendCommandToRX(134);
}

void dock() 
{
  sendCommandToRX(143);
}

void power() 
{
  sendCommandToRX(133);
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

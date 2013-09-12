

void setup() {
  Serial.begin(9600);
}

//temporary string that is the incoming bytes
String incString="";
char incBuf[2] = {};

//complete packet that is to be processed
String incomingPacket="";
unsigned char PACKET_END_CHAR = 0x03;

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
    if (incomingPacket== "SAY_HI")
    {
      Serial.write("HI!");
    }
    //Clear incoming packet
    incomingPacket ="";
  }
}





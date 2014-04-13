#include <SoftwareSerial.h>
#include <VirtualWire.h>
char *controller;

int ROOMBArxPin = 3;
int ROOMBAtxPin = 4;
SoftwareSerial Roomba(ROOMBArxPin,ROOMBAtxPin);

void setup() 
{
  Roomba.begin(115200);
  
  //receive
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_set_rx_pin(12);
    vw_setup(4000);  // Bits per sec
    pinMode(13, OUTPUT);

    vw_rx_start();       // Start the receiver PLL running
}

void loop() { 
  //if (vw_have_message())
  //{

    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
       digitalWrite(13,1);
       Roomba.write((uint8_t)buf[0]);
    }
  //}

  delay(500);
}

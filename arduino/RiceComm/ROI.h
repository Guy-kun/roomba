// ROI commands
 
int rxPin = 3;
int txPin = 4;
 
SoftwareSerial Roomba(rxPin,txPin);

void start() 
{
  Roomba.write(128);
}

void safe() 
{
  Roomba.write(131);
}

void full() 
{
  Roomba.write(132);
}

void clean() 
{
  Roomba.write(135);
}

void max() 
{
  Roomba.write(136);
}

void spot() 
{
  Roomba.write(134);
}

void dock() 
{
  Roomba.write(143);
}

void power() 
{
  Roomba.write(133);
}
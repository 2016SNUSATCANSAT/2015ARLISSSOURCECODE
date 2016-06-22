//MAX-6Q I2C cpp file
//2015.07.14 

#include "Arduino.h"
#include "MAX.h"
MAX::MAX()
{
  count = 0;
  latitude = 0;
  longitude = 0;
  height = 0;
  sLatitude = "0";
  sLongitude = "0";
  sHeight = "0";
  count = 0;
  deltaH = 1000;
  GPSBuf = "";
  GPSPhr = "";
}

void MAX::MAXstart()
{
  Wire.begin();
  delay(250);
}

int MAX::renew()
{

  BufIn(GPSBuf);
  int i = getPhrase(GPSBuf, GPSPhr);
  if(i == 1) return 0;  //not renewed 
  else{
    String tempLat = getLat(GPSPhr);
    String tempLng = getLong(GPSPhr);
    String temphgt = getHigh(GPSPhr);

    int a = spellCheck(tempLat);
    int b = spellCheck(tempLng);
    int c = spellCheck(temphgt);

    if(a == 0) {sLatitude = tempLat;}
    if(b == 0) sLongitude = tempLng;
    if(c == 0) sHeight = temphgt;
    int r = StoF();
    
    if(r==0){
      count ++;
      return 1;
    }
    else if(r==-1) {return 0;}
  }
}

double MAX::getLat(){return latitude;}
double MAX::getLng(){return longitude;}
double MAX::getHgt(){return height;}
double MAX::getDeltaH(){return deltaH;}

String MAX::getSLat(){return sLatitude;}
String MAX::getSLng(){return sLongitude;}
String MAX::getSHgt(){return sHeight;}



void MAX::BufIn(String & buf){  // Get GPS data from GPS module and store the data into GPSBuf
 // buf = "";
  byte1 = 0;
  byte2 = 0;
  while(byte1+byte2 <= 0)
  {
    writeRegister8(0xFD);
    readRegister8();
    delay(250);
  }
  
    int i = 0;
    Wire.beginTransmission(ADDRESS); 
    while(i<byte1+byte2)
    {
      buf += charreadRegister8();
      i++;
    }
    Wire.endTransmission();
   // Serial.println("_____________");
   //Serial.println(buf);
  //  Serial.println("_____________");
 
}

int MAX::getPhrase(String & momBuf, String & sonBuf){ //Get the phrase that includes longitude and latitude data.
  String AddrIndex = "$GPGGA";
  char EndIndex = '*';
  char Index = '\n';
  int i = 0;
  int j = 0;
  int e = 0;// error check
  int k = 0;

  i = momBuf.indexOf(AddrIndex);
 
  j = momBuf.indexOf(EndIndex, i+1);  
 
  if(i == -1)
  {
    e = 1;
    momBuf = "";
    return e; 
  }
  else if(j == -1)
  {
    e = 1;
    return e;
  }
  else
  {
    sonBuf = momBuf.substring(i,j);
    k = sonBuf.indexOf(Index);
    if(k != -1)
    {
      sonBuf= momBuf.substring(i,k) + momBuf.substring(k+1,j);
    }
    i = momBuf.indexOf(AddrIndex, j+1);
    if(i == -1)
    {
      momBuf = "";
    }
    else
    {
      momBuf = momBuf.substring(i);
    }
  }
  //Serial.println(sonBuf);
  return e;
}

String MAX::getLat(String Buf){
  char comma = ',';
  String temp;
  int i = 0;
  int j = 0;
  i = Buf.indexOf(comma);
  i = Buf.indexOf(comma,i+1);
  j = Buf.indexOf(comma,i+1);
  if(i + 1 == j)  return "0";
  else{
    temp = Buf.substring(i+1,j);
    return temp;
  }
}

String MAX::getLong(String Buf){
  char comma = ',';
  String temp;
  int i = 0;
  int j = 0;
  i = Buf.indexOf(comma);
  i = Buf.indexOf(comma,i+1);
  i = Buf.indexOf(comma,i+1);
  i = Buf.indexOf(comma,i+1);
  j = Buf.indexOf(comma,i+1);
  if(i + 1 == j)  return "0";
  else{
    temp = Buf.substring(i+1,j);
    return temp;
  }
}

String MAX::getHigh(String Buf){
  char comma = ',';
  String temp;
  int i = 0;
  int j = 0;
  i = Buf.indexOf(comma);
  i = Buf.indexOf(comma,i+1);
  i = Buf.indexOf(comma,i+1);
  i = Buf.indexOf(comma,i+1);
  i = Buf.indexOf(comma,i+1);
  i = Buf.indexOf(comma,i+1);
  i = Buf.indexOf(comma,i+1);
  i = Buf.indexOf(comma,i+1);
  i = Buf.indexOf(comma,i+1);
  j = Buf.indexOf(comma,i+1);
  if(i + 1 == j)  return "0";
  else{
    temp = Buf.substring(i+1,j);
    return temp;
  }
}

int MAX::StoF(){
  char buf0[sLatitude.length()];
  char buf1[sLongitude.length()];
  char buf2[sHeight.length()];
  float temp;
  float htemp;

  if(sLatitude.length() != 0)
  {
    sLatitude.toCharArray(buf0,sLatitude.length());
    temp = atof(buf0);
    if(temp != 0.0) {latitude = temp;}

    sLongitude.toCharArray(buf1,sLongitude.length());
    temp = atof(buf1);
   
    if(temp != 0.0) {longitude = temp;}

    sHeight.toCharArray(buf2,sHeight.length());
    htemp = height;
    temp = atof(buf2);
    if(temp != 0.0) {
      height = temp;
      deltaH = height - htemp;

    }
    

    return 0;
  }
  else{
    latitude = 0;
    longitude = 0;
    height = 0;

    return -1;
  }
}

int MAX::spellCheck(String Buf){

  int n = Buf.length();
  int i = 0;
  char c;

  while(i<n){
    c = Buf.charAt(i);
    if((c < '0' || c > '9') && c!='.'){return -1;}
    i++;
  }
  return 0;
}

void MAX::writeRegister8(uint8_t Reg)
{
   Wire.beginTransmission(ADDRESS);
   
   #if ARDUINO >= 100
      Wire.write(Reg);
   #else
      Wire.send(Reg);
   #endif

   Wire.endTransmission(false);
} 

void MAX::readRegister8()
{

   Wire.beginTransmission(ADDRESS);
   Wire.requestFrom(ADDRESS, 1);
   if(Wire.available() == false){ 
     // Serial.println("error : no byte");
   }

   #if ARDUINO >= 100
      byte1 = Wire.read();

   #else
      byte1 = Wire.receive();
   #endif
  
   Wire.requestFrom(ADDRESS, 1);
   if(Wire.available() == false){ 
     //Serial.println("error : no byte");
   }

   #if ARDUINO >= 100
      byte2 = Wire.read();

   #else
      byte2 = Wire.receive();
   #endif

   Wire.endTransmission();

}

char MAX::charreadRegister8()
{
  char c;
  Wire.requestFrom(ADDRESS, 1);
  if(Wire.available() == false){ 
   // Serial.println("error : no data");
  }

  #if ARDUINO >= 100
     c = Wire.read();

  #else
     c = Wire.receive();
  #endif
   
  return c;
}

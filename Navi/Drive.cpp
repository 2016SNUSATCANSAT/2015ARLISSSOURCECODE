//Drive cpp file
//2015.06.26
//Kim Ju Hyeon
//2015.07.02 --> add getDrive()
//2015.07.10 --> delete println

#include "Arduino.h"
#include "Drive.h"
//#include "math.h"
#include "IMU.h"
#include <Wire.h>

Drive::Drive(){
  drive = 0;
  myLat = 0;
  myLng = 0;
  desLat = 0;
  desLng = 0;
  yaw = 0;
  angV = 0;
	goalLat = 0;
	goalLng = 0;
}

void Drive::RunR(double Vel){
   if(Vel < 0){
      escR.write(map(Vel, 0, -1000, 92, 25));
   }
   else{
      escR.write(map(Vel, 0, 1000, 92, 156));
   }
   /*if (countR >= 10){
	   Serial.print("RVelocity = ");
     Serial.println(Vel);
	   countR = 0;
   }
   delay(10);*/
}

void Drive::RunL(double Vel){
	if (Vel < 0){
		escL.write(map(Vel, 0, -1000, 92, 25));
	}
	else{
		escL.write(map(Vel, 0, 1000, 92, 156));
	}
	/*if (countL >= 10){
	  Serial.print("LVelocity = ");
		Serial.println(Vel);
		countL = 0;
	}
	delay(10);*/
}

void Drive::update(double Lat, double Lng, double y, double aV){
  myLat = Lat;
  myLng = Lng;
  yaw = y;
  angV = aV;
}

void Drive::setDrive(int Status){
  drive = Status;
}

int Drive::getDrive() {return drive;}

void Drive::initiate(double Lat, double Lng){
  //Serial.println("Motor Initiating");
  escR.attach(RightMotor);
  escL.attach(LeftMotor);
  delay(4000);
  //Serial.println("Ready to Drive");
  goalLat = Lat;
  goalLng = Lng;
  //Serial.print("Destination Lat = ");
  //Serial.println(goalLat);
  //Serial.print("            Lng = ");
  //Serial.println(goalLng);
}

void Drive::stop(){
  RunR(0);
  RunL(0);
}

void Drive::gotoGoal(){
  double vel;
  double str;
  vel = Velcoeff*sqrt((((myLat-goalLat)*1000000)*((myLat-goalLat)*1000000))+(((myLng-goalLng)*1000000)*((myLng-goalLng)*1000000)));
  str = Strcoeff1*calSteer(myLat, myLng, goalLat, goalLng, yaw) + Strcoeff2*angV;
  if(str > Maxstr){
    str = Maxstr;
  }
  else if(str < -Maxstr){
    str = -Maxstr;
  }
  if(vel > Maxvel){
    vel = Maxvel;
  }
  else if(vel < -Maxvel){
    vel = -Maxvel;
  }
  RunR(vel - str);
  RunL(vel + str);
}

void Drive::gotoDes(){
	double vel;
  double str;
  vel = Velcoeff*sqrt((((myLat-desLat)*1000000)*((myLat-desLat)*1000000))+(((myLng-desLng)*1000000)*((myLng-desLng)*1000000)));
  str = Strcoeff1*calSteer(myLat, myLng, desLat, desLng, yaw) + Strcoeff2*angV;
  if(str > Maxstr){
    str = Maxstr;
  }
  else if(str < -Maxstr){
    str = -Maxstr;
  }
  if(vel > Maxvel){
    vel = Maxvel;
  }
  else if(vel < -Maxvel){
    vel = -Maxvel;
  }
  RunR(vel - str);
  RunL(vel + str);
        /*double myLngdeg = transDeg(myLng);
        double myLatdeg = transDeg(myLat);
        double goalLngdeg = transDeg(goalLng);
        double goalLatdeg = transDeg(goalLat);
	double A = (PI/180)*abs(myLngdeg - goalLngdeg);
//Serial.println(A*180/PI);
	double b = (PI/180)*abs(90 - myLatdeg);
//Serial.println(b*180/PI);
	double c = (PI/180)*abs(90 - goalLatdeg);
//Serial.println(c*180/PI);
        double Distance = 64000*acos(cos(b)*cos(c) + sin(b)*sin(c)*cos(A));
        //Serial.print("Distance = ");
        //Serial.print(Distance, 6);
        //Serial.println("m");
	vel = 50000*acos(cos(b)*cos(c) + sin(b)*sin(c)*cos(A));
*/
  //drive = 0(Stop), drive = 1(go to goal point), drive = 2(go to a point)
}

void Drive::escape(){
  RunR(-1000);
  RunL(-1000);
  delay(3000);
  RunR(1000);
  RunL(1000);
  delay(10000);
  RunR(-1000);
  RunL(-1000);
  delay(3000);
  RunR(1000);
  RunL(-1000);
  delay(1000);
  RunR(1000);
  RunL(1000);
  delay(2000);
  RunR(-1000);
  RunL(1000);
  delay(1000);
  RunR(1000);
  RunL(1000);
  delay(5000);
  RunR(0);
  RunL(0);
}

void Drive::setDes(double Lat, double Lng){
  desLat = Lat;
  desLng = Lng;
}

float Drive::transDeg(double Ang){
  float Deg;
  float D;
  float M;
  float S;
  D = float(int(Ang / 100));
  M = (float(int(Ang) % 100))/60.0;
  S = (float(long(Ang*100) % 100))/3600.0;
  Deg = D + M + S;
  return Deg;
}
//Ang = DDMM.SSSSSS

float Drive::calSteer(double myLat, double myLng, double goLat, double goLng, double Y){
  float Target = 0;
  Target = atan((goLng - myLng)/(goLat - myLat));
  if(goLat < myLat){
    if(goLng < myLng){
      Target = Target - PI;
    }
    else{
      Target = Target + PI;
    }
  }
  float Yaw;
  if(Y > 180){
    Yaw = Y - 360;
  }
  else Yaw = Y;
  float Steer = 0;
  Steer = (Target*180/PI) - Yaw; //If Steer is (+), turn right. in degree
  //Serial.print("Target = ");
  //Serial.println(Target, 6);
  //Serial.print("Steer = ");
  //Serial.println(Steer, 6);
  return Steer;  
}

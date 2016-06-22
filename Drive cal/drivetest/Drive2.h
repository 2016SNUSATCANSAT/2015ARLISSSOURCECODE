//2015 ARLISS
//Rover Drive
//2015.06.26
//2015.07.02 --> add getDrive()
//2015.07.10 --> delete println
//2015.08.26 --> drive cal test

#ifndef Drive2_h
#define Drive2_h

#include "Arduino.h"
#include <Servo.h>

#define RightMotor 6
#define LeftMotor 5
//#define Velcoeff 0.0075
//#define Strcoeff1 1.0
//#define Strcoeff2 0.5
//#define Maxvel 900
//#define Maxstr 100

class Drive{
public:
    Drive();
    void update(double myLat, double myLng, double yaw, double angV);
    void gotoDes();
    void gotoGoal();
    void stop();
    void initiate(double goalLat, double goalLng);
    void setDrive(int Status);
    int getDrive();
    void setDes(double desLat, double desLng);
    void escape();
    void setvalue(double velcoeff, double strcoeff1, double strcoeff2, double maxvel, double maxstr);


private:
    int drive;
    double myLat;
    double myLng;
    double desLat;
    double desLng;
    double yaw;
    double angV;
    double goalLat;
    double goalLng;
    void RunR(double Vel);
    void RunL(double Vel);
    float transDeg(double Ang);
    float calSteer(double myLat, double myLng, double desLat, double desLng, double Yaw);
    int countR;
    int countL;
    Servo escR;
    Servo escL;
    double Velcoeff;
    double Strcoeff1;
    double Strcoeff2;
    double Maxvel;
    double Maxstr;
};
#endif

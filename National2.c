#pragma config(Sensor, S1,     DIMC,           sensorEV3_GenericI2C)
#pragma config(Sensor, S2,     ,               sensorEV3_GenericI2C)
#pragma config(Sensor, S3,     inf1d,          sensorEV3_GenericI2C)
#pragma config(Sensor, S4,     inf2d,          sensorEV3_GenericI2C)
#pragma config(Motor,  motorA,          FR,            tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorB,          BR,            tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorC,          BL,            tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorD,          FL,            tmotorEV3_Medium, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


#include "mindsensors-ev3smux.h"
#include "hitechnic-irseeker-v2.h"

tMSEV3 muxedSensor[3];
tEV3SensorTypeMode typeMode[3] = {colorReflectedLight, colorReflectedLight, colorReflectedLight};

int goalRange = 6;
int goalDirection = SensorValue[S1];
int goalMax = goalDirection + goalRange;
int goalMin = goalDirection - goalRange;
int goalLogic;
int motorShootSpeed = 100;
int motorOrbitSpeed = 80;
int motorAimSpeed = 40;
int motorCompassSpeed = 30;
int inferredFrontDirection,inferredBackDirection,inferredFrontRange,inferredBackRange;
bool compassTrigger = true;
float mux[3];

void Mstop()   {motor[FR] = 0;  			motor[BR] = 0;  				motor[BL] = 0;  				motor[FL] = 0;}
void Mforward(){motor[FR] = motorShootSpeed;motor[BR] = motorShootSpeed; 	motor[BL] = -motorShootSpeed;	motor[FL] = -motorOrbitSpeed;}
void Mright()  {motor[FR] = -motorOrbitSpeed;	motor[BR] = motorOrbitSpeed; 		motor[BL] = motorOrbitSpeed; 		motor[FL] = -motorOrbitSpeed;}
void Mmright() {motor[FR] = -motorCompassSpeed;		motor[BR] = motorAimSpeed; 			motor[BL] = motorAimSpeed; 			motor[FL] = -motorAimSpeed;}
void Mleft()   {motor[FR] = motorOrbitSpeed; 	motor[BR] = -motorOrbitSpeed;		motor[BL] = -motorOrbitSpeed;		motor[FL] = motorOrbitSpeed;}
void Mmleft()  {motor[FR] = motorAimSpeed; 		motor[BR] = -motorAimSpeed;			motor[BL] = -motorAimSpeed;			motor[FL] = motorAimSpeed;}
void Mback()   {motor[FR] = -motorOrbitSpeed;	motor[BR] = -motorOrbitSpeed;		motor[BL] = motorOrbitSpeed; 		motor[FL] = motorOrbitSpeed;}
void Tleft()   {motor[FR] = motorCompassSpeed; 		motor[BR] = motorCompassSpeed; 			motor[BL] = motorCompassSpeed; 			motor[FL] = motorCompassSpeed;}
void Tright()  {motor[FR] = -motorCompassSpeed;		motor[BR] = -motorCompassSpeed;			motor[BL] = -motorCompassSpeed;			motor[FL] = -motorCompassSpeed;}

void outliner()
{
	for (int i = 0; i < 3; i++)
	{
		if (!readSensor(&muxedSensor[i]))
			writeDebugStreamLine("readSensor() failed! for %d", i);

		switch(muxedSensor[i].typeMode)
		{
		case colorReflectedLight:
			/*displayTextLine(i*3, "Chan[%d]: Ref Light", i+1);
			displayTextLine(i*3 + 1, "Value: %d", muxedSensor[i].light);*/
			mux[i] = muxedSensor[i].light;
			break;
		}
	}
	if(inferredFrontDirection==0&&inferredBackDirection==0&&compassTrigger==true){
		Mstop();
	}
	if(mux[0]>10&&mux[2]>10){
		Mback();
		sleep(2500);
	}
	else if(mux[0]>10){
		Mright();
		sleep(200);
	}
	else if(mux[1]>10){
		Mforward();
		sleep(200);
	}
	else if(mux[2]>10){
		Mleft();
		sleep(200);
	}
}

void compass()
{
	tHTIRS2 irSeeker1;
	tHTIRS2 irSeeker2;
	initSensor(&irSeeker1, inf1d);
	initSensor(&irSeeker2, inf2d);
	readSensor(&irSeeker1);
	readSensor(&irSeeker2);
	goalDirection = SensorValue[S1];
	inferredFrontDirection = irSeeker1.acDirection;
	inferredBackDirection = irSeeker2.acDirection;
	inferredFrontRange = irSeeker1.enhStrength;
	inferredBackRange = irSeeker2.enhStrength;
}



void logic()
{
	outliner();
	compass();
}

task main()
{
	if(goalDirection <=90){
		goalLogic = 1;
		} else{
		goalLogic = 2;
	}
	while(1){
		logic();
	}
}

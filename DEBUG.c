#pragma config(Sensor, S1,     DIMC,           sensorEV3_GenericI2C)
#pragma config(Sensor, S2,     ,               sensorEV3_GenericI2C)
#pragma config(Sensor, S3,     inf1d,          sensorEV3_GenericI2C)
#pragma config(Sensor, S4,     inf2d,          sensorEV3_GenericI2C)
#pragma config(Motor,  motorA,          FL,            tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorB,          FR,            tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorC,          BR,            tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorD,          BL,            tmotorEV3_Medium, PIDControl, encoder)

#include "mindsensors-ev3smux.h"
#include "hitechnic-irseeker-v2.h"

int goalcomp; //Goal Direction
int Sorbit = 50; //Orbit Speed
int Saim = 30; //Aiming speed
int range = 5; //Radius of Accuracy (The lower the better accuarcy)
int Sshooting = 100; //Shooting Speed
int comp,inf1,inf1s,inf2,inf2s;
double mux[3];

tMSEV3 muxedSensor[3];
tEV3SensorTypeMode typeMode[3] = {colorReflectedLight, colorReflectedLight, colorReflectedLight};

task main()
{
	if (!initSensor(&muxedSensor[0], msensor_S2_1, typeMode[0]))
		writeDebugStreamLine("initSensor() failed! for msensor_S2_1");

	if (!initSensor(&muxedSensor[1], msensor_S2_2, typeMode[1]))
		writeDebugStreamLine("initSensor() failed! for msensor_S2_2");

	if (!initSensor(&muxedSensor[2], msensor_S2_3, typeMode[2]))
		writeDebugStreamLine("initSensor() failed! for msensor_S2_3");

	tHTIRS2 irSeeker1;
	tHTIRS2 irSeeker2;

  initSensor(&irSeeker1, inf1d);
	initSensor(&irSeeker2, inf2d);
	comp = SensorValue[S1];
	goalcomp = comp;

  while(true)
  {
    readSensor(&irSeeker1);
		readSensor(&irSeeker2);
		comp = SensorValue[S1];
		inf1 = irSeeker1.acDirection;
		inf2 = irSeeker2.acDirection;
		inf1s = irSeeker1.enhStrength;
		inf2s = irSeeker2.enhStrength;

    for (int i = 0; i < 3; i++)
		{
			if (!readSensor(&muxedSensor[i]))
				writeDebugStreamLine("readSensor() failed! for %d", i);

			switch(muxedSensor[i].typeMode)
			{
			case colorReflectedLight:
				//displayTextLine(i*3, "Chan[%d]: Ref Light", i+1);
				//displayTextLine(i*3 + 1, "Value: %d", muxedSensor[i].light);
				mux[i] = muxedSensor[i].light;
				break;
			}
		}

		displayTextLine(1, "Value: %d", mux[0]);
		displayTextLine(4, "Value: %d", mux[1]);
		displayTextLine(7, "Value: %d", mux[2]);

		displayTextLine(10,"Inf1: %i",inf1);
		displayTextLine(11,"Inf1s: %i",inf1s);
		displayTextLine(12,"Inf2: %i",inf2);
		displayTextLine(13,"Inf2s: %i",inf2s);
		displayTextLine(14,"Comp: %i",comp);
  }
}

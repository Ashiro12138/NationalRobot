#pragma config(Sensor, S1,     DIMC,           sensorEV3_GenericI2C)
#pragma config(Motor,  motorA,          FL,            tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorB,          FR,            tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorC,          BR,            tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorD,          BL,            tmotorEV3_Medium, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int inf1;
int inf2;

task main()
{
	while(true)
	{
		inf1 = SensorValue[S3];
		inf2 = SensorValue[S4];
		if(inf1==0)
		{
			if(inf2>5)
			{
				motor[FL] = 100;
				motor[FR] = 100;
				motor[BR] = 100;
				motor[BL] = 100;
			}
			if(inf2<6)
			{
				motor[FL] = -100;
				motor[FR] = -100;
				motor[BR] = -100;
				motor[BL] = -100;
			}
		}
		if(inf1<=9&&inf1>5)
		{
			motor[FL] = -100;
			motor[FR] = -100;
			motor[BR] = -100;
			motor[BL] = -100;
		}
		if(inf1>0&&inf1<5)
		{
			motor[FL] = 100;
			motor[FR] = 100;
			motor[BR] = 100;
			motor[BL] = 100;
		}
		if(inf1==5)
		{
			motor[FL] = 50;
			motor[FR] = 50;
			motor[BR] = -50;
			motor[BL] = -50;
		}
	}
}
#pragma config(Sensor, S1,     DIMC,           sensorEV3_GenericI2C)
#pragma config(Sensor, S2,     ,               sensorEV3_GenericI2C)
#pragma config(Sensor, S3,     inf1d,          sensorEV3_GenericI2C)
#pragma config(Sensor, S4,     inf2d,          sensorEV3_GenericI2C)
#pragma config(Motor,  motorA,          FL,            tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorB,          FR,            tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorC,          BR,            tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorD,          BL,            tmotorEV3_Medium, PIDControl, encoder)

task main()
{
	while(true){
		motor[FL] = 50;
		motor[FR] = 50;
		motor[BR] = -50;
		motor[BL] = -50;
	}
}

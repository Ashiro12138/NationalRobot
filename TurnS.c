#pragma config(Motor,  motorA,          FR,            tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorB,          BR,            tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorC,          BL,            tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorD,          FL,            tmotorEV3_Medium, PIDControl, encoder)
/*
//forward
motor[FR] = 50;
motor[BR] = 50;
motor[BL] = -50;
motor[FL] = -50;
//left
motor[FR] = 50;
motor[BR] = -50;
motor[BL] = -50;
motor[FL] = 50;
//backward
motor[FR] = -50;
motor[BR] = -50;=
motor[BL] = 50;
motor[FL] = 50;
//right
motor[FR] = -50;
motor[BR] = 50;
motor[BL] = 50;
motor[FL] = -50;
*/

void absolute(int a,int b,int c,int d){
	motor[FR] = a;
	motor[BR] = b;
	motor[BL] = c;
	motor[FL] = d;
}

void relative(int a,int b,int c,int d){
	motor[FR] += a;
	motor[BR] += b;
	motor[BL] += c;
	motor[FL] += d;
}

void motors(){
	writeDebugStreamLine("%d,%d,%d,%d",motor[FR],motor[BR],motor[BL],motor[FL]);
}

task main()
{
	clearDebugStream();
	absolute(20,20,-30,-30);
	for(int i=0;i<20;i++){
		relative(1,-1,-1,1)
		motors();
		sleep(50);
	}
}

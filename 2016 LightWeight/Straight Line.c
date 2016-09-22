#pragma config(Motor,  motorA,          FL,            tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorB,          FR,            tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorC,          BR,            tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorD,          BL,            tmotorEV3_Medium, PIDControl, encoder)

task main()
{
	while(true){
		motor[FL] = -100;
		motor[FR] = 100;
		motor[BR] = 100;
		motor[BL] = -100;
	}
}

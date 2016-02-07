/*
 * ExampleCommand.h
 *
 */

#ifndef SMINGCORE_EXAMPLE_COMMAND_H_
#define SMINGCORE_EXAMPLE_COMMAND_H_

#include <SmingCore.h>
#include "WString.h"
#include "../Services/CommandProcessing/CommandProcessingIncludes.h"

//https://www.gitbook.com/book/smartarduino/user-mannual-for-esp-12e-motor-shield/details

//Direcrtion
#define FW 0
#define BK 1
#define STOP 2
//#define FW_NEUTRAL 3

//Turn
#define TL 4
#define TR 5
#define STRAIGHT 6

//Motor movements
#define MOTOR_FW 1
#define MOTOR_BK 0

typedef Delegate<void()> carMotorDelegate;

class CarCommand
{
public:
	CarCommand(int leftMotorPWM, int rightMotorPWM, int leftMotorDir, int rightMotorDir);
	virtual ~CarCommand();
	void initCommand();

private:

	int lastY = 0;
	int currentX = 0;

	// Direction
	int dir=FW;

	// Turn Status
	int t = 0;
	int tdir = STRAIGHT;
	int tcount = 0;

//	int x = 0; //X movement percent
//	int y = 0; // Y movement percent

//	bool stopped = true;

	int leftMotorPWM;
	int rightMotorPWM;
	int leftMotorDir;
	int rightMotorDir;
	int duration = 200;

	//--target Speed
	int spdTargetLeft=1023;

	//--current speed
	int spdCurrentLeft=0;

	//--target Speed
	int spdTargetRight = 1023;
	//--current speed
	int spdCurrentRight = 0;

	long lastActionTime;
	Timer motorTimer;

	DriverPWM pwmMotors;

	int i = 0;
	bool countUp = true;
	bool countDown = false;

	void processCarCommands(String commandLine, CommandOutput* commandOutput);
	void handleMotorTimer();
	void drive(int leftDir, int leftPwm, int rightDir, int rightPwm);

	int switchDir(int state);
	void doPWM();
};


#endif /* SMINGCORE_DEBUG_H_ */

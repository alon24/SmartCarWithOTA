/*
 * ExampleCommand.h
 *
 */

#ifndef SMINGCORE_EXAMPLE_COMMAND_H_
#define SMINGCORE_EXAMPLE_COMMAND_H_

#include "SmingCore.h"
#include <libraries/Ultrasonic/Ultrasonic.h>

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

#define headLights 12
#define ULTRASONIC_TRIG_PIN 4
#define ULTRASONIC_ECHO_PIN 5

typedef Delegate<void()> carMotorDelegate;

struct CarParamaters {
	int freq = 30;
	bool useSteeringMotor = false;
};

class CarCommand
{
public:
	CarParamaters carParams;

	CarCommand(int leftMotorPWM, int rightMotorPWM, int leftMotorDir, int rightMotorDir);
	virtual ~CarCommand();
	void initCommand();
private:
	Ultrasonic ultrasonic = Ultrasonic();

	int lastY = 0;
	int lastX = 0;
	int currentX = 0;

	// Direction
	int dir=FW;

	// Turn Status
	int t = 0;
	int tdir = STRAIGHT;
	int tcount = 0;

	uint8 leftMotorPWM;
	uint8 rightMotorPWM;
	int leftMotorDir;
	int rightMotorDir;

	long lastActionTime;
	Timer motorTimer;
	HardwarePWM *pwmMotors;

	int i = 0;
	bool countUp = true;
	bool countDown = false;
	int minPower = 1;

//	int pwmWorkingFreq = 30;

	void processCarCommands(String commandLine, CommandOutput* commandOutput);
	void handleMotorTimer();
	void drive(int leftDir, int leftPwm, int rightDir, int rightPwm);

	void testPWM();
	void handleFixedXy(int x, int y);
	void handleJoystickXY(int x, int y);
	void handleUseSteeringMotor(int x, int y);
	void handleNotUseSteeringMotor(int x, int y);
	void handleCheckFreq(int pin, int freq, int pwr);
	int getCurrentFreq();
	void setFreq(int freq);
	void tuneCarParamaters(int freq, bool useSteering);
	void measure();
};


#endif /* SMINGCORE_DEBUG_H_ */

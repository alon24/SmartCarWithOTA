/*
 * ExampleCommand.h
 *
 */

#ifndef SMINGCORE_EXAMPLE_COMMAND_H_
#define SMINGCORE_EXAMPLE_COMMAND_H_

#include <SmingCore/SmingCore.h>
#include "WString.h"
#include "../Services/CommandProcessing/CommandProcessingIncludes.h"

//https://www.gitbook.com/book/smartarduino/user-mannual-for-esp-12e-motor-shield/details

typedef Delegate<void()> carMotorDelegate;

class CarCommand
{
public:
	CarCommand(int pwmA, int pwmB, int dirA, int dirB);
	virtual ~CarCommand();
	void initCommand();

private:
	int pwmA;
	int pwmB;
	int dirA;
	int dirB;

	//--target Speed
	int spdTargetA=1023;

	//--current speed
	int spdCurrentA=0;

	//--target Speed
	int spdTargetB = 1023;

	//--current speed
	int spdCurrentB = 0;

	bool stopFlag =true;

	DriverPWM motoAPWM;
	DriverPWM motoBPWM;
	Timer motorTimer;

	void processCarCommands(String commandLine, CommandOutput* commandOutput);
	void doAPWM();
	void doBPWM();

	void handleMotorTimer();
};


#endif /* SMINGCORE_DEBUG_H_ */

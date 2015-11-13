/*
 * Debug.cpp
 *
 */

#include <CarCommand.h>

CarCommand::CarCommand(int pwmA, int pwmB, int dirA, int dirB)
{
	this->pwmA = pwmA;
	this->pwmB = pwmB;
	this->dirA = dirA;
	this->dirB = dirB;

//	pinMode(pwmA, OUTPUT);
//	pinMode(pwmB, OUTPUT);

	pinMode(dirA, OUTPUT);
	digitalWrite(dirA, LOW);
	pinMode(dirB, OUTPUT);
	digitalWrite(dirB, LOW);

	motoAPWM.initialize();
	motoBPWM.initialize();
	motorTimer.setCallback(carMotorDelegate(&CarCommand::handleMotorTimer, this));

	debugf("CarCommand Instantiating");
}

CarCommand::~CarCommand()
{
}

void CarCommand::initCommand()
{
	commandHandler.registerCommand(CommandDelegate("Move","Example Command from Class","Application",commandFunctionDelegate(&CarCommand::processCarCommands,this)));
}

void CarCommand::processCarCommands(String commandLine, CommandOutput* commandOutput)
{
	Vector<String> commandToken;
	int numToken = splitString(commandLine, ' ' , commandToken);

	if (numToken == 1)
	{
		commandOutput->printf("Move Commands available : \r\n");
		commandOutput->printf("faster   : Set example status ON\r\n");
		commandOutput->printf("slower  : Set example status OFF\r\n");
		commandOutput->printf("up : Show example status\r\n");
		commandOutput->printf("down : Show example status\r\n");
		commandOutput->printf("left : Show example status\r\n");
		commandOutput->printf("right : Show example status\r\n");
		commandOutput->printf("stop : Show example status\r\n");
	}
	else
	{
		if (commandToken[1] == "faster")
		{
			commandOutput->printf("faster\r\n");
		}
		else if (commandToken[1] == "slower") {
			commandOutput->printf("slower\r\n");
		}
		else if (commandToken[1] == "up") {
			commandOutput->printf("up\r\n");
		}
		else if (commandToken[1] == "down") {
			commandOutput->printf("down\r\n");
		}
		else if (commandToken[1] == "left") {
			commandOutput->printf("lwft\r\n");
		}
		else if (commandToken[1] == "right") {
			commandOutput->printf("right\r\n");
		}
		else if (commandToken[1] == "stop") {
			commandOutput->printf("stop\r\n");
		};

	}
}

void CarCommand::handleMotorTimer() {

};


//
//int i = 0;
//bool countUp = true;
//bool countDown = false;

void CarCommand::doAPWM()
{
//	if(countUp){
//		i++;
//		if(i == 100){
//			countUp = false;
//			countDown = true;
//		}
//	}
//	else{
//		i--;
//		if(i == 0){
//			countUp = true;
//			countDown = false;
//		}
//	}
//	Serial.println(i);
//	ledPWM.analogWrite(LED_PIN, i);
}

void CarCommand::doBPWM() {

};



/*
 * Debug.cpp
 *
 */

#include <CarCommand.h>

/*
 * dirA = leftMotorDir
 * dirB = rightMotorDir
 * pwmA = leftMotorPWM
 * pwmB = rightMotorPWM
 */

CarCommand::CarCommand(int leftMotorPWM, int rightMotorPWM, int leftMotorDir, int rightMotorDir)
{
	this->leftMotorPWM = leftMotorPWM;
	this->rightMotorPWM = rightMotorPWM;
	this->leftMotorDir = leftMotorDir;
	this->rightMotorDir = rightMotorDir;

//	pinMode(pwmA, OUTPUT);
//	pinMode(pwmB, OUTPUT);

	pinMode(leftMotorDir, OUTPUT);
	digitalWrite(leftMotorDir, LOW);
	pinMode(rightMotorDir, OUTPUT);
	digitalWrite(rightMotorDir, LOW);

	pinMode(leftMotorPWM, OUTPUT);
	pinMode(rightMotorPWM, OUTPUT);
	digitalWrite(leftMotorPWM, LOW);
	digitalWrite(rightMotorPWM, LOW);

//	motoAPWM.initialize();
//	motoBPWM.initialize();
	motorTimer.setCallback(carMotorDelegate(&CarCommand::handleMotorTimer, this));
	motorTimer.setIntervalMs(80);
	motorTimer.start(true);

	debugf("CarCommand Instantiating");
}

CarCommand::~CarCommand()
{
}

void CarCommand::initCommand()
{
	commandHandler.registerCommand(CommandDelegate("Move","Example Command from Class","Application",commandFunctionDelegate(&CarCommand::processCarCommands,this)));
//	motorTimer.initializeMs()
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
		commandOutput->printf("forward : Show example status\r\n");
		commandOutput->printf("back : Show example status\r\n");
		commandOutput->printf("left : Show example status\r\n");
		commandOutput->printf("right : Show example status\r\n");

		commandOutput->printf("ffLeft : Show example status\r\n");
		commandOutput->printf("ffRight : Show example status\r\n");
		commandOutput->printf("backRight : Show example status\r\n");
		commandOutput->printf("backLeft : Show example status\r\n");

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
		else if (commandToken[1] == "forward") {
			commandOutput->printf("forward\r\n");
			enableMovement(true);

//			digitalWrite(pwmA, LOW);
//			digitalWrite(pwmB, LOW);

			digitalWrite(leftMotorDir, LOW);
			digitalWrite(rightMotorDir, LOW);

//			digitalWrite(pwmA, HIGH);
//			digitalWrite(pwmB, HIGH);

			direction = FORWARD;
			lastActionTime = millis();
		}
		else if (commandToken[1] == "back") {
			commandOutput->printf("back\r\n");

//			digitalWrite(pwmA, LOW);
//			digitalWrite(pwmB, LOW);

			digitalWrite(leftMotorDir, HIGH);
			digitalWrite(rightMotorDir, HIGH);

//			digitalWrite(pwmA, HIGH);
//			digitalWrite(pwmB, HIGH);
			enableMovement(true);
			direction = BACK;
			lastActionTime = millis();
		}
		else if (commandToken[1] == "left") {
			commandOutput->printf("lwft\r\n");

			digitalWrite(leftMotorPWM, LOW);
//			digitalWrite(pwmB, LOW);

			digitalWrite(rightMotorDir, LOW);
//			digitalWrite(dirA, HIGH);

//			digitalWrite(pwmA, HIGH);
			digitalWrite(rightMotorPWM, HIGH);
//			enableMovement(true);
			lastActionTime = millis();
		}
		else if (commandToken[1] == "right") {
			commandOutput->printf("right\r\n");
//			digitalWrite(pwmA, LOW);
			digitalWrite(rightMotorPWM, LOW);

//			digitalWrite(dirB, HIGH);
			digitalWrite(leftMotorDir, LOW);

			digitalWrite(leftMotorPWM, HIGH);
//			digitalWrite(pwmB, HIGH);
//			enableMovement(true);
			lastActionTime = millis();
		}
		else if (commandToken[1] == "ffLeft") {
			commandOutput->printf("ffLeft\r\n");
//			digitalWrite(pwmA, LOW);
			digitalWrite(rightMotorPWM, LOW);

//			digitalWrite(dirB, HIGH);
			digitalWrite(leftMotorDir, LOW);

			digitalWrite(leftMotorPWM, HIGH);
//			digitalWrite(pwmB, HIGH);
//			enableMovement(true);
			lastActionTime = millis();
		} else if (commandToken[1] == "ffRight") {
			commandOutput->printf("ffRight\r\n");
			//			digitalWrite(pwmA, LOW);
			digitalWrite(rightMotorPWM, LOW);

			//			digitalWrite(dirB, HIGH);
			digitalWrite(leftMotorDir, LOW);

			digitalWrite(leftMotorPWM, HIGH);
			//			digitalWrite(pwmB, HIGH);
			//			enableMovement(true);
			lastActionTime = millis();
		} else if (commandToken[1] == "backLeft") {
			commandOutput->printf("backLeft\r\n");
			//			digitalWrite(pwmA, LOW);
			digitalWrite(rightMotorPWM, LOW);

			//			digitalWrite(dirB, HIGH);
			digitalWrite(leftMotorDir, LOW);

			digitalWrite(leftMotorPWM, HIGH);
			//			digitalWrite(pwmB, HIGH);
			//			enableMovement(true);
			lastActionTime = millis();
		} else if (commandToken[1] == "backRight") {
			commandOutput->printf("backRight\r\n");
			//			digitalWrite(pwmA, LOW);
			digitalWrite(rightMotorPWM, LOW);

			//			digitalWrite(dirB, HIGH);
			digitalWrite(leftMotorDir, LOW);

			digitalWrite(leftMotorPWM, HIGH);
			//			digitalWrite(pwmB, HIGH);
			//			enableMovement(true);
			lastActionTime = millis();
		}
		else if (commandToken[1] == "stop") {
			commandOutput->printf("stop\r\n");
			digitalWrite(leftMotorPWM, LOW);
			digitalWrite(rightMotorPWM, LOW);
			stopped = true;
		};

	}
}

void CarCommand::enableMovement(bool state) {
	if(state) {
		digitalWrite(leftMotorPWM, HIGH);
		digitalWrite(rightMotorPWM, HIGH);
		stopped = false;
	} else {
		digitalWrite(leftMotorPWM, LOW);
		digitalWrite(rightMotorPWM, LOW);
		stopped = true;
	}
}

void CarCommand::handleMotorTimer() {
//	if()
//	if(stopped) {
//		digitalWrite(pwmA, LOW);
//		digitalWrite(pwmB, LOW);
//	} else
//	{
//		digitalWrite(pwmA, HIGH);
//				digitalWrite(pwmB, HIGH);
//	}
};

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
	debugf("CarCommand Instantiating");

	pwmMotors.analogWrite(leftMotorPWM, 100);
	pwmMotors.analogWrite(rightMotorPWM, 100);
}

CarCommand::~CarCommand()
{
}

void CarCommand::initCommand()
{
	commandHandler.registerCommand(CommandDelegate("Move","Example Command from Class","Application",commandFunctionDelegate(&CarCommand::processCarCommands,this)));

	pinMode(leftMotorDir, OUTPUT);
	digitalWrite(leftMotorDir, HIGH);
	pinMode(rightMotorDir, OUTPUT);
	digitalWrite(rightMotorDir, HIGH);

	pinMode(leftMotorPWM, OUTPUT);
	pinMode(rightMotorPWM, OUTPUT);
	digitalWrite(leftMotorPWM, LOW);
	digitalWrite(rightMotorPWM, LOW);

	//Check and act upon car commands
	motorTimer.setCallback(carMotorDelegate(&CarCommand::handleMotorTimer, this));
	motorTimer.setIntervalMs(50);
	motorTimer.start(true);
}

void CarCommand::processCarCommands(String commandLine, CommandOutput* commandOutput)
{
	Vector<String> commandToken;
	int numToken = splitString(commandLine, ' ' , commandToken);

	debugf("Got commandLine = %s", commandLine.c_str());
	if (numToken == 1)
	{
		commandOutput->printf("Move Commands available : \r\n");
		commandOutput->printf("faster   : Set example status ON\r\n");
		commandOutput->printf("slower  : Set example status OFF\r\n");
		commandOutput->printf("forward : Show example status\r\n");
		commandOutput->printf("back : Show example status\r\n");
		commandOutput->printf("left : Show example status\r\n");
		commandOutput->printf("right : Show example status\r\n");

		commandOutput->printf("ffLeft : Move faster ff left\r\n");
		commandOutput->printf("ffRight : Move faster ff right\r\n");
		commandOutput->printf("backLeft : Move faster bk left\r\n");
		commandOutput->printf("backRight : Move faster bk lefts\r\n");

		commandOutput->printf("stop : Show example status\r\n");
		commandOutput->printf("x,y : Send X axis PWR, Y axis PWR (can be negative for reverse)\n");
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
//			enableMovement(true);
//
////			digitalWrite(pwmA, LOW);
////			digitalWrite(pwmB, LOW);
//
//			digitalWrite(leftMotorDir, LOW);
//			digitalWrite(rightMotorDir, LOW);
//
////			digitalWrite(pwmA, HIGH);
////			digitalWrite(pwmB, HIGH);

			dir = FW;
			tdir = STRAIGHT;
//			stopped = false;
			lastActionTime = millis();
		}
		else if (commandToken[1] == "back") {
			commandOutput->printf("back\r\n");
			dir = BK;
			tdir = STRAIGHT;
//			stopped = false;
			lastActionTime = millis();
		}
		else if (commandToken[1] == "left") {
			commandOutput->printf("left\r\n");
			dir = FW;
			tdir = TL;
			tcount = 0;
			lastActionTime = millis();
		}
		else if (commandToken[1] == "right") {
			commandOutput->printf("right\r\n");
			dir = FW;
			tdir =TR;
			tcount = 0;
			lastActionTime = millis();
		}
//		else if (commandToken[1] == "ffLeft") {
//			commandOutput->printf("ffLeft\r\n");
//			direction = LEFT;
//			lastActionTime = millis();
//		} else if (commandToken[1] == "ffRight") {
//			commandOutput->printf("ffRight\r\n");
////			//			digitalWrite(pwmA, LOW);
////			digitalWrite(rightMotorPWM, LOW);
////
////			//			digitalWrite(dirB, HIGH);
////			digitalWrite(leftMotorDir, LOW);
////
////			digitalWrite(leftMotorPWM, HIGH);
////			//			digitalWrite(pwmB, HIGH);
////			//			enableMovement(true);
////			lastActionTime = millis();
//		} else if (commandToken[1] == "backLeft") {
//			commandOutput->printf("backLeft\r\n");
////			//			digitalWrite(pwmA, LOW);
////			digitalWrite(rightMotorPWM, LOW);
////
////			//			digitalWrite(dirB, HIGH);
////			digitalWrite(leftMotorDir, LOW);
////
////			digitalWrite(leftMotorPWM, HIGH);
////			//			digitalWrite(pwmB, HIGH);
////			//			enableMovement(true);
////			lastActionTime = millis();
//		} else if (commandToken[1] == "backRight") {
//			commandOutput->printf("backRight\r\n");
//			//			digitalWrite(pwmA, LOW);
////			digitalWrite(rightMotorPWM, LOW);
////
////			//			digitalWrite(dirB, HIGH);
////			digitalWrite(leftMotorDir, LOW);
////
////			digitalWrite(leftMotorPWM, HIGH);
////			//			digitalWrite(pwmB, HIGH);
////			//			enableMovement(true);
////			lastActionTime = millis();
//		}
		else if (commandToken[1] == "stop") {
			commandOutput->printf("stop\r\n");
//			digitalWrite(leftMotorPWM, LOW);
//			digitalWrite(rightMotorPWM, LOW);
			dir = STOP;
//			stopped = true;
		}
		else if (commandToken[1].startsWith("xy")) {
//			commandOutput->printf("XY\r\n");
//			String st = commandToken[2];
//			commandOutput->printf(st.c_str());
//			digitalWrite(leftMotorPWM, LOW);
//			digitalWrite(rightMotorPWM, LOW);

			commandOutput->printf(commandToken[2].c_str());

			if (y > 0) {
				dir = FW;
				spdTargetLeft = (abs(y), 0, 100,  0, 1023);
				spdTargetRight= (abs(y), 0, 100,  0, 1023);
			} else if (y == 0) {
				dir = STOP;
			} else {
				dir = BK;
			}


			if (x > 0) {
				dir = FW;
				spdTargetLeft = (abs(y), 0, 100,  0, 1023);
				spdTargetRight= (abs(y), 0, 100,  0, 1023);
			} else if (x == 0) {
				dir = STOP;
			} else {
				dir = BK;
			}
		}

	}
}

//void CarCommand::enableMovement(bool state) {
//	if(state) {
//		digitalWrite(leftMotorPWM, HIGH);
//		digitalWrite(rightMotorPWM, HIGH);
//		stopped = false;
//	} else {
//		digitalWrite(leftMotorPWM, LOW);
//		digitalWrite(rightMotorPWM, LOW);
//		stopped = true;
//	}
//}

void CarCommand::handleMotorTimer() {
	long currentTime = millis();
//	debugf("current =%d, last=%d", currentTime, lastActionTime);

	if(currentTime - (lastActionTime + duration) >= 0) {
		dir = STOP;
		digitalWrite(leftMotorPWM, LOW);
		digitalWrite(rightMotorPWM, LOW);
		return;
	}

	if (dir == STOP) {
		digitalWrite(leftMotorPWM, LOW);
		digitalWrite(rightMotorPWM, LOW);
		return;
	}

	int lpwm = 0;
	int rpwm = 0;
	int lm = 0;
	int rm = 0;

	if (tdir == STRAIGHT) {
		if (dir == FW) {
			lpwm = HIGH;
			rpwm = HIGH;
			lm = MOTOR_FW;
			rm = MOTOR_FW;
		} else if (dir == BK) {
			lpwm = HIGH;
			rpwm = HIGH;
			lm = MOTOR_BK;
			rm = MOTOR_BK;
		}
	} else if (tdir == TL) {
		lpwm = LOW;
		rpwm = HIGH;
		if (dir == FW) {
			rm = MOTOR_FW;
		} else if (dir == BK) {
			rm = MOTOR_BK;
		}
	} else if (tdir == TR) {
		lpwm = HIGH;
		rpwm = LOW;
		if (dir == FW) {
			lm = MOTOR_FW;
		} else if (dir == BK) {
			lm = MOTOR_BK;
		}
	}

	digitalWrite(leftMotorPWM, lpwm);
	digitalWrite(rightMotorPWM, rpwm);
	digitalWrite(leftMotorDir, lm);
	digitalWrite(rightMotorDir, rm);

//	if(direction == STRAIGHT)
//	{
//		digitalWrite(leftMotorPWM, HIGH);
//		digitalWrite(rightMotorPWM, HIGH);
//		if (vector == FORWARD) {
//			digitalWrite(leftMotorDir, FF);
//			digitalWrite(rightMotorDir, FF);
//		} else if(vector == BACK) {
//			digitalWrite(leftMotorDir, REV);
//			digitalWrite(rightMotorDir, REV);
//		}
//	} else if(direction == LEFT) {
//		digitalWrite(leftMotorPWM, LOW);
//		digitalWrite(rightMotorPWM, HIGH);
//		if (vector == FORWARD) {
//			digitalWrite(rightMotorDir, FF);
//		} else if(vector == BACK) {
//			digitalWrite(rightMotorDir, REV);
//		}
//	} else if(direction == RIGHT) {
//		digitalWrite(leftMotorPWM, HIGH);
//		digitalWrite(rightMotorPWM, LOW);
//		if (vector == FORWARD) {
//			digitalWrite(leftMotorDir, FF);
//		} else if(vector == BACK) {
//			digitalWrite(leftMotorDir, REV);
//		}
//	}
};

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

//	uint8_t pins[8] = { 4, 5, 0, 2, 15, 13, 12, 14 }; // List of pins that you want to connect to pwm
//	HardwarePWM HW_pwm(pins, 8);

//	pwmMotors.analogWrite(leftMotorPWM, 100);
//	pwmMotors.analogWrite(rightMotorPWM, 100);
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

//	pinMode(leftMotorPWM, OUTPUT);
//	pinMode(rightMotorPWM, OUTPUT);
//	digitalWrite(leftMotorPWM, LOW);
//	digitalWrite(rightMotorPWM, LOW);

	pwmMotors.initialize();

	//Check and act upon car commands
	motorTimer.setCallback(carMotorDelegate(&CarCommand::handleMotorTimer, this));
	motorTimer.setIntervalMs(100);

//	motorTimer.setCallback(carMotorDelegate(&CarCommand::doPWM, this));
//	motorTimer.setIntervalMs(1000);
//	motorTimer.start(true);
}


void CarCommand::doPWM()
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

	if (countUp) {

		i = 100;
		countUp = false;
		countDown = true;
		pwmMotors.analogWrite(leftMotorPWM, 1023);
	}else {
		i = 1;
		countUp = true;
		countDown = false;
		pwmMotors.noAnalogWrite(leftMotorPWM);
//		pwmMotors.analogWrite(leftMotorPWM, 1);
	}

	int pp = map(i, 0, 100, 0, 1023);
	Serial.println(pp);
//	pwmMotors.analogWrite(leftMotorPWM, pp);
//	digitalWrite(leftMotorDir, LOW);
//	pwmMotors.analogWrite(rightMotorPWM, pp);
//	digitalWrite(rightMotorDir, HIGH);
}

void CarCommand::processCarCommands(String commandLine, CommandOutput* commandOutput)
{
	Vector<String> commandToken;
	int numToken = splitString(commandLine, ' ' , commandToken);
	int rightPwm =0;
	int leftPwm = 0;
	int rightDir = 0;
	int leftDir = 0;

	debugf("Got commandLine = %s", commandLine.c_str());
	if (numToken == 1)
	{
		commandOutput->printf("Move Commands available : \r\n");
//		commandOutput->printf("faster   : Set example status ON\r\n");
//		commandOutput->printf("slower  : Set example status OFF\r\n");
//		commandOutput->printf("forward : Show example status\r\n");
//		commandOutput->printf("back : Show example status\r\n");
//		commandOutput->printf("left : Show example status\r\n");
//		commandOutput->printf("right : Show example status\r\n");
//
//		commandOutput->printf("ffLeft : Move faster ff left\r\n");
//		commandOutput->printf("ffRight : Move faster ff right\r\n");
//		commandOutput->printf("backLeft : Move faster bk left\r\n");
//		commandOutput->printf("backRight : Move faster bk lefts\r\n");

		commandOutput->printf("stop : Show example status\r\n");
		commandOutput->printf("xy xValue yValue: Send X axis PWR, Y axis PWR (can be negative for reverse)\n");
	}
	else
	{
		//first thing stop the "stop timer"
		if (motorTimer.isStarted()) {
			motorTimer.stop();
		}

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
		else if (commandToken[1] == "stop") {
			commandOutput->printf("stop\r\n");
			drive(0,0,0,0);
//			digitalWrite(leftMotorPWM, LOW);
//			digitalWrite(rightMotorPWM, LOW);
			dir = STOP;
//			stopped = true;
		}
		else if (commandToken[1].startsWith("xy")) {

			int tmpX = commandToken[2].toInt();
			int tmpY = commandToken[3].toInt();

			if (tmpY > 0) {
				dir = FW;
				pwmMotors.noAnalogWrite(rightMotorPWM);
				rightDir = HIGH;
//				spdTargetLeft = (abs(tmpY), 0, 100,  0, 1023);
//				spdTargetRight= spdTargetLeft;
			} else if (tmpY == 0) {
				dir = STOP;
			} else {
				dir = BK;
//				spdTargetLeft = -(abs(tmpY), 0, 100,  0, 1023);
//				spdTargetRight= spdTargetLeft;
			}

			if (dir != STOP) {
				//first set motors to run
				leftPwm = (abs(tmpY), 0, 100,  0, 1023);
				rightPwm = (abs(tmpY), 0, 100,  0, 1023);


				if (tmpX>0) {
					rightDir = HIGH;
					leftDir = LOW;
//					leftPwm = 0;
				} else if (tmpX<0){
					leftDir = HIGH;
					rightDir = LOW;
//					rightPwm = 0;
				}
				else if (dir == FW)
				{
					leftDir = HIGH;
					rightDir = HIGH;
				}
				else {
					leftDir = LOW;
					rightDir = LOW;
				}

				if (dir == FW && tmpX != 0) {
					rightDir = switchDir(rightDir);
					leftDir = switchDir(leftDir);
				}
			}
			else {
				leftPwm = 0;
				rightPwm = 0;
			}

			debugf("inside command:leftD=%i,leftP=%i,rightD-%i,rightP=%i", leftDir, leftPwm, rightDir, rightPwm);
		}

		drive(leftDir, leftPwm, rightDir, rightPwm);
		motorTimer.startOnce();
	}
}

int CarCommand::switchDir(int state) {
	return state == HIGH ? LOW : HIGH;
}

void CarCommand::drive(int leftDir, int leftPwm, int rightDir, int rightPwm) {
	debugf("drive command:leftD=%i,leftP=%i,rightD-%i,rightP=%i", leftDir, leftPwm, rightDir, rightPwm);
	spdTargetLeft = leftPwm;
	spdTargetRight = rightPwm;

	digitalWrite(leftMotorDir, leftDir);
	digitalWrite(rightMotorDir, rightDir);
	if (leftPwm == 0 ){
		pwmMotors.noAnalogWrite(leftMotorPWM);
	} else {
		pwmMotors.analogWrite(leftMotorPWM, leftPwm);
	}

	if (rightPwm == 0 ){
		pwmMotors.noAnalogWrite(rightMotorPWM);
	} else {
		pwmMotors.analogWrite(rightMotorPWM, rightPwm);
	}
}

//Stop the car
void CarCommand::handleMotorTimer() {
//	drive(0,0,0,0);

//	long currentTime = millis();
////	debugf("current =%d, last=%d", currentTime, lastActionTime);
//
//	if(currentTime - (lastActionTime + duration) >= 0) {
//		dir = STOP;
//		digitalWrite(leftMotorPWM, LOW);
//		digitalWrite(rightMotorPWM, LOW);
//		return;
//	}
//
//	if (dir == STOP) {
//		digitalWrite(leftMotorPWM, LOW);
//		digitalWrite(rightMotorPWM, LOW);
//		return;
//	}
//
//	int lpwm = 0;
//	int rpwm = 0;
//	int lm = 0;
//	int rm = 0;
//
//	if (tdir == STRAIGHT) {
//		if (dir == FW) {
//			lpwm = HIGH;
//			rpwm = HIGH;
//			lm = MOTOR_FW;
//			rm = MOTOR_FW;
//		} else if (dir == BK) {
//			lpwm = HIGH;
//			rpwm = HIGH;
//			lm = MOTOR_BK;
//			rm = MOTOR_BK;
//		}
//	} else if (tdir == TL) {
//		lpwm = LOW;
//		rpwm = HIGH;
//		if (dir == FW) {
//			rm = MOTOR_FW;
//		} else if (dir == BK) {
//			rm = MOTOR_BK;
//		}
//	} else if (tdir == TR) {
//		lpwm = HIGH;
//		rpwm = LOW;
//		if (dir == FW) {
//			lm = MOTOR_FW;
//		} else if (dir == BK) {
//			lm = MOTOR_BK;
//		}
//	}
//
//	digitalWrite(leftMotorPWM, lpwm);
//	digitalWrite(rightMotorPWM, rpwm);
//	digitalWrite(leftMotorDir, lm);
//	digitalWrite(rightMotorDir, rm);
};

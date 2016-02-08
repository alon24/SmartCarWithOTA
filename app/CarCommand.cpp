/*
 * CarCommand.cpp
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
		commandOutput->printf("stop : Show example status\r\n");
		commandOutput->printf("xy xValue yValue: Send X axis PWR, Y axis PWR (can be negative for reverse)\n");
	}
	else
	{
		//first thing stop the "stop timer"
		if (motorTimer.isStarted()) {
			motorTimer.stop();
		}

		if (commandToken[1].startsWith("xy")) {

			int x = commandToken[2].toInt();
			int y = commandToken[3].toInt();
//			debugf("1:y=%i, abs(y) =%i, leftP=%i,rightP=%i",y, abs(y), leftPwm, rightPwm);
			//check direction to move(needed for knowing which side to move - wheels)
			if (y > 0) {
				dir = FW;
			} else if (y == 0) {
				dir = STOP;
			}
			else {
				dir = BK;
			}

			// if currently we just do right or left, keep the last heading (lastY)
			if (x != 0 && y == 0) {
				if (lastY != 0) {
					if (lastY > 0) {
						dir = FW;
						y = lastY;
					}
					else {
						dir = BK;
						y = lastY;
					}
				}
			}

			lastY = y;
			lastX = x;

			if (dir != STOP) {
				if (x>0) {
					tdir = TR;
				} else if (x<0) {
					tdir = TL;
				} else {
					tdir = STRAIGHT;
				}

				//set motors to run (power)
				leftPwm = map(abs(y), 0, 100,  0, 1023);
				rightPwm = map(abs(y), 0, 100,  0, 1023);

				//check if we want to move right
				if (dir == FW) {
					if (tdir == TL) {
						rightDir = HIGH;
						leftPwm = 0;
					} else if (tdir == TR) {
						leftDir = HIGH;
						rightPwm = 0;
					}else if (tdir == STRAIGHT) {
						leftDir = HIGH;
						rightDir = HIGH;
					}
				}
				else if (dir == BK)
				{
					if (tdir == TL) {
						rightDir = LOW;
						leftPwm = 0;
					} else if (tdir == TR) {
						leftDir = LOW;
						rightPwm = 0;
					}else if (tdir == STRAIGHT) {
						leftDir = LOW;
						rightDir = LOW;
					}
				}
			}
			else {
				leftPwm = 0;
				rightPwm = 0;
			}

//			debugf("inside command:leftD=%i,leftP=%i,rightD=%i,rightP=%i", leftDir, leftPwm, rightDir, rightPwm);
		}

		drive(leftDir, leftPwm, rightDir, rightPwm);
		motorTimer.startOnce();
	}
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
	drive(0,0,0,0);
};

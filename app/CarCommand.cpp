/*
 * Debug.cpp
 *
 */

#include <CarCommand.h>

CarCommand::CarCommand()
{
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
		commandOutput->printf("Example Commands available : \r\n");
		commandOutput->printf("on   : Set example status ON\r\n");
		commandOutput->printf("off  : Set example status OFF\r\n");
		commandOutput->printf("status : Show example status\r\n");
	}
	else
	{
		if (commandToken[1] == "on")
		{
			status = true;
			commandOutput->printf("Status ON\r\n");
		}
		else if (commandToken[1] == "off")
		{
			status = false;
			commandOutput->printf("Status OFF\r\n");
		}
		else if (commandToken[1] == "status")
		{
			String tempString = status ? "ON" : "OFF";
			commandOutput->printf("Example Status is %s\r\n",tempString.c_str());
		};

	}
}



/*
 * ExampleCommand.h
 *
 */

#ifndef SMINGCORE_EXAMPLE_COMMAND_H_
#define SMINGCORE_EXAMPLE_COMMAND_H_

#include "WString.h"
#include "../Services/CommandProcessing/CommandProcessingIncludes.h"

class CarCommand
{
public:
	CarCommand();
	virtual ~CarCommand();
	void initCommand();

private:
	bool status = true;
	void processCarCommands(String commandLine, CommandOutput* commandOutput);
};


#endif /* SMINGCORE_DEBUG_H_ */

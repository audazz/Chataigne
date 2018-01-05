/*
  ==============================================================================

    OSPowerCommand.cpp
    Created: 5 Jan 2018 4:05:45pm
    Author:  Ben

  ==============================================================================
*/

#include "OSPowerCommand.h"

OSPowerCommand::OSPowerCommand(OSModule * _module, CommandContext context, var params) :
	BaseCommand(_module, context, params)
{
	actionType = (ActionType)(int)params.getProperty("type", SHUTDOWN);
}

OSPowerCommand::~OSPowerCommand()
{
}

void OSPowerCommand::trigger()
{
	switch (actionType)
	{
	case SHUTDOWN:
#if JUCE_WINDOWS
		std::system("shutdown -s -t 0");
#elif JUCE_MAC
		std::system("shutdown -s now");
#elif JUCE_LINUX
		std::system("shutdown -h now");
#endif
		break;

	case REBOOT:
#if JUCE_WINDOWS
		std::system("shutdown -r -t 0");
#elif JUCE_MAC
		std::system("shutdown -r now");
#elif JUCE_LINUX
		std::system("shutdown -r now");
#endif
		break;
	}
}

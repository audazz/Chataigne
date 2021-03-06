/*
  ==============================================================================

    PJLinkModule.h
    Created: 5 Jan 2018 3:41:58pm
    Author:  Ben

  ==============================================================================
*/

#pragma once

#pragma once
#include "../TCPModule.h"

class PJLinkModule :
	public TCPModule
{
public:
	PJLinkModule();
	~PJLinkModule() {}

	CommandDefinition * getBasePJCommand(const String &menu, const String &commandName, const String &command, CommandContext context = CommandContext::ACTION);

	static PJLinkModule * create() { return new PJLinkModule(); }
	virtual String getDefaultTypeString() const override { return "PJLink"; }

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PJLinkModule)
};
/*
  ==============================================================================

	StreamingModule.cpp
	Created: 5 Jan 2018 10:39:38am
	Author:  Ben

  ==============================================================================
*/

#include "StreamingModule.h"
#include "SendStreamRawDataCommand.h"
#include "SendStreamStringCommand.h"

StreamingModule::StreamingModule(const String & name) :
	Module(name)
{
	setupIOConfiguration(true, true);
	streamingType = moduleParams.addEnumParameter("Protocol", "Protocol for treating the incoming data");
	streamingType->addOption("Lines", LINES)->addOption("Raw", RAW)->addOption("Data255", DATA255)->addOption("COBS", COBS);

	scriptObject.setMethod(sendId, StreamingModule::sendStringFromScript);
	scriptObject.setMethod(sendBytesId, StreamingModule::sendBytesFromScript);

	defManager.add(CommandDefinition::createDef(this, "", "Send string", &SendStreamStringCommand::create, CommandContext::ACTION));
	defManager.add(CommandDefinition::createDef(this, "", "Send raw data", &SendStreamRawDataCommand::create, CommandContext::ACTION));
}

StreamingModule::~StreamingModule()
{

}

void StreamingModule::processDataLine(const String & message)
{
	if (!enabled->boolValue()) return;
	if (logIncomingData->boolValue()) NLOG(niceName, "Message received :\n" + message);
	inActivityTrigger->trigger();

	scriptManager->callFunctionOnAllItems(dataEventId, message);
}

void StreamingModule::processDataBytes(Array<uint8_t> data)
{
	if (!enabled->boolValue()) return;
	if (logIncomingData->boolValue())
	{
		String msg = String(data.size()) + "bytes received :";
		for (auto &d : data) msg += "\n" + String(d);
		NLOG(niceName, msg);
	}

	inActivityTrigger->trigger();

	if (scriptManager->items.size() > 0)
	{
		var args;
		for (auto &d : data) args.append(d);
		scriptManager->callFunctionOnAllItems(dataEventId, args);
	}
}

void StreamingModule::sendMessage(const String & message)
{
	if (!enabled->boolValue() || !isReadyToSend()) return;
	sendMessageInternal(message);
	outActivityTrigger->trigger();
	if (logOutgoingData->boolValue()) NLOG(niceName, "Sending : " << message);
}

void StreamingModule::sendBytes(Array<uint8> bytes)
{
	if (!enabled->boolValue() || !isReadyToSend()) return;

	sendBytesInternal(bytes);
	outActivityTrigger->trigger();
	if (logOutgoingData->boolValue()) NLOG(niceName, "Sending " + String(bytes.size()) + " bytes");
}

var StreamingModule::sendStringFromScript(const var::NativeFunctionArgs & a)
{
	StreamingModule * m = getObjectFromJS<StreamingModule>(a);
	if (a.numArguments == 0) return var();
	m->sendMessage(a.arguments[0].toString());
	return var();
}

var StreamingModule::sendBytesFromScript(const var::NativeFunctionArgs & a)
{
	StreamingModule * m = getObjectFromJS<StreamingModule>(a);
	if (a.numArguments == 0) return var();
	Array<uint8> data;
	for (int i = 0; i < a.numArguments; i++)
	{
		if (a.arguments[i].isArray())
		{
			Array<var> * aa = a.arguments[i].getArray();
			for (auto &vaa : *aa) data.add((uint8)(int)vaa);
		} else if (a.arguments[i].isInt())
		{
			data.add((uint8)(int)a.arguments[i]);
		}
	}

	m->sendBytes(data);
	return var();
}
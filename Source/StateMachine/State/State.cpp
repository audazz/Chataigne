/*
  ==============================================================================

    State.cpp
    Created: 28 Oct 2016 8:19:10pm
    Author:  bkupe

  ==============================================================================
*/

#include "State.h"

State::State() :
	BaseItem(getTypeString(),true),
	pm("Processors")
{ 
	//canInspectChildContainers = false;

	active = addBoolParameter("Active", "If active, the state's actions and mappings will be effective, otherwise this state won't do anything.", false);

	addChildControllableContainer(&pm);

	pm.setForceDisabled(true);

	helpID = "State";
	
}

State::~State()
{
	masterReference.clear();
}


void State::onContainerParameterChangedInternal(Parameter *p)
{
	if (p == active || p == enabled)
	{
		stateListeners.call(&StateListener::stateActivationChanged, this);
		pm.setForceDisabled(!active->boolValue() || !enabled->boolValue());
	}
}

var State::getJSONData()
{
	var data = BaseItem::getJSONData();
	var pData = pm.getJSONData();
	if(!pData.isVoid() && pData.getDynamicObject()->getProperties().size() > 0) data.getDynamicObject()->setProperty("processors", pData);
	return data;
}

void State::loadJSONDataInternal(var data)
{
	BaseItem::loadJSONDataInternal(data);
	pm.loadJSONData(data.getProperty("processors", var()));
}

/*
  ==============================================================================

    Consequence.cpp
    Created: 28 Oct 2016 8:07:55pm
    Author:  bkupe

  ==============================================================================
*/

#include "Consequence.h"

Consequence::Consequence() :
	BaseCommandHandler("Consequence"),
	forceDisabled(false)
{
	editorIsCollapsed = false;
	isSelectable = false;
}

Consequence::~Consequence()
{

}

void Consequence::triggerCommand()
{
	if (!enabled->boolValue() || forceDisabled) return;
	BaseCommandHandler::triggerCommand();
}
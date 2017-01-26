/*
  ==============================================================================

    BaseItemEditor.cpp
    Created: 18 Jan 2017 2:23:31pm
    Author:  Ben

  ==============================================================================
*/

#include "BaseItemEditor.h"
#include "AssetManager.h"

  BaseItemEditor::BaseItemEditor(BaseItem * bi, bool isRoot) :
	  InspectableEditor(bi, isRoot),
	  headerHeight(20),
	  item(bi),
	  paintHeaderOnly(isRoot)
{
	  if (item->canBeDisabled)
	  {
		  enabledUI = item->enabled->createImageToggle(AssetManager::getInstance()->getPowerBT());
		  addAndMakeVisible(enabledUI);
	  }

	  nameUI = item->nameParam->createStringParameterUI();
	  addAndMakeVisible(nameUI);

	  if (!isRoot)
	  {
		  removeBT = AssetManager::getInstance()->getRemoveBT();
		  this->addAndMakeVisible(removeBT);
		  removeBT->addListener(this);
	  }
}

BaseItemEditor::~BaseItemEditor()
{
}

void BaseItemEditor::paint(Graphics & g)
{
	Rectangle<int> r = getLocalBounds();
	if(paintHeaderOnly) r.setHeight((int)headerHeight);
	Colour c = (item->canBeDisabled && item->enabled->boolValue()) ? BG_COLOR.brighter(.1f):BG_COLOR.darker(.1f);
	g.setColour(c);
	g.fillRoundedRectangle(r.toFloat(), 2);

}

void BaseItemEditor::resized()
{
	Rectangle<int> r = getLocalBounds().withHeight((int)headerHeight);
	Rectangle<int> hr = r.reduced(2);

	if (item->canBeDisabled)
	{
		enabledUI->setBounds(hr.removeFromLeft(hr.getHeight()));
	}
	if (!isRoot)
	{
		removeBT->setBounds(hr.removeFromRight(hr.getHeight()));
		hr.removeFromRight(2);
	}
	resizedInternalHeader(hr);
	nameUI->setBounds(hr);

	r.translate(0, hr.getBottom() + 5);
	r.setHeight(0); //if no override, ensure bottom is set

	resizedInternalContent(r);
	setBounds(getLocalBounds().withBottom(r.getBottom()));

	
}


void BaseItemEditor::newMessage(const ContainerAsyncEvent & e)
{
	switch (e.type)
	{
	case ContainerAsyncEvent::ControllableFeedbackUpdate:
		controllableFeedbackAsyncUpdate(e.targetControllable);
		break;
	}
}

void BaseItemEditor::childBoundsChanged(Component *)
{
	resized();
}

void BaseItemEditor::buttonClicked(Button * b)
{
	if (b == removeBT)
	{
		item->remove();
		return;
	}
}


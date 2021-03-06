/*
  ==============================================================================

    Action.h
    Created: 28 Oct 2016 8:05:02pm
    Author:  bkupe

  ==============================================================================
*/

#ifndef ACTION_H_INCLUDED
#define ACTION_H_INCLUDED

#include "../Processor.h"
#include "Condition/ConditionManager.h"
#include "Consequence/ConsequenceManager.h"

class Action :
	public Processor,
	public ConditionManager::ConditionManagerListener
{
public:
	Action(const String &name = "Action", var params = var());
	virtual ~Action();

	bool autoTriggerWhenAllConditionAreActives; //default true, but if false, let use Actions as user check tool without auto behavior (like TimeTriggers)

	bool hasOffConsequences;

	ConditionManager cdm;
	ScopedPointer<ConsequenceManager> csmOn;
	ScopedPointer<ConsequenceManager> csmOff;

	BoolParameter * isActive;
	Trigger * triggerOn;
	Trigger * triggerOff;

	virtual void setForceDisabled(bool value, bool force = false) override;

	var getJSONData() override;
	void loadJSONDataInternal(var data) override;

	void onContainerParameterChangedInternal(Parameter * p) override;
    void onContainerTriggerTriggered(Trigger *) override;
	void conditionManagerValidationChanged(ConditionManager *) override;

	ProcessorUI * getUI() override;

	class ActionListener
	{
	public:
		virtual ~ActionListener() {}
		virtual void actionEnableChanged(Action *) {}
		virtual void actionValidationChanged(Action *) {}
		virtual void actionActivationChanged(Action *) {}
	};

	ListenerList<ActionListener> actionListeners;
	void addActionListener(ActionListener* newListener) { actionListeners.add(newListener); }
	void removeActionListener(ActionListener* listener) { actionListeners.remove(listener); }


	static Action * create(var params) { return new Action("Action", params); }
	String getTypeString() const override { return "Action"; };

	//InspectableEditor * getEditor(bool /*isRoot*/) override;


	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Action)
};





#endif  // ACTION_H_INCLUDED

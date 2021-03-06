/*
  ==============================================================================

    Mapping.h
    Created: 28 Oct 2016 8:06:13pm
    Author:  bkupe

  ==============================================================================
*/

#ifndef MAPPING_H_INCLUDED
#define MAPPING_H_INCLUDED

#include "../Processor.h"
#include "Input/MappingInput.h"
#include "Filter/MappingFilterManager.h"
#include "Output/MappingOutputManager.h"
#include "../Action/Condition/ConditionManager.h"

class Mapping :
	public Processor,
	public MappingInput::Listener,
	public Timer,
	public MappingFilterManager::BaseManager::Listener
{
public:
	Mapping(bool canBeDisabled = true);
	virtual ~Mapping();

	MappingInput input;
	ConditionManager cdm;
	MappingFilterManager fm;
	MappingOutputManager om;

	BoolParameter * continuousProcess;

	bool inputIsLocked;
	void lockInputTo(Parameter * lockParam);
	void checkFiltersNeedContinuousProcess();

	void process();

	var getJSONData() override;
	void loadJSONDataInternal(var data) override;

	void inputReferenceChanged(MappingInput *) override;
	void inputParameterValueChanged(MappingInput *) override;

	void onContainerParameterChangedInternal(Parameter *) override;

	void itemAdded(MappingFilter * m) override;
	void itemRemoved(MappingFilter * m) override;

	// Inherited via Timer
	virtual void timerCallback() override;

	ProcessorUI * getUI() override;

	static Mapping * create(var) { return new Mapping(); }
	String getTypeString() const override { return "Mapping"; };

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Mapping)

	
};




#endif  // MAPPING_H_INCLUDED

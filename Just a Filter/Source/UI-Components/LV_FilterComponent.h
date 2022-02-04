/*
  ==============================================================================

    LV_FilterComponent.h
    Created: 3 Feb 2022 9:02:30pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "../Widgets/WidgetIncludes.h"

//==============================================================================
/*
*/
class LV_FilterComponent  : public juce::Component
{
public:
    LV_FilterComponent(JustaFilterAudioProcessor& p);
    ~LV_FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    JustaFilterAudioProcessor& audioProcessor;
    
    juce::LV_GroupComponent filterBorder;
    juce::LV_Dial cutoffDial {" Hz", 20.0, 20000.0, 1.0, 1000.0};
    juce::LV_Dial qDial {" Q", 0.05, 0.95, 0.01, 0.33};
    juce::LV_Dial gainDial {" dB", -12.0, 12.0, 0.01, 0.0};
    
    juce::LV_Label cutoffDialLabel;
    juce::LV_Label qDialLabel;
    juce::LV_Label gainDialLabel;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> cutoffDialAttach;
    std::unique_ptr<SliderAttachment> qDialAttach;
    std::unique_ptr<SliderAttachment> gainDialAttach;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LV_FilterComponent)
};

/*
  ==============================================================================

    LV_HeaderComponent.h
    Created: 17 Jan 2022 5:31:27pm
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
class LV_HeaderComponent  : public juce::Component
{
public:
    LV_HeaderComponent(juce::AudioProcessorValueTreeState& tree);
    ~LV_HeaderComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void setWidthAndHeight(float w, float h);

private:
    
    juce::LV_Menu oversamplingMenu;
    juce::LV_Menu filterTypeMenu;
    juce::LV_Menu bandwidthTypeMenu;
    
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    
    std::unique_ptr<ComboBoxAttachment> oversamplingMenuAttach;
    std::unique_ptr<ComboBoxAttachment> filterTypeMenuAttach;
    std::unique_ptr<ComboBoxAttachment> bandwidthTypeMenuAttach;
    
    /** Logo and Link =========================================================*/
    juce::Image footerLogo;
    juce::HyperlinkButton mWebLink;
    juce::URL mWebUrl {"https://www.patreon.com/ViatorDSP"};
    
    /** Vars ==================================================================*/
    float width {0.0f};
    float height {0.0f};
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LV_HeaderComponent)
};

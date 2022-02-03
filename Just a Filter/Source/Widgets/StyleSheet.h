/*
  ==============================================================================

    StyleSheet.h
    Created: 20 Jul 2021 6:38:58pm
    Author:  landon viator

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace juce
{

    class LV_CustomAbleDialLAF : public LookAndFeel_V4
    {
        
    public:
        
        LV_CustomAbleDialLAF(bool isStereoDial)
        {
            setDialIsStereoDial(isStereoDial);
        }
        
        void drawRotarySlider (Graphics &,
                               int x, int y,
                               int width, int height,
                               float sliderPosProportional,
                               float rotaryStartAngle,
                               float rotaryEndAngle, Slider &) override;
        
        void setDialIsStereoDial(bool isStereoDial);
        
    private:
        
        float stereoDialScalar = 1.0;
    };

    class LV_AlphaDialLAF : public juce::LookAndFeel_V4
    {
        
    public:
        void drawRotarySlider(Graphics &g,
                              int x,
                              int y,
                              int width,
                              int height,
                              float sliderPos,
                              float rotaryStartAngle,
                              float rotaryEndAngle,
                              Slider &slider) override;
        
        void drawLabel (Graphics& g, Label& label) override;
    };

    class LV_HardDialLAF : public juce::LookAndFeel_V4
    {
        
    public:
        
        void drawRotarySlider(Graphics &g,
                              int x,
                              int y,
                              int width,
                              int height,
                              float sliderPos,
                              float rotaryStartAngle,
                              float rotaryEndAngle,
                              Slider &slider) override;

        void drawLabel (Graphics& g, Label& label) override;
    };


    class LV_FaderLAF : public LookAndFeel_V4
    {
    public:
        
        void drawLinearSlider (Graphics& g,
                               int x,
                               int y,
                               int width,
                               int height,
                               float sliderPos,
                               float minSliderPos,
                               float maxSliderPos,
                               const Slider::SliderStyle style,
                               Slider& slider) override;
        
        void drawLabel(Graphics &g, Label &label) override;
        
    private:
        
        juce::String sliderFont {"Helvetica"};
        
    };

    class LV_PhaseToggleLAF : public LookAndFeel_V4
    {
        
    public:
        
        
        void drawToggleButton(juce::Graphics &g,
                              juce::ToggleButton &toggleButton,
                              bool shouldDrawButtonAsHighlighted,
                              bool shouldDrawButtonAsDown) override;
    };

    class LV_PowerToggleLAF : public LookAndFeel_V4
    {
        
    public:
        
        
        void drawToggleButton(juce::Graphics &g,
                              juce::ToggleButton &toggleButton,
                              bool shouldDrawButtonAsHighlighted,
                              bool shouldDrawButtonAsDown) override;
    };

    class LV_CustomBorder : public LookAndFeel_V2
    {
        public:
        
        void drawGroupComponentOutline (Graphics& g, int width, int height,
                                                   const String& text, const Justification& position,
                                                   GroupComponent& group) override;
    };
    
}

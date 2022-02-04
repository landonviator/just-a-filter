/*
  ==============================================================================

    LV_FilterComponent.cpp
    Created: 3 Feb 2022 9:02:30pm
    Author:  Landon Viator

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LV_FilterComponent.h"

//==============================================================================
LV_FilterComponent::LV_FilterComponent(JustaFilterAudioProcessor& p) : audioProcessor(p)
{
    // Border
    addAndMakeVisible(filterBorder);
    filterBorder.setText("Just a Filter");
    
    // Cutoff Dial
    cutoffDialAttach = std::make_unique<SliderAttachment>(audioProcessor.treeState, cutoffID, cutoffDial);
    addAndMakeVisible(cutoffDial);
    addAndMakeVisible(cutoffDialLabel);
    cutoffDialLabel.attachToComponent(&cutoffDial, false);
    cutoffDialLabel.setText("Cutoff", juce::dontSendNotification);
    
    // Q Dial
    qDialAttach = std::make_unique<SliderAttachment>(audioProcessor.treeState, bandwidthID, qDial);
    addAndMakeVisible(qDial);
    qDial.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::orange.darker(0.5));
    qDial.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::black.brighter(0.1).withAlpha(0.8f));
    qDial.forceShadow();
      addAndMakeVisible(qDialLabel);
    qDialLabel.attachToComponent(&qDial, false);
    qDialLabel.setText("Bandwidth", juce::dontSendNotification);
    
    // Gain Dial
    gainDialAttach = std::make_unique<SliderAttachment>(audioProcessor.treeState, gainID, gainDial);
    addAndMakeVisible(gainDial);
    gainDial.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::palevioletred.darker(1.0).darker(0.3));
    gainDial.forceShadow();
      addAndMakeVisible(gainDialLabel);
    gainDialLabel.attachToComponent(&gainDial, false);
    gainDialLabel.setText("Gain", juce::dontSendNotification);
}

LV_FilterComponent::~LV_FilterComponent()
{
    cutoffDialAttach = nullptr;
    qDialAttach = nullptr;
    gainDialAttach = nullptr;
}

void LV_FilterComponent::paint (juce::Graphics& g)
{

}

void LV_FilterComponent::resized()
{
    auto leftMargin = getWidth() * 0.05f;
    auto topMargin = getHeight() * 0.05f;
    auto dialSize = getWidth() * 0.2f;
    auto spaceBetween = 1.5;
    
    filterBorder.setBounds(leftMargin, topMargin, getWidth() - leftMargin * 2.0f, getHeight() - topMargin * 2.0f);
    
    cutoffDial.setBounds(leftMargin * 2.0, topMargin * 5.0f, dialSize, dialSize);
    qDial.setBounds(cutoffDial.getX() + cutoffDial.getWidth() * spaceBetween, cutoffDial.getY() * 1.75f, dialSize, dialSize);
    gainDial.setBounds(qDial.getX() + qDial.getWidth() * spaceBetween, cutoffDial.getY(), dialSize, dialSize);
}

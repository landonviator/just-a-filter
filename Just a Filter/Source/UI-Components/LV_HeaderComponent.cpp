/*
  ==============================================================================

    LV_HeaderComponent.cpp
    Created: 17 Jan 2022 5:31:27pm
    Author:  Landon Viator

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LV_HeaderComponent.h"

//==============================================================================
LV_HeaderComponent::LV_HeaderComponent(juce::AudioProcessorValueTreeState& tree)
{
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    
    //oversamplingMenuAttach = std::make_unique<ComboBoxAttachment>(tree, qualityID, oversamplingMenu);

    oversamplingMenu.setTextWhenNothingSelected("Quality");
    oversamplingMenu.addItem("Normal Quality", 1);
    oversamplingMenu.addItem("High Quality", 2);
    addAndMakeVisible(oversamplingMenu);
    
    bandwidthTypeMenuAttach = std::make_unique<ComboBoxAttachment>(tree, bandwidthTypeID, bandwidthTypeMenu);
    bandwidthTypeMenu.setTextWhenNothingSelected("Q Type");
    bandwidthTypeMenu.addItem("Linear", 1);
    bandwidthTypeMenu.addItem("Propotional", 2);
    addAndMakeVisible(bandwidthTypeMenu);
    
    filterTypeMenuAttach = std::make_unique<ComboBoxAttachment>(tree, filterTypeID, filterTypeMenu);
    filterTypeMenu.setTextWhenNothingSelected("Filter Type");
    filterTypeMenu.addItem("Low Shelf", 1);
    filterTypeMenu.addItem("Low Cut", 2);
    filterTypeMenu.addItem("Notch", 3);
    filterTypeMenu.addItem("High Cut", 4);
    filterTypeMenu.addItem("High Shelf", 5);
    addAndMakeVisible(filterTypeMenu);
}

LV_HeaderComponent::~LV_HeaderComponent()
{
    oversamplingMenuAttach = nullptr;
    filterTypeMenuAttach = nullptr;
    bandwidthTypeMenuAttach = nullptr;
}

void LV_HeaderComponent::paint (juce::Graphics& g)
{
    // Header rectangle
    juce::Rectangle<float> header;
    header.setBounds(0, 0, width, height);
    g.setColour(juce::Colours::black.brighter(0.1).withAlpha(0.8f));
    g.fillRect(header);

    // Logo layer
    footerLogo = juce::ImageCache::getFromMemory(BinaryData::landon5504_png, BinaryData::landon5504_pngSize);

    // Draw and position the image
    g.drawImageWithin(footerLogo, width * 0.025, 4.0f, getHeight() * 3.5f, getHeight() * 0.75, juce::RectanglePlacement::stretchToFit);

    // Patreon link
    mWebLink.setURL(mWebUrl);
    addAndMakeVisible(mWebLink);
    mWebLink.setBounds(width * 0.38, height * 0.9, width * 0.25, height * 0.1);
}

void LV_HeaderComponent::resized()
{
    float rightMargin = width * 0.99f;
    float spaceBetween = width * 0.01f;
    float topMargin = getHeight() * 0.125f;
    float menuWidth = width * 0.15f;
    float menuHeight = getHeight() * 0.75f;
    
    oversamplingMenu.setBounds(rightMargin - menuWidth, topMargin, menuWidth, menuHeight);
    bandwidthTypeMenu.setBounds(oversamplingMenu.getX() - spaceBetween - oversamplingMenu.getWidth(), topMargin, menuWidth, menuHeight);
    filterTypeMenu.setBounds(bandwidthTypeMenu.getX() - spaceBetween - bandwidthTypeMenu.getWidth(), topMargin, menuWidth, menuHeight);
}

void LV_HeaderComponent::setWidthAndHeight(float w, float h)
{
    width = w;
    height = h;
}

/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JustaFilterAudioProcessor::JustaFilterAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
treeState (*this, nullptr, "PARAMETER", createParameterLayout())
#endif
{
}

JustaFilterAudioProcessor::~JustaFilterAudioProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout JustaFilterAudioProcessor::createParameterLayout()
{
  std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;

  // Make sure to update the number of reservations after adding params
  //params.reserve(16);
    
    juce::StringArray filterTypes =
    {
        "Low Shelf",
        "Low Cut",
        "Notch",
        "High Cut",
        "High Shelf"
    };
    
    juce::StringArray qTypes =
    {
        "Linear",
        "Proportional"
    };

  auto pFilterType = std::make_unique<juce::AudioParameterChoice>("filter type", "Filter Type", filterTypes, 0);
    
  auto pQType = std::make_unique<juce::AudioParameterChoice>("bandwidth type", "Bandwith Type", qTypes, 0);
    
  auto pCutoff = std::make_unique<juce::AudioParameterFloat>("cutoff", "Cutoff", juce::NormalisableRange<float> (20.0f, 20000.0f, 1.0f, 0.3f, false), 1000.0f);
    
  auto pQ = std::make_unique<juce::AudioParameterFloat>("q", "Q", 0.05f, 0.95f, 0.33f);
    
  auto pQGain = std::make_unique<juce::AudioParameterFloat>("gain", "Gain", -24.0f, 24.0f, 0.0f);
  
  params.push_back(std::move(pFilterType));
  params.push_back(std::move(pQType));
  params.push_back(std::move(pCutoff));
  params.push_back(std::move(pQ));
  params.push_back(std::move(pQGain));

  return { params.begin(), params.end() };
}

void JustaFilterAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
}

//==============================================================================
const juce::String JustaFilterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JustaFilterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JustaFilterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JustaFilterAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double JustaFilterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JustaFilterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int JustaFilterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JustaFilterAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String JustaFilterAudioProcessor::getProgramName (int index)
{
    return {};
}

void JustaFilterAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void JustaFilterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void JustaFilterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JustaFilterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void JustaFilterAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool JustaFilterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* JustaFilterAudioProcessor::createEditor()
{
    //return new JustaFilterAudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void JustaFilterAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void JustaFilterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JustaFilterAudioProcessor();
}

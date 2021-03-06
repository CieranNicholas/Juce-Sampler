/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class FirstSamplerAudioProcessorEditor  : public juce::AudioProcessorEditor, 
                                          public juce::FileDragAndDropTarget
                                            
{
public:
    FirstSamplerAudioProcessorEditor (FirstSamplerAudioProcessor&);
    ~FirstSamplerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    bool isInterestedInFileDrag(const juce::StringArray& files) override;
    void filesDropped(const juce::StringArray& files, int x, int y) override;
    


private:
    juce::TextButton mLoadButton { "Load" };
    std::vector<float> mAudioPoints;
    bool mShouldBePaining { false };

    FirstSamplerAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FirstSamplerAudioProcessorEditor)
};

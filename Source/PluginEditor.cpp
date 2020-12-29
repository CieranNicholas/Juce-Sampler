/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FirstSamplerAudioProcessorEditor::FirstSamplerAudioProcessorEditor (FirstSamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (600, 200);
}

FirstSamplerAudioProcessorEditor::~FirstSamplerAudioProcessorEditor()
{
}

//==============================================================================
void FirstSamplerAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::seagreen);
    g.setColour(juce::Colours::white);

    if(mShouldBePaining)
    {   
        juce::Path p;
        mAudioPoints.clear();
        
        auto waveForm = audioProcessor.getWaveForm();
        auto ratio = waveForm.getNumSamples() / getWidth();
        auto buffer = waveForm.getReadPointer (0);

        //Scale audio file to window x axis
        for (int sample = 0; sample < waveForm.getNumSamples(); sample += ratio)
        {
            mAudioPoints.push_back(buffer[sample]);
        }

        p.startNewSubPath(0, getHeight() / 2.0f);

        //scale audio file to window y axis
        for (int sample = 0; sample < mAudioPoints.size(); ++sample)
        {
            auto point = juce::jmap<float>(mAudioPoints[sample], -1.0f, 1.0f, 200.0f, 0.0f);
            p.lineTo(sample, point);
        }

        g.strokePath(p, juce::PathStrokeType (2));

        mShouldBePaining = false;
    }

    

    //new file dropped?
        //if yes
            //draw the waveform

    //g.setColour(juce::Colours::white);
    //g.setFont(15.0f);

    //
    //
    //if (audioProcessor.getNumSamplerSounds() > 0)
    //{
    //    g.fillAll(juce::Colours::red);
    //    g.drawText("Sound Loaded", getWidth() / 2 - 50, getHeight() / 2 - 10, 100, 20, juce::Justification::centred);
    //}
    //else
    //{
    //    g.drawText("Load a Sound", getWidth() / 2 - 50, getHeight() / 2 - 10, 100, 20, juce::Justification::centred);
    //}
}

void FirstSamplerAudioProcessorEditor::resized()
{
    //mLoadButton.setBounds(getWidth() / 2 - 50, getHeight() / 2 - 50, 100, 100);
}


 bool FirstSamplerAudioProcessorEditor::isInterestedInFileDrag(const juce::StringArray& files)
 {  
     for (auto file : files)
     {
         if (file.contains(".wav") || file.contains(".mp3") || file.contains(".aif"))
         {
             return true;
         }
     }

     return false;
 }

 void FirstSamplerAudioProcessorEditor::filesDropped(const juce::StringArray& files, int x, int y)
 {
    for (auto file : files)
    {
        if (isInterestedInFileDrag(file))
        {       
            mShouldBePaining = true;
            audioProcessor.loadFile(file);
        }
    }

    repaint();
 }

 

 

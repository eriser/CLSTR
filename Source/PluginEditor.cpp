/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 450);
    
    wetMixSlider.setSliderStyle (Slider::LinearBarVertical);
    wetMixSlider.setRange(0.0, 1.0, 0.01);
    wetMixSlider.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
    wetMixSlider.setPopupDisplayEnabled (false, this);
    wetMixSlider.setTextValueSuffix (" Global Wet");
    wetMixSlider.setValue(p.wetMix);
    
    wetMixSlider.setColour(Slider::backgroundColourId, Colours::red);
    
    dryMixSlider.setSliderStyle (Slider::LinearBarVertical);
    dryMixSlider.setRange(0.0, 1.0, 0.01);
    dryMixSlider.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
    dryMixSlider.setPopupDisplayEnabled (false, this);
    dryMixSlider.setTextValueSuffix (" Dry");
    dryMixSlider.setValue(p.dryMix);
    
    addAndMakeVisible (&wetMixSlider);
    wetMixSlider.addListener(this);
    
    addAndMakeVisible (&dryMixSlider);
    dryMixSlider.addListener(this);
    
    for(int i = 0; i< 8; i++){ //for each echo chamber
        
        delaysWet[i].setSliderStyle (Slider::LinearBarVertical);
        delaysWet[i].setRange(0.0, 1.0, 0.01);
        delaysWet[i].setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
        delaysWet[i].setPopupDisplayEnabled (true, this);
        delaysWet[i].setTextValueSuffix (" Delay Wet");
        delaysWet[i].setValue(p.delayGain[i]);
        addAndMakeVisible (&delaysWet[i]);
        delaysWet[i].addListener(this);
    }
    startTimer(50);
    
    

}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

void NewProjectAudioProcessorEditor::timerCallback(){ //update UI from parameter changes
    
    NewProjectAudioProcessor* theProcessor = getProcessor();
    
    wetMixSlider.setValue(theProcessor->wetMix, dontSendNotification);
    dryMixSlider.setValue(theProcessor->dryMix, dontSendNotification);
    
    for(int i = 0; i< 8; i++){
        
        
        delaysWet[i].setValue(theProcessor->delayGain[i], dontSendNotification);
    
    }
}

void NewProjectAudioProcessorEditor::sliderValueChanged (Slider* slider)

{
    if (slider == &wetMixSlider){//index 0,
        getProcessor()->setParameterNotifyingHost(0, (float) wetMixSlider.getValue());
    }
    
    if (slider == &dryMixSlider){//index 1,
        getProcessor()->setParameterNotifyingHost(1, (float) dryMixSlider.getValue());
    }
    
    for(int i = 0; i<8; i++){ //delay sliders
        if (slider == &delaysWet[i]){//index 1,
            getProcessor()->setParameterNotifyingHost(i+2, (float) delaysWet[i].getValue());
        }
    }
}
    
AudioParameterFloat* NewProjectAudioProcessorEditor::getParameterForSlider (Slider* slider)
{
    const OwnedArray<AudioProcessorParameter>& params = getAudioProcessor()->getParameters();
    return dynamic_cast<AudioParameterFloat*> (params[0]);
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colour::fromRGB(148 ,176, 209));
    g.setColour (Colours::white);
    
    Font mainFont("Montserrat", 30.0f, Font::plain);
    Font secondaryFont("Montserrat", 12.0f, Font::plain);
    
    mainFont.setExtraKerningFactor(.2);
    secondaryFont.setExtraKerningFactor(.2);

    g.setFont (mainFont);
    g.drawText("DELAY DESIGNER", getWidth()/2-200, 30, 400,20,Justification::centred, true);
    
    g.setFont(secondaryFont);
    g.drawText("WET", getWidth()-58, getHeight() - 90, 40,20, Justification::centredTop, true);
    
     g.drawText("DRY", getWidth()-98, getHeight() - 90, 40,20, Justification::centredTop, true);
}

void NewProjectAudioProcessorEditor::resized()
{
    wetMixSlider.setBounds (getWidth()-40, 100, 5, getHeight() - 200);
    dryMixSlider.setBounds (getWidth()-80, 100, 5, getHeight() - 200);
    
    for(int i = 0; i< 8; i++){
        
        delaysWet[i].setBounds (80*(i+1), 100, 5, getHeight() - 200);
        
    }
    
}

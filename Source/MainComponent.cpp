#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "./Synth.cpp"

using namespace std;

const String AUDIO_FILE_FORMAT = ".wav";
const String SAMPLES_PATH = "/Users/RyanJamesMcGill/Documents/Projects/JuceProjects/selector2/audioSamples/";

class MainContentComponent   : public AudioAppComponent
{
public:
  //==============================================================================
  MainContentComponent()
  {
    setAudioChannels (0, 2);
    initialiseMidi();
    initialiseSynth();
  }

  ~MainContentComponent()
  {
    shutdownAudio();
  }

  //==============================================================================
  void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override
  {
    midiCollector.reset(sampleRate);
    synth.setCurrentPlaybackSampleRate(sampleRate);
  }

  void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
  {
    bufferToFill.clearActiveBufferRegion();
    MidiBuffer incomingMidi;
    midiCollector.removeNextBlockOfMessages(incomingMidi, bufferToFill.numSamples);
    synth.renderNextBlock(*bufferToFill.buffer, incomingMidi, 0, bufferToFill.numSamples);
  }

  void releaseResources() override
  {
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
  }

  //==============================================================================
  void initialiseMidi()
  {
    const StringArray list (MidiInput::getDevices());
    String midiDeviceName = list[MidiInput::getDefaultDeviceIndex()];
    if(midiDeviceName.isEmpty()){
      cout << "No midi devices detected." << endl;
    } else {
      cout << "activating midi device: " << midiDeviceName << endl;
      deviceManager.setMidiInputEnabled(midiDeviceName, true);
      deviceManager.addMidiInputCallback(midiDeviceName, &midiCollector);   
    }
  }

  void initialiseSynth()
  {
    for (int i = 0; i < 16; i++) {
      synth.addVoice(new SamplerVoice());
    }
    String filePath;
    for (int i = 0; i < 128; i++)
    {
      filePath = SAMPLES_PATH;
      filePath.operator+=(i);
      filePath.append(AUDIO_FILE_FORMAT, AUDIO_FILE_FORMAT.length());
      setUsingSampledSound(filePath, i);
    }
  }

  void setUsingSampledSound(String filePath, int intNote)
  {
    WavAudioFormat wavFormat;
    if (File(filePath).exists()){
      cout << "Loading: " << filePath << endl;
      ScopedPointer<AudioFormatReader> audioReader (wavFormat.createReaderFor(new FileInputStream(filePath), true));
      BigInteger noteRange;
      noteRange.setRange(intNote, 1, true);
      //noteRange.setRange(0, 128, true);
      synth.addSound(
        new SamplerSound(
          "sample",
          *audioReader,
          noteRange,
          intNote, // root midi note
          0.1,     // attack time
          0.1,     // release time
          15.0     // max sample length
        )
      );
    }
  }

  MidiMessageCollector midiCollector;
  Synth synth;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

Component* createMainContentComponent()  { return new MainContentComponent(); }

#endif  // MAINCOMPONENT_H_INCLUDED

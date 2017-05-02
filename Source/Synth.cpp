#ifndef SYNTH_H_
#define SYNTH_H_
#include "../JuceLibraryCode/JuceHeader.h"

const float VELOCITY = 0.25f;

class Synth: public juce::Synthesiser {
public:
   void handleMidiEvent (const MidiMessage& m) override 
   {
      const int channel = m.getChannel();

      if (m.isNoteOn())
      {
          noteOn (channel, m.getNoteNumber(), VELOCITY);
      }
      else if (m.isNoteOff())
      {
          noteOff (channel, m.getNoteNumber(), VELOCITY, true);
      }
      else if (m.isAllNotesOff() || m.isAllSoundOff())
      {
          allNotesOff (channel, true);
      }
      else if (m.isPitchWheel())
      {
          const int wheelPos = m.getPitchWheelValue();
          lastPitchWheelValues [channel - 1] = wheelPos;
          handlePitchWheel (channel, wheelPos);
      }
      else if (m.isAftertouch())
      {
          handleAftertouch (channel, m.getNoteNumber(), m.getAfterTouchValue());
      }
      else if (m.isChannelPressure())
      {
          handleChannelPressure (channel, m.getChannelPressureValue());
      }
      else if (m.isController())
      {
          handleController (channel, m.getControllerNumber(), m.getControllerValue());
      }
      else if (m.isProgramChange())
      {
          handleProgramChange (channel, m.getProgramChangeNumber());
      }
   };
};


#endif /* SYNTH_H_ */




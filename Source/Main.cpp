/*
  ==============================================================================

  This file was auto-generated!

  It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

using namespace std;

Component* createMainContentComponent();

//==============================================================================
class selector2Application  : public JUCEApplication
{
public:
  //==============================================================================
  selector2Application() {}

  const String getApplicationName() override     { return ProjectInfo::projectName; }
  const String getApplicationVersion() override { return ProjectInfo::versionString; }
  bool moreThanOneInstanceAllowed() override     { return true; }

  //==============================================================================
  void initialise (const String& commandLine) override
  {
    cout << "--- S E L E C T O R ---" << endl;
    cout << "App version: " << getApplicationVersion() << endl;
    createMainContentComponent();
  }

  void shutdown() override
  {
    // Add your application's shutdown code here..

    //mainWindow = nullptr; // (deletes our window)
  }

  //==============================================================================
  void systemRequestedQuit() override
  {
    // This is called when the app is being asked to quit: you can ignore this
    // request and let the app carry on running, or call quit() to allow the app to close.
    quit();
  }

  void anotherInstanceStarted (const String& commandLine) override
  {
    // When another instance of the app is launched while this one is running,
    // this method is invoked, and the commandLine parameter tells you what
    // the other instance's command-line arguments were.
  }
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (selector2Application)

#include "Application.h"
#include "Config.h"
#include "CurrModeHandler.h"
#include "EventHandler.h"
#include "Input.h"
#include "Mode.h"
#include "Params.h"
#include "TimeStats.h"
#include "WordProvider.h"

int main(int argc, char **argv) 
{    
  Params params(argc, argv);
  Config config(params.getConfigFile());
  WordProvider& provider = config.getWordProvider(); 
  TimeStats stats(provider.total());
  Application app;
  EventHandler eventHadler;

  PlayMode playMode(eventHadler, provider, stats);
  StartMode startmode(eventHadler);
  FinishedMode finishedMode(eventHadler, stats, provider);
  CurrModeHandler currModeHandler;
  currModeHandler.addMode(&startmode, &playMode);
  currModeHandler.addMode(&playMode, &finishedMode);

  app.mainLoop(eventHadler, currModeHandler);

  return EXIT_SUCCESS;
}
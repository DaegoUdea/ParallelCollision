#include "gametimer.h"

GameTimer::GameTimer() {
   //Initialize the variables
   mStartTicks = 0;
   mPausedTicks = 0;
   mPaused = false;
   mStarted = false;
}

void GameTimer::start()
{
  mStarted = true; // Starts the timer
  mPaused = false; // Unpause the timer

  mStartTicks = SDL_GetTicks(); //Gets the current clock time;
	mPausedTicks = 0;
}

void GameTimer::stop()
{
  mStarted = false; // Stops the timer
  mPaused = false; // Unpause the timer

	mStartTicks = 0; // Clear tick variables
	mPausedTicks = 0;
}

void GameTimer::pause()
{
  // If the timer is running and isn't already paused
  if( mStarted && !mPaused )
  {
    mPaused = true; // Pause the timer
    //Calculate the paused ticks
    mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
  }
}

void GameTimer::unpause()
{
    //If the timer is running and paused
    if( mStarted && mPaused )
    {
        mPaused = false; // Unpause the timer
        //Reset the starting ticks
        mStartTicks = SDL_GetTicks() - mPausedTicks;
        //Reset the paused ticks
        mPausedTicks = 0;
    }
}

Uint32 GameTimer::getTicks()
{
	Uint32 time = 0; //The actual timer time
  // If the timer is running
  if( mStarted )
  {
      //If the timer is paused
      if( mPaused )
      {
        //Return the number of ticks when the timer was paused
        time = mPausedTicks;
      }
      else
      {
        //Return the current time minus the start time
        time = SDL_GetTicks() - mStartTicks;
      }
  }

  return time;
}

bool GameTimer::isStarted()
{
	//Timer is running and paused or unpaused
    return mStarted;
}

bool GameTimer::isPaused()
{
	//Timer is running and paused
    return mPaused && mStarted;
}

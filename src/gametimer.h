#ifndef SRC_GAME_TIMER_H_
#define SRC_GAME_TIMER_H_

#include <SDL2/SDL.h>
#include <sstream>

class GameTimer {
    public:
		//Initializes variables
		GameTimer();

		//The various clock actions
		void start();
		void stop();
		void pause();
		void unpause();

		//Gets the timer's time
		Uint32 getTicks();

		//Checks the status of the timer
		bool isStarted();
		bool isPaused();

    private:

		Uint32 mStartTicks; // The clock time when the timer started
		Uint32 mPausedTicks; //The ticks stored when the timer was paused

		//The timer status
		bool mPaused;
		bool mStarted;
};

#endif // SRC_GAME_TIMER_H_

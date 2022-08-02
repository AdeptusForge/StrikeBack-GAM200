#pragma once
#include "MADRpch.h"
#include "glfw3.h"
#include "glm.hpp"


void TimeStartup();
int GetCurrentTick();
void UpdateTime(GLFWwindow*);

//unsigned int SecondsToFrames(float seconds);

//Widely used frame-locked timer. 
//Timer starts counting from 1 instead of 0, like all clocks.
class Event_Timer
{
private:
	//Timer's duration in frames;
	unsigned int timerDuration;
	//Timer's current time keeping-from when it started. 
	//Starts at 1 instead of 0, like all clocks.
	unsigned int timerCount;
	bool paused = false;
	bool looping = false;
	//TODO: Make function for mapping timerIDs
	unsigned int timerID = 0;
public:
	Event_Timer() : timerCount(), timerDuration(), timerID() 
	{
	};
	Event_Timer(unsigned int duration, unsigned int ID) : timerCount(), timerDuration(duration), timerID(ID) 
	{
	};

	//Stops timer momentarily.
	void PauseTimer()
	{
		if (timerCount < timerDuration)
		{
			paused = true;
		}
	};
	//Ends timer but doesn't send timer Event.
	void StopTimer()
	{
		TimerEnd();
	}
	void UnpauseTimer()
	{
		paused = false;
	};
	//Deletes the timer, preventing it from acting or counting further. 
	//Skips the timer event if not called from TimerCompletion
	void TimerEnd()
	{
		
	}
	//Sends the completed timer event, and resets the timer if looping.
	void TimerCompletion()
	{
		//TODO:: SEND TIMER COMPLETED EVENT
		
		if (looping)
			timerCount = 1;
		else
			TimerEnd();
	}
	void TimerUpdate()
	{
		//WriteDebug(timerID + " Updated");
		if (!paused)
		{
			if (timerCount >= timerDuration)
			{
				TimerCompletion();
			}
			timerCount++;
		}
	}
};
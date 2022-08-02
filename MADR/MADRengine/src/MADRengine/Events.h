#pragma once
#include "MADRpch.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Input.h"

#pragma region Event Reqs
class EventListener;
enum class EventType
{
	Engine_Event,
	Input_Event,
	Inventory_Event,
	Sound_Event,
	Map_Event,
	Narrative_Event,
	UI_Event,
	CollisionEvent,


};

class EventData
{
private:
	std::map<std::string, int > intData;
	std::map<std::string, int >::iterator intIter;
	std::map<std::string, std::string > stringData;
	std::map<std::string, std::string >::iterator stringIter;
	std::map<std::string, float > floatData;
	std::map<std::string, float >::iterator floatIter;
	std::map<std::string, glm::vec2 > vec2Data;
	std::map<std::string, glm::vec2 >::iterator vec2Iter;
	std::map<std::string, glm::vec3 > vec3Data;
	std::map<std::string, glm::vec3 >::iterator vec3Iter;
	InputFrame inputs;

public:
#pragma region Setters
	void SetInt(std::string tag, int value)
	{
		intIter = intData.begin();
		intData.insert({ tag, value });
	}

	void SetString(std::string tag, std::string value)
	{
		stringIter = stringData.begin();
		stringData.insert({ tag, value });
	}

	void SetFloat(std::string tag, float value)
	{
		floatIter = floatData.begin();
		floatData.insert({ tag, value });
	}

	void SetVector2(std::string tag, glm::vec2 value)
	{
		vec2Iter = vec2Data.begin();
		vec2Data.insert({ tag, value });
	}
	void SetVector3(std::string tag, glm::vec3 value)
	{
		vec3Iter = vec3Data.begin();
		vec3Data.insert({ tag, value });
	}
	void SetInputs(InputFrame i)
	{
		inputs = i;
	}
#pragma endregion

#pragma region Getters
	const int GetInt(std::string tag) { return intData.find(tag)->second; }
	const std::string GetString(std::string tag) { return stringData.find(tag)->second; }
	const float GetFloat(std::string tag) { return floatData.find(tag)->second; }
	const glm::vec2 GetVec2(std::string tag) { return vec2Data.find(tag)->second; }
	const glm::vec3 GetVec3(std::string tag) { return vec3Data.find(tag)->second; }
	const InputFrame GetInputs() { return inputs; }
#pragma endregion
public:
	EventData() {};
};

class EVENT
{
public:
	EventType Etype;
	EventData data = EventData();
	std::string triggeredBy;

	EVENT(EventType etype, EventData edata, std::string trigger = "Undefined Trigger") : Etype(etype), data(edata), triggeredBy(trigger) {};
	EVENT(EventType etype, std::string trigger = "Undefined Trigger") : Etype(etype), triggeredBy(trigger) { data = EventData(); };
	EVENT(std::string trigger) : Etype(EventType::Engine_Event), triggeredBy(trigger) {};
	EVENT() : Etype(), triggeredBy("Undefined Trigger") {};
};

void AddEventListener(EventListener* newListener, EventType criterion);
void AddEventListener(EventListener* newListener);
void RemoveEventListener(EventListener* removee);

class EventListener
{
public:
	std::vector <EventType> typeCriterion;
protected:
	virtual void EventResponse(EVENT eventNotice)
	{
		//WriteDebug("Recieved Event:" + eventNotice.data.GetString("TestEvent"));
	};

public:
	void BASEEventResponse(EVENT e) { EventResponse(e); }

	EventListener(std::vector<EventType> crit) : typeCriterion(crit) {};
	EventListener() {};
	virtual ~EventListener() { RemoveEventListener(this); }
};

class EventSender
{

	std::vector<EventListener*> listeners;
	std::vector<EVENT> eventQueue;
	EVENT currEvent;
public:

	EventSender() {};
	void QueueEvent(EVENT e)
	{
		eventQueue.push_back(e);
	};
	void SendQueuedEvents()
	{
		if (eventQueue.size() > 0)
		{
			while (eventQueue.size() > 0)
			{
				SendEventImmediately(*eventQueue.begin());
				eventQueue.erase(eventQueue.begin());
			}
		}
		else
		{
			//WriteDebug("No Events to send.");
		}
	}
	void SendEventImmediately(EVENT eventNotice)
	{
		currEvent = eventNotice;
		for (unsigned int i = 0; i < listeners.size(); i++)
			if (!none_of(listeners[i]->typeCriterion.begin(), listeners[i]->typeCriterion.end(), [=](EventType eT) {return eT == eventNotice.Etype; }))
			{
				EventListener* p = &(*listeners[i]);
				p->BASEEventResponse(currEvent);
			}
	}
	void AddListener(EventListener* newLis)
	{
		//WriteDebug("Adding listener " + std::to_string(listeners.size()));
		if (none_of(listeners.begin(), listeners.end(), [=](EventListener* e) {return e == newLis; }))
			listeners.push_back(newLis);
		//else { WriteDebug("Already contains that listener."); }
	}
	void RemoveListener(EventListener* removee)
	{
		//WriteDebug("Removing listener " + std::to_string(listeners.size()));

		for (unsigned int i = 0; i < listeners.size(); i++)
		{
			if (listeners[i] == removee)
			{
				listeners.erase(listeners.begin() + i);
				//WriteDebug("Removed listener " + std::to_string(listeners.size()));
			}
		}
	}
	int GetTotalListeners() { return (int)listeners.size(); };
};
void EventManagerUpdate();
void QueueEvent(EVENT);
void SendEventImmediately(EVENT e);
void AddEventListener(EventListener* newListener, EventType criterion);
void AddEventListener(EventListener* newListener);
void RemoveEventListener(EventListener* removee);
void EventStartup();


#pragma endregion

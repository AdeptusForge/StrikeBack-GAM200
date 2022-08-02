#include "Events.h"

EventSender globalEventManager;
void EventManagerUpdate()
{
	globalEventManager.SendQueuedEvents();
};
void QueueEvent(EVENT e)
{
	globalEventManager.QueueEvent(e);
	//WriteDebug(std::to_string(globalEventManager.GetTotalListeners()));
}
void SendEventImmediately(EVENT e)
{
	globalEventManager.SendEventImmediately(e);
}
void AddEventListener(EventListener* newListener, EventType criterion)
{
	globalEventManager.AddListener(newListener);
	newListener->typeCriterion.push_back(criterion);
	//WriteDebug(std::to_string(globalEventManager.GetTotalListeners()));
}
void AddEventListener(EventListener* newListener)
{
	globalEventManager.AddListener(newListener);
	//WriteDebug(std::to_string(globalEventManager.GetTotalListeners()));
}
void RemoveEventListener(EventListener* removee)
{
	globalEventManager.RemoveListener(removee);
}
void EventStartup()
{
	globalEventManager = EventSender();
	EventManagerUpdate();
}
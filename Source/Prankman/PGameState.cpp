#include "PGameState.h"

#include "log.h"

void APGameState::BeginPlay()
{
}

void APGameState::OnEvent()
{

}

void APGameState::ClientStartEvent_Implementation(EPEventType EventType)
{
    EventDelegate.Broadcast(EventType);
}
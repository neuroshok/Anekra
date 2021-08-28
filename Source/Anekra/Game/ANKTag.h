#pragma once
#include "GameplayTagContainer.h"

struct ANKTag_
{
    struct Event_
    {
        FGameplayTag Snake = FGameplayTag::RequestGameplayTag("Event.Snake");
    } Event;
} ANKTag;
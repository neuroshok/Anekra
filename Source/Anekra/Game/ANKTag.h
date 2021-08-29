#pragma once
#include "GameplayTagContainer.h"
/*
        FGameplayTag Snake = FGameplayTag::RequestGameplayTag("Event.Snake");
    } Event;

    struct FState
    {
        FGameplayTag Dead = FGameplayTag::RequestGameplayTag("State.Dead");
        FGameplayTag Moving = FGameplayTag::RequestGameplayTag("State.Moving");
*/

static struct FANKTag
{
    static auto Get(const char* Tag) { return FGameplayTag::RequestGameplayTag(Tag); }

    struct FAbility
    {
        //FGameplayTag Unlock;
        const char* Unlock = "Ability.Unlock";
    } Ability;

    struct FEvent
    {
        const char* Snake = "Event.Snake";
    } Event;

    struct FState
    {
        const char* Dead = "State.Dead";
        const char* Moving = "State.Moving";
    } State;
} ANKTag;
#pragma once

#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"

#define InitTag(Name) Name = Manager.AddNativeGameplayTag(#Name)

static struct ANEKRA_API FANKTag : public FGameplayTagNativeAdder
{
    struct
    {
        FGameplayTag Unlock;
    } Ability;

    struct
    {
        FGameplayTag Snake;
    } Event;

    struct
    {
        FGameplayTag Dead;
        FGameplayTag Moving;
    } State;

protected:
    virtual void AddTags() override
    {
        UGameplayTagsManager& Manager = UGameplayTagsManager::Get();

        InitTag(Ability.Unlock);

        InitTag(Event.Snake);

        InitTag(State.Dead);
        InitTag(State.Moving);
    }
} ANKTag;
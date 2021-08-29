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
        FGameplayTag Burn;
        FGameplayTag Freeze;
        FGameplayTag Heal;
    } Effect;

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

        InitTag(Effect.Burn);
        InitTag(Effect.Freeze);
        InitTag(Effect.Heal);

        InitTag(Event.Snake);

        InitTag(State.Dead);
        InitTag(State.Moving);
    }
} ANKTag;
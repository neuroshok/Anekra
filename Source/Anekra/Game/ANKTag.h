#pragma once

#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"

#define InitRoot(Name) Name.Root = Manager.AddNativeGameplayTag(#Name)
#define InitTag(Name) Name = Manager.AddNativeGameplayTag(#Name)
#define InitTagAndCue(Name) Name = Manager.AddNativeGameplayTag(#Name); GC.Name = Manager.AddNativeGameplayTag("GameplayCue." #Name)

static struct ANEKRA_API FANKTag : public FGameplayTagNativeAdder
{
    struct
    {
        struct
        {
            FGameplayTag Freeze;
            FGameplayTag CrossFire;
            FGameplayTag Stealth;
        } Ability;
    } GC;

    //

    struct
    {
        FGameplayTag Root;
        FGameplayTag CrossFire;
        FGameplayTag Freeze;
        FGameplayTag Unlock;
        FGameplayTag Stealth;
        FGameplayTag StealthCue;
    } Ability;

    struct
    {
        FGameplayTag Burn;
        FGameplayTag Freeze;
        FGameplayTag Heal;
    } Effect;

    struct
    {
        FGameplayTag Root;
        FGameplayTag FindCell;
        FGameplayTag Snake;
    } Event;

    struct
    {
        FGameplayTag Casting;
        FGameplayTag Dead;
        FGameplayTag Moving;
    } State;

protected:
    virtual void AddTags() override
    {
        UGameplayTagsManager& Manager = UGameplayTagsManager::Get();

        InitRoot(Ability);
        InitTagAndCue(Ability.Freeze);
        InitTagAndCue(Ability.Stealth);
        InitTagAndCue(Ability.CrossFire);
        InitTag(Ability.Unlock);

        InitTag(Effect.Burn);
        InitTag(Effect.Freeze);
        InitTag(Effect.Heal);

        InitRoot(Event);
        InitTag(Event.FindCell);
        InitTag(Event.Snake);

        InitTag(State.Casting);
        InitTag(State.Dead);
        InitTag(State.Moving);
    }
} ANKTag;

#undef InitRoot
#undef InitTag
#undef InitTagAndCue
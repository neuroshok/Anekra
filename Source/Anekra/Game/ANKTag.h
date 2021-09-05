#pragma once

#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"

#define InitRoot(Name) Name.Root = Manager.AddNativeGameplayTag(#Name)
#define InitTag(Name) Name = Manager.AddNativeGameplayTag(#Name)
#define InitTagAndCue(Name) Name = Manager.AddNativeGameplayTag(#Name); Name##Cue = Manager.AddNativeGameplayTag("GameplayCue." #Name)

#define Tag(Name) FGameplayTag Name
#define TagCue(Name) FGameplayTag Name; FGameplayTag Name##Cue

static struct ANEKRA_API FANKTag : public FGameplayTagNativeAdder
{
    struct
    {
        Tag(Root);
        TagCue(CrossFire);
        TagCue(Drain);
        TagCue(Freeze);
        TagCue(LaserBurst);
        Tag(Unlock);
        TagCue(Stealth);
    } Ability;

    struct
    {
        Tag(Burn);
        Tag(Damage);
        Tag(Freeze);
        Tag(Heal);
    } Effect;

    struct
    {
        Tag(Root);
        Tag(FindCell);
        Tag(Snake);
    } Event;

    struct
    {
        Tag(Casting);
        Tag(Dead);
        Tag(Moving);
    } State;

protected:
    virtual void AddTags() override
    {
        UGameplayTagsManager& Manager = UGameplayTagsManager::Get();

        InitRoot(Ability);
        InitTagAndCue(Ability.Drain);
        InitTagAndCue(Ability.Freeze);
        InitTagAndCue(Ability.LaserBurst);
        InitTagAndCue(Ability.Stealth);
        InitTagAndCue(Ability.CrossFire);
        InitTag(Ability.Unlock);

        InitTag(Effect.Burn);
        InitTag(Effect.Damage);
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
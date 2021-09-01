#pragma once

#include "Anekra/Game/ANKAbilitySystemComponent.h"
#include "Anekra/Player/Hero.h"
#include "Anekra/Player/ANKPlayerState.h"
#include "Anekra/Player/ANKPlayerController.h"
#include "Anekra/Asset/MontageAsset.h"

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Ability.generated.h"

UCLASS()
class ANEKRA_API UAbility : public UGameplayAbility
{
    GENERATED_BODY()

public:
    UAbility();

    UEffectAsset* GetEffects();
    UMontageAsset* GetMontages();
    AHero* GetHero();
    AANKPlayerState* GetANKPlayerState();
    AANKPlayerController* GetANKPlayerController();

protected:
    UANKAbilitySystemComponent* GetAbilitySystemComponent();
};
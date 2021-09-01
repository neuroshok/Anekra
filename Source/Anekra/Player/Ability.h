#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Anekra/Game/ANKAbilitySystemComponent.h"
#include "Ability.generated.h"

UCLASS()
class ANEKRA_API UAbility : public UGameplayAbility
{
    GENERATED_BODY()

public:
    UAbility();

    class AHero* GetHero();
    class ANKPlayerState* GetANKPlayerState();
    class ANKPlayerController* GetANKPlayerController();

protected:
    UANKAbilitySystemComponent* GetAbilitySystemComponent();
};
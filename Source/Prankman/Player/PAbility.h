#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Prankman/Game/PAbilitySystemComponent.h"
#include "PAbility.generated.h"

UCLASS()
class PRANKMAN_API UPAbility : public UGameplayAbility
{
    GENERATED_BODY()

public:
    UPAbility();

protected:
    class UPAbilitySystemComponent* GetAbilitySystemComponent();
};
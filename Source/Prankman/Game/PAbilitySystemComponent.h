#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "UObject/Object.h"
#include "PAbilitySystemComponent.generated.h"

UCLASS()
class PRANKMAN_API UPAbilitySystemComponent : public UAbilitySystemComponent
{
    GENERATED_BODY()

public:
    virtual void BindAbilityActivationToInputComponent(UInputComponent* InputComponent, FGameplayAbilityInputBinds BindInfo) override;

private:
    bool BoundAbilities = false;
};
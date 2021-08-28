#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Anekra/Asset/EffectAsset.h"
#include "UObject/Object.h"
#include "ANKAbilitySystemComponent.generated.h"

UCLASS(BlueprintType, Blueprintable)
class ANEKRA_API UANKAbilitySystemComponent : public UAbilitySystemComponent
{
    GENERATED_BODY()

    UANKAbilitySystemComponent();

public:
    virtual void BeginPlay() override;
    virtual void BindAbilityActivationToInputComponent(UInputComponent* InputComponent, FGameplayAbilityInputBinds BindInfo) override;

    void ApplyEffect(TSubclassOf<UGameplayEffect>);
    void RemoveEffect(const FGameplayTag&);

    UPROPERTY()
    UEffectAsset* Effects = nullptr;

private:
    bool BoundAbilities = false;
};
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ANKTag.h"
#include "Anekra/Asset/EffectAsset.h"
#include "UObject/Object.h"
#include "ANKAbilitySystemComponent.generated.h"

UCLASS(BlueprintType, Blueprintable)
class ANEKRA_API UANKAbilitySystemComponent : public UAbilitySystemComponent
{
    GENERATED_BODY()

    UANKAbilitySystemComponent();

public:
    virtual void BindAbilityActivationToInputComponent(UInputComponent* InputComponent, FGameplayAbilityInputBinds BindInfo) override;

    void AddTag(const char*);
    void RemoveTag(const char*);

    void ApplyEffect(TSubclassOf<UGameplayEffect>);
    FGameplayEffectSpecHandle ApplyEffectSpec(TSubclassOf<UGameplayEffect>);
    void RemoveEffectByTag(const char*);

    UPROPERTY()
    UEffectAsset* Effects = nullptr;

protected:
    virtual void BeginPlay() override;

private:
    bool BoundAbilities = false;
};
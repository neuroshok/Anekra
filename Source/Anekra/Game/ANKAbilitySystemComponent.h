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

    void AddTag(const FGameplayTag&);
    void RemoveTag(const FGameplayTag&);

    void ApplyEffect(TSubclassOf<UGameplayEffect>);

    FGameplayEffectSpecHandle ApplyEffectSpec(TSubclassOf<UGameplayEffect>, const FGameplayTag& Tag, float Magnitude);
    void RemoveEffectByTag(const FGameplayTag&);

    void ExecuteLocalCue(const FGameplayTag& GameplayCueTag, AActor* Target = nullptr, const FGameplayCueParameters& GameplayCueParameters = FGameplayCueParameters{});
    void AddLocalCue(const FGameplayTag& GameplayCueTag, AActor* Target = nullptr, const FGameplayCueParameters& GameplayCueParameters = FGameplayCueParameters{});
    void RemoveLocalCue(const FGameplayTag& GameplayCueTag, AActor* Target = nullptr, const FGameplayCueParameters& GameplayCueParameters = FGameplayCueParameters{});

    UPROPERTY()
    UEffectAsset* Effects = nullptr;

protected:
    virtual void BeginPlay() override;

};
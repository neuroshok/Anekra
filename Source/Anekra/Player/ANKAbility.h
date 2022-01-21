#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Anekra/Asset/AbilityAsset.h"
#include "ANKAbility.generated.h"

UCLASS()
class ANEKRA_API UANKAbility : public UGameplayAbility
{
    GENERATED_BODY()

public:
    UANKAbility();

    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;



    UFUNCTION(BlueprintCallable, Category = "Anekra")
    class UEffectAsset* GetEffects();
    UFUNCTION(BlueprintCallable, Category = "Anekra")
    class UAbilityAsset* GetAbilities();
    UFUNCTION(BlueprintCallable, Category = "Anekra")
    class AHero* GetHero() const;
    UFUNCTION(BlueprintCallable, Category = "Anekra")
    class AANKPlayerState* GetANKPlayerState() const;
    UFUNCTION(BlueprintCallable, Category = "Anekra")
    class AANKPlayerController* GetANKPlayerController() const;
    UFUNCTION(BlueprintCallable, Category = "Anekra")
    class UANKGameInstance* GetANKGameInstance() const;
    UFUNCTION(BlueprintCallable, Category = "Anekra")
    class AANKGameState* GetANKGameState() const;

    struct FAbilityData* Data = nullptr;
    bool bAutoRemove = true;

protected:
    class UANKAbilitySystemComponent* GetAbilitySystemComponent();
};
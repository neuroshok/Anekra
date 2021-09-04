#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpec.h"
#include "GameFramework/PlayerController.h"
#include "ANKPlayerController.generated.h"

UCLASS()
class ANEKRA_API AANKPlayerController : public APlayerController
{
    GENERATED_BODY()

    DECLARE_MULTICAST_DELEGATE(FOnAbilitiesUpdateDelegate)

public:
    void InitializeHUD();

    UFUNCTION(BlueprintCallable)
    void AddAbility(int AbilityID);
    UFUNCTION(BlueprintCallable)
    void RemoveAbility(FGameplayAbilitySpecHandle Handle);
    UFUNCTION(BlueprintCallable)
    void NotifyError(FString Message);

    void Unlock();

    UFUNCTION()
    void OnAbilitiesUpdated();

    FOnAbilitiesUpdateDelegate OnAbilitiesUpdateDelegate;

    UFUNCTION(BlueprintCallable)
    int GetAbilitiesCountMax() { return AbilitiesCountMax; }
    UFUNCTION(BlueprintCallable)
    int GetAbilitiesCount() { return AbilitiesCount; }
    UFUNCTION(BlueprintCallable)
    const TArray<int>& GetAbilities() { return Abilities; }

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    int AbilitiesCountMax = 4;

protected:
    virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
    UPROPERTY(Replicated, ReplicatedUsing = OnAbilitiesUpdated)
    TArray<int> Abilities;

    UPROPERTY(Replicated)
    int AbilitiesCount = 0;

    TMap<FGameplayAbilitySpecHandle, int> Slots;
};
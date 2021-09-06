#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpec.h"
#include "GameFramework/PlayerController.h"
#include "ANKPlayerController.generated.h"

UCLASS()
class ANEKRA_API AANKPlayerController : public APlayerController
{
    GENERATED_BODY()

    DECLARE_MULTICAST_DELEGATE(FClickDelegate);
    DECLARE_MULTICAST_DELEGATE(FOnAbilitiesUpdateDelegate)

public:
    virtual void SetupInputComponent() override;

    void InitializeHUD();

    UFUNCTION(BlueprintCallable, Category = "Anekra")
    void AddAbility(int AbilityID);
    UFUNCTION(BlueprintCallable, Category = "Anekra")
    void RemoveAbility(FGameplayAbilitySpecHandle Handle);
    UFUNCTION(BlueprintCallable, Category = "Anekra")
    void NotifyError(FString Message);

    void Unlock();

    void OnClick();
    void OnTabPressed();
    void OnTabReleased();

    UFUNCTION()
    void OnAbilitiesUpdated();

    FOnAbilitiesUpdateDelegate OnAbilitiesUpdateDelegate;
    FClickDelegate ClickDelegate;

    UFUNCTION(BlueprintCallable, Category = "Anekra")
    int GetAbilitiesCountMax() { return AbilitiesCountMax; }
    UFUNCTION(BlueprintCallable, Category = "Anekra")
    int GetAbilitiesCount() { return AbilitiesCount; }
    UFUNCTION(BlueprintCallable, Category = "Anekra")
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
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Prankman/PAbilityType.h"
#include "PPlayerController.generated.h"

UCLASS()
class PRANKMAN_API APPlayerController : public APlayerController
{
    GENERATED_BODY()

    DECLARE_MULTICAST_DELEGATE(FOnAbilitiesUpdateDelegate)

public:
    void InitializeHUD();

    void AddAbility(EPAbilityType);
    void NotifyError(FString);

    void Unlock();

    UFUNCTION()
    void OnAbilitiesUpdated();

    FOnAbilitiesUpdateDelegate OnAbilitiesUpdateDelegate;

protected:
    virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
    UPROPERTY(Replicated, ReplicatedUsing = OnAbilitiesUpdated)
    TArray<EPAbilityType> Abilities;
};
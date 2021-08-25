#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Anekra/AbilityType.h"
#include "ANKPlayerController.generated.h"

UCLASS()
class ANEKRA_API AANKPlayerController : public APlayerController
{
    GENERATED_BODY()

    DECLARE_MULTICAST_DELEGATE(FOnAbilitiesUpdateDelegate)

public:
    void InitializeHUD();

    void AddAbility(EAbilityType);
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
    TArray<EAbilityType> Abilities;
};
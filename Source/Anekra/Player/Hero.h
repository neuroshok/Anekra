#pragma once

#include "AbilitySystemInterface.h"
#include "Camera/CameraComponent.h"
#include "Anekra/Game/ANKAbilitySystemComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Hero.generated.h"

class USpringArmComponent;

UCLASS()
class ANEKRA_API AHero final : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    AHero();

    virtual void OnRep_PlayerState() override;
    virtual void PossessedBy(AController*) override;
    virtual void SetupPlayerInputComponent(UInputComponent*) override;
    virtual class UANKAbilitySystemComponent* GetAbilitySystemComponent() const override;
    void UpdateMovingTag();

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    class UAnimMontage* UnlockMontage;

protected:
    virtual void BeginPlay() override;
    virtual void AddMovementInput(FVector WorldDirection, float ScaleValue = 1.0f, bool bForce = false) override;

    void MoveForward(float);
    void MoveBackward(float);
    void MoveLeft(float);
    void MoveRight(float);
    void MoveYaw(float);
    void MovePitch(float);

private:
    void TryBindAbilities();

    TWeakObjectPtr<class UANKAbilitySystemComponent> ANKAbilitySystemComponent;

    UPROPERTY()
    class USpringArmComponent* SpringArmComponent;
    UPROPERTY()
    class UCameraComponent* Camera;

    bool bHasMovingEffect = false;
};
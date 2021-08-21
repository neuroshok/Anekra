// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "Camera/CameraComponent.h"

#include "CoreMinimal.h"
#include "GameplayAbilitySpec.h"
#include "GameFramework/Character.h"
#include "PHero.generated.h"

class USpringArmComponent;

UCLASS()
class PRANKMAN_API APHero final : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    APHero();

    virtual void OnRep_PlayerState() override;
    virtual void PossessedBy(AController*) override;
    virtual void SetupPlayerInputComponent(UInputComponent*) override;
    virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Prankman")
    TSubclassOf<class UGameplayEffect> UnlockEffect;

protected:
    virtual void BeginPlay() override;

    void MoveForward(float);
    void MoveBackward(float);
    void MoveLeft(float);
    void MoveRight(float);
    void MoveYaw(float);
    void MovePitch(float);

private:
    void TryBindAbilities();

    TWeakObjectPtr<class UPAbilitySystemComponent> PAbilitySystemComponent;

    UPROPERTY()
    class USpringArmComponent* SpringArmComponent;
    UPROPERTY()
    class UCameraComponent* Camera;
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "PHero.generated.h"

class USpringArmComponent;
UCLASS()
class PRANKMAN_API APHero final : public ACharacter
{
    GENERATED_BODY()

public:
    APHero();

protected:
    virtual void BeginPlay() override;

    void MoveForward(float);
    void MoveBackward(float);
    void MoveLeft(float);
    void MoveRight(float);
    void MoveYaw(float);
    void MovePitch(float);

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
    class USpringArmComponent* SpringArmComponent;
    class UCameraComponent* Camera;
};
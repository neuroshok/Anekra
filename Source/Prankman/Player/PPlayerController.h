// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PPlayerController.generated.h"

UCLASS()
class PRANKMAN_API APPlayerController : public APlayerController
{
    GENERATED_BODY()

public:

protected:
    virtual void BeginPlay() override;

private:

};
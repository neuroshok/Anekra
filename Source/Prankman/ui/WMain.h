// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WMain.generated.h"

/**
 * 
 */
UCLASS()
class PRANKMAN_API UWMain : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
    class UTextBlock* WEventText;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
    class UProgressBar* WHealth;
};
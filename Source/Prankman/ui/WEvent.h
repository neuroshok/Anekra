// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "WEvent.generated.h"

UCLASS()
class PRANKMAN_API UWEvent : public UUserWidget
{
    GENERATED_BODY()

protected:
    void NativeConstruct() override;

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
    class UTextBlock* WEventText;
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
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
    UFUNCTION()
    void OnStartCasting(float Duration);


    void OnUpdateHealth(const FOnAttributeChangeData&);

    //

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
    class UTextBlock* WEventText;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
    class UProgressBar* WCastBar;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
    class UProgressBar* WHealth;

protected:
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
    bool bCasting = false;
    float CastProgress;
    float CastDuration;
};
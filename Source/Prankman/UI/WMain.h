#pragma once

#include "GameplayEffectTypes.h"
#include "Prankman/PEventType.h"

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
    UFUNCTION()
    void OnCasting(float Duration);


    void OnAbilitiesUpdated();
    void OnEventUpdated(EPEventType Type/*, EventData*/);
    void OnHealthUpdated(const FOnAttributeChangeData&);

    //

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
    class UTextBlock* WEventText;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
    class UTextBlock* WMessage;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
    class UProgressBar* WCastBar;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
    class UProgressBar* WHealth;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
    class UHorizontalBox* WAbilityBox;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TSubclassOf<UUserWidget> BP_WAbility;

protected:
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
    virtual void NativeOnInitialized() override;

private:
    bool bCasting = false;
    float CastProgress;
    float CastDuration;
};
#pragma once

#include "GameplayEffectTypes.h"

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Blueprint/UserWidget.h"
#include "WMain.generated.h"

UCLASS()
class ANEKRA_API UWMain : public UUserWidget
{
    GENERATED_BODY()

public:
    void OnCasting(float Duration);
    void OnCastingCancelled();

    void OnAbilitiesUpdated();
    void OnEventUpdated(FGameplayTag Tag, int32 Count);
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

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TSubclassOf<UUserWidget> BP_WAbility;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TSubclassOf<UUserWidget> BP_WLog;

protected:
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
    virtual void NativeOnInitialized() override;

private:
    bool bCasting = false;
    float CastProgress;
    float CastDuration;
};
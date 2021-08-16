#include "WMain.h"

#include "GameplayEffectTypes.h"
#include "Components/ProgressBar.h"
#include "Prankman/Player/PPlayerState.h"


void UWMain::NativeTick(const FGeometry& MovieSceneBlends, float InDeltaTime)
{
    Super::NativeTick(MovieSceneBlends, InDeltaTime);
    if (bCasting)
    {
        CastProgress += InDeltaTime;
        WCastBar->SetPercent(CastProgress / CastDuration);
        if (CastProgress >= CastDuration)
        {
            bCasting = false;
            CastProgress = 0;
            WCastBar->SetVisibility(ESlateVisibility::Hidden);
        }
    }
}

void UWMain::OnStartCasting(float Duration)
{
    WCastBar->SetPercent(0);
    WCastBar->SetVisibility(ESlateVisibility::Visible);
    CastDuration = Duration;
    bCasting = true;
}

void UWMain::OnUpdateHealth(const FOnAttributeChangeData& Data)
{
    WHealth->SetPercent(Data.NewValue / 100);
}
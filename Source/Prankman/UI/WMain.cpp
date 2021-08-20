#include "WMain.h"

#include "GameplayEffectTypes.h"
#include "WAbility.h"
#include "Brushes/SlateImageBrush.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Prankman/log.h"
#include "Prankman/PEventType.h"
#include "Prankman/Game/PGameInstance.h"
#include "Prankman/Player/PPlayerController.h"

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

void UWMain::NativeOnInitialized()
{
    Super::NativeOnInitialized();
}

void UWMain::OnCasting(float Duration)
{
    WCastBar->SetPercent(0);
    WCastBar->SetVisibility(ESlateVisibility::Visible);
    CastDuration = Duration;
    bCasting = true;
}

void UWMain::OnAbilitiesUpdated()
{
    auto Abilities = Cast<APPlayerController>(GetOwningPlayer())->Abilities;

    WAbilityBox->ClearChildren();
    for (int i = 0; i < Abilities.Num(); ++i)
    {
        auto WAbility = CreateWidget<UWAbility>(GetWorld(), BP_WAbility);
        WAbility->SetImage(static_cast<EPAbilityType>(Abilities[i]));
        WAbilityBox->AddChild(WAbility);
    }
}

void UWMain::OnEventUpdated(EPEventType Type/*, EventData*/)
{
    UE_LOG(LogTemp, Warning, TEXT("OnEvent"))
    FText EventText;
    switch (Type)
    {
    /*case EPEventType::FindColor:
        EventText = FText::Format(FText::FromString("Find a {} cell !"), (int)Type);
        break;
    case EPEventType::StopMove:
        EventText = FText::FromString("Stop move !");
        break;*/
        case EPEventType::Snake:
        EventText = FText::FromString("Snake: don't touch a colored cell !");
        break;
    default:
        WEventText->SetVisibility(ESlateVisibility::Hidden);
    }

    WEventText->SetText(EventText);
    WEventText->SetVisibility(ESlateVisibility::Visible);
}

void UWMain::OnHealthUpdated(const FOnAttributeChangeData& Data)
{
    WHealth->SetPercent(Data.NewValue / 100);
}
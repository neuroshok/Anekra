#include "WMain.h"

#include "GameplayEffectTypes.h"
#include "WAbility.h"
#include "Brushes/SlateImageBrush.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Anekra/Game/ANKTag.h"
#include "Anekra/EventType.h"
#include "Anekra/Game/ANKGameInstance.h"
#include "Anekra/Game/Event/SnakeEvent.h"
#include "Anekra/Player/ANKPlayerController.h"
#include "Anekra/Player/ANKPlayerState.h"

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
    CastProgress = 0;
    WCastBar->SetVisibility(ESlateVisibility::Visible);
    CastDuration = Duration;
    bCasting = true;
}

void UWMain::OnCastingCancelled()
{
    WCastBar->SetVisibility(ESlateVisibility::Hidden);
    bCasting = false;
}



void UWMain::OnAbilitiesUpdated()
{
    auto& Abilities = Cast<AANKPlayerController>(GetOwningPlayer())->GetAbilities();

    WAbilityBox->ClearChildren();
    for (int i = 0; i < Abilities.Num(); ++i)
    {
        auto WAbility = CreateWidget<UWAbility>(GetWorld(), BP_WAbility);
        WAbility->SetImage(Abilities[i]);
        WAbilityBox->AddChild(WAbility);
    }
}

void UWMain::OnEventUpdated(FGameplayTag Tag, int32 Count)
{
    FText EventText;
    WEventText->SetVisibility(ESlateVisibility::Hidden);

    FGameplayTagContainer Tags;
    Cast<AANKPlayerState>(GetOwningPlayerState())->GetAbilitySystemComponent()->GetOwnedGameplayTags(Tags);

    if (Tags.HasTagExact(ANKTag.Event.Snake))
    {
        EventText = FText::FromString("Snake: don't touch a colored cell !");
    }
    else if (Tags.HasTagExact(ANKTag.Event.FindCell))
    {
        EventText = FText::FromString("FindCell: go over a marked cell !");
    }


    WEventText->SetText(EventText);
    WEventText->SetVisibility(ESlateVisibility::Visible);
}

void UWMain::OnHealthUpdated(const FOnAttributeChangeData& Data)
{
    WHealth->SetPercent(Data.NewValue / 100);
}
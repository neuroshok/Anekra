#include "PHUD.h"

#include "PGameState.h"
#include "PPlayerState.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "ui/WMain.h"

void APHUD::BeginPlay()
{
    Super::BeginPlay();
    check(BP_WMain);

    auto gameState = Cast<APGameState>(GetWorld()->GetGameState());
    check(gameState);

    WMain = CreateWidget<UWMain>(GetWorld(), BP_WMain);
    check(WMain);
    WMain->AddToViewport();

    FInputModeGameOnly Mode;
    GetOwningPlayerController()->SetInputMode(Mode);

    WMain->WEventText->SetVisibility(ESlateVisibility::Hidden);
    WMain->WCastBar->SetVisibility(ESlateVisibility::Hidden);

    gameState->UpdateEventDelegate.AddDynamic(this, &APHUD::OnUpdateEvent);
    gameState->UpdateHealthDelegate.AddDynamic(WMain, &UWMain::OnUpdateHeal);
}

void APHUD::OnUpdateEvent(EPEventType Type/*, EventData*/)
{
    UE_LOG(LogTemp, Warning, TEXT("OnEvent"))
    FText EventText;
    switch (Type)
    {
        case EPEventType::FindColor:
            EventText = FText::Format(FText::FromString("Find a {} cell !"), (int)Type);
        break;
        case EPEventType::StopMove:
            EventText = FText::FromString("Stop move !");
        break;
        default: {
            WMain->WEventText->SetVisibility(ESlateVisibility::Hidden);
            return;
        };
    }

    WMain->WEventText->SetText(EventText);
    WMain->WEventText->SetVisibility(ESlateVisibility::Visible);
}
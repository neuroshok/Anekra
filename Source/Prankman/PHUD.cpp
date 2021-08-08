#include "PHUD.h"

#include "PGameState.h"
#include "Components/TextBlock.h"
#include "ui/WMain.h"

void APHUD::BeginPlay()
{
    check(BP_WMain);

    auto gameState = Cast<APGameState>(GetWorld()->GetGameState());
    check(gameState);
    gameState->EventDelegate.AddDynamic(this, &APHUD::OnEvent);

    WMain = CreateWidget<UWMain>(GetWorld(), BP_WMain);
    check(WMain);
    WMain->AddToViewport();
    FInputModeGameOnly Mode;
    GetOwningPlayerController()->SetInputMode(Mode);

    WMain->WEventText->SetVisibility(ESlateVisibility::Hidden);
}

void APHUD::OnEvent(EPEventType Type/*, EventData*/)
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
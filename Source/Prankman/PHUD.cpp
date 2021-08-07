#include "PHUD.h"

#include "PGameState.h"
#include "Components/TextBlock.h"
#include "ui/WEvent.h"

void APHUD::BeginPlay()
{
    check(BP_WEvent);

    auto gameState = Cast<APGameState>(GetWorld()->GetGameState());
    check(gameState);
    gameState->EventDelegate.AddDynamic(this, &APHUD::OnEvent);

    WEvent = CreateWidget<UWEvent>(GetWorld(), BP_WEvent);
	check(WEvent);
    WEvent->SetVisibility(ESlateVisibility::Hidden);
    WEvent->AddToViewport();
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
            WEvent->SetVisibility(ESlateVisibility::Hidden);
            return;
        };
    }

    WEvent->WEventText->SetText(EventText);
    WEvent->SetVisibility(ESlateVisibility::Visible);
}
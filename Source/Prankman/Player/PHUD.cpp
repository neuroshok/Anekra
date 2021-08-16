#include "PHUD.h"

#include "AbilitySystemComponent.h"
#include "PPlayerController.h"
#include "Attribute/PBasic.h"
#include "Prankman/Game/PGameState.h"
#include "Prankman/Player/PPlayerState.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Prankman/log.h"
#include "Prankman/UI/WMain.h"


void APHUD::Initialize()
{
    // wait for replication

}

void APHUD::BeginPlay()
{
    Super::BeginPlay();

    check(BP_WMain);
    auto PPlayerController = Cast<APPlayerController>(GetOwningPlayerController());

    WMain = CreateWidget<UWMain>(GetWorld(), BP_WMain);
    check(WMain);
    WMain->AddToViewport();

    FInputModeGameOnly Mode;
    GetOwningPlayerController()->SetInputMode(Mode);

    WMain->WEventText->SetVisibility(ESlateVisibility::Hidden);
    WMain->WCastBar->SetVisibility(ESlateVisibility::Hidden);

    PPlayerController->OnCastingDelegate.AddUObject(WMain, &UWMain::OnStartCasting);

    // fix: wait valid playerstate
    auto PPlayerState = GetOwningPlayerController()->GetPlayerState<APPlayerState>();
    check(PPlayerState);
    PPlayerState->GetAbilitySystemComponent()
        ->GetGameplayAttributeValueChangeDelegate(PPlayerState->PAttributeBasic->GetHealthAttribute())
        .AddUObject(WMain, &UWMain::OnUpdateHealth);
}

void APHUD::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if (!bInitialized)
    {
        Initialize();
        bInitialized = true;
    }
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
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
    auto PPlayerState = GetOwningPlayerController()->GetPlayerState<APPlayerState>();
    auto GameState = Cast<APGameState>(GetWorld()->GetGameState());

    if (PPlayerState && GameState)
    {
        GameState->OnEventDelegate.AddUObject(WMain, &UWMain::OnEventUpdated);

        PPlayerState->GetAbilitySystemComponent()
            ->GetGameplayAttributeValueChangeDelegate(PPlayerState->PAttributeBasic->GetHealthAttribute())
            .AddUObject(WMain, &UWMain::OnHealthUpdated);

        PPlayerState->OnCastingDelegate.AddUObject(WMain, &UWMain::OnCasting);

        Cast<APPlayerController>(GetOwningPlayerController())->OnAbilitiesUpdateDelegate.AddUObject(WMain, &UWMain::OnAbilitiesUpdated);

        bInitialized = true;
    }
}

void APHUD::Error(FString Message)
{
    WMain->WMessage->SetText(FText::FromString(Message));
    WMain->WMessage->SetVisibility(ESlateVisibility::Visible);
    GetWorld()->GetTimerManager().SetTimer(MessageTimer, [this]{ WMain->WMessage->SetVisibility(ESlateVisibility::Hidden); }, 1, false);
}

void APHUD::BeginPlay()
{
    Super::BeginPlay();

    check(BP_WMain);

    WMain = CreateWidget<UWMain>(GetWorld(), BP_WMain);
    check(WMain);
    WMain->AddToViewport();

    FInputModeGameOnly Mode;
    GetOwningPlayerController()->SetInputMode(Mode);

    WMain->WEventText->SetVisibility(ESlateVisibility::Hidden);
    WMain->WCastBar->SetVisibility(ESlateVisibility::Hidden);
    WMain->WMessage->SetVisibility(ESlateVisibility::Hidden);

    Initialize();
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
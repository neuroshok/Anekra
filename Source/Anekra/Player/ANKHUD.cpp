#include "ANKHUD.h"

#include "Attribute/Basic.h"
#include "AbilitySystemComponent.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

#include "Anekra/Player/ANKPlayerController.h"
#include "Anekra/Game/ANKGameState.h"
#include "Anekra/Player/ANKPlayerState.h"
#include "Anekra/UI/WEndGame.h"
#include "Anekra/UI/WMain.h"
#include "Anekra/UI/WGameStats.h"


void AANKHUD::Initialize()
{
    // wait for replication
    auto ANKPlayerState = GetOwningPlayerController()->GetPlayerState<AANKPlayerState>();
    auto GameState = Cast<AANKGameState>(GetWorld()->GetGameState());

    if (ANKPlayerState && GameState)
    {
        auto ASC = ANKPlayerState->GetAbilitySystemComponent();
        //GameState->OnEventUpdateDelegate.AddUObject(WMain, &UWMain::OnEventUpdated);
        GameState->OnGameStatusUpdateDelegate.AddUObject(this, &AANKHUD::OnGameStatusUpdated);

        ASC->RegisterGameplayTagEvent(ANKTag.Event.Root).AddUObject(WMain, &UWMain::OnEventUpdated);

        ASC->GetGameplayAttributeValueChangeDelegate(ANKPlayerState->AttributeBasic->GetHealthAttribute())
            .AddUObject(WMain, &UWMain::OnHealthUpdated);

        ANKPlayerState->OnCastingDelegate.AddUObject(WMain, &UWMain::OnCasting);
        ANKPlayerState->OnCastingCancelDelegate.AddUObject(WMain, &UWMain::OnCastingCancelled);

        Cast<AANKPlayerController>(GetOwningPlayerController())->OnAbilitiesUpdateDelegate.AddUObject(WMain, &UWMain::OnAbilitiesUpdated);

        bInitialized = true;
    }
}

void AANKHUD::Error(FString Message)
{
    WMain->WMessage->SetText(FText::FromString(Message));
    WMain->WMessage->SetVisibility(ESlateVisibility::Visible);
    GetWorld()->GetTimerManager().SetTimer(MessageTimer, [this]{ WMain->WMessage->SetVisibility(ESlateVisibility::Hidden); }, 1, false);
}

void AANKHUD::ShowStats()
{
    WGameStats->SetVisibility(ESlateVisibility::Visible);
}

void AANKHUD::HideStats()
{
    WGameStats->SetVisibility(ESlateVisibility::Hidden);
}

void AANKHUD::OnGameStatusUpdated(EGameStatus Status)
{
    switch (Status)
    {
    case EGameStatus::Started:
        WMain->SetVisibility(ESlateVisibility::Visible);
        WEndGame->SetVisibility(ESlateVisibility::Hidden);
        break;
    case EGameStatus::Finished:
        WMain->SetVisibility(ESlateVisibility::Hidden);
        WEndGame->Update();
        WEndGame->SetVisibility(ESlateVisibility::Visible);
        ShowStats();
        GetOwningPlayerController()->SetInputMode(FInputModeUIOnly{});
        GetOwningPlayerController()->SetShowMouseCursor(true);
        break;
    }
}

void AANKHUD::BeginPlay()
{
    Super::BeginPlay();

    check(BP_WMain);

    WMain = CreateWidget<UWMain>(GetWorld(), BP_WMain);
    WMain->AddToViewport();

    WGameStats = CreateWidget<UWGameStats>(GetWorld(), BP_WGameStats);
    WGameStats->AddToViewport(1);
    WGameStats->SetVisibility(ESlateVisibility::Hidden);

    WEndGame = CreateWidget<UWEndGame>(GetWorld(), BP_WEndGame);
    WEndGame->AddToViewport(2);
    WEndGame->SetVisibility(ESlateVisibility::Hidden);

    FInputModeGameOnly Mode;
    GetOwningPlayerController()->SetInputMode(Mode);

    WMain->WEventText->SetVisibility(ESlateVisibility::Hidden);
    WMain->WCastBar->SetVisibility(ESlateVisibility::Hidden);
    WMain->WMessage->SetVisibility(ESlateVisibility::Hidden);

    Initialize();
}

void AANKHUD::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    /*
    if (!bInitialized)
    {
        Initialize();
        bInitialized = true;
    }*/
}
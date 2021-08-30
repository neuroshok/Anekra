#include "ANKHUD.h"

#include "AbilitySystemComponent.h"
#include "ANKPlayerController.h"
#include "Attribute/Basic.h"
#include "Anekra/Game/ANKGameState.h"
#include "Anekra/Player/ANKPlayerState.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Anekra/Log.h"
#include "Anekra/UI/WMain.h"


void AANKHUD::Initialize()
{
    // wait for replication
    auto ANKPlayerState = GetOwningPlayerController()->GetPlayerState<AANKPlayerState>();
    auto GameState = Cast<AANKGameState>(GetWorld()->GetGameState());

    if (ANKPlayerState && GameState)
    {
        auto ASC = ANKPlayerState->GetAbilitySystemComponent();
        //GameState->OnEventUpdateDelegate.AddUObject(WMain, &UWMain::OnEventUpdated);

        ASC->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag("Event")).AddUObject(WMain, &UWMain::OnEventUpdated);

        ASC->GetGameplayAttributeValueChangeDelegate(ANKPlayerState->PAttributeBasic->GetHealthAttribute())
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

void AANKHUD::BeginPlay()
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
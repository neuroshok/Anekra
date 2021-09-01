#include "SnakeEvent.h"

#include "Anekra/Game/ANKGameInstance.h"
#include "Anekra/Game/ANKGameMode.h"
#include "Anekra/Game/ANKGameState.h"
#include "Anekra/Player/ANKPlayerState.h"
#include "Anekra/World/Cell.h"

void USnakeEvent::Start()
{
    UEvent::Start();

    auto Effect = Cast<UANKGameInstance>(GetWorld()->GetGameInstance())->GetEffectAsset()->SnakeEffect;

    for (auto PlayerState : GetWorld()->GetGameState()->PlayerArray)
    {
        auto ANKPlayerState = Cast<AANKPlayerState>(PlayerState);

        ANKPlayerState->GetAbilitySystemComponent()->ApplyEffect(Effect);
    }
    float Duration = 0.f;
    bool Status = Effect.GetDefaultObject()->DurationMagnitude.GetStaticMagnitudeIfPossible(1, Duration);
    check(Status);

    // todo
    Delay(Duration, [this]
    {
        for (ACell* Cell : Cast<AANKGameMode>(GetWorld()->GetAuthGameMode())->GetCells())
        {
            Cell->SetColor({ 0.2, 0.2, 0.8 });
        }

        GetWorld()->GetGameState<AANKGameState>()->ClientUpdateEvent(EEventType::Snake, EEventPhase::Stop);
        UEvent::Complete();
    });
}
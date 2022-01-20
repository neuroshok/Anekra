#include "ReduceCellEvent.h"

#include "Anekra/Game/ANKGameState.h"
#include "Anekra/World/Cell.h"

void UReduceCellEvent::Start()
{
    UEvent::Start();

    for (auto Cell : Cast<AANKGameState>(GetWorld()->GetGameState())->GetCells())
    {
        Cell->SetActorRelativeScale3D({0.5, 0.5, 1});
    }

    Delay(3, [this]
    {
        // stop timer in gamemode
        if (!GetWorld()->bIsTearingDown)
        {
            for (auto Cell : Cast<AANKGameState>(GetWorld()->GetGameState())->GetCells())
            {
                Cell->SetActorRelativeScale3D({1, 1, 1});
            }
            UEvent::Complete();
        }
    });
}
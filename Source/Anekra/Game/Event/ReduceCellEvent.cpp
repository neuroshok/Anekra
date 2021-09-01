#include "ReduceCellEvent.h"

#include "Anekra/Game/ANKGameMode.h"
#include "Anekra/World/Cell.h"

void UReduceCellEvent::Start()
{
    UEvent::Start();

    for (auto Cell : Cast<AANKGameMode>(GetWorld()->GetAuthGameMode())->GetCells())
    {
        Cell->SetActorRelativeScale3D({0.5, 0.5, 1});
    }

    Delay(3, [this]
    {
        for (auto Cell : Cast<AANKGameMode>(GetWorld()->GetAuthGameMode())->GetCells())
        {
            Cell->SetActorRelativeScale3D({1, 1, 1});
        }
        UEvent::Complete();
    });
}
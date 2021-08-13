#include "WMain.h"

#include "Components/ProgressBar.h"
#include "Prankman/Player/PPlayerState.h"


void UWMain::OnUpdateHeal()
{
    if (!GetOwningPlayerState()) return;
    WHealth->SetPercent(Cast<APPlayerState>(GetOwningPlayerState())->Health);
}
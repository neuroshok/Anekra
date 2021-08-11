#include "WMain.h"

#include "Components/ProgressBar.h"
#include "Prankman/PPlayerState.h"



void UWMain::OnUpdateHeal()
{

    WHealth->SetPercent(Cast<APPlayerState>(GetOwningPlayerState())->Health);
}
#include "WAbility.h"

#include "Components/Image.h"
#include "Anekra/Game/ANKGameInstance.h"

void UWAbility::SetImage(int AbilityID)
{
    if (AbilityID == -1) return;
    WImage->SetBrushFromSoftTexture(Cast<UANKGameInstance>(GetGameInstance())->GetAbility(AbilityID)->Image);
}
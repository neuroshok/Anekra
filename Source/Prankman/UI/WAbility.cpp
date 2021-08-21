#include "WAbility.h"

#include "Components/Image.h"
#include "Prankman/Game/PGameInstance.h"

void UWAbility::SetImage(EPAbilityType AbilityID)
{
    WImage->SetBrushFromSoftTexture(Cast<UPGameInstance>(GetGameInstance())->GetBasicAsset()->GetAbility(AbilityID));
}
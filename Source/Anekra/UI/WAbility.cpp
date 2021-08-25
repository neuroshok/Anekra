#include "WAbility.h"

#include "Components/Image.h"
#include "Anekra/Game/ANKGameInstance.h"

void UWAbility::SetImage(EAbilityType AbilityID)
{
    WImage->SetBrushFromSoftTexture(Cast<UANKGameInstance>(GetGameInstance())->GetBasicAsset()->GetAbility(AbilityID));
}
#include "WAbility.h"

#include "Components/Image.h"
#include "Anekra/Game/ANKGameInstance.h"

void UWAbility::SetImage(EAbilityType AbilityID)
{
    if (AbilityID == EAbilityType::None) return;
    WImage->SetBrushFromSoftTexture(Cast<UANKGameInstance>(GetGameInstance())->GetBasicAsset()->GetAbility(AbilityID));
}
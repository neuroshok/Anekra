#include "PBasicAsset.h"

#include "Prankman/log.h"

UPBasicAsset::UPBasicAsset()
{

    for (int i = 0; i < static_cast<int>(EPAbilityType::Count); ++i)
    {
        auto v = UEnum::GetValueAsString(static_cast<EPAbilityType>(i));
        PM_LOG("Load asset %s", *v)
    }

}

UTexture2D* UPBasicAsset::GetAbility(EPAbilityType AbilityID) const
{
    check(Abilities.Contains(AbilityID));
    return Abilities[AbilityID];
}
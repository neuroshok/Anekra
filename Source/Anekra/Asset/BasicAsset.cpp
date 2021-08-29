#include "BasicAsset.h"

#include "Anekra/Log.h"

UBasicAsset::UBasicAsset()
{
    for (int i = 0; i < static_cast<int>(EAbilityType::Count); ++i)
    {
        auto v = UEnum::GetValueAsString(static_cast<EAbilityType>(i));
        ANK_LOG("Load asset %s", *v)
    }

}

UTexture2D* UBasicAsset::GetAbility(EAbilityType AbilityID) const
{
    check(Abilities.Contains(AbilityID));
    return Abilities[AbilityID];
}
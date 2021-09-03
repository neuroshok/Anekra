#include "Anekra/Game/ANKGameInstance.h"

#include "ANKTag.h"
#include "Anekra/Log.h"

UANKGameInstance::UANKGameInstance()
{
}

UANKAbility* UANKGameInstance::GetAbility(int ID) const
{
    return GetAbilityAsset()->Abilities[ID].GetDefaultObject();
}

TSubclassOf<UANKAbility> UANKGameInstance::GetAbilityClass(int ID) const
{
    return GetAbilityAsset()->Abilities[ID];
}

UAbilityAsset* UANKGameInstance::GetAbilityAsset() const
{
    return AbilityAsset.GetDefaultObject();
}

UBasicAsset* UANKGameInstance::GetBasicAsset() const
{
    return BasicAsset.GetDefaultObject();
}

UEffectAsset* UANKGameInstance::GetEffectAsset() const
{
    return EffectAsset.GetDefaultObject();
}
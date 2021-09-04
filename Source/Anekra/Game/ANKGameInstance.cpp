#include "Anekra/Game/ANKGameInstance.h"

#include "ANKTag.h"
#include "Anekra/Log.h"

UANKGameInstance::UANKGameInstance()
{
}

void UANKGameInstance::Init()
{
    Super::Init();

    for (TFieldIterator<FProperty> It{ UAbilityAsset::StaticClass() }; It; ++It)
    {
        FProperty* Property = *It;
        auto Data = Property->ContainerPtrToValuePtr<FAbilityData>(AbilityAsset->GetDefaultObject());
        if (Data->AbilityClass)
        {
            Cast<UANKAbility>(Data->AbilityClass->GetDefaultObject())->Data = Data;
            if (!Data->bIsStatic) Abilities.Add(Data);
        }

    }
    ANK_LOG("Load %d abilities", Abilities.Num())
}

FAbilityData* UANKGameInstance::GetAbility(int ID) const
{
    return Abilities[ID];
}

UANKAbility* UANKGameInstance::GetAbilityClass(int ID) const
{
    check(ID < Abilities.Num());
    return Abilities[ID]->AbilityClass.GetDefaultObject();
}

const TArray<FAbilityData*>& UANKGameInstance::GetAbilities() const
{
    return Abilities;
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
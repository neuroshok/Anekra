#include "Anekra/Game/ANKGameInstance.h"

#include "ANKTag.h"

UANKGameInstance::UANKGameInstance()
{

}

UBasicAsset* UANKGameInstance::GetBasicAsset()
{
    return BasicAsset.GetDefaultObject();
}

UEffectAsset* UANKGameInstance::GetEffectAsset()
{
    return EffectAsset.GetDefaultObject();
}

UMontageAsset* UANKGameInstance::GetMontageAsset()
{
    return MontageAsset.GetDefaultObject();
}
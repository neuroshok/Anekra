#include "Anekra/Game/ANKGameInstance.h"

UANKGameInstance::UANKGameInstance()
{

}

UBasicAsset* UANKGameInstance::GetBasicAsset()
{
    return BasicAsset.GetDefaultObject();
}
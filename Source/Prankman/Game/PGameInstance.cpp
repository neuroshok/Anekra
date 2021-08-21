#include "Prankman/Game/PGameInstance.h"

UPGameInstance::UPGameInstance()
{

}

UPBasicAsset* UPGameInstance::GetBasicAsset()
{
    return BasicAsset.GetDefaultObject();
}
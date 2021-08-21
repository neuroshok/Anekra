#pragma once

#include "Prankman/Asset/PBasicAsset.h"

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PGameInstance.generated.h"

UCLASS()
class PRANKMAN_API UPGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
    UPGameInstance();

    UPBasicAsset* GetBasicAsset();

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Prankman")
    TSubclassOf<UPBasicAsset> BasicAsset;
};
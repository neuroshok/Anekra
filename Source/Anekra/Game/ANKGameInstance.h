#pragma once

#include "Anekra/Asset/BasicAsset.h"

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ANKGameInstance.generated.h"

UCLASS()
class ANEKRA_API UANKGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
    UANKGameInstance();

    UBasicAsset* GetBasicAsset();

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TSubclassOf<UBasicAsset> BasicAsset;
};
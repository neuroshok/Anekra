#pragma once

#include "Anekra/Asset/BasicAsset.h"
#include "Anekra/Asset/EffectAsset.h"

#include "CoreMinimal.h"
#include "Anekra/Asset/MontageAsset.h"
#include "Engine/GameInstance.h"
#include "ANKGameInstance.generated.h"

UCLASS()
class ANEKRA_API UANKGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    UANKGameInstance();

    UBasicAsset* GetBasicAsset();
    UEffectAsset* GetEffectAsset();
    UMontageAsset* GetMontageAsset();

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TSubclassOf<UBasicAsset> BasicAsset;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TSubclassOf<UEffectAsset> EffectAsset;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TSubclassOf<UMontageAsset> MontageAsset;
};
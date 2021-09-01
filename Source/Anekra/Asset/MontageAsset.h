#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MontageAsset.generated.h"

UCLASS(BlueprintType, Blueprintable)
class ANEKRA_API UMontageAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    class UAnimMontage* UnlockMontage;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    class UAnimMontage* CrossFireMontage;
};
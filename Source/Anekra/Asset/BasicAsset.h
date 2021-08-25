#pragma once

#include "Anekra/AbilityType.h"

#include "CoreMinimal.h"
#include "BasicAsset.generated.h"

UCLASS(BlueprintType, Blueprintable)
class ANEKRA_API UBasicAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    UBasicAsset();

    UTexture2D* GetAbility(EAbilityType) const;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TMap<EAbilityType, class UTexture2D*> Abilities;
};
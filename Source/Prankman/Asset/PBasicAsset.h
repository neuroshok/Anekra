#pragma once

#include "Prankman/PAbilityType.h"

#include "CoreMinimal.h"
#include "PBasicAsset.generated.h"

UCLASS(BlueprintType, Blueprintable)
class PRANKMAN_API UPBasicAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    UPBasicAsset();

    UTexture2D* GetAbility(EPAbilityType) const;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Prankman")
    TMap<EPAbilityType, class UTexture2D*> Abilities;
};
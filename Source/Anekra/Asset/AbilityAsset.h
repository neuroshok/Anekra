#pragma once

#include "CoreMinimal.h"
#include "Anekra/Player/ANKAbility.h"
#include "UObject/Object.h"
#include "AbilityAsset.generated.h"

UCLASS(BlueprintType, Blueprintable)
class ANEKRA_API UAbilityAsset : public UObject
{
    GENERATED_BODY()

public:
    UAbilityAsset();

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TArray<TSubclassOf<UANKAbility>> Abilities;

private:
};
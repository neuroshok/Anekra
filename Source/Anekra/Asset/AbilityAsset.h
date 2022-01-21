#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AbilityAsset.generated.h"

USTRUCT(BlueprintType)
struct FAbilityData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TSubclassOf<class UANKAbility> AbilityClass;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    FText Name;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    bool bIsStatic = false;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    FText Description;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    class UTexture2D* Image = nullptr;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    class UAnimMontage* Montage = nullptr;
};

UCLASS(BlueprintType, Blueprintable)
class ANEKRA_API UAbilityAsset : public UObject
{
    GENERATED_BODY()

public:
    UAbilityAsset();

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Static")
    FAbilityData Unlock;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dynamic")
    FAbilityData CrossFire;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dynamic")
    FAbilityData Drain;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dynamic")
    FAbilityData Freeze;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dynamic")
    FAbilityData LaserBurst;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dynamic")
    FAbilityData Stealth;

private:
};
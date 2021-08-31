#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EffectAsset.generated.h"

UCLASS(BlueprintType, Blueprintable)
class ANEKRA_API UEffectAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TSubclassOf<class UGameplayEffect> BurnEffect;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TSubclassOf<class UGameplayEffect> DeadEffect;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TSubclassOf<class UGameplayEffect> FreezeEffect;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TSubclassOf<class UGameplayEffect> HealEffect;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TSubclassOf<class UGameplayEffect> StealthEffect;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TSubclassOf<class UGameplayEffect> UnlockEffect;
    // event
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra|Event")
    TSubclassOf<class UGameplayEffect> SnakeEffect;
};
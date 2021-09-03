#pragma once

#include "Anekra/Asset/BasicAsset.h"
#include "Anekra/Asset/EffectAsset.h"

#include "CoreMinimal.h"
#include "Anekra/Asset/AbilityAsset.h"
#include "Anekra/Player/ANKAbility.h"
#include "Engine/GameInstance.h"
#include "ANKGameInstance.generated.h"

UCLASS()
class ANEKRA_API UANKGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    UANKGameInstance();

    class UANKAbility* GetAbility(int ID) const;
    TSubclassOf<UANKAbility> GetAbilityClass(int ID) const;

    UAbilityAsset* GetAbilityAsset() const;
    UBasicAsset* GetBasicAsset() const;
    UEffectAsset* GetEffectAsset() const;


    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TSubclassOf<UAbilityAsset> AbilityAsset;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TSubclassOf<UBasicAsset> BasicAsset;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TSubclassOf<UEffectAsset> EffectAsset;

private:

};
#pragma once

#include "Anekra/Asset/BasicAsset.h"
#include "Anekra/Asset/EffectAsset.h"
#include "Anekra/Asset/AbilityAsset.h"
#include "Anekra/Player/ANKAbility.h"

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ANKGameInstance.generated.h"

UCLASS()
class ANEKRA_API UANKGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    UANKGameInstance();
    virtual void Init() override;

    struct FAbilityData* GetAbility(int ID) const;
    class UANKAbility* GetAbilityClass(int ID) const;
    const TArray<struct FAbilityData*>& GetAbilities() const;

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
    TArray<struct FAbilityData*> Abilities;
};
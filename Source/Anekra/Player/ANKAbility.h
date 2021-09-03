#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ANKAbility.generated.h"

UCLASS()
class ANEKRA_API UANKAbility : public UGameplayAbility
{
    GENERATED_BODY()

public:
    UANKAbility();

    UFUNCTION(BlueprintCallable)
    class UEffectAsset* GetEffects();
    UFUNCTION(BlueprintCallable)
    class AHero* GetHero() const;
    UFUNCTION(BlueprintCallable)
    class AANKPlayerState* GetANKPlayerState() const;
    UFUNCTION(BlueprintCallable)
    class AANKPlayerController* GetANKPlayerController() const;
    UFUNCTION(BlueprintCallable)
    class UANKGameInstance* GetANKGameInstance() const;

    const FText& GetName() const { return Name; }
    const FText& GetDescription() const { return Description; }
    class UTexture2D* GetImage() const { return Image; }

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    FText Name;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    FText Description;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    class UTexture2D* Image;

protected:
    class UANKAbilitySystemComponent* GetAbilitySystemComponent();
};
#pragma once

#include "Anekra/AbilityType.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WAbility.generated.h"

UCLASS()
class ANEKRA_API UWAbility : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetImage(EAbilityType);

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
    class UImage* WImage;
};
#pragma once

#include "Prankman/PAbilityType.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WAbility.generated.h"

UCLASS()
class PRANKMAN_API UWAbility : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetImage(EPAbilityType);

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
    class UImage* WImage;
};
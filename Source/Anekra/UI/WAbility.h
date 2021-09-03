#pragma once


#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WAbility.generated.h"

UCLASS()
class ANEKRA_API UWAbility : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetImage(int);

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
    class UImage* WImage;
};
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WEndGame.generated.h"

UCLASS()
class ANEKRA_API UWEndGame : public UUserWidget
{
    GENERATED_BODY()

public:
    void Update();

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
    class UTextBlock* WStatusText;

protected:
    virtual void NativeConstruct() override;

};
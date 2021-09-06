#pragma once

#include "CoreMinimal.h"
#include "Anekra/PlayerNetStatus.h"
#include "Blueprint/UserWidget.h"
#include "WLog.generated.h"

UCLASS()
class ANEKRA_API UWLog : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
    class URichTextBlock* WText;

private:
    virtual void NativeConstruct() override;
    void OnPlayerNetStatusUpdated(class AANKPlayerState*, EPlayerNetStatus);
};
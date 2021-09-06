#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "WGameStatsEntry.generated.h"

UCLASS()
class ANEKRA_API UWGameStatsEntry : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
    class UBorder* WBorder;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
    class UTextBlock* WName;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
    class UTextBlock* WKills;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
    class UTextBlock* WPing;
};
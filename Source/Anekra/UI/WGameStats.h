#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WGameStats.generated.h"

UCLASS()
class ANEKRA_API UWGameStats : public UUserWidget
{
	GENERATED_BODY()

public:
    void Update();

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
    class UVerticalBox* WStats;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TSubclassOf<UUserWidget> BP_WGameStatsEntry;

private:
    virtual void NativeConstruct() override;
};
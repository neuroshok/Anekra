#pragma once

#include "Anekra/EventType.h"

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EventSystem.generated.h"

UCLASS(Blueprintable, BlueprintType)
class ANEKRA_API UEventSystem : public UObject
{
    GENERATED_BODY()

public:
    void Start();
    void Stop();

    UFUNCTION()
    void UpdateEvent();
    UFUNCTION()
    void ClearEvent();

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TSubclassOf<class UGameplayEffect> SnakeEffect;

private:
    FTimerHandle EventTimer;
    EEventType EventType;
};
#pragma once

#include "Prankman/PEventType.h"

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PEventSystem.generated.h"

UCLASS(Blueprintable, BlueprintType)
class PRANKMAN_API UPEventSystem : public UObject
{
    GENERATED_BODY()

public:
    void Start();
    void Stop();

    UFUNCTION()
    void UpdateEvent();
    UFUNCTION()
    void ClearEvent();

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Prankman")
    TSubclassOf<class UGameplayEffect> SnakeEffect;

private:
    FTimerHandle EventTimer;
    EPEventType EventType;
};
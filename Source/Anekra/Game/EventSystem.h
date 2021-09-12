#pragma once

#include "Anekra/EventType.h"

#include "CoreMinimal.h"
#include "Anekra/Asset/EffectAsset.h"
#include "UObject/Object.h"
#include "EventSystem.generated.h"

UCLASS(BlueprintType, Blueprintable)
class ANEKRA_API UEventSystem : public UObject
{
    GENERATED_BODY()

public:
    UEventSystem();
    void Initialize();

    void Start();
    void Stop();

    UFUNCTION()
    void StartEvent();

private:
    UPROPERTY()
    UEffectAsset* Effects = nullptr;

    UPROPERTY()
    TArray<class UEvent*> Events;

    FTimerHandle EventTimer;
    EEventType EventType;


    float NoEventDuration;
};
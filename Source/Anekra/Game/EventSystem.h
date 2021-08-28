#pragma once

#include "Anekra/EventType.h"

#include "CoreMinimal.h"
#include "Anekra/Asset/EffectAsset.h"
#include "UObject/Object.h"
#include "EventSystem.generated.h"

UCLASS(Blueprintable, BlueprintType)
class ANEKRA_API UEventSystem : public UObject
{
    GENERATED_BODY()

public:
    void Initialize();

    void Start();
    void Stop();

    UFUNCTION()
    void UpdateEvent();
    UFUNCTION()
    void ClearEvent();

private:
    UPROPERTY()
    UEffectAsset* Effects = nullptr;

    FTimerHandle EventTimer;
    EEventType EventType;
};
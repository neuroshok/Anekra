#pragma once

#include "CoreMinimal.h"
#include "Anekra/EventType.h"
#include "Anekra/Game/Event.h"
#include "ReduceCellEvent.generated.h"

UCLASS()
class ANEKRA_API UReduceCellEvent : public UEvent
{
    GENERATED_BODY()

public:
    void Start() override;
    EEventType GetType() override { return EEventType::ReduceCell; }
};
#pragma once

#include "CoreMinimal.h"
#include "Anekra/Game/Event.h"
#include "SnakeEvent.generated.h"

UCLASS()
class ANEKRA_API USnakeEvent : public UEvent
{
    GENERATED_BODY()

public:
    void Start() override;
};
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Event.generated.h"

UCLASS()
class ANEKRA_API UEvent : public UObject
{
    GENERATED_BODY()

    DECLARE_DELEGATE(FOnCompleted)

public:
    UEvent();

    virtual void Start() {}

    FOnCompleted OnCompleted;

protected:
    void Delay(float Duration, TFunction<void()> Delegate);

private:
    FTimerHandle EventTimer;
};
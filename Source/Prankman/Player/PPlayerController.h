#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PPlayerController.generated.h"

UCLASS()
class PRANKMAN_API APPlayerController : public APlayerController
{
    GENERATED_BODY()

    DECLARE_MULTICAST_DELEGATE_OneParam(FOnCastingDelegate, float);

public:
    FOnCastingDelegate OnCastingDelegate;

protected:
    virtual void BeginPlay() override;


private:

};
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PPlayerController.generated.h"

UCLASS()
class PRANKMAN_API APPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    void InitializeHUD();

protected:
    virtual void BeginPlay() override;


private:

};
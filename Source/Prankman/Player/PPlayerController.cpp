#include "Prankman/Player/PPlayerController.h"

#include "PHUD.h"
#include "Prankman/log.h"

void APPlayerController::InitializeHUD()
{
    if (GetHUD() || !IsLocalPlayerController()) return;
    SpawnDefaultHUD();
    Cast<APHUD>(GetHUD())->Initialize();
}

void APPlayerController::BeginPlay()
{
    Super::BeginPlay();
}
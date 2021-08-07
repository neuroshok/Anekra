#include "PGameMode.h"
#include "PCell.h"
#include "PHero.h"
#include "log.h"
#include "PGameState.h"

void APGameMode::StartPlay()
{
    Super::StartPlay();

    //EventSystem.Start();
}

void APGameMode::BeginPlay()
{
    PM_LOG("______________________________________________BeginPlay")
    MakeMap();
    //GetWorldTimerManager().SetTimer(EventTimer, this, &APGameMode::OnEventTimer, 5.f, true, 5.f);
}

void APGameMode::MakeMap()
{
    if (!BP_Cell) PM_LOG("bp_cell not found")
    else
    {
        PM_LOG("______________________________________________MakeMap")
        int size = 8;
        FVector position;

        for (int x = 0; x < size; ++x)
        {
            for (int y = 0; y < size; ++y)
            {
                position.X = x * 410;
                position.Y = y * 410;
                FActorSpawnParameters params;
                params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
                auto Cell = GetWorld()->SpawnActor<APCell>(BP_Cell, position, FRotator{0, 0, 0}, params);
                if (!Cell) break;
                if (x == 1 && y == 1) Cell->SetType(EPCellType::Rotating);
                if (x == 2 && y == 3) Cell->SetType(EPCellType::Heal);
                if (x == 2 && y == 2) Cell->SetType(EPCellType::Ghost);
                PM_LOG("%d %d", x, y)
            }
        }
    }
}

void APGameMode::OnEventTimer()
{
    PM_LOG("TIMER")
    auto randomType = FMath::RandRange(static_cast<int32>(EPEventType::None), static_cast<int32>(EPEventType::Max) - 1);
    EventType = static_cast<EPEventType>(randomType);
    GetGameState<APGameState>()->ClientStartEvent(EventType);
}

void APGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
    Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

    //FString id = UGameplayStatics::ParseOption(Options, TEXT("id"));
    UE_LOG(LogTemp, Warning, TEXT("PreLogin"))
}

void APGameMode::PostLogin(APlayerController* PC)
{
    Super::PostLogin(PC);
    UE_LOG(LogTemp, Warning, TEXT("PostLogin"))

    FActorSpawnParameters params;
    params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    GetWorld()->SpawnActor<APHero>(FVector{ 0, 0, 0 }, FRotator{ 0, 0, 0 }, params);
}

FString APGameMode::InitNewPlayer(APlayerController* PlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal)
{
    FString init = Super::InitNewPlayer(PlayerController, UniqueId, Options, Portal);

    UE_LOG(LogTemp, Warning, TEXT("InitNewPlayer"));
    if (GetLocalRole() == ROLE_Authority)
    {
        UE_LOG(LogTemp, Warning, TEXT("InitNewPlayer server"));
    }

    return init;
}


void APGameMode::Logout(AController* Controller)
{

    UE_LOG(LogTemp, Warning, TEXT("Logout"));
}
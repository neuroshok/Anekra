#include "Anekra/Player/ANKPlayerState.h"

#include "Hero.h"
#include "Anekra/Player/Attribute/Basic.h"
#include "Anekra/Game/ANKGameMode.h"
#include "Anekra/Game/ANKGameState.h"
#include "Anekra/Game/ANKAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpectatorPawn.h"

#include "Net/UnrealNetwork.h"

AANKPlayerState::AANKPlayerState()
{
    NetUpdateFrequency = 100.0f;
    ANKAbilitySystemComponent = CreateDefaultSubobject<UANKAbilitySystemComponent>(FName("Ability System Component"));
    ANKAbilitySystemComponent->SetIsReplicated(true);
    ANKAbilitySystemComponent->ReplicationMode = EGameplayEffectReplicationMode::Full;

    AttributeBasic = CreateDefaultSubobject<UAttributeBasic>(TEXT("AttributeBasic"));
}

UANKAbilitySystemComponent* AANKPlayerState::GetAbilitySystemComponent() const
{
    return ANKAbilitySystemComponent;
}

void AANKPlayerState::ComputeCellPosition()
{
    check(GetPawn());
    float X = GetPawn()->GetActorLocation().X;
    float Y = GetPawn()->GetActorLocation().Y;

    auto ANKGameState = Cast<AANKGameState>(GetWorld()->GetGameState());
    const float MapWidth = ANKGameState->GetMapWidth();
    const float CellSize = ANKGameState->GetMapCellSize();

    float CellX = (X + CellSize / 2.f) / CellSize;
    float CellY = (Y + CellSize / 2.f) / CellSize;


    //bIsOut = false;
    //ANK_LOG("%f %f", CellX, CellY)
    if (CellX < 0 || CellX > CellSize - 1 || CellY < 0 || CellY > CellSize - 1)
    {
        //bIsOut = true;
        return;
    }

    CellPosition.X = static_cast<int32>(CellX);
    CellPosition.Y = static_cast<int32>(CellY);
}

FIntVector AANKPlayerState::GetCellPosition() const
{
    return CellPosition;
}

bool AANKPlayerState::IsDead() const
{
    return bIsDead;
}

bool AANKPlayerState::IsAlive() const
{
    return !bIsDead;
}

void AANKPlayerState::OnHealthUpdated(const FOnAttributeChangeData& Data)
{
    if (!(AttributeBasic->GetHealth() > 0.f))
    {
        Die();
    }
}

void AANKPlayerState::BeginPlay()
{
    Super::BeginPlay();

    OnHealthUpdateDelegate = GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(AttributeBasic->GetHealthAttribute()).AddUObject(this, &AANKPlayerState::OnHealthUpdated);
}

// server
void AANKPlayerState::Die()
{
    if (!HasAuthority()) return;

    GetAbilitySystemComponent()->ApplyEffect(GetAbilitySystemComponent()->Effects->DeadEffect);
    bIsDead = true;

    auto Hero = Cast<AHero>(GetPawn());

    Hero->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Hero->GetCharacterMovement()->GravityScale = 0;
    Hero->GetCharacterMovement()->Velocity = {0};
    Hero->SetActorLocation({4000, 4000, 2000});

    auto ANKGameState = Cast<AANKGameState>(GetWorld()->GetGameState());
    ANKGameState->CheckEndGame();

    //GetAbilitySystemComponent()->CancelAllAbilities();
    //GetAbilitySystemComponent()->ClearAllAbilities();

    /*
    GetPawn()->Destroy();
    auto Spectator = GetWorld()->SpawnActor(ASpectatorPawn::StaticClass());
    Cast<APlayerController>(GetOwner())->Possess(Cast<APawn>(Spectator));*/
}
#include "Prankman/World/PCell.h"

#include "AbilitySystemComponent.h"

#include "Net/UnrealNetwork.h"
#include "NiagaraComponent.h"
#include "Prankman/Player/PHero.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Prankman/Game/PEventSystem.h"

APCell::APCell()
{
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
    RootComponent = MeshComponent;

    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;
    bAlwaysRelevant = true;
}

void APCell::AddState(EPEventType PEventType)
{
    State |= static_cast<int32>(PEventType);
}

void APCell::BeginPlay()
{
    check(BP_Mesh);
    MeshComponent->SetStaticMesh(BP_Mesh);

    MaterialInstanceDynamic = MeshComponent->CreateAndSetMaterialInstanceDynamicFromMaterial(0, BP_Material);
    Super::BeginPlay();

    Color = { 0.2, 0.2, 0.8 };
    OnTypeUpdated();
    OnStateUpdated();
}

void APCell::SetActive(bool bState)
{
    if (bState) State |= static_cast<int32>(EPCellState::Active);
    else State &= ~static_cast<int32>(EPCellState::Active);
}

void APCell::SetEffectVisible(bool bState)
{
    auto PrevState = State;
    if (bState) State |= static_cast<int32>(EPCellState::EffectVisible);
    else State &= ~static_cast<int32>(EPCellState::EffectVisible);
    if (State != PrevState) OnStateUpdated();
}

void APCell::SetColor(FLinearColor NewColor)
{
    if (Color == NewColor) return;
    Color = NewColor;
    if (!MaterialInstanceDynamic) return;
    MaterialInstanceDynamic->SetVectorParameterValue("Color", Color);
}

void APCell::SetType(EPCellType CellType)
{
    if (Type == CellType) return;
    Type = CellType;
    OnTypeUpdated();
}

void APCell::Enter(APPlayerState* PPlayerState)
{
    auto PHero = Cast<APHero>(PPlayerState->GetPawn());

    switch (Type)
    {
        case EPCellType::Slow:break;
        case EPCellType::Heal:ApplyEffect(PPlayerState, HealingEffect); break;
        case EPCellType::Burn:ApplyEffect(PPlayerState, BurningEffect); break;
    }
}

void APCell::Leave(APPlayerState* PPlayerState)
{
    auto PHero = Cast<APHero>(PPlayerState->GetPawn());
    FGameplayTagContainer EventTags;
    PHero->GetAbilitySystemComponent()->GetOwnedGameplayTags(EventTags);

    if (EventTags.HasTagExact(FGameplayTag::RequestGameplayTag("Event.Snake")))
    {
        SetType(EPCellType::Burn);
        OnTypeUpdated();
    }
    else
    {
        switch (Type)
        {
        case EPCellType::Slow:break;
        case EPCellType::Heal:RemoveEffect(PPlayerState, HealingEffect); break;
        case EPCellType::Burn:RemoveEffect(PPlayerState, BurningEffect); break;
        }
    }
}

void APCell::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(APCell, Type);
    DOREPLIFETIME(APCell, State);
}

void APCell::OnTypeUpdated()
{
    switch (Type)
    {
        case EPCellType::Heal: break;
            /*
            if (TypeEffect) TypeEffect->DestroyComponent();
            TypeEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, BP_TypeEffect, GetActorLocation());
            TypeEffect->SetRenderingEnabled(false);*/
        case EPCellType::Burn: SetColor({1, 0, 0}) ; break;
        case EPCellType::Slow: SetColor({0.2, 0.2, 0}) ; break;
    }
}

void APCell::OnStateUpdated()
{
    if (State & static_cast<int32>(EPEventType::Snake))
    {
        SetColor({0.1, 0.7, 0.1});
    }
    /*
    if (State & static_cast<int32>(EPCellState::EffectVisible))
    {
        TypeEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, BP_TypeEffect, GetActorLocation());
    }
    else
    {
        if (TypeEffect) TypeEffect->DestroyInstance();
    }*/

}

void APCell::ApplyEffect(APPlayerState* PPlayerState, TSubclassOf<UGameplayEffect> Effect)
{
    auto PHero = Cast<APHero>(PPlayerState->GetPawn());
    FGameplayEffectContextHandle EffectContext = PHero->GetAbilitySystemComponent()->MakeEffectContext();
    EffectContext.AddSourceObject(this);

    FGameplayEffectSpecHandle EffectHandle = PHero->GetAbilitySystemComponent()->MakeOutgoingSpec(Effect, 1, EffectContext);
    check(EffectHandle.IsValid());
    PHero->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectHandle.Data.Get(), PHero->GetAbilitySystemComponent());
}

void APCell::RemoveEffect(APPlayerState* PPlayerState, TSubclassOf<UGameplayEffect> Effect)
{
    auto PHero = Cast<APHero>(PPlayerState->GetPawn());
    PHero->GetAbilitySystemComponent()->RemoveActiveGameplayEffectBySourceEffect(Effect, PHero->GetAbilitySystemComponent());
}

void APCell::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    /// server
    if (GetWorld()->IsServer())
    {
        switch (Type)
        {
        case EPCellType::Heal:

            break;
        case EPCellType::Burn:

            break;

        case EPCellType::Ghost:
            //SetActorEnableCollision(false);
            break;
        case EPCellType::Rotating: {
            auto Rotator = RootComponent->GetRelativeRotation();
            //RootComponent->AddLocalRotation(FRotator{ 0.5, 0, 0 });
        }
            break;
        case EPCellType::Boom:
            break;
        case EPCellType::Basic:
        default:;
        }
    }
}
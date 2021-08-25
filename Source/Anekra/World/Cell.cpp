#include "Anekra/World/Cell.h"

#include "AbilitySystemComponent.h"

#include "Net/UnrealNetwork.h"
#include "NiagaraComponent.h"
#include "Anekra/Player/Hero.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Anekra/Game/EventSystem.h"

ACell::ACell()
{
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
    RootComponent = MeshComponent;

    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;
    bAlwaysRelevant = true;
}

void ACell::AddState(EEventType PEventType)
{
    State |= static_cast<int32>(PEventType);
}

void ACell::BeginPlay()
{
    check(BP_Mesh);
    MeshComponent->SetStaticMesh(BP_Mesh);

    MaterialInstanceDynamic = MeshComponent->CreateAndSetMaterialInstanceDynamicFromMaterial(0, BP_Material);
    Super::BeginPlay();

    Color = { 0.2, 0.2, 0.8 };
    OnTypeUpdated();
    OnStateUpdated();
}

void ACell::SetActive(bool bState)
{
    if (bState) State |= static_cast<int32>(ECellState::Active);
    else State &= ~static_cast<int32>(ECellState::Active);
}

void ACell::SetEffectVisible(bool bState)
{
    auto PrevState = State;
    if (bState) State |= static_cast<int32>(ECellState::EffectVisible);
    else State &= ~static_cast<int32>(ECellState::EffectVisible);
    if (State != PrevState) OnStateUpdated();
}

void ACell::SetColor(FLinearColor NewColor)
{
    if (Color == NewColor) return;
    Color = NewColor;
    if (!MaterialInstanceDynamic) return;
    MaterialInstanceDynamic->SetVectorParameterValue("Color", Color);
}

void ACell::SetType(ECellType CellType)
{
    if (Type == CellType) return;
    Type = CellType;
    OnTypeUpdated();
}

void ACell::Enter(AANKPlayerState* ANKPlayerState)
{
    auto Hero = Cast<AHero>(ANKPlayerState->GetPawn());

    switch (Type)
    {
        case ECellType::Slow:break;
        case ECellType::Heal:ApplyEffect(ANKPlayerState, HealingEffect); break;
        case ECellType::Burn:ApplyEffect(ANKPlayerState, BurningEffect); break;
    }
}

void ACell::Leave(AANKPlayerState* ANKPlayerState)
{
    auto Hero = Cast<AHero>(ANKPlayerState->GetPawn());
    FGameplayTagContainer EventTags;
    Hero->GetAbilitySystemComponent()->GetOwnedGameplayTags(EventTags);

    if (EventTags.HasTagExact(FGameplayTag::RequestGameplayTag("Event.Snake")))
    {
        SetType(ECellType::Burn);
        OnTypeUpdated();
    }
    else
    {
        switch (Type)
        {
        case ECellType::Slow:break;
        case ECellType::Heal:RemoveEffect(ANKPlayerState, HealingEffect); break;
        case ECellType::Burn:RemoveEffect(ANKPlayerState, BurningEffect); break;
        }
    }
}

void ACell::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ACell, Type);
    DOREPLIFETIME(ACell, State);
}

void ACell::OnTypeUpdated()
{
    switch (Type)
    {
        case ECellType::Heal: break;
            /*
            if (TypeEffect) TypeEffect->DestroyComponent();
            TypeEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, BP_TypeEffect, GetActorLocation());
            TypeEffect->SetRenderingEnabled(false);*/
        case ECellType::Burn: SetColor({1, 0, 0}) ; break;
        case ECellType::Slow: SetColor({0.2, 0.2, 0}) ; break;
    }
}

void ACell::OnStateUpdated()
{
    if (State & static_cast<int32>(EEventType::Snake))
    {
        SetColor({0.1, 0.7, 0.1});
    }
    /*
    if (State & static_cast<int32>(ECellState::EffectVisible))
    {
        TypeEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, BP_TypeEffect, GetActorLocation());
    }
    else
    {
        if (TypeEffect) TypeEffect->DestroyInstance();
    }*/

}

void ACell::ApplyEffect(AANKPlayerState* ANKPlayerState, TSubclassOf<UGameplayEffect> Effect)
{
    auto Hero = Cast<AHero>(ANKPlayerState->GetPawn());
    FGameplayEffectContextHandle EffectContext = Hero->GetAbilitySystemComponent()->MakeEffectContext();
    EffectContext.AddSourceObject(this);

    FGameplayEffectSpecHandle EffectHandle = Hero->GetAbilitySystemComponent()->MakeOutgoingSpec(Effect, 1, EffectContext);
    check(EffectHandle.IsValid());
    Hero->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectHandle.Data.Get(), Hero->GetAbilitySystemComponent());
}

void ACell::RemoveEffect(AANKPlayerState* ANKPlayerState, TSubclassOf<UGameplayEffect> Effect)
{
    auto Hero = Cast<AHero>(ANKPlayerState->GetPawn());
    Hero->GetAbilitySystemComponent()->RemoveActiveGameplayEffectBySourceEffect(Effect, Hero->GetAbilitySystemComponent());
}

void ACell::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    /// server
    if (GetWorld()->IsServer())
    {
        switch (Type)
        {
        case ECellType::Heal:

            break;
        case ECellType::Burn:

            break;

        case ECellType::Ghost:
            //SetActorEnableCollision(false);
            break;
        case ECellType::Rotating: {
            auto Rotator = RootComponent->GetRelativeRotation();
            //RootComponent->AddLocalRotation(FRotator{ 0.5, 0, 0 });
        }
            break;
        case ECellType::Boom:
            break;
        case ECellType::Basic:
        default:;
        }
    }
}
#include "PCell.h"
#include "log.h"
#include "PGameState.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/GameStateBase.h"
#include "Net/UnrealNetwork.h"

APCell::APCell()
{
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
    RootComponent = MeshComponent;

    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;
    bAlwaysRelevant = true;
}

void APCell::BeginPlay()
{
    check(BP_Mesh);
    MeshComponent->SetStaticMesh(BP_Mesh);

    CellBox = MeshComponent->GetStaticMesh()->GetBoundingBox();
    CellBox = CellBox.MoveTo(GetActorLocation());

    MaterialInstanceDynamic = MeshComponent->CreateAndSetMaterialInstanceDynamicFromMaterial(0, BP_Material);
    Super::BeginPlay();

    OnColorUpdate();
    OnTypeUpdate();
}

void APCell::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(APCell, Color);
    DOREPLIFETIME(APCell, Type);
}

void APCell::SetColor(FLinearColor NewColor)
{
    if (Color == NewColor) return;
    Color = NewColor;
    OnColorUpdate();
}

void APCell::SetType(EPCellType CellType)
{
    Type = CellType;
    OnTypeUpdate();
}

void APCell::OnColorUpdate()
{
    if (!HasActorBegunPlay()) return;
    MaterialInstanceDynamic->SetVectorParameterValue("Color", Color);
}

void APCell::OnTypeUpdate()
{
    if (!HasActorBegunPlay()) return;
    switch (Type)
    {
    case EPCellType::Heal:
        TypeEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, BP_TypeEffect, GetActorLocation());
        break;
    };
}

void APCell::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    switch (Type)
    {
        case EPCellType::Heal:
            for (auto PPlayerState : PlayersOver)
            {
                SetColor({0, 200, 0});
                PPlayerState->AddHealth(0.0005f);
            }
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
        case EPCellType::Slow:
            // foreach player, player.speed--
        break;
        case EPCellType::Basic:
        default:;
    }
}

void APCell::AddPlayerOver(APPlayerState* PPlayer)
{
    PlayersOver.Add(PPlayer);
}

/*
void APCell::PlayersOver()
{
    auto playerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

    if (CellBox.IsInsideXY(playerPosition))
    {
        Color = FLinearColor{ 90, 0, 0 };
        MaterialInstanceDynamic->SetVectorParameterValue("Color", FLinearColor{ 90, 0, 0 });
    }
    else
    {
        //Color = FLinearColor{ 0, 0, 200 };
        //MaterialInstanceDynamic->SetVectorParameterValue("Color", FLinearColor{ 0, 0, 200 });
    }
}*/
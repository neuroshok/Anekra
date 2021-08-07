#include "PCell.h"
#include "log.h"
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

void APCell::SetType(EPCellType CellType)
{
    Type = CellType;

    switch (Type)
    {
    case EPCellType::Heal:
        OnColorUpdate();
        TypeEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, BP_TypeEffect, GetActorLocation());
        break;
    };
}

void APCell::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    DOREPLIFETIME(APCell, Color);
    DOREPLIFETIME(APCell, Type);
}

void APCell::BeginPlay()
{
    Super::BeginPlay();
    check(BP_Mesh);

    MeshComponent->SetStaticMesh(BP_Mesh);

    CellBox = MeshComponent->GetStaticMesh()->GetBoundingBox();
    CellBox = CellBox.MoveTo(GetActorLocation());

    MaterialInstanceDynamic = MeshComponent->CreateAndSetMaterialInstanceDynamicFromMaterial(0, BP_Material);
}

void APCell::OnColorUpdate()
{
    if (MaterialInstanceDynamic) MaterialInstanceDynamic->SetVectorParameterValue("Color", Color);
}

void APCell::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    switch (Type)
    {
        case EPCellType::Ghost:
            SetActorEnableCollision(false);
        break;
        case EPCellType::Rotating: {
            auto Rotator = RootComponent->GetRelativeRotation();
            RootComponent->AddLocalRotation(FRotator{ 0.5, 0, 0 });
        }
        break;
        case EPCellType::Slow:
            // foreach player, player.speed--
        break;
        case EPCellType::Basic:
        default:;
    }



    //PlayersOver();
    //if (PlayersOver) color = ...
}

void APCell::PlayersOver()
{
    auto playerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();


    //auto cellbox = CellBox.MoveTo(GetActorLocation());

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
}
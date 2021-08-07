// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PCellType.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PCell.generated.h"

UCLASS()
class PRANKMAN_API APCell : public AActor
{
    GENERATED_BODY()

public:	
    APCell();

    void SetType(EPCellType);

    virtual void Tick(float DeltaTime) override;
    void PlayersOver();

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cell")
    class UStaticMesh* BP_Mesh;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cell")
    class UMaterial* BP_Material;

    class UMaterialInstanceDynamic* MaterialInstanceDynamic;

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnColorUpdate();

private:
    UPROPERTY(Replicated, ReplicatedUsing = OnColorUpdate)
    FLinearColor Color;

    UPROPERTY(Replicated)
    EPCellType Type;

    class UStaticMeshComponent* MeshComponent;
    FBox CellBox;
};
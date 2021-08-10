// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PCellType.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "PPlayerState.h"

#include "PCell.generated.h"

UCLASS()
class PRANKMAN_API APCell : public AActor
{
    GENERATED_BODY()

protected:
    virtual void Tick(float DeltaTime) override;
    virtual void BeginPlay() override;

public:	
    APCell();

    void SetColor(FLinearColor NewColor);
    void SetType(EPCellType CellType);

    UFUNCTION()
    void OnColorUpdate();
    UFUNCTION()
    void OnTypeUpdate();


    void AddPlayerOver(class APPlayerState*);

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cell")
    class UStaticMesh* BP_Mesh;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cell")
    class UMaterial* BP_Material;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cell")
    class UNiagaraSystem* BP_TypeEffect;

    class UMaterialInstanceDynamic* MaterialInstanceDynamic;

private:
    UPROPERTY(Replicated, ReplicatedUsing = OnColorUpdate)
    FLinearColor Color;

    UPROPERTY(Replicated, ReplicatedUsing = OnTypeUpdate)
    EPCellType Type;

    UPROPERTY()
    class UStaticMeshComponent* MeshComponent;

    UPROPERTY()
    class UNiagaraComponent* TypeEffect;

    FBox CellBox;
};
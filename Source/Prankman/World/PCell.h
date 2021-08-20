#pragma once

#include "Prankman/PCellType.h"
#include "Prankman/Player/PPlayerState.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "Prankman/PEventType.h"

#include "PCell.generated.h"

UENUM(meta = (Bitflags))
enum class EPCellState : int32
{
    None = 0 UMETA(Hidden),
    Active = 1 << 0,
    Visible = 1 << 1,
    EffectVisible = 1 << 2,
};
ENUM_CLASS_FLAGS(EPCellState);

UCLASS()
class PRANKMAN_API APCell : public AActor
{
    GENERATED_BODY()

protected:
    virtual void Tick(float DeltaTime) override;
    virtual void BeginPlay() override;

public:	
    APCell();

    void AddState(EPEventType);
    void SetActive(bool);
    void SetEffectVisible(bool);
    void SetColor(FLinearColor NewColor);
    void SetType(EPCellType CellType);

    void Enter(class APPlayerState*);
    void Leave(class APPlayerState*);

    UFUNCTION()
    void OnTypeUpdated();
    UFUNCTION()
    void OnStateUpdated();

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Prankman")
    TSubclassOf<class UGameplayEffect> HealingEffect;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Prankman")
    TSubclassOf<class UGameplayEffect> BurningEffect;

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cell")
    class UStaticMesh* BP_Mesh;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cell")
    class UMaterial* BP_Material;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cell")
    class UNiagaraSystem* BP_TypeEffect;

    UPROPERTY()
    class UMaterialInstanceDynamic* MaterialInstanceDynamic;

private:
    void ApplyEffect(APPlayerState*, TSubclassOf<UGameplayEffect>);
    void RemoveEffect(APPlayerState*, TSubclassOf<UGameplayEffect>);

    UPROPERTY(Replicated, ReplicatedUsing = OnTypeUpdated)
    EPCellType Type;
    UPROPERTY(Replicated, ReplicatedUsing = OnStateUpdated)
    int32 State;

    FLinearColor Color;
    int32 VisualState;

    UPROPERTY()
    class UStaticMeshComponent* MeshComponent;
    UPROPERTY()
    class UNiagaraComponent* TypeEffect;

    FBox CellBox;
};
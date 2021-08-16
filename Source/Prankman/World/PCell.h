#pragma once

#include "Prankman/PCellType.h"
#include "Prankman/Player/PPlayerState.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"

#include "PCell.generated.h"

UENUM(meta = (Bitflags))
enum class EPCellState: uint8
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

    void SetActive(bool);
    void SetEffectVisible(bool);
    void SetColor(FLinearColor NewColor);
    void SetType(EPCellType CellType);

    void Enter(class APPlayerState*);
    void Leave(class APPlayerState*);

    UFUNCTION()
    void OnColorUpdate();
    UFUNCTION()
    void OnTypeUpdate();
    UFUNCTION()
    void OnStateUpdate();

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

    class UMaterialInstanceDynamic* MaterialInstanceDynamic = nullptr;

private:
    void TypeApply();
    void ApplyEffect(APPlayerState*, TSubclassOf<UGameplayEffect>);
    void RemoveEffect(APPlayerState*, TSubclassOf<UGameplayEffect>);

    UPROPERTY(Replicated, ReplicatedUsing = OnColorUpdate)
    FLinearColor Color;
    UPROPERTY(Replicated, ReplicatedUsing = OnTypeUpdate)
    EPCellType Type;
    UPROPERTY(Replicated, ReplicatedUsing = OnStateUpdate)
    int32 State;

    UPROPERTY()
    class UStaticMeshComponent* MeshComponent = nullptr;

    class UNiagaraComponent* TypeEffect = nullptr;

    FBox CellBox;
};
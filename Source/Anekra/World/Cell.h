#pragma once

#include "Anekra/CellType.h"
#include "Anekra/Player/ANKPlayerState.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "Anekra/EventType.h"

#include "Cell.generated.h"

UENUM(meta = (Bitflags))
enum class ECellState : int32
{
    None = 0 UMETA(Hidden),
    Active = 1 << 0,
    Visible = 1 << 1,
    EffectVisible = 1 << 2,
};
ENUM_CLASS_FLAGS(ECellState);

UCLASS()
class ANEKRA_API ACell : public AActor
{
    GENERATED_BODY()

protected:
    virtual void Tick(float DeltaTime) override;
    virtual void BeginPlay() override;

public:	
    ACell();

    void AddState(EEventType);
    void SetActive(bool);
    void SetEffectVisible(bool);
    UFUNCTION(BlueprintCallable, Category = "Anekra")
    void SetColor(FLinearColor NewColor);
    UFUNCTION(BlueprintCallable, Category = "Anekra")
    void SetType(ECellType CellType);

    void Enter(class AANKPlayerState*);
    void Leave(class AANKPlayerState*);

    UFUNCTION()
    void OnTypeUpdated();
    UFUNCTION()
    void OnStateUpdated();

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
    void ApplyEffect(AANKPlayerState*, TSubclassOf<UGameplayEffect>);
    void RemoveEffect(AANKPlayerState*, TSubclassOf<UGameplayEffect>);

    UPROPERTY(Replicated, ReplicatedUsing = OnTypeUpdated)
    ECellType Type;
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
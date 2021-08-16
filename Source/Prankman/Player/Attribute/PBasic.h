#pragma once

#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "CoreMinimal.h"
#include "PBasic.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class PRANKMAN_API UPAttributeBasic : public UAttributeSet
{
    GENERATED_BODY()

public:
    UPAttributeBasic();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

    UPROPERTY(ReplicatedUsing = OnRep_Health)
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UPAttributeBasic, Health)

    UPROPERTY(ReplicatedUsing = OnRep_MoveSpeed)
    FGameplayAttributeData MoveSpeed;
    ATTRIBUTE_ACCESSORS(UPAttributeBasic, MoveSpeed)

protected:
    UFUNCTION()
    void OnRep_Health(const FGameplayAttributeData& PreviousHealth);
    UFUNCTION()
    void OnRep_MoveSpeed(const FGameplayAttributeData& PreviousMoveSpeed);
};
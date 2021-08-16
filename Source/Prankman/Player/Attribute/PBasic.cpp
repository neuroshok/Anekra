#include "PBasic.h"

#include "Net/UnrealNetwork.h"
#include "Prankman/log.h"

UPAttributeBasic::UPAttributeBasic()
{
    InitHealth(100);
}

void UPAttributeBasic::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(UPAttributeBasic, Health);
    DOREPLIFETIME(UPAttributeBasic, MoveSpeed);
}

void UPAttributeBasic::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    if (Attribute == GetHealthAttribute())
    {
        NewValue = FMath::Clamp<float>(NewValue, 0, 100);
        GetOwningAbilitySystemComponent()->ApplyModToAttributeUnsafe(GetHealthAttribute(), EGameplayModOp::Additive, NewValue);
    }

    Super::PreAttributeChange(Attribute, NewValue);
}

void UPAttributeBasic::OnRep_Health(const FGameplayAttributeData& PreviousHealth)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UPAttributeBasic, Health, PreviousHealth);
}

void UPAttributeBasic::OnRep_MoveSpeed(const FGameplayAttributeData& PreviousMoveSpeed)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UPAttributeBasic, MoveSpeed, PreviousMoveSpeed);
}
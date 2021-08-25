#include "Basic.h"

#include "Net/UnrealNetwork.h"
#include "Anekra/Log.h"

UAttributeBasic::UAttributeBasic()
{
    InitHealth(100);
}

void UAttributeBasic::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(UAttributeBasic, Health);
    DOREPLIFETIME(UAttributeBasic, MoveSpeed);
}

void UAttributeBasic::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);
    if (Attribute == GetHealthAttribute())
    {
        NewValue = FMath::Clamp<float>(NewValue, 0, 100);
        //GetOwningAbilitySystemComponent()->ApplyModToAttributeUnsafe(GetHealthAttribute(), EGameplayModOp::Additive, NewValue);
    }

}

void UAttributeBasic::OnRep_Health(const FGameplayAttributeData& PreviousHealth)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeBasic, Health, PreviousHealth);
}

void UAttributeBasic::OnRep_MoveSpeed(const FGameplayAttributeData& PreviousMoveSpeed)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeBasic, MoveSpeed, PreviousMoveSpeed);
}
#include "ANKAbilitySystemComponent.h"

#include "ANKGameInstance.h"
#include "Kismet/GameplayStatics.h"

UANKAbilitySystemComponent::UANKAbilitySystemComponent()
{
    SetIsReplicated(true);
    ReplicationMode = EGameplayEffectReplicationMode::Full;
}

void UANKAbilitySystemComponent::AddTag(const FGameplayTag& GameplayTag)
{
    AddLooseGameplayTag(GameplayTag);
}

void UANKAbilitySystemComponent::RemoveTag(const FGameplayTag& GameplayTag)
{
    RemoveLooseGameplayTag(GameplayTag);
}

void UANKAbilitySystemComponent::BeginPlay()
{
    Super::BeginPlay();
    Effects = Cast<UANKGameInstance>(GetWorld()->GetGameInstance())->GetEffectAsset();
}

void UANKAbilitySystemComponent::BindAbilityActivationToInputComponent(UInputComponent* InputComponent, FGameplayAbilityInputBinds BindInfo)
{
    if (!InputComponent || BoundAbilities) return;
    Super::BindAbilityActivationToInputComponent(InputComponent, BindInfo);
    BoundAbilities = true;
}

void UANKAbilitySystemComponent::ApplyEffect(TSubclassOf<UGameplayEffect> Effect)
{
    FGameplayEffectContextHandle EffectContext = MakeEffectContext();
    EffectContext.AddSourceObject(this);
    ApplyGameplayEffectToSelf(Effect.GetDefaultObject(), 1, EffectContext);
}

FGameplayEffectSpecHandle UANKAbilitySystemComponent::ApplyEffectSpec(TSubclassOf<UGameplayEffect> Effect)
{
    FGameplayEffectContextHandle EffectContext = MakeEffectContext();
    EffectContext.AddSourceObject(this);
    FGameplayEffectSpecHandle EffectHandle = MakeOutgoingSpec(Effect, 1, EffectContext);
    check(EffectHandle.IsValid())
    ApplyGameplayEffectSpecToTarget(*EffectHandle.Data.Get(), this);
    return EffectHandle;
}

void UANKAbilitySystemComponent::RemoveEffectByTag(const FGameplayTag& GameplayTag)
{
    FGameplayTagContainer Tags;
    Tags.AddTag(GameplayTag);
    RemoveActiveEffectsWithGrantedTags(Tags);
}
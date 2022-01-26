#include "ANKAbilitySystemComponent.h"

#include "ANKGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "AbilitySystemGlobals.h"
#include "GameplayCueManager.h"

UANKAbilitySystemComponent::UANKAbilitySystemComponent()
{
    SetIsReplicated(true);
    ReplicationMode = EGameplayEffectReplicationMode::Full;
}

void UANKAbilitySystemComponent::AddTag(const FGameplayTag& GameplayTag)
{
    AddLooseGameplayTag(GameplayTag);
    // avoid stacks
    SetTagMapCount(GameplayTag, 1);
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
    if (!InputComponent) return;
    Super::BindAbilityActivationToInputComponent(InputComponent, BindInfo);
}

void UANKAbilitySystemComponent::ApplyEffect(TSubclassOf<UGameplayEffect> Effect)
{
    FGameplayEffectContextHandle EffectContext = MakeEffectContext();
    EffectContext.AddSourceObject(this);
    ApplyGameplayEffectToSelf(Effect.GetDefaultObject(), 1, EffectContext);
}

FGameplayEffectSpecHandle UANKAbilitySystemComponent::ApplyEffectSpec(TSubclassOf<UGameplayEffect> Effect, const FGameplayTag& Tag, float Magnitude)
{
    FGameplayEffectContextHandle EffectContext = MakeEffectContext();
    EffectContext.AddSourceObject(this);
    FGameplayEffectSpecHandle EffectHandle = MakeOutgoingSpec(Effect, 1, EffectContext);
    EffectHandle.Data->SetSetByCallerMagnitude(Tag, Magnitude);
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

void UANKAbilitySystemComponent::ExecuteLocalCue(const FGameplayTag& GameplayCueTag, AActor* Target, const FGameplayCueParameters& GameplayCueParameters)
{
    if (Target == nullptr) Target = GetAvatarActor();
    UAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(Target, GameplayCueTag, EGameplayCueEvent::Type::Executed, GameplayCueParameters);
}

void UANKAbilitySystemComponent::AddLocalCue(const FGameplayTag& GameplayCueTag, AActor* Target, const FGameplayCueParameters& GameplayCueParameters)
{
    if (Target == nullptr) Target = GetAvatarActor();
    UAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(Target, GameplayCueTag, EGameplayCueEvent::Type::OnActive, GameplayCueParameters);
    UAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(Target, GameplayCueTag, EGameplayCueEvent::Type::WhileActive, GameplayCueParameters);
}

void UANKAbilitySystemComponent::RemoveLocalCue(const FGameplayTag& GameplayCueTag, AActor* Target, const FGameplayCueParameters& GameplayCueParameters)
{
    if (Target == nullptr) Target = GetAvatarActor();
    UAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(Target, GameplayCueTag, EGameplayCueEvent::Type::Removed, GameplayCueParameters);
}
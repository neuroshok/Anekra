#include "ANKAbilitySystemComponent.h"

#include "ANKGameInstance.h"
#include "Kismet/GameplayStatics.h"

UANKAbilitySystemComponent::UANKAbilitySystemComponent()
{
    SetIsReplicated(true);
    ReplicationMode = EGameplayEffectReplicationMode::Full;
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

void UANKAbilitySystemComponent::RemoveEffect(const FGameplayTag& GameplayTag)
{
    FGameplayTagContainer Tags;
    Tags.AddTag(GameplayTag);
    RemoveActiveEffectsWithGrantedTags(Tags);
}
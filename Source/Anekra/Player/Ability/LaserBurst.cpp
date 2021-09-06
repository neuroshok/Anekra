#include "LaserBurst.h"

#include "Anekra/Game/ANKAbilitySystemComponent.h"
#include "Anekra/Game/ANKTag.h"
#include "Anekra/Player/Hero.h"
#include "Anekra/Game/ANKGameState.h"
#include "Task/LaserTargetTask.h"

void ULaserBurst::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                  const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* EventData)
{
    if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
    {
        if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
        {
            EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
            return;
        }

        FGameplayEffectContextHandle EffectContext =  MakeEffectContext(Handle, ActorInfo);
        EffectContext.AddSourceObject(GetAbilitySystemComponent());
        EffectContext.AddInstigator(ActorInfo->AvatarActor.Get(), ActorInfo->AvatarActor.Get());
        auto H = GetAbilitySystemComponent()->ApplyGameplayEffectToSelf(GetEffects()->LaserTargeting.GetDefaultObject(), 1, EffectContext);

        auto Task = ULaserTargetTask::Create(this);
        Task->OnCompleteDelegate.AddUObject(this, &ULaserBurst::OnCompleted);

        Task->ReadyForActivation();

    }
}

void ULaserBurst::OnCompleted()
{
    for (auto Player : GetANKGameState()->GetPlayersAtCellPosition(GetANKGameState()->GetCellPosition(ComputeTargetLocation())))
    {
        auto ANKPlayer = Cast<AANKPlayerState>(Player);

        ANKPlayer->GetAbilitySystemComponent()->ApplyEffectSpec(GetEffects()->DamageEffect, ANKTag.Effect.Damage, -25);
    }

    GetAbilitySystemComponent()->RemoveEffectByTag(ANKTag.State.LaserTargeting);

    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}

FVector ULaserBurst::ComputeTargetLocation()
{
    auto Hero = GetHero();
    auto SourceLocation = Hero->GetCamera()->GetComponentLocation();
    auto AimLocation = Hero->GetCamera()->GetForwardVector();
    AimLocation = SourceLocation + (AimLocation + FVector{0, 0, 0.3f}) * 5000;

    FHitResult Result;
    FCollisionObjectQueryParams ObjectParams;
    ObjectParams.ObjectTypesToQuery = FCollisionObjectQueryParams::AllDynamicObjects;
    FCollisionQueryParams Params;
    Params.TraceTag = "trace";
    GetWorld()->DebugDrawTraceTag = "trace";
    GetWorld()->LineTraceSingleByObjectType(Result, SourceLocation, AimLocation, ObjectParams, Params);
    return Result.Location;
}
#include "Anekra/Player/Hero.h"

#include "ANKHUD.h"
#include "ANKPlayerController.h"
#include "Anekra/World/Cell.h"
#include "Anekra/Player/Ability/Unlock.h"
#include "Anekra/Game/ANKAbilitySystemComponent.h"
#include "Anekra/Player/Ability/Binding.h"

#include "Abilities/GameplayAbilityTypes.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Anekra/Log.h"
#include "Anekra/Game/ANKTag.h"

AHero::AHero()
{
    bReplicates = true;

    // springarm
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
    SpringArmComponent->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 90.0f), FRotator(-30, 0.0f, 0.0f));
    SpringArmComponent->TargetArmLength = 800.f;
    //SpringArmComponent->bEnableCameraLag = true;
    SpringArmComponent->CameraLagSpeed = 30.0f;
    SpringArmComponent->SetupAttachment(GetMesh());

    // camera
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

    SpringArmComponent->bUsePawnControlRotation = true;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->bUseControllerDesiredRotation = true;
    GetCharacterMovement()->bIgnoreBaseRotation = true;

}

void AHero::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();

    AANKPlayerState* ANKPlayerState = Cast<AANKPlayerState>(GetPlayerState());
    if (!ANKPlayerState) return;

    ANKAbilitySystemComponent = ANKPlayerState->GetAbilitySystemComponent();
    ANKAbilitySystemComponent->InitAbilityActorInfo(ANKPlayerState, this);
    TryBindAbilities();

    auto ANKPlayerController = Cast<AANKPlayerController>(GetOwner());
    if (!ANKPlayerController) return;
    Cast<AANKHUD>(ANKPlayerController->GetHUD())->Initialize();
}

// server
void AHero::PossessedBy(AController* PlayerController)
{
    Super::PossessedBy(PlayerController);
    AANKPlayerState* ANKPlayerState = Cast<AANKPlayerState>(GetPlayerState());
    check(ANKPlayerState);

    ANKAbilitySystemComponent = ANKPlayerState->GetAbilitySystemComponent();
    ANKAbilitySystemComponent->InitAbilityActorInfo(ANKPlayerState, this);

    ANKAbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(UUnlockAbility::StaticClass(), 1, static_cast<int32>(EBinding::Unlock), this));
}

// Called when the game starts or when spawned
void AHero::BeginPlay()
{
    Super::BeginPlay();
}

void AHero::AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce)
{
    Super::AddMovementInput(WorldDirection, ScaleValue, bForce);

}

void AHero::MoveForward(float Value)
{
    if (Controller && Value != 0.0f)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation{ 0, Rotation.Yaw, 0 };

        const FVector Direction = FRotationMatrix{ YawRotation }.GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
    UpdateMovingTag();
}

void AHero::MoveBackward(float Value)
{
    MoveForward(-Value);
}

void AHero::MoveLeft(float Value)
{
    if (Controller && Value != 0.0f)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation{ 0, Rotation.Yaw, 0 };

        const FVector Direction = FRotationMatrix{ YawRotation }.GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, -Value);
    }
    UpdateMovingTag();
}

void AHero::MoveRight(float Value)
{
    MoveLeft(-Value);
}

void AHero::MoveYaw(float Value)
{
    FRotator Rotation = Controller->GetControlRotation();
    Rotation.Yaw += Value;
    Controller->SetControlRotation(Rotation);
}
void AHero::MovePitch(float Value)
{
    FRotator Rotation = Controller->GetControlRotation();
    Rotation.Pitch += Value;
    Controller->SetControlRotation(Rotation);
}


void AHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    InputComponent->BindAxis("MoveForward", this, &AHero::MoveForward);
    InputComponent->BindAxis("MoveBackward", this, &AHero::MoveBackward);
    InputComponent->BindAxis("MoveLeft", this, &AHero::MoveLeft);
    InputComponent->BindAxis("MoveRight", this, &AHero::MoveRight);
    InputComponent->BindAxis("RotateX", this, &AHero::MoveYaw);
    InputComponent->BindAxis("RotateY", this, &AHero::MovePitch);

    InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

    TryBindAbilities();
}

UANKAbilitySystemComponent* AHero::GetAbilitySystemComponent() const
{
    return ANKAbilitySystemComponent.Get();
}

void AHero::UpdateMovingTag()
{
    if (GetAbilitySystemComponent())
    {
        if (!GetVelocity().IsZero())
        {
            if (!bHasMovingEffect)
            {
                GetAbilitySystemComponent()->AddTag(ANKTag.State.Moving);
                bHasMovingEffect = true;
            }
        }
        else
        {
            if (bHasMovingEffect)
            {
                GetAbilitySystemComponent()->RemoveTag(ANKTag.State.Moving);
                bHasMovingEffect = false;
            }
        }
    }
}

void AHero::TryBindAbilities()
{
    if (!ANKAbilitySystemComponent.IsValid()) return;

    ANKAbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent,
                                                                   FGameplayAbilityInputBinds(
                                                                   FString("ConfirmTarget"),
                                                                   FString("CancelTarget"),
                                                                   FString("EBinding"), static_cast<int32>(EBinding::Confirm), static_cast<int32>(EBinding::Cancel)));
}
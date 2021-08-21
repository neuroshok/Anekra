#include "Prankman/Player/PHero.h"

#include "PHUD.h"
#include "PPlayerController.h"
#include "Prankman/World/PCell.h"
#include "Prankman/Player/Ability/PUnlock.h"
#include "Prankman/Game/PAbilitySystemComponent.h"
#include "Prankman/Player/Ability/PBinding.h"

#include "Abilities/GameplayAbilityTypes.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Prankman/log.h"

APHero::APHero()
{
    bReplicates = true;

    // springarm
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
    SpringArmComponent->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 90.0f), FRotator(-30, 0.0f, 0.0f));
    SpringArmComponent->TargetArmLength = 400.f;
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

void APHero::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();

    APPlayerState* PPlayerState = Cast<APPlayerState>(GetPlayerState());
    check(PPlayerState);

    PAbilitySystemComponent = Cast<UPAbilitySystemComponent>(PPlayerState->GetAbilitySystemComponent());
    PAbilitySystemComponent->InitAbilityActorInfo(PPlayerState, this);
    TryBindAbilities();

    auto PPlayerController = Cast<APPlayerController>(GetOwner());
    if (!PPlayerController) return;
    Cast<APHUD>(PPlayerController->GetHUD())->Initialize();
}

/// server
void APHero::PossessedBy(AController* PlayerController)
{
    Super::PossessedBy(PlayerController);
    APPlayerState* PPlayerState = Cast<APPlayerState>(GetPlayerState());
    check(PPlayerState);

    PAbilitySystemComponent = Cast<UPAbilitySystemComponent>(PPlayerState->GetAbilitySystemComponent());
    PAbilitySystemComponent->InitAbilityActorInfo(PPlayerState, this);

    PAbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(UPUnlockAbility::StaticClass(), 1, static_cast<int32>(EPBinding::Unlock), this));
}

// Called when the game starts or when spawned
void APHero::BeginPlay()
{
    Super::BeginPlay();
}

void APHero::MoveForward(float Value)
{
    if (Controller && Value != 0.0f)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation{ 0, Rotation.Yaw, 0 };

        const FVector Direction = FRotationMatrix{ YawRotation }.GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void APHero::MoveBackward(float Value)
{
    MoveForward(-Value);
}

void APHero::MoveLeft(float Value)
{
    if (Controller && Value != 0.0f)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation{ 0, Rotation.Yaw, 0 };

        const FVector Direction = FRotationMatrix{ YawRotation }.GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, -Value);
    }
}

void APHero::MoveRight(float Value)
{
    MoveLeft(-Value);
}

void APHero::MoveYaw(float Value)
{
    FRotator Rotation = Controller->GetControlRotation();
    Rotation.Yaw += Value;
    Controller->SetControlRotation(Rotation);
}
void APHero::MovePitch(float Value)
{
    FRotator Rotation = Controller->GetControlRotation();
    Rotation.Pitch += Value;
    Controller->SetControlRotation(Rotation);
}


void APHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    InputComponent->BindAxis("MoveForward", this, &APHero::MoveForward);
    InputComponent->BindAxis("MoveBackward", this, &APHero::MoveBackward);
    InputComponent->BindAxis("MoveLeft", this, &APHero::MoveLeft);
    InputComponent->BindAxis("MoveRight", this, &APHero::MoveRight);
    InputComponent->BindAxis("RotateX", this, &APHero::MoveYaw);
    InputComponent->BindAxis("RotateY", this, &APHero::MovePitch);

    InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

    TryBindAbilities();
}

UAbilitySystemComponent* APHero::GetAbilitySystemComponent() const
{
    return PAbilitySystemComponent.Get();
}

void APHero::TryBindAbilities()
{
    if (!PAbilitySystemComponent.IsValid()) return;

    PAbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent,
                                                                   FGameplayAbilityInputBinds(
                                                                   FString("ConfirmTarget"),
                                                                   FString("CancelTarget"),
                                                                   FString("EPBinding"), static_cast<int32>(EPBinding::Confirm), static_cast<int32>(EPBinding::Cancel)));
}
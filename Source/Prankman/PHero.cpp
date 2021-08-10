#include "PHero.h"
#include "log.h"
#include "PCell.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

APHero::APHero()
{

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

    bReplicates = true;
    //bReplicateMovement = true;

    //SetActorEnableCollision(false);
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent->bUsePawnControlRotation = true;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->bUseControllerDesiredRotation = true;
    GetCharacterMovement()->bIgnoreBaseRotation = true;

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

// Called every frame
void APHero::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
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
}
#include "AssignmentPawn.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "AssignmentPlayerController.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"


AAssignmentPawn::AAssignmentPawn()
{
    PrimaryActorTick.bCanEverTick = false;

    SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    RootComponent = SphereComp;

    SkeletalComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletlComp"));
    SkeletalComp->SetupAttachment(RootComponent);

    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
    SpringArmComp->SetupAttachment(RootComponent);
    SpringArmComp->TargetArmLength = 600.0f;
    SpringArmComp->bUsePawnControlRotation = false;

    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
    CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
    CameraComp->bUsePawnControlRotation = false;

    MovementComp = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComp"));
    MovementComp->SetUpdatedComponent(RootComponent);
    MovementComp->MaxSpeed = 600.f;
}

void AAssignmentPawn::BeginPlay()
{
    Super::BeginPlay();

    if (CameraComp)
    {
        Pitch = CameraComp->GetRelativeRotation().Pitch;
    }
}

void AAssignmentPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    APawn::SetupPlayerInputComponent(PlayerInputComponent);

    if (TObjectPtr<UEnhancedInputComponent>EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (TObjectPtr<AAssignmentPlayerController> PlayerController = Cast<AAssignmentPlayerController>(GetController()))
        {
            if (PlayerController->MoveAction)
            {
                EnhancedInput->BindAction(
                    PlayerController->MoveAction,
                    ETriggerEvent::Triggered,
                    this,
                    &AAssignmentPawn::Move
                );
            }

            if (PlayerController->LookAction)
            {
                EnhancedInput->BindAction(
                    PlayerController->LookAction,
                    ETriggerEvent::Triggered,
                    this,
                    &AAssignmentPawn::Look
                );
            }
        }
    }
}

void AAssignmentPawn::Move(const FInputActionValue& value)
{
    if (!Controller) return;

    const FVector2D MoveInput = value.Get<FVector2D>();

    if (!FMath::IsNearlyZero(MoveInput.X))
    {
        AddMovementInput(GetActorForwardVector(), MoveInput.X);
    }

    if (!FMath::IsNearlyZero(MoveInput.Y))
    {
        AddMovementInput(GetActorRightVector(), MoveInput.Y);
    }
}

void AAssignmentPawn::Look(const FInputActionValue& value)
{
    const FVector2D LookInput = value.Get<FVector2D>();
    if (LookInput.IsNearlyZero() || !CameraComp)
    {
        return;
    }
    const float DeltaYaw = LookInput.X * MouseSensitivity;
    AddActorLocalRotation(FRotator(0.0f, DeltaYaw, 0.0f));

    Pitch -= LookInput.Y * MouseSensitivity;
    Pitch = FMath::Clamp(Pitch, MinPitch, MaxPitch);

    SpringArmComp->SetRelativeRotation(FRotator(Pitch, 0.0f, 0.0f));
}
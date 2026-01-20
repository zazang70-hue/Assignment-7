#include "AssignmentPlayerController.h"
#include "EnhancedInputSubsystems.h"


AAssignmentPlayerController::AAssignmentPlayerController()
    : InputMappingContext(nullptr),
    MoveAction(nullptr),
    LookAction(nullptr)
{
    
}

void AAssignmentPlayerController :: BeginPlay()
{
    Super::BeginPlay();

    if (TObjectPtr<ULocalPlayer>LocalPlayer = GetLocalPlayer())
    {
        if (TObjectPtr<UEnhancedInputLocalPlayerSubsystem> Subsystem =
            LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            if (InputMappingContext)
            {
                Subsystem->AddMappingContext(InputMappingContext, 0);
            }
        }
    }
}
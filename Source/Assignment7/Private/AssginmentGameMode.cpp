#include "AssginmentGameMode.h"
#include "AssignmentPawn.h"
#include "AssignmentPlayerController.h"

AAssginmentGameMode::AAssginmentGameMode()
{
    DefaultPawnClass = AAssignmentPawn::StaticClass();
    PlayerControllerClass = AAssignmentPlayerController::StaticClass();
}

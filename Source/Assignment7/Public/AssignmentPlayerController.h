#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AssignmentPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class ASSIGNMENT7_API AAssignmentPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAssignmentPlayerController();

	UPROPERTY(EditAnywhere, Blueprintreadwrite, Category = "Input");
	TObjectPtr<UInputMappingContext> InputMappingContext;
	UPROPERTY(EditAnywhere, Blueprintreadwrite, Category = "Input");
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, Blueprintreadwrite, Category = "Input");
	TObjectPtr<UInputAction> LookAction;

protected:
	virtual void BeginPlay() override;
};

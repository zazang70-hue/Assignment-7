#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AssignmentPawn.generated.h"

class USphereComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UFloatingPawnMovement;
struct FInputActionValue;

UCLASS()
class ASSIGNMENT7_API AAssignmentPawn : public APawn
{
	GENERATED_BODY()

public:

	AAssignmentPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	TObjectPtr<UFloatingPawnMovement> MovementComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components");
	TObjectPtr<USphereComponent>SphereComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components");
	TObjectPtr<USkeletalMeshComponent>SkeletalComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera");
	TObjectPtr<USpringArmComponent>SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera");
	TObjectPtr<UCameraComponent>CameraComp;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;

	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);

	UPROPERTY(EditAnywhere, Category = "Look")
	float MouseSensitivity = 0.8f;

	UPROPERTY(EditAnywhere, Category = "Look")
	float MinPitch = -80.0f;

	UPROPERTY(EditAnywhere, Category = "Look")
	float MaxPitch = 80.0f;



private:

	float Yaw = 0.0f;
	float Pitch = 0.0f;

};

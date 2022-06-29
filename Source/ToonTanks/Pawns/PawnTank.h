// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PawnBase.h"
#include "PawnTank.generated.h"

/**
 * 
 */
class APLayerController;
UCLASS()
class TOONTANKS_API APawnTank : public APawnBase
{
	GENERATED_BODY()
	
public:
	APawnTank();
	virtual void Tick(float DeltaTime) override;

	bool GetIsPlayerAlive();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void HandleDeath() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Components", meta = (AllowPrivateAccess = "true"));
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Components", meta = (AllowPrivateAccess = "true"));
	UCameraComponent* Cam;

	FVector MoveDirection;
	FQuat RotateDirection;
	
	APlayerController* PlayerControllerRef;
	
	bool bIsPlayerAlive= true;

	void CalculateMoveSpeed(float Value);
	void CalculateTurnSpeed(float Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"));
	float MoveSpeed = 600.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"));
	float TurnSpeed = 200.f;

	void Move();
	void Rotate();
	
};

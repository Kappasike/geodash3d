// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "JumperChar.generated.h"

UCLASS()
class GEODASH3D_API AJumperChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJumperChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveRight(float value);

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	void Start();

	void Stop();

	void JumpGD();

	void Straighten();

	float TurnRate;
	float LookRate;
	float currentRot;
	float roll;

	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* BoomArm;

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* GeoCube;

	UPROPERTY(EditAnywhere, Category = Movement)
		float PitchValue;

	UPROPERTY(EditAnywhere, Category = Movement)
		float YawValue;

	UPROPERTY(EditAnywhere, Category = Movement)
		float RollValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpinnyThing)
		FRotator RotationRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpinnyThing)
		FRotator DefaultRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpinnyThing)
		FRotator UpsideDownRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpinnyThing)
		float Speed;
};

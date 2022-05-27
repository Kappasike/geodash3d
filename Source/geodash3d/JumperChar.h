// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "JumperChar.generated.h"

class UNiagaraSystem;
class USoundBase;

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

	void Straighten();

	float TurnRate;
	float LookRate;
	float currentRot;
	float roll;

	bool bDead;

	UFUNCTION()
		void StartJump(float value);

	UFUNCTION()
		void StopJump();

	UFUNCTION()
		void Explode();

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = "UI Hud")
		TSubclassOf<UUserWidget> Player_Info_Widget_Class;
	UUserWidget* Player_Info_Widget;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int Attempts = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Death")
		UNiagaraSystem* NS_Explosion;

	UPROPERTY(EditDefaultsOnly, Category = "Death")
		USoundBase* SB_Explosion;
};

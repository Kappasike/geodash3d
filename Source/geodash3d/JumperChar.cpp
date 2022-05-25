// Fill out your copyright notice in the Description page of Project Settings.


#include "JumperChar.h"

// Sets default values
AJumperChar::AJumperChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	BoomArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	BoomArm->SetupAttachment(RootComponent);
	BoomArm->TargetArmLength = 500.f;
	BoomArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(BoomArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->MaxWalkSpeed = 0.f;

	LookRate = 40.0f;

	PitchValue = 0.f;
	YawValue = 0.f;
	RollValue = 1.f;
}

// Called when the game starts or when spawned
void AJumperChar::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AJumperChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveRight(1.f);

	if (GetCharacterMovement()->IsFalling()) {
		FQuat QuatRotation = FQuat(FRotator(PitchValue, YawValue, RollValue));

		AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None); 
	}
	else {
		FQuat DefaultRot = FQuat(FRotator(0.f, 0.f, 0.f));
		SetActorRotation(DefaultRot);
	}
}

// Called to bind functionality to input
void AJumperChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("TurnRate", this, &AJumperChar::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AJumperChar::LookUpAtRate);

	PlayerInputComponent->BindAction("JumpGD", IE_Pressed, this, &AJumperChar::JumpGD);
	PlayerInputComponent->BindAction("Start", IE_Pressed, this, &AJumperChar::Start);
	PlayerInputComponent->BindAction("Stop", IE_Pressed, this, &AJumperChar::Stop);
}

void AJumperChar::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * GetWorld()->GetDeltaSeconds() * TurnRate);
}

void AJumperChar::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * GetWorld()->GetDeltaSeconds() * LookRate);
}

void AJumperChar::JumpGD()
{
	AJumperChar::Jump();
}

void AJumperChar::Start()
{
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
}

void AJumperChar::Stop()
{
	GetCharacterMovement()->MaxWalkSpeed = 0.f;
	SetActorLocation(FVector(590.0f, -1350.0f, 112.f), false, 0, ETeleportType::None);
}

void AJumperChar::MoveRight(float value)
{
	/*const FRotator Yaw(0, 0, 0);
	const FVector direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y);

	AddMovementInput(FVector(90.f), value);
	*/
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, value);
}
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

	GeoCube = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Drippy Cube"));
	GeoCube->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CubeAsset(TEXT("SkeletalMesh'/Game/Mesh/othermodel/geometrydashrender.geometrydashrender'"));

	if (CubeAsset.Succeeded())
	{
		GeoCube->SetSkeletalMesh(CubeAsset.Object);
		GeoCube->SetRelativeLocation(FVector(0.f, 0.f, -3.0f));
		GeoCube->SetRelativeScale3D(FVector(0.84f, 0.84f, 0.84f));
		GeoCube->SetRelativeRotation(FQuat(FRotator(0.f, 0.f, 0.f)));
	}

	GetCharacterMovement()->MaxWalkSpeed = 0.f;
	GetCharacterMovement()->Mass = 500.f;
	GetCharacterMovement()->GravityScale = 4.f;
	GetCharacterMovement()->JumpZVelocity = 800.f;
	

	LookRate = 40.0f;
	TurnRate = 0.f;

	PitchValue = 0.f;
	YawValue = 0.f;
	RollValue = 3.f;
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
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("IsFalling=true"));
		FQuat QuatRotation = FQuat(FRotator(PitchValue, YawValue, RollValue));

		GeoCube->AddLocalRotation(QuatRotation, false, 0, ETeleportType::None);
	}
	else {
		FQuat DefaultRot = FQuat(FRotator(0.f, 0.f, 0.f));

		GeoCube->SetRelativeRotation(DefaultRot);
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
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
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
// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeActor.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACubeActor::ACubeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	CollisionBox->SetBoxExtent(FVector(26.f, 26.f, 26.f));
	CollisionBox->SetCollisionProfileName("Trigger");
	RootComponent = CollisionBox;

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACubeActor::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ACubeActor::OnOverlapEnd);

	CubeObj = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeComponent"));
	CubeObj->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeAsset(TEXT("StaticMesh'/Game/Mesh/geocubeblock.geocubeblock'"));

	if (CubeAsset.Succeeded())
	{
		CubeObj->SetStaticMesh(CubeAsset.Object);
		CubeObj->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		CubeObj->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));
		CubeObj->SetRelativeRotation(FQuat(FRotator(0.f, 0.f, 0.f)));
	}
}

// Called when the game starts or when spawned
void ACubeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACubeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACubeActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "Overlap Begin Function Called");

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/Levels/YouAreDead"), TRAVEL_Absolute);
}

void ACubeActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Overlap End Function Called");
}


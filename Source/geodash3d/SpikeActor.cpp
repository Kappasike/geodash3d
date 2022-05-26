// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikeActor.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpikeActor::ASpikeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	CollisionBox->SetBoxExtent(FVector(26.f, 26.f, 26.f));
	CollisionBox->SetCollisionProfileName("Trigger");
	RootComponent = CollisionBox;

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ASpikeActor::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ASpikeActor::OnOverlapEnd);

	SpikeObj = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpikeComponent"));
	SpikeObj->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SpikeAsset(TEXT("StaticMesh'/Game/Mesh/GeoSpike.GeoSpike'"));

	if (SpikeAsset.Succeeded())
	{
		SpikeObj->SetStaticMesh(SpikeAsset.Object);
		SpikeObj->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		SpikeObj->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));
		SpikeObj->SetRelativeRotation(FQuat(FRotator(0.f, 0.f, 0.f)));
	}
}

// Called when the game starts or when spawned
void ASpikeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpikeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpikeActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "Overlap Begin Function Called");

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/Levels/YouAreDead"), TRAVEL_Absolute);
}

void ASpikeActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Overlap End Function Called");
}


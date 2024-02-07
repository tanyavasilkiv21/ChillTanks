// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPoint.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerPoint::APlayerPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerPointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Point Mesh"));
	RootComponent = PlayerPointMesh;
}

// Called when the game starts or when spawned
void APlayerPoint::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerPointMesh->OnComponentBeginOverlap.AddDynamic(this, &APlayerPoint::BeginOverlap);
}

void APlayerPoint::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor == Player)
	{
		Destroy();
	}
}

// Called every frame
void APlayerPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


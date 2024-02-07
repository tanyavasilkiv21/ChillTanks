// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakingWall.h"

#include "HitBoxComponent.h"


// Sets default values
ABreakingWall::ABreakingWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall Mesh"));
	RootComponent = WallMesh;
	HitBox = CreateDefaultSubobject<UHitBoxComponent>(TEXT("Hit Box"));
	HitBox->SetupAttachment(WallMesh);
	
}

// Called when the game starts or when spawned
void ABreakingWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABreakingWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABreakingWall::HandleDistraction()
{
	Destroy();
}


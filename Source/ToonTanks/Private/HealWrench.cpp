// Fill out your copyright notice in the Description page of Project Settings.


#include "HealWrench.h"

#include "HitBoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
AHealWrench::AHealWrench()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WrenchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wrench"));
	RootComponent = WrenchMesh;
}

// Called when the game starts or when spawned
void AHealWrench::BeginPlay()
{
	Super::BeginPlay();
	WrenchMesh->OnComponentBeginOverlap.AddDynamic(this, &AHealWrench::BeginOverlap);
	StartLocation = GetActorLocation();
}

void AHealWrench::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto HitBox = Cast<UHitBoxComponent>(OtherComp);
	if(HitBox)
	{
		HitBox->DamageHealed(Heal);
		this->Destroy();
		if(LaunchSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation(), GetActorRotation());
		}
		if(HitParticles)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,HitParticles,
				OtherActor->GetActorLocation(), OtherActor->GetActorRotation());
			
		}
	}
}

void AHealWrench::MoveWrench(float DeltaTime)
{
	if(DistanceForMove <= FVector::Dist(StartLocation, GetActorLocation()))
	{
		FVector MoveDirection = WrenchVelocity.GetSafeNormal();
		StartLocation += (MoveDirection * DistanceForMove);
		SetActorLocation(StartLocation);
		WrenchVelocity = -WrenchVelocity;
	}
	else
	{
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation += (DeltaTime * WrenchVelocity);
		SetActorLocation(CurrentLocation);
	}
}

// Called every frame
void AHealWrench::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveWrench(DeltaTime);
	
}


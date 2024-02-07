// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "HitBoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraShakeBase.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));
	MovementComponent->InitialSpeed = 2000.f;
	MovementComponent->MaxSpeed = 2000.f;

	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System Component"));
	TrailParticles->SetupAttachment(ProjectileMesh);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	ProjectileMesh->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::BeginOverlap);
	
	if(LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation(), GetActorRotation());
	}
}

void AProjectile::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto const MyOwner = GetOwner();
	if(MyOwner == nullptr)
	{
		Destroy();
		return;
	};
	auto HitBox = Cast<UHitBoxComponent>(OtherComp);
	if(OtherActor && OtherActor!= nullptr && OtherActor != MyOwner && !(OtherActor->IsHidden()))
	{
		if(HitBox)
		{
			HitBox->DamageReduced(Damage);
			this->Destroy();
		}
		else
		{
			return;
		}
		if(HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}
		if(HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation(), GetActorRotation());
		}
		if(HitParticles && HitSound)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
		}
	}
	Destroy();
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


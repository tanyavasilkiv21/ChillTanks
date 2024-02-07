// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "HitBoxComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;
	HitBoxBase = CreateDefaultSubobject<UHitBoxComponent>(TEXT("HitBox Base"));
	HitBoxBase->SetupAttachment(BaseMesh);
	
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);
	HitBoxTurret = CreateDefaultSubobject<UHitBoxComponent>(TEXT("HitBox Turret"));
	HitBoxTurret->SetupAttachment(TurretMesh);
	HitBoxGun = CreateDefaultSubobject<UHitBoxComponent>(TEXT("HitBox Gun"));
	HitBoxGun->SetupAttachment(TurretMesh);
	
	ProjectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn"));
	ProjectileSpawn-> SetupAttachment(TurretMesh);

}

void ABasePawn::HandleDistraction()
{
	//effects
	if(DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(), GetActorRotation());
	}
	if(HitParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
	}
	if(HitCameraShakeDeathClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeDeathClass);
	}
}

void ABasePawn::RotatePawn(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(), LookAtRotation,
		UGameplayStatics::GetWorldDeltaSeconds(this), 25.f)
		);
}

void ABasePawn::Fire()
{
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
		ProjectileSpawn->GetComponentLocation(),ProjectileSpawn->GetComponentRotation());
	if(Projectile)
	{
		Projectile->SetOwner(this);
	}
}

UStaticMeshComponent* ABasePawn::GetBaseMesh()
{
	return BaseMesh;
}

UStaticMeshComponent* ABasePawn::GetTurretMesh()
{
	return TurretMesh;
}

USceneComponent* ABasePawn::GetProjectileSpawn()
{
	return ProjectileSpawn;
}





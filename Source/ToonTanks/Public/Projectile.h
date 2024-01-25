// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"


UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();

protected:
	virtual void BeginPlay() override;
	
private:
	//variables of projectile
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent *MovementComponent;
	
	UPROPERTY(EditAnywhere, Category= "Combat")
	float Damage = 20.f;
	
	//variables for effects
	UPROPERTY(EditAnywhere, Category= "Combat")
	class UParticleSystem* HitParticles;

	UPROPERTY(VisibleAnywhere, Category= "Combat")
	class UParticleSystemComponent * TrailParticles;

	UPROPERTY(EditAnywhere, Category= "Combat")
	class USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category= "Combat")
	USoundBase* HitSound;
	
	UPROPERTY(EditAnywhere, Category= "Combat")
	TSubclassOf<UCameraShakeBase> HitCameraShakeClass;
	
	//functions
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult);
	
	// UFUNCTION()
	// void OverlapEnd(UPrimitiveComponent* OverlappedComponent,
	// 	AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
public:
	virtual void Tick(float DeltaTime) override;

};

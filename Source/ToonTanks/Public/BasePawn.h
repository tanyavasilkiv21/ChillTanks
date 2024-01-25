// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	 //functions
	ABasePawn();
	virtual void HandleDistraction();
	UStaticMeshComponent* GetBaseMesh();
	UStaticMeshComponent* GetTurretMesh();
	USceneComponent* GetProjectileSpawn();
	
protected:
	//functions
	virtual void RotatePawn(FVector LookAtTarget);
	void Fire();
	
private:
	//variables for pawn
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawn;

	//variables for hit boxes
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UHitBoxComponent* HitBoxBase;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UHitBoxComponent* HitBoxTurret;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UHitBoxComponent* HitBoxGun;
	
	//variable for projectile
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;
	
	//variable for effects
	UPROPERTY(EditAnywhere, Category= "Combat")
	class UParticleSystem* HitParticles;
	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* DeathSound;
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<UCameraShakeBase> HitCameraShakeDeathClass;
};

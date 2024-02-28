// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealWrench.generated.h"

UCLASS()
class TOONTANKS_API AHealWrench : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealWrench();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	//mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WrenchMesh;
	//heal
	float Heal = 20.f;
	//overlap
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult);
	//move
	float DistanceForMove = 50.f;
	FVector StartLocation;
	FVector WrenchVelocity = {0, 0, 70};
	void MoveWrench(float DeltaTime);
	//efects
	UPROPERTY(EditAnywhere, Category= "Combat")
	class UNiagaraSystem* HitParticles;
	UPROPERTY(EditAnywhere, Category= "Combat")
	class USoundBase* LaunchSound;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

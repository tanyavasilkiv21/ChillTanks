// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerPoint.generated.h"

UCLASS()
class TOONTANKS_API APlayerPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PlayerPointMesh;
	class ATank* Player;
	class AToonTanksGameMode* GameMode;
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult);
	//efects
	UPROPERTY(EditAnywhere, Category= "Combat")
	class USoundBase* LaunchSound;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

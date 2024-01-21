// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
public:
	ATank();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void HandleDistraction() override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(VisibleAnywhere,  Category= "Components")
	class USpringArmComponent * SpringArm;
	
	UPROPERTY(VisibleAnywhere, Category= "Components")
	class UCameraComponent * Camera;
	
	UPROPERTY(EditAnywhere,  Category= "Movement")
	float Speed = 6000.f;
	
	UPROPERTY(EditAnywhere,  Category= "Movement")
	float TurnRate = 200.f;
	
	void Move(float Value);
	void Turn(float Value);
	
	void RotatePawn(FVector LookAtTarget) override;
	APlayerController* TankPlayerController;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	APlayerController* GetTankPlayerController() const;
};

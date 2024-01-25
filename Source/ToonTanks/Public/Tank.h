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
	//functions
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void HandleDistraction() override;
protected:
	
	virtual void BeginPlay() override;
	
private:
	//variables for camera
	UPROPERTY(VisibleAnywhere,  Category= "Components")
	class USpringArmComponent * SpringArm;
	UPROPERTY(VisibleAnywhere, Category= "Components")
	class UCameraComponent * Camera;
	
	//variables for tank
	UPROPERTY(EditAnywhere,  Category= "Movement")
	float Speed = 6000.f;
	UPROPERTY(EditAnywhere,  Category= "Movement")
	float TurnRate = 200.f;
	
	class AToonTanksPlayerController* TankPlayerController;
	
	//functions
	virtual void RotatePawn(FVector LookAtTarget) override;
	void Move(float Value);
	void Turn(float Value);
	
public:	
	virtual void Tick(float DeltaTime) override;
	APlayerController* GetTankPlayerController() const;
};

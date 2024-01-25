// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "ToonTanksPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Navigation/PathFollowingComponent.h"

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spting Arm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	GetBaseMesh()->SetSimulatePhysics(true);
	GetBaseMesh()->SetRelativeRotation(FRotator::ZeroRotator);
	GetTurretMesh()->SetRelativeRotation(FRotator::ZeroRotator);
	SetActorTickEnabled(false);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::HandleDistraction()
{
	Super::HandleDistraction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	TankPlayerController = Cast<AToonTanksPlayerController>(GetController());
}

void ATank::Move(float Value)
{
	GetBaseMesh()->AddImpulse(GetBaseMesh()->GetForwardVector() * 9000.f * Value);
}

void ATank::Turn(float Value)
{
	FRotator RotationActor = FRotator::ZeroRotator;
	RotationActor.Yaw = Value * (UGameplayStatics::GetWorldDeltaSeconds(this)) * TurnRate;
	GetBaseMesh()->AddRelativeRotation(RotationActor);
	GetTurretMesh()->SetRelativeRotation(GetBaseMesh()->GetComponentRotation());
}

void ATank::RotatePawn(FVector LookAtTarget)
{
	const FVector ToTarget =  GetTurretMesh()->GetComponentLocation() - LookAtTarget;
	const FRotator LookAtRotation = FRotator(0.f, ToTarget.ToOrientationRotator().Yaw , 0.f);
	FRotator Temp = LookAtRotation - GetTurretMesh()->GetRelativeRotation();
	Temp.Yaw += -180;
	Temp.Pitch = 0;
	Temp.Roll = 0;          
	GetTurretMesh()->SetRelativeRotation(Temp);
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(TankPlayerController && TankPlayerController->IsEnable())
	{
		FHitResult HitResult;
		TankPlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 20.f ,16, FColor::Silver, false, -1.f);
		RotatePawn(HitResult.ImpactPoint);
	}
}

APlayerController* ATank::GetTankPlayerController() const
{
	return TankPlayerController;
}



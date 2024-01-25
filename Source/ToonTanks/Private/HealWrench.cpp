// Fill out your copyright notice in the Description page of Project Settings.


#include "HealWrench.h"

#include "HitBoxComponent.h"

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
}

void AHealWrench::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto HitBox = Cast<UHitBoxComponent>(OtherComp);
	UE_LOG(LogTemp, Warning, TEXT("Name of component: %s"), *OtherComp->GetName());
	if(HitBox)
	{
		HitBox->DamageHealed(Heal);
		this->Destroy();
	}
	else
	{
		return;
	}
}

// Called every frame
void AHealWrench::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = MeshComponent;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	MovementComponent->InitialSpeed = MovementSpeed;
	MovementComponent->MaxSpeed = MovementSpeed;
	InitialLifeSpan = 3.0f;

}

void AProjectileBase::PostActorCreated()
{
	Super::PostActorCreated();
	MovementComponent->InitialSpeed = MovementSpeed;
	MovementComponent->MaxSpeed = MovementSpeed;
	
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}




// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	MeshComponent->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	RootComponent = MeshComponent;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	MovementComponent->InitialSpeed = MovementSpeed;
	MovementComponent->MaxSpeed = MovementSpeed;
	InitialLifeSpan = 3.0f;

	ParticleTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Projectile Trail Particle"));
	ParticleTrail->SetupAttachment(RootComponent);
	

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

	UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();

	if (!MyOwner) return;

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this, DamageType);
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation());
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitShake);
		Destroy();
	}

	
}



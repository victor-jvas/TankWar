// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"

#include "Kismet/GameplayStatics.h"
#include "Pawns/PawnTurret.h"
#include "PlayerControllers/PlayerControllerBase.h"

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
	
}

void ATankGameModeBase::HandleGameStart()
{
	TargetTurrets = GetTargetTurretCount();
	
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

	PlayerController = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	GameStart();

	if (PlayerController)
	{
		PlayerController->SetPlayerEnabledState(false);

		FTimerHandle EnableHandle;
		FTimerDelegate EnableDelegate = FTimerDelegate::CreateUObject(PlayerController, &APlayerControllerBase::SetPlayerEnabledState, true);

		GetWorld()->GetTimerManager().SetTimer(EnableHandle, EnableDelegate, StartDelay, false);
	}
	
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	GameOver(PlayerWon);
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();
		HandleGameOver(false);

		if (PlayerController)
		{
			PlayerController->SetPlayerEnabledState(false);
		}

		return;
	}

	if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();
		if (--TargetTurrets == 0)
		{
			HandleGameOver(true);
		}
	}
	
	
}

int32 ATankGameModeBase::GetTargetTurretCount() const
{
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);

	return TurretActors.Num();
}



// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"


void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled) {

	Super::PawnKilled(PawnKilled);

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController) {
		EndGame(false);
	}
	else {
		for (AShooterAIController* AIController : TActorRange<AShooterAIController>(GetWorld())) {
			if (!AIController->IsDead()) {
				return;
			}
		}
		EndGame(true);
	}
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner) {
	for (AController* Controller : TActorRange<AController>(GetWorld())) {
		if (Controller->IsPlayerController()) {
			Controller->GameHasEnded(Controller->GetPawn(), bIsPlayerWinner);
		}
		else {
			Controller->GameHasEnded(Controller->GetPawn(), !bIsPlayerWinner);
		}
	}
}
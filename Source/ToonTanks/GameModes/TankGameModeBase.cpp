// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "ToonTanks/PlayerController/PlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"	
#include "TimerManager.h"


void ATankGameModeBase::BeginPlay()

{
    Super::BeginPlay();

    HandleGameStart();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)

{
    if (PlayerTank == DeadActor) {

        PlayerTank->HandleDeath();
        HandleGameOver(false);

        if(PlayerControllerRef) {

            PlayerControllerRef->SetPlayerEnabledState(false);
        }

    } else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor)) {
    
        DestroyedTurret->HandleDeath();
        if (--TargetTurrets == 0) {
            HandleGameOver(true);
        }
    }

}

void ATankGameModeBase::HandleGameStart()

{
    TargetTurrets = GetTargetTurrets();
    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
    PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this,0));

    GameStart();
    if(PlayerControllerRef) {

            PlayerControllerRef->SetPlayerEnabledState(false);
            FTimerHandle PlayerEnableHandle;
            FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnabledState, true);
            GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
        }
}


void ATankGameModeBase::HandleGameOver(bool PlayerWon)

{
    GameOver(PlayerWon);

}


int32 ATankGameModeBase::GetTargetTurrets() {

    TArray<AActor*> TurretsActors;

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretsActors);

    return TurretsActors.Num();

}
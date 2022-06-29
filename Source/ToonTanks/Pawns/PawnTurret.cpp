// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"

APawnTurret::APawnTurret() {

}

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(FireRateTimer, this, &APawnTurret::CheckFireCon, FireRate, true);

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!PlayerPawn || GetDist() > FireRange)
	{
		return;
	}

	RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireCon() {

	if(!PlayerPawn || !PlayerPawn->GetIsPlayerAlive()) {
		return;
	}

	if (GetDist() < FireRange) {

	Fire();
	}

}

float APawnTurret::GetDist() {

	if(!PlayerPawn) {
		return 0.0f;
	}

	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());

}

void APawnTurret::HandleDeath() {
	Super::HandleDeath();
	Destroy();

}
// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanks/Pawns/PawnTank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

APawnTank::APawnTank() {
    PrimaryActorTick.bCanEverTick = true;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm Component"));
    SpringArm->SetupAttachment(RootComponent);

    Cam =  CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
    Cam->SetupAttachment(SpringArm);

}
// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();

    PlayerControllerRef = Cast<APlayerController>(GetController());
	
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    Move();
    Rotate();

    if (PlayerControllerRef) 
    {
        FHitResult TraceHit;
        PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility,false, TraceHit);
        FVector HitLocation = TraceHit.ImpactPoint;

        RotateTurret(HitLocation);
    }

    

}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveSpeed);
    PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateTurnSpeed);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);
}

void APawnTank::CalculateMoveSpeed(float Value) {

    MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);

}

void APawnTank::CalculateTurnSpeed(float Value) {

    float RotateAmount = Value * TurnSpeed * GetWorld()->DeltaTimeSeconds;

    FRotator Rotate = FRotator(0,RotateAmount,0);

    RotateDirection = FQuat(Rotate);
}

void APawnTank::Move() {
    AddActorLocalOffset(MoveDirection, true);
}

void APawnTank::Rotate() {
    AddActorLocalRotation(RotateDirection, true);
}


void APawnTank::HandleDeath() {
	Super::HandleDeath();

    bIsPlayerAlive = false;

    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);


}

bool APawnTank::GetIsPlayerAlive() {
    return bIsPlayerAlive;
}
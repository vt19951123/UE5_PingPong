// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddle.h"

// Sets default values
APaddle::APaddle()
{
	PrimaryActorTick.bCanEverTick = false;

	pPaddleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PaddleMesh"));
	RootComponent = pPaddleMesh;

	mMoveSpeed = 500.0f;
	mBoundLimit = 400.0f;

	// Enable this pawn to receive input from player 0
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void APaddle::BeginPlay()
{
	Super::BeginPlay();

	// Set default mesh if none is assigned in Blueprint
	if (pPaddleMesh && !pPaddleMesh->GetStaticMesh())
	{
		// Load default cube mesh from engine content
		UStaticMesh* CubeMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Cube.Cube"));
		if (CubeMesh)
		{
			pPaddleMesh->SetStaticMesh(CubeMesh);
			// Scale paddle to appropriate size for ping pong
			SetActorScale3D(FVector(0.2f, 0.2f, 1.0f));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to load default cube mesh for paddle"));
		}
	}
	
}

void APaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveVertical", this, &APaddle::MovePaddle);

}

void APaddle::MovePaddle(float value)
{
	//UE_LOG(LogTemp, Warning, TEXT("MovePaddle......................... %f"), value);
	if (value == 0.0f) return;

	FVector current_location = GetActorLocation(); // Get current location
	float moveDelta = value * mMoveSpeed * GetWorld()->GetDeltaSeconds(); // Get movespeed with delta time
	FVector new_location = current_location + FVector(moveDelta, 0.0f, 0.0f); // Add to new location
	
	FVector clamped_location = ClampMovement(new_location);
	SetActorLocation(clamped_location);
}

FVector APaddle::ClampMovement(const FVector& inputVector)
{
	FVector ret_vector = inputVector;
	ret_vector.X = FMath::Clamp(inputVector.X, -mBoundLimit, mBoundLimit);
	return ret_vector;
}
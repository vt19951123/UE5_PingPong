// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddle.h"

// Sets default values
APaddle::APaddle()
{

}

void APaddle::BeginPlay()
{
	Super::BeginPlay();
	
}

void APaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APaddle::ClampMovement()
{
}

void APaddle::MovePaddle(float value)
{
	if (value == 0.0f) return;

	FVector current_location = GetActorLocation(); // Get current location
	float moveDelta = value * mMoveSpeed * GetWorld()->GetDeltaSeconds(); // Get movespeed with delta time
	FVector new_location = current_location + FVector(moveDelta, 0.0f, 0.0f); // Add to new location
	
	SetActorLocation(new_location);
	ClampMovement();
}

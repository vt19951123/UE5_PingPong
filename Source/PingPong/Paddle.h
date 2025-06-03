// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Paddle.generated.h"

UCLASS()
class PINGPONG_API APaddle : public APawn
{
	GENERATED_BODY()

public:
	APaddle();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* pPaddleMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float mMoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float mBoundLimit;

	void MovePaddle(float value);

	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	FVector ClampMovement(const FVector& inputVector);

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PingPongActor.generated.h"

UCLASS()
class PINGPONG_API APingPongActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APingPongActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ping Pong")
	float TestFloat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ping Pong")
	FString TestString;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Ping Pong")
	void TestFunction();

	UFUNCTION(BlueprintImplementableEvent, Category = "Ping Pong")
	void OnTestEvent(float TestScore);

};

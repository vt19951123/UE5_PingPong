// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongActor.h"

// Sets default values
APingPongActor::APingPongActor()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	TestFloat = 10.0f;
	TestString = TEXT("Hello UE5");

}

// Called when the game starts or when spawned
void APingPongActor::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("PingPongActor started! Test String: %s"), *TestString);
}

// Called every frame
void APingPongActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APingPongActor::TestFunction()
{
	UE_LOG(LogTemp, Warning, TEXT("TestFunction called! TestFloat value: %f"), TestFloat);

	// Gọi Blueprint Event
	OnTestEvent(42);

	// Hiển thị message trên screen
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
			FString::Printf(TEXT("TestFunction called! Value: %f"), TestFloat));
	}

}


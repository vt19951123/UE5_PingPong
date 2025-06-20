﻿#include "Ball.h"
#include "Components/StaticMeshComponent.h" // Thêm để sử dụng UStaticMeshComponent
#include "Kismet/GameplayStatics.h" // Thêm để sử dụng các hàm gameplay tĩnh

ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = true;

	SetupBallMesh();
	SetupSphereCollision();                         
	SetupProjectileMovement();
	LoadDefaultBallMesh();

}

void ABall::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABall::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

}

void ABall::LaunchBall(FVector InitialVelocity)
{
}

void ABall::ResetBall()
{
}

void ABall::SetInitialProperties()
{
}

void ABall::LoadDefaultBallMesh()
{
	// Load default mesh cho BallMesh (ví dụ: Sphere)
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (SphereMeshAsset.Succeeded())
	{
		BallMesh->SetStaticMesh(SphereMeshAsset.Object);
		BallMesh->SetRelativeScale3D(FVector(0.3f)); // Điều chỉnh kích thước mesh cho phù hợp
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load default sphere mesh for ball"));
	}
}

void ABall::SetupProjectileMovement()
{
	// Tạo Projectile Movement Component
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = RootComponent; // Component này sẽ cập nhật vị trí của RootComponent (SphereCollision)
	ProjectileMovement->InitialSpeed = 0.f;               // Tốc độ ban đầu
	ProjectileMovement->MaxSpeed = 3000.0f;               // Tốc độ tối đa
	ProjectileMovement->bRotationFollowsVelocity = false; // Bóng không cần xoay theo hướng di chuyển
	ProjectileMovement->bShouldBounce = true;             // Bật tính năng nảy
	ProjectileMovement->Bounciness = 1.0f;                // Độ nảy (1.0f là nảy hoàn hảo)
	ProjectileMovement->ProjectileGravityScale = 0.0f;    // Không có trọng lực ảnh hưởng đến projectile
	ProjectileMovement->Friction = 0.0f;                  // Ma sát bằng 0
	ProjectileMovement->Velocity = FVector::ZeroVector;   // Vận tốc ban đầu là zero
}

void ABall::SetupSphereCollision()
{
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	RootComponent = SphereCollision;

	// Setup cho SphereCollision
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); // Turn on both query và physics collision
	SphereCollision->SetCollisionProfileName(TEXT("BlockAllDynamic"));      // Use profile coliison "BlockAllDynamic"
	SphereCollision->SetSimulatePhysics(true);                              // Turn on physic simulate
	SphereCollision->SetEnableGravity(false);                               // Disable gravity
	SphereCollision->SetNotifyRigidBodyCollision(true);                     // notify when has rigid body collision
	SphereCollision->SetSphereRadius(15.0f);								// set radius for sphere
}

void ABall::SetupBallMesh()
{
	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	BallMesh->SetupAttachment(RootComponent);
	BallMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BallMesh->SetSimulatePhysics(false);
}
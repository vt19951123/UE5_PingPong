#include "Ball.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

ABall::ABall()
{
    PrimaryActorTick.bCanEverTick = true;

    // ✅ BallMesh làm root component
    BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
    RootComponent = BallMesh;

    // Load default mesh
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
    if (SphereMeshAsset.Succeeded())
    {
        BallMesh->SetStaticMesh(SphereMeshAsset.Object);
        BallMesh->SetRelativeScale3D(FVector(0.3f));
    }

    SetupBallCollision();
    SetupProjectileMovement();
}

void ABall::SetupBallCollision()
{
    // ✅ BallMesh collision settings
    BallMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    BallMesh->SetCollisionProfileName(TEXT("BlockAll"));
    BallMesh->SetSimulatePhysics(false);
    BallMesh->SetEnableGravity(false);
    BallMesh->SetMobility(EComponentMobility::Movable);
    BallMesh->SetNotifyRigidBodyCollision(true);

    // Bind collision event
    BallMesh->OnComponentHit.AddDynamic(this, &ABall::OnHit);
}

void ABall::SetupProjectileMovement()
{
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->UpdatedComponent = BallMesh; // ✅ Direct reference to BallMesh
    ProjectileMovement->InitialSpeed = 1000.f;
    ProjectileMovement->MaxSpeed = 3000.0f;
    ProjectileMovement->bRotationFollowsVelocity = false;
    ProjectileMovement->bShouldBounce = true;
    ProjectileMovement->Bounciness = 1.0f;
    ProjectileMovement->ProjectileGravityScale = 0.0f;
    ProjectileMovement->Friction = 0.0f;
}

void ABall::BeginPlay()
{
    Super::BeginPlay();

    InitialBallLocation = GetActorLocation();
    SetInitialProperties();

    // Test timer
    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
        {
            const float LaunchSpeed = 1000.0f;
            const float RandX = FMath::FRandRange(-0.5f, 0.5f);
            const float RandY = FMath::RandBool() ? 1.0f : -1.0f;
            FVector LaunchVelocity = FVector(RandX, RandY, 0.0f);
            LaunchVelocity.Normalize();
            LaunchVelocity *= LaunchSpeed;

            LaunchBall(LaunchVelocity);

        }, 2.0f, false);
}

void ABall::LaunchBall(FVector InitialVelocity)
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Ball LaunchBall"));
    if (ProjectileMovement)
    {
        ProjectileMovement->Velocity = InitialVelocity;
        bIsMoving = true;
        UE_LOG(LogTemp, Warning, TEXT("Ball launched with velocity: %s"), *InitialVelocity.ToString());
    }
}

void ABall::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Debug movement
    if (bIsMoving && ProjectileMovement)
    {
        FVector Velocity = ProjectileMovement->Velocity;
        if (!Velocity.IsNearlyZero(1.0f))
        {
            FVector Position = GetActorLocation();
            GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::White,
                FString::Printf(TEXT("Ball Pos: %.0f,%.0f | Vel: %.0f,%.0f"),
                    Position.X, Position.Y, Velocity.X, Velocity.Y));
        }
    }
}

void ABall::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red,
        FString::Printf(TEXT("Ball hit: %s"), OtherActor ? *OtherActor->GetName() : TEXT("Unknown")));
    UE_LOG(LogTemp, Warning, TEXT("Ball collision with: %s"), OtherActor ? *OtherActor->GetName() : TEXT("Unknown"));
}

void ABall::SetInitialProperties()
{
    if (ProjectileMovement) {
        ProjectileMovement->Velocity = FVector::ZeroVector;
        // ✅ Không set InitialSpeed = 0
    }
}

void ABall::ResetBall()
{
    SetActorLocation(InitialBallLocation);
    if (ProjectileMovement)
    {
        ProjectileMovement->StopMovementImmediately();
    }
    bIsMoving = false;
}
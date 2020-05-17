#include "Agent.h"

AAgent::AAgent() {
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AgentMesh"));
	RootComponent = Mesh;
	Velocity = FVector(0.f);

	Mesh->SetNotifyRigidBodyCollision(true);
	Mesh->OnComponentHit.AddDynamic(this, &AAgent::hit1);
}

void AAgent::BeginPlay() {
	Super::BeginPlay();
}

void AAgent::Init(UStaticMeshComponent* mesh, int id) {
	UE_LOG(LogTemp, Warning, TEXT("Agent initialized."));
	Mesh->SetStaticMesh(mesh->GetStaticMesh());
}

void AAgent::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	FVector loc = GetActorLocation();
	SetActorLocation(loc + Velocity);
}

void AAgent::hit1(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	UE_LOG(LogTemp, Warning, TEXT("HIT"));
}

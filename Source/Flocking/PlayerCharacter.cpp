// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshContainer(TEXT("SkeletalMesh'/Game/vanguard_t_choonyung.vanguard_t_choonyung'"));
	if (MeshContainer.Succeeded()) {

		GetMesh()->SetSkeletalMesh(MeshContainer.Object);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -87));

	}

	Mesh2 = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh2->SetNotifyRigidBodyCollision(true);
	Mesh2->OnComponentHit.AddDynamic(this, &APlayerCharacter::Hit1);
	Camera = CreateDefaultSubobject<UCameraComponent>("CameraComponent");

	Camera->SetRelativeLocation(FVector(-500.f, 0.f, 0.f));
	Camera->SetupAttachment(Mesh2);

	// OnActorHit.AddDynamic(this, &APlayerCharacter::Hit1);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MovingForward);
	PlayerInputComponent->BindAxis("MoveSideway", this, &APlayerCharacter::MovingSideway);
}

void APlayerCharacter::MovingForward(float Amount) {
	AddMovementInput(GetActorForwardVector(), Amount);
}

void APlayerCharacter::MovingSideway(float Amount) {
	AddMovementInput(GetActorRightVector(), Amount);
}

void APlayerCharacter::Hit1(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	
	// if (OtherActor->GetClass())
	UE_LOG(LogTemp, Warning, TEXT("HIT"));
	UE_LOG(LogTemp, Warning, TEXT("HIT, %s"), Hit.GetActor());
}
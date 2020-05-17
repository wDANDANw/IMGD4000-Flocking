// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlockingManager.generated.h"

UCLASS()
class FLOCKING_API UFlockingManager : public UObject
{

public:
	GENERATED_BODY()

	void Init(UWorld* world, UStaticMeshComponent* mesh);
	void Flock();

	UPROPERTY(EditAnywhere)
	AActor* PlayerPtr;

private:
	UWorld* World;
	bool initialized;
	TArray<class AAgent*> Agents;

	FVector rule1(AAgent* agent);
	FVector rule2(AAgent* agent);
	FVector rule3(AAgent* agent);

	// Approaches to player
	FVector rule4(AAgent* agent);

	void capVelocity(AAgent* agent);
};
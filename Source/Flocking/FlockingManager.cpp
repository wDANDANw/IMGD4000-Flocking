#include "FlockingManager.h"
#include "Agent.h"
#include "Kismet/KismetMathLibrary.h"

#define AGENT_COUNT 10
#define MAX_VEL 30

void UFlockingManager::Init(UWorld * world, UStaticMeshComponent * mesh) {
	UE_LOG(LogTemp, Warning, TEXT("Manager initialized"));

	World = world;
	float incr = (PI * 2.f) / AGENT_COUNT;
	for (int i = 0; i < AGENT_COUNT; i++) {
		if (World != nullptr) {
			FRotator rotation = FRotator(0,i*36,0);

			FVector location = FVector(0,0,0);
			location.X = FMath::Sin(incr * i) * 4500.f;
			location.Y = FMath::Cos(incr * i) * 4500.f;

			AAgent* agent = World->SpawnActor<AAgent>(location, rotation);
			agent->Init(mesh, i);
			Agents.Add(agent);
		}
	}

	initialized = true;
}

void UFlockingManager::Flock() {
	
	FVector v1;
	FVector v2;
	FVector v3;
	FVector v4;

	AAgent* agent;

	for (int i = 0; i < AGENT_COUNT; i++) {
		agent = Agents[i];

		v1 = rule1(agent);
		v2 = rule2(agent);
		v3 = rule3(agent);
		v4 = rule4(agent);

		agent->Velocity = agent->Velocity + (v1 + v2 + v3 + v4) * 0.02;
		capVelocity(agent);
	}
}

FVector UFlockingManager::rule1(AAgent* agent)
{
	FVector perceievedCenter = FVector(0,0,0);
	AAgent* currentAgent;

	for (int i = 0; i < AGENT_COUNT; i++) {
		currentAgent = Agents[i];
		if (currentAgent != agent) {
			perceievedCenter = perceievedCenter + currentAgent->GetActorLocation();
		}
	}

	perceievedCenter = perceievedCenter / (AGENT_COUNT - 1);

	return (perceievedCenter - agent->GetActorLocation()) / 100;
}

FVector UFlockingManager::rule2(AAgent* agent)
{
	FVector c = FVector(0,0,0);
	AAgent* currentAgent;

	for (int i = 0; i < AGENT_COUNT; i++) {
		currentAgent = Agents[i];
		if (currentAgent != agent) {
			if (UKismetMathLibrary::Abs(currentAgent->GetDistanceTo(agent)) < 100) {
				c = c - (currentAgent->GetActorLocation() - agent->GetActorLocation());
			}
		}
	}

	return c;
}

FVector UFlockingManager::rule3(AAgent* agent)
{
	FVector perceievedVelocity = FVector(0,0,0);
	AAgent* currentAgent;

	for (int i = 0; i < AGENT_COUNT; i++) {
		currentAgent = Agents[i];
		if (currentAgent != agent) {
			perceievedVelocity = perceievedVelocity + currentAgent->Velocity;
		}
	}

	perceievedVelocity = perceievedVelocity / (AGENT_COUNT - 1);

	return perceievedVelocity / 8;
}

FVector UFlockingManager::rule4(AAgent* agent) {
	return (World->GetFirstPlayerController()->GetPawn()->GetActorLocation() - agent->GetActorLocation()) / 100;
}

void UFlockingManager::capVelocity(AAgent* agent){

	if (agent->Velocity.Size() > MAX_VEL) {
		agent->Velocity = (agent->Velocity / agent->Velocity.Normalize()) * MAX_VEL;
	}

}


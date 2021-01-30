// Copyright Mister Class 2020

#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "OpenDoor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	//Init values for door opening
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw += InitialYaw;

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has the open door component on it, but no pressure plate set."), *GetOwner()->GetName());
	}

	//Get our player pawn
	ActorThatOpen = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Open with overlapping
	if (TotalMassOfActors() > LimitMass)
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{	
		if (GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorOpenDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
	
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	/*UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), GetOwner()->GetActorRotation().Yaw);*/

	//CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, DeltaTime);
	//CurrentYaw = FMath::FInterpConstantTo(CurrentYaw, TargetYaw, DeltaTime, 45.f);
	CurrentYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, DoorOpenSpeed);
	FRotator OpenRotator(0.f, CurrentYaw, 0.f);
	GetOwner()->SetActorRotation(OpenRotator);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	/*UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), GetOwner()->GetActorRotation().Yaw);*/
	
	CurrentYaw = FMath::FInterpTo(CurrentYaw, InitialYaw, DeltaTime, DoorCloseSpeed);
	FRotator OpenRotator(0.f, CurrentYaw, 0.f);
	GetOwner()->SetActorRotation(OpenRotator);
}

float UOpenDoor::TotalMassOfActors() const
{
	float TotalMass = 0.f;

	//Find all overlapping components
	TArray<UPrimitiveComponent*> OverlappingComponents;
	PressurePlate->GetOverlappingComponents(OUT OverlappingComponents);

	for (UPrimitiveComponent* Component : OverlappingComponents)
	{
		TotalMass += Component->GetMass();
	}
	
	return TotalMass;
}


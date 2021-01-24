// Copyright Mister Class 2020

#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Grabber.h"

//For code readability with out params
#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber is ready!"));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Get player viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(		//OUT is used only for readability
		OUT PlayerViewPointLocation, 
		OUT PlayerViewPointRotation
	);

	UE_LOG(LogTemp, Warning, TEXT("Player view point location is %s"), 
		*PlayerViewPointLocation.ToString()
	);
	UE_LOG(LogTemp, Warning, TEXT("Player view point rotation is %s"), 
		*PlayerViewPointRotation.ToString()
	);
}


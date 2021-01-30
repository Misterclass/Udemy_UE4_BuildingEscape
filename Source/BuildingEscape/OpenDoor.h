// Copyright Mister Class 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//
	void OpenDoor(float DeltaTime);

	//
	void CloseDoor(float DeltaTime);

private:
	float CurrentYaw;
	float InitialYaw;

	UPROPERTY(EditAnywhere)
		float LimitMass = 60.f;

	UPROPERTY(EditAnywhere)
		float TargetYaw = 90.f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	float DoorLastOpened = 0.f;

	UPROPERTY(EditAnywhere)
		float DoorOpenDelay = .5f;
	
	UPROPERTY(EditAnywhere)
		float DoorOpenSpeed = 2.f;
	
	UPROPERTY(EditAnywhere)
		float DoorCloseSpeed = 2.f;

	bool IsOpened = false;

	UPROPERTY()
		UAudioComponent* AudioComponent = nullptr;

	//Get sum mass of actors
	float TotalMassOfActors() const;

	//Get audio component for playing
	void FindAudioComponent();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IPickable.h"
#include "GameFramework/Actor.h"
#include "Pickable.generated.h"

UCLASS()
class INTERACTIONS_API APickable : public AActor , public IIPickable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Pickable")
	FString DisplayName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Pickable")
	FString PickableID;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Pickable")
	int MaxAmmo;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Pickable")
	int StartAmmo;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Pickable")
	int AmmoPickupCount;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Pickable")
	EPickableType PickableType;

	virtual FString GetDisplayName_Implementation() const override;
	
	virtual FString GetPickableID_Implementation() const override;
	
	virtual EPickableType GetPickableType_Implementation() const override;
	
	virtual void Interact_Implementation() override;
	
	virtual int GetMaxAmmo_Implementation() const override;
	
	virtual int GetStartAmmo_Implementation() const override;
	virtual int GetAmmoPickupCount_Implementation() const override;
};

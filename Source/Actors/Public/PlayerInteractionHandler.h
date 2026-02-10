// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInventory.h"
#include "Components/ActorComponent.h"
#include "UMessagingBus.h"
#include "PlayerInteractionHandler.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerInteractedAction);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTORS_API UPlayerInteractionHandler : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerInteractionHandler();
	void InvokePlayerInteractedAction();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Raycast" , meta = (AllowPrivateAccess = true))
	float RayLength = 800.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Raycast" , meta = (AllowPrivateAccess = true))
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Raycast" , meta = (AllowPrivateAccess = true))
	bool bDebugDraw = false;

	// Returns true if we hit something that implements InterfaceClass
	UFUNCTION(BlueprintCallable, Category="Raycast")
	bool RaycastCenterScreenForInterface(TSubclassOf<UInterface> InterfaceClass, FHitResult& OutHit, AActor*& OutActor);
	
	UFUNCTION(BlueprintCallable, Category="Interaction|Events")
	bool InteractPickableActor(TScriptInterface<UIPickable> Pickable);
	
	UFUNCTION(BlueprintCallable, Category="Interaction|Events")
	void OnActorInterfaceHit(FInteractionEventData EventData);
	
	UFUNCTION(BlueprintCallable, Category="Interaction|Events")
	void OnResetActorInterfaceHit();
	
	TObjectPtr<UPlayerInventory> PlayerInventory;
	
	UPROPERTY(BlueprintAssignable, Category="Interaction|Events" , meta = (AllowPrivateAccess = true))
	FOnPlayerInteractedAction OnPlayerInteracted;
	
	UMessagingBus* GetMessagingBus();
};

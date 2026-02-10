// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerInteractionHandler.h"
#include "IPickable.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UPlayerInteractionHandler::UPlayerInteractionHandler()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UPlayerInteractionHandler::InvokePlayerInteractedAction()
{
	if (OnPlayerInteracted.IsBound())
	{
		OnPlayerInteracted.Broadcast();
	}
}


UMessagingBus* UPlayerInteractionHandler::GetMessagingBus()
{
	ULocalPlayer* LP = GetWorld()->GetFirstLocalPlayerFromController();
	
	if (!LP)
	{
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("Could not get LocalPlayer from %s")  , *GetName() ));
		UE_LOG(LogTemp, Warning, TEXT("Could not get LocalPlayer from %s") , *GetName() ) ;
		return nullptr;
	}
	
	UMessagingBus* MessagingBus = LP->GetSubsystem<UMessagingBus>();
	if (!MessagingBus)
	{
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("Could not get MessagingBus from %s") , *GetName() ));
		UE_LOG(LogTemp, Warning, TEXT("Could not get MessagingBus from %s") , *GetName() ) ;
	}
	return MessagingBus;
}

// Called when the game starts
void UPlayerInteractionHandler::BeginPlay()
{
	Super::BeginPlay();

	PlayerInventory =  GetOwner()->FindComponentByClass<UPlayerInventory>();
}


// Called every frame
void UPlayerInteractionHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/*
	FHitResult OutHit;
	AActor* OutActor = nullptr;
	bool bHit = RaycastCenterScreenForInterface(UIPickable::StaticClass() , OutHit , OutActor);
	
	if (bHit && OutActor != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Green , FString::Printf(TEXT("Hit Pickable , Name: %s") , *OutActor->GetName()));
	}
	// ...
	*/
}

bool UPlayerInteractionHandler::RaycastCenterScreenForInterface(
	TSubclassOf<UInterface> InterfaceClass,
	FHitResult& OutHit,
	AActor*& OutActor)
{
	OutHit = FHitResult{};
	OutActor = nullptr;

	UWorld* World = GetWorld();
	if (!World || !InterfaceClass)
		return false;

	APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);
	if (!PC)
		return false;

	int32 SizeX = 0, SizeY = 0;
	PC->GetViewportSize(SizeX, SizeY);
	const FVector2D ScreenCenter(SizeX * 0.5f, SizeY * 0.5f);

	FVector RayOrigin, RayDir;
	if (!PC->DeprojectScreenPositionToWorld(ScreenCenter.X, ScreenCenter.Y, RayOrigin, RayDir))
		return false;

	const FVector RayEnd = RayOrigin + (RayDir * RayLength);

	FCollisionQueryParams Params(SCENE_QUERY_STAT(CenterScreenRaycast), /*bTraceComplex*/ true);
	Params.AddIgnoredActor(GetOwner()); // don't hit yourself

	const bool bHit = World->LineTraceSingleByChannel(OutHit, RayOrigin, RayEnd, TraceChannel, Params);

	if (bDebugDraw)
	{
		DrawDebugLine(World, RayOrigin, RayEnd, bHit ? FColor::Green : FColor::Red, false, 0.02f, 0, 1.5f);
		if (bHit)
			DrawDebugPoint(World, OutHit.ImpactPoint, 8.f, FColor::Yellow, false, 0.02f);
	}

	if (!bHit)
		return false;

	AActor* HitActor = OutHit.GetActor();
	if (!HitActor)
		return false;

	if (HitActor->GetClass()->ImplementsInterface(InterfaceClass))
	{
		OutActor = HitActor;
		return true;
	}

	return false;
}

bool UPlayerInteractionHandler::InteractPickableActor(TScriptInterface<UIPickable> Pickable)
{
	if (Pickable == nullptr || Pickable.GetInterface() == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1 , 10.f, FColor::Red , FString::Printf(TEXT("In InteractPickableActor Pickable Actor is null")));
		UE_LOG(LogTemp, Warning, TEXT("InteractPickableActor is null"));
		return false;
	}
	IIPickable::Execute_Interact(Pickable.GetObject());
	PlayerInventory->Interact(Pickable);
	return true;
}

void UPlayerInteractionHandler::OnActorInterfaceHit(FInteractionEventData EventData)
{
	UMessagingBus* MessagingBus = GetMessagingBus();
	
	if (MessagingBus != nullptr)
	{
		MessagingBus->BroadcastInteractionDataStart(EventData);
	}
}

void UPlayerInteractionHandler::OnResetActorInterfaceHit()
{
	UMessagingBus* MessagingBus = GetMessagingBus();
	if (MessagingBus != nullptr )
	{
		MessagingBus->BroadcastInteractionDataReset();
	}
}


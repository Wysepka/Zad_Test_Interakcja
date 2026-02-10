#pragma once

#include "Blueprint/UserWidget.h"
#include "UHUDInteractPopup.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionActorHit, FString, Message);

UCLASS()
class UIRUNTIME_API UHUDInteractPopup : public UUserWidget
{
private:
	UPROPERTY(BlueprintAssignable, Category="Interaction")
	FOnInteractionActorHit OnInteractionSetTextEvent;
	
public:
	GENERATED_BODY()	
	
	void InvokeOnInteractionSetTextEvent(FString DisplayName);
};


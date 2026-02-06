// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = true;
	
	auto charMovement = GetCharacterMovement();
	charMovement->bOrientRotationToMovement = true;
	charMovement->RotationRate = FRotator(0.f , 540.f ,0.f);
	charMovement->MaxWalkSpeed = 600.f;
	charMovement->JumpZVelocity = 600.f;
	charMovement->AirControl = 0.3f;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (ULocalPlayer* LP = PC->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
				LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
				UE_LOG(LogTemp, Warning, TEXT("Added Mapping Context: %s") , *DefaultMappingContext.GetName());
			}
		}
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red ,FString::Printf(TEXT("Player Input Component: %s"), *Controller->GetName()));
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	
	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	ensure(EIC);

	EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
	EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
	EIC->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerCharacter::Jump);
	EIC->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopJumping);
	
	/*
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::StopJump);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);
	*/
}

/*
void APlayerCharacter::MoveRight(float Value)
{
	GEngine->AddOnScreenDebugMessage(-1 , 2.f , FColor::Red ,
		FString::Printf(TEXT("Moving Left/Right with Value: %f"), Value));
	
	if (Controller && Value != 0)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction =
			FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, Value);
	}
}
*/

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FString valueStringed = Value.Get<FVector2D>().ToString();
	GEngine->AddOnScreenDebugMessage(-1 , 2.f , FColor::Red ,
	FString::Printf(TEXT("Moving Back/Forward with Value: %s") ,*valueStringed ));
	
	const FVector2D Axis = Value.Get<FVector2D>();

	if (Controller)
	{
		const FRotator YawRot(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Forward = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
		const FVector Right   = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

		AddMovementInput(Forward, Axis.Y);
		AddMovementInput(Right,   Axis.X);
	}
}

/*
void APlayerCharacter::Turn(float Value)
{
	GEngine->AddOnScreenDebugMessage(-1 , 2.f , FColor::Red ,
FString::Printf(TEXT("Turning with Value: %f" ), Value));
	AddControllerYawInput(Value);
}
*/

void APlayerCharacter::Look(const FInputActionValue&  Value)
{
	FString valueStringed = Value.Get<FVector2D>().ToString();
	GEngine->AddOnScreenDebugMessage(-1 , 2.f , FColor::Red ,
FString::Printf(TEXT("Looking with Value: %s" ), *valueStringed));
	
	const FVector2D Axis = Value.Get<FVector2D>();

	AddControllerPitchInput(Axis.Y);
	AddControllerYawInput(Axis.X);
}

void APlayerCharacter::StartJump()
{
	
}

void APlayerCharacter::StopJump()
{
	
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/D1PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AD1PlayerController::AD1PlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void AD1PlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(InputMappingContext , 0);
	}
}

void AD1PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(AttackAction , ETriggerEvent::Triggered , this, &ThisClass::Input_Attack);
		EnhancedInputComponent->BindAction(MoveAction , ETriggerEvent::Triggered , this, &ThisClass::Input_Move);
		EnhancedInputComponent->BindAction(TurnAction , ETriggerEvent::Triggered , this, &ThisClass::Input_Turn);
	}
}

void AD1PlayerController::Input_Attack(const FInputActionValue& InputValue)
{
	GEngine->AddOnScreenDebugMessage(0 , 1.0f, FColor::Cyan, TEXT("Attack"));
}

void AD1PlayerController::Input_Move(const FInputActionValue& InputValue)
{
	FVector2D MovementVector = InputValue.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.0f , Rotation.Yaw , 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	GetPawn()->AddMovementInput(ForwardDirection , MovementVector.X);
	GetPawn()->AddMovementInput(RightDirection , MovementVector.Y);

	//if (MovementVector.X != 0)
	//{
	//	FVector Direction = GetPawn()->GetActorForwardVector() * MovementVector.X;
	//	GetPawn()->AddActorWorldOffset(Direction);
	//}

	//if (MovementVector.Y != 0)
	//{
	//	FVector Direction = GetPawn()->GetActorRightVector() * MovementVector.Y;
	//	GetPawn()->AddActorWorldOffset(Direction);
	//}
}

void AD1PlayerController::Input_Turn(const FInputActionValue& InputValue)
{
	float XValue = InputValue.Get<float>();
	AddYawInput(XValue);

	//GetPawn()->AddControllerYawInput(XValue);
	//FRotator Rotation(0.0f , XValue , 0.0f);
	//GetPawn()->AddActorWorldRotation(Rotation);
}

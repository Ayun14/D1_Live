// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/D1Player.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AD1Player::AD1Player()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 700.0f;
	SpringArm->SetRelativeRotation(FRotator(-30.0f , 0.0f , 0.0f));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;
}

void AD1Player::BeginPlay()
{
	Super::BeginPlay();
}

void AD1Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AD1Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

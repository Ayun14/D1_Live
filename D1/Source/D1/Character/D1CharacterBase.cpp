// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/D1CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AD1CharacterBase::AD1CharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Pawn
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Capsule
	GetCapsuleComponent()->InitCapsuleSize(34.0f , 88.0f);
		
	// Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f , 720.0f , 0.0f);

	// Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f , 0.0f , -88.0f) , FRotator(0.0f , -90.0f , 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> FindMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/_Art/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));
	if (FindMeshRef.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(FindMeshRef.Object);
	}
}

// Called when the game starts or when spawned
void AD1CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AD1CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AD1CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


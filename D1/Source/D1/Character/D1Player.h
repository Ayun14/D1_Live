// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/D1CharacterBase.h"
#include "D1Player.generated.h"

/**
 * 
 */
UCLASS()
class D1_API AD1Player : public AD1CharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AD1Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	UPROPERTY(VisibleAnywhere , BlueprintReadOnly)
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere , BlueprintReadOnly)
	TObjectPtr<class UCameraComponent> Camera;

private:

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/D1CharacterBase.h"
#include "D1Monster.generated.h"

/**
 * 
 */
UCLASS()
class D1_API AD1Monster : public AD1CharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AD1Monster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

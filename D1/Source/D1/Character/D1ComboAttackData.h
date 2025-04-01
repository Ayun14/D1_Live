// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "D1ComboAttackData.generated.h"

/**
 * 
 */
UCLASS()
class D1_API UD1ComboAttackData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Combo)
	FString MontageSectionNamePrefix;

	UPROPERTY(EditAnywhere , Category = Combo)
	uint8 MaxComboCount;

	UPROPERTY(EditAnywhere , Category = Combo)
	float FrameRate;

	UPROPERTY(EditAnywhere , Category = Combo)
	TArray<float> EffectiveFrameCount;
};

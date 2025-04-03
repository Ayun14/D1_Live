// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/D1CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "D1ComboAttackData.h"

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

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> FindMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/_Art/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Warrior.SK_CharM_Warrior'"));
	if (FindMeshRef.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(FindMeshRef.Object);
	}

	// Animation
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceRef(TEXT("/Script/Engine.AnimBlueprint'/Game/Animation/ABP_Player.ABP_Player_C'"));
	if (AnimInstanceRef.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceRef.Class);
	}

	// Attack Montage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Animation/AM_Attack.AM_Attack'"));
	if (AttackMontageRef.Succeeded())
	{
		AttackMontage = AttackMontageRef.Object;
	}

	// ComboAttack Montage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboAttackMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Animation/AM_ComboAttack.AM_ComboAttack'"));
	if (ComboAttackMontageRef.Succeeded())
	{
		ComboAttackMontage = ComboAttackMontageRef.Object;
	}

	// ComboAttack Data
	static ConstructorHelpers::FObjectFinder<UD1ComboAttackData> ComboAttackDataRef(TEXT("/Script/D1.D1ComboAttackData'/Game/CharacterAction/DA_ComboAttackData.DA_ComboAttackData'"));
	if (ComboAttackDataRef.Succeeded())
	{
		ComboAttackData = ComboAttackDataRef.Object;
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

void AD1CharacterBase::ProcessAttack()
{
	if (GetCurrentMontage() == AttackMontage) return;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && AttackMontage)
	{
		int32 Index = FMath::RandRange(1, 4);
		FString SectionName = FString::Printf(TEXT("Attack%d"), Index);
		AnimInstance->Montage_Play(AttackMontage, 1.0f);
		AnimInstance->Montage_JumpToSection(FName(*SectionName));
	}
}

void AD1CharacterBase::ProcessComboAttack()
{
	if (CurrentCombo == 0)
	{
		ComboAttackBegine();
		return;
	}

	if (ComboTimerHandle.IsValid())
	{
		HasNextComboCommand = true;
	}
	else
	{
		HasNextComboCommand = false;
	}
}

void AD1CharacterBase::ComboAttackBegine()
{
	GetCharacterMovement()->SetMovementMode(MOVE_None);

	CurrentCombo = 1;

	const float AttackSpeedRate = 1.0f;
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(ComboAttackMontage , AttackSpeedRate);

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this , &AD1CharacterBase::ComboAttackEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate , ComboAttackMontage);

	ComboTimerHandle.Invalidate();
	SetComboCheckTimer();
}

void AD1CharacterBase::ComboAttackEnd(UAnimMontage* TargetMontage , bool IsProperlyEnded)
{
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	CurrentCombo = 0;
}

void AD1CharacterBase::SetComboCheckTimer()
{
	int32 ComboIndex = CurrentCombo - 1;

	const float AttackSpeedRate = 1.0f;
	float ComboEffectiveTime = 
		(ComboAttackData->EffectiveFrameCount[ComboIndex] / ComboAttackData->FrameRate) / AttackSpeedRate;

	if (ComboEffectiveTime > 0.0f)
	{
		GetWorld()->GetTimerManager()
			.SetTimer(ComboTimerHandle , this , &AD1CharacterBase::ComboCheck, ComboEffectiveTime, false);
	}
}

void AD1CharacterBase::ComboCheck()
{
	ComboTimerHandle.Invalidate();

	if (HasNextComboCommand)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		CurrentCombo = FMath::Clamp(CurrentCombo + 1 , 1 , ComboAttackData->MaxComboCount);

		FName NextSection = *FString::Printf(TEXT("%s%d") , *ComboAttackData->MontageSectionNamePrefix , CurrentCombo);

		AnimInstance->Montage_JumpToSection(NextSection , ComboAttackMontage);

		SetComboCheckTimer();
		HasNextComboCommand = false;
	}
}

void AD1CharacterBase::AttackHitCheck()
{
	FHitResult OutHitResult;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack) , false , this);

	const float AttackRange = 40.0f;
	const float AttackRadius = 50.0f;
	const float AttackDamage = 30.0f;

	const FVector Start = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector End = Start + GetActorForwardVector() * AttackRange;

	bool HitDetected = GetWorld()->SweepSingleByChannel(OutHitResult , Start , End , FQuat::Identity ,
		ECollisionChannel::ECC_GameTraceChannel2 , FCollisionShape::MakeSphere(AttackRadius) , Params);

	if (HitDetected)
	{
		UE_LOG(LogTemp , Log , TEXT("HitDetected"));
	}

#if ENABLE_DRAW_DEBUG
	FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
	float CapsuleHalfHeight = AttackRange * 0.5f;
	FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;

	DrawDebugCapsule(GetWorld() , CapsuleOrigin , CapsuleHalfHeight , AttackRadius ,
		FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat() , DrawColor , false , 5.0f);
#endif
}
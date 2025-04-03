// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_AttackHitCheck.h"
#include "Interface/D1AttackInterface.h"

void UAnimNotify_AttackHitCheck::Notify(USkeletalMeshComponent* MeshComp , UAnimSequenceBase* Animation , const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp , Animation , EventReference);

	if (MeshComp)
	{
		// 주인공 캐릭터에서 충돌 판정
		ID1AttackInterface* AttackInterface = Cast<ID1AttackInterface>(MeshComp->GetOwner());
		if (AttackInterface)
		{
			AttackInterface->AttackHitCheck();
		}
	}
}

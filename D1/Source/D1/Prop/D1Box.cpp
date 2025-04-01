// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/D1Box.h"

// Sets default values
AD1Box::AD1Box()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	SetRootComponent(BoxMesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/_Art/LevelPrototyping/Meshes/SM_ChamferCube.SM_ChamferCube'"));
	if (BoxMeshRef.Succeeded())
	{
		BoxMesh->SetStaticMesh(BoxMeshRef.Object);
	}
}

// Called when the game starts or when spawned
void AD1Box::BeginPlay()
{
	Super::BeginPlay();
	
	BoxMesh->OnComponentHit.AddDynamic(this , &AD1Box::OnHit);
	BoxMesh->OnComponentBeginOverlap.AddDynamic(this , &AD1Box::OnBeginOverlap);
}

// Called every frame
void AD1Box::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AD1Box::OnHit(UPrimitiveComponent* HitComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , FVector NormalImpulse , const FHitResult& Hit)
{
	Destroy();
}

void AD1Box::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1 , 2.0f , FColor::Magenta , TEXT("D1BoxOverlap!"));
}


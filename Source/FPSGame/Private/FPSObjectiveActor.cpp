// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSObjectiveActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.h"

// Sets default values
AFPSObjectiveActor::AFPSObjectiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	// collision to no
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RootComponent = MeshComp;
	
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));	
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // collision to query only
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore); // ignore all
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // for player
	
	SphereComp->SetupAttachment(MeshComp);
	// SphereComp->OnComponentBeginOverlap
}

// Called when the game starts or when spawned
void AFPSObjectiveActor::BeginPlay()
{
	Super::BeginPlay();
	
}
// Play Effect, protected not called from outside
void AFPSObjectiveActor::PlayEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, PickupFX, GetActorLocation());

}


// Called when Actor is Overlapped
void AFPSObjectiveActor::NotifyActorBeginOverlap(AActor* OtherActor) {

	Super::NotifyActorBeginOverlap(OtherActor);

	PlayEffects();

	AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(OtherActor);

	if (MyCharacter) {
		MyCharacter->bIsCarryingObjective = true;

		Destroy();
	}
}

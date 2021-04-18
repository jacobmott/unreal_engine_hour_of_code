// Fill out your copyright notice in the Description page of Project Settings.


#include "C_MySequenceFloatIslandActor.h"
#include "Runtime/LevelSequence/Public/LevelSequence.h"
#include "Runtime/LevelSequence/Public/LevelSequencePlayer.h"
#include "Runtime/MovieScene/Public/MovieSceneSequence.h"
#include "Runtime/MovieScene/Public/MovieSceneSequencePlayer.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AC_MySequenceFloatIslandActor::AC_MySequenceFloatIslandActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
  MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
  MeshComp->SetCollisionResponseToAllChannels(ECR_Ignore);
  MeshComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
  RootComponent = MeshComp;

  FMovieSceneSequencePlaybackSettings PlaybackSettings;
  LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
    GetWorld(),
    SequenceAsset,
    PlaybackSettings,
    MovieActor
  );

  //SequenceAsset->GetMovieScene()->AddPossessable("MESH", MeshComp->GetClass());
  //SequenceAsset->GetMovieScene()->Track
  //MovieActor = GetWorld()->SpawnActor<ALevelSequenceActor>();
  //MovieActor = GetWorld()->SpawnActor<ALevelSequenceActor>(static_cast<UClass>(ALevelSequenceActor));
  //MovieActor->SetSequence(IntroMovieSequence);
  //MovieActor->SequencePlayer->Play();

}

// Called when the game starts or when spawned
void AC_MySequenceFloatIslandActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_MySequenceFloatIslandActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


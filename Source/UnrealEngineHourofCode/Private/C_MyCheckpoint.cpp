// Fill out your copyright notice in the Description page of Project Settings.


#include "C_MyCheckpoint.h"
#include "Components/SphereComponent.h"
//#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
//#include "Blueprint/AIBlueprintHelperLibrary.h"
#include <string>
#include "Engine/GameEngine.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "C_Logger.h"
#include "C_MyGameStateBase.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

// Sets default values
AC_MyCheckpoint::AC_MyCheckpoint()
{
  //FObjectInitializer& Init;


  //DefaultInstanceData = Init.CreateDefaultSubobject<UDefaultLevelSequenceInstanceData>(this, "InstanceData");

  // SequencePlayer must be a default sub object for it to be replicated correctly
  //SequencePlayer = Init.CreateDefaultSubobject<ULevelSequencePlayer>(this, "AnimationPlayer");
  //FStringAssetReference SequenceName("/Game/NewLevelSequence.NewLevelSequence");
  //ULevelSequence* Asset = Cast<ULevelSequence>(SequenceName.TryLoad());
  //static ULevelSequencePlayer* CreateLevelSequencePlayer(UObject* WorldContextObject, ULevelSequence* LevelSequence, FMovieSceneSequencePlaybackSettings Settings);
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;
  //ACLoggerInstance->printToScreen(10.0f, FColor::Green, TEXT("Called AC_MyCheckpoint::AC_MyCheckpoint (Contructor)"));

  //SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
  //RootComponent = SceneComp;



  MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
  MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
  MeshComp->SetCollisionResponseToAllChannels(ECR_Ignore);
  MeshComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
  RootComponent = MeshComp;

  MeshComp2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp2"));
  MeshComp2->SetupAttachment(MeshComp);
  MeshComp2->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
  MeshComp2->SetCollisionResponseToAllChannels(ECR_Ignore);
  MeshComp2->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);

  SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
  SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AC_MyCheckpoint::HandleOverlap);
  SphereComp->SetupAttachment(MeshComp);
  paperSpriteTransformLocation = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("CheckpointTransform"));
  paperSpriteTransformLocation->AddRelativeLocation(FVector(0.0f, 0.0f, -7.0f));
  paperSpriteTransformLocation->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("/Game/Hour_of_Code/Sprites/location.location")).Object);
  paperSpriteTransformLocation->SetupAttachment(MeshComp);



  soundCue = CreateDefaultSubobject<USoundCue>(TEXT("SoundCue"));
  audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
  audioComponent->SetAutoActivate(false);
  audioComponent->SetupAttachment(MeshComp);
  //create dynamic material anywhere u like, Constructor or anywhere .
  //UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(Material, this);
  //MeshComp->SetMaterial(0, DynMaterial);
}

void AC_MyCheckpoint::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{

  ACLoggerInstance->printToScreen( 10.0f, FColor::Green, FString::Printf( TEXT("Called AC_MyCheckpoint::HandleOverlap (HandleOverlap): %s"), isCheckPointEnabled ? TEXT("True") : TEXT("False") ) );
  if (isCheckPointEnabled) {
    //Get the first material of the static mesh and turn it into a material instance
    UMaterialInstanceDynamic* Material1;
    if (MeshComp->GetMaterial(0)->IsA(UMaterialInstanceDynamic::StaticClass())) {
      ACLoggerInstance->printToScreen(10.0f, FColor::Yellow, TEXT("Called AC_MyCheckpoint::HandleOverlap (HandleOverlap): Checkpoint Enabled: MeshComp's material is already a UMaterialInstanceDynamic"));
      Material1 = static_cast<UMaterialInstanceDynamic*>(MeshComp->GetMaterial(1));
    }
    else {
      Material1 = UMaterialInstanceDynamic::Create(MeshComp->GetMaterial(0), this);
    }
    if (Material1) {
      dumpMaterial(Material1);
    }
  }
  else{
    isCheckPointEnabled = true;

    //Get the first material of the static mesh and turn it into a material instance
    UMaterialInstanceDynamic* Material1;
    if (MeshComp->GetMaterial(0)->IsA(UMaterialInstanceDynamic::StaticClass())) {
      ACLoggerInstance->printToScreen(10.0f, FColor::Yellow, TEXT("Called AC_MyCheckpoint::HandleOverlap (HandleOverlap): Checkpoint Enabled false: MeshComp's material is already a UMaterialInstanceDynamic"));
      Material1 = static_cast<UMaterialInstanceDynamic*>(MeshComp->GetMaterial(0));
    }
    else {
      Material1 = UMaterialInstanceDynamic::Create(MeshComp->GetMaterial(0), this);
    }
    //If we have a valid dynamic material instance, modify its parameters
    if (Material1){
      //Generate random RGB and Alpha values for our Vector Parameter
      FLinearColor RandomColor;
      //RandomColor.R = FMath::RandRange(0, 1);
      //RandomColor.G = FMath::RandRange(0, 1);
      //RandomColor.B = FMath::RandRange(0, 1);
      //RandomColor.A = FMath::RandRange(0, 1);
      //Blue
      RandomColor.R = 0.0f;
      RandomColor.G = 1.0;
      RandomColor.B = 0.0;
      RandomColor.A = 1;
      ACLoggerInstance->printToScreen(10.0f, FColor::Yellow, TEXT("Called AC_MyCheckpoint::HandleOverlap (HandleOverlap): Setting Material Color"));
      Material1->SetVectorParameterValue(FName("Color"), RandomColor);
      MeshComp->SetMaterial(0, Material1);
      dumpMaterial(Material1);
    }
  }

  if (OtherActor) {
    AC_MyGameStateBase* const MyGameState = GetWorld() != NULL ? GetWorld()->GetGameState<AC_MyGameStateBase>() : NULL;
    MyGameState->setPlayerSpawnLocation(paperSpriteTransformLocation->GetComponentTransform().GetLocation());
    ACLoggerInstance->printToScreen(10.0f, FColor::Yellow, TEXT("Called AC_MyCheckpoint::HandleOverlap (setPlayerSpawnLocation)"));
    // You can fade the sound in... 
    float startTime = 0.0f;
    float volume = 1.0f;
    float fadeTime = 0.0f;
    audioComponent->FadeIn(fadeTime, volume, startTime);
    audioComponent->Play(0.0f);
  }
  

}

// Called when the game starts or when spawned
void AC_MyCheckpoint::BeginPlay()
{
  Super::BeginPlay();

  AC_MyGameStateBase* const MyGameState = GetWorld() != NULL ? GetWorld()->GetGameState<AC_MyGameStateBase>() : NULL;
  ACLoggerInstance = MyGameState->getLogger();
  ACLoggerInstance->printToScreen(10.0f, FColor::Green, TEXT("Called AC_MyCheckpoint::BeginPlay (BeginPlay)"));
    
  //Get the first material of the static mesh and turn it into a material instance
  UMaterialInstanceDynamic* Material1;
  if ( MeshComp->GetMaterial(0)->IsA(UMaterialInstanceDynamic::StaticClass()) ) {
    ACLoggerInstance->printToScreen(10.0f, FColor::Yellow, TEXT("Called AC_MyCheckpoint::BeginPlay (BeginPlay): MeshComp's material is already a UMaterialInstanceDynamic"));
    Material1 = static_cast<UMaterialInstanceDynamic*>(MeshComp->GetMaterial(0));
  }
  else {
    Material1 = UMaterialInstanceDynamic::Create(MeshComp->GetMaterial(0), this);
  }

  //UMaterialInstanceDynamic* Material1 = UMaterialInstanceDynamic::Create(MeshComp->GetMaterial(0), this);
  //Material = MeshComp->CreateAndSetMaterialInstanceDynamic(0);


  //If we have a valid dynamic material instance, modify its parameters
  if (Material1)
  {
    FLinearColor RandomColor;
    RandomColor.R = 1;
    RandomColor.G = 0.0;
    RandomColor.B = 0.0;
    RandomColor.A = 1;
    ACLoggerInstance->printToScreen(10.0f, FColor::Yellow, TEXT("Called AC_MyCheckpoint::BeginPlay (BeginPlay): Setting Material Color"));
    Material1->SetVectorParameterValue(FName("Color"), RandomColor);
    MeshComp->SetMaterial(0, Material1);
    dumpMaterial(Material1);
  }
}

void AC_MyCheckpoint::dumpMaterial(UMaterialInstanceDynamic* Material1)
{

  FLinearColor result = Material1->K2_GetVectorParameterValue(FName("Color"));
  ACLoggerInstance->printToScreen(10.0f, FColor::Red, FString::Printf(TEXT("Called AC_MyCheckpoint::dumpMaterial (dumpMaterial): name: %s"), *Material1->GetName()));
  ACLoggerInstance->printToScreen(10.0f, FColor::Orange, FString::Printf(TEXT("Called AC_MyCheckpoint::dumpMaterial (dumpMaterial): result R: %f"), result.R));
  ACLoggerInstance->printToScreen(10.0f, FColor::Orange, FString::Printf(TEXT("Called AC_MyCheckpoint::dumpMaterial (dumpMaterial): result G: %f"), result.G));
  ACLoggerInstance->printToScreen(10.0f, FColor::Orange, FString::Printf(TEXT("Called AC_MyCheckpoint::dumpMaterial (dumpMaterial): result B: %f"), result.B));
  ACLoggerInstance->printToScreen(10.0f, FColor::Orange, FString::Printf(TEXT("Called AC_MyCheckpoint::dumpMaterial (dumpMaterial): result A: %f"), result.A));

}

// Called every frame
void AC_MyCheckpoint::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void AC_MyCheckpoint::NotifyActorBeginOverlap(AActor * OtherActor)
{

  Super::NotifyActorBeginOverlap(OtherActor);

  //HandleOverlap();



}




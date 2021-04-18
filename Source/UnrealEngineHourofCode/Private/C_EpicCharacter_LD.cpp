// Fill out your copyright notice in the Description page of Project Settings.


#include "C_EpicCharacter_LD.h"
#include "C_Logger.h"
#include "C_MyGameStateBase.h"
#include "Components/InputComponent.h"

// Sets default values
AC_EpicCharacter_LD::AC_EpicCharacter_LD()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
  bReplicates = true;
  AutoPossessPlayer = EAutoReceiveInput::Player0;


  static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'/Game/Hour_of_Code/Blueprints/BC_MYIsland.BC_MYIsland'"));
  if (ItemBlueprint.Object)
  {
    spawnIsland = (UClass*)ItemBlueprint.Object->GeneratedClass;
  }


}

// Called when the game starts or when spawned
void AC_EpicCharacter_LD::BeginPlay()
{
	Super::BeginPlay();

  AC_MyGameStateBase* const MyGameState = GetWorld() != NULL ? GetWorld()->GetGameState<AC_MyGameStateBase>() : NULL;
  ACLoggerInstance = MyGameState->getLogger();
  UE_LOG(LogTemp, Warning, TEXT("Called AC_EpicCharacter_LD::BeginPlay"));
  ACLoggerInstance->printToScreen(10.0f, FColor::Red, TEXT("Called AC_EpicCharacter_LD::BeginPlay"));
	
}

// Called every frame
void AC_EpicCharacter_LD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AC_EpicCharacter_LD::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


  InputComponent->BindAction("SpawnIsland", IE_Pressed, this, &AC_EpicCharacter_LD::SpawnIsland);
}

void AC_EpicCharacter_LD::SpawnIsland()
{

  ACLoggerInstance->printToScreen(10.0f, FColor::Green, TEXT("Called AC_EpicCharacter_LD::SpawnIsland"));

  //FActorSpawnParameters SpawnInfo;
  //SpawnInfo.Owner = this;
  //FStringAssetReference itemRef = "Blueprint'/Game/Hour_of_Code/Blueprints/BC_MYIsland.BC_MYIsland'";
  //UObject* itemObj = itemRef.TryLoad();
  //UBlueprint* gen = Cast<UBlueprint>(itemObj);
  ////UClass* MyItemBlueprintClass = StaticLoadClass(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/ThirdPersonBP/Blueprints/EpicCharacter.EpicCharacter'"), NULL, LOAD_None, NULL);
  ////AC_EpicCharacter_LD* SpawnedActor = GetWorld()->SpawnActor<AC_EpicCharacter_LD>(MyItemBlueprintClass, playerLocation, FRotator(), SpawnInfo);
  //GetWorld()->SpawnActor<UStaticMeshComponent>(gen->GeneratedClass, GetActorLocation() + FVector(1.0f, 1.0f, 1.0f), FRotator(), SpawnInfo);


  //UClass* MyItemBlueprintClass;
  //if (ItemBlueprint.Object) {
  //  MyItemBlueprintClass = (UClass*)ItemBlueprint.Object->GeneratedClass;
  //}


  if (GetWorld()) {
    FActorSpawnParameters SpawnParams;
    SpawnParams.Instigator = this;
    FVector location = GetActorLocation() + FVector(1.0f, 1.0f, 1.0f);
    FRotator rotation = FRotator();
    //GetWorld()->SpawnActor(ItemBlueprint.Object->GetClass(), &location, &rotation, SpawnParams);


    AActor* equipOnSpawn = GetWorld()->SpawnActor(spawnIsland, &location, &rotation, SpawnParams);

  }

}


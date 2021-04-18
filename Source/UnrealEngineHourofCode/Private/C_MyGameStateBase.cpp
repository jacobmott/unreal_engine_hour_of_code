// Fill out your copyright notice in the Description page of Project Settings.


#include "C_MyGameStateBase.h"
#include "C_Logger.h"
#include "Kismet/GameplayStatics.h"
#include "C_EpicCharacter_LD.h"

void AC_MyGameStateBase::HandleBeginPlay() {
  Super::HandleBeginPlay();
  getLogger();
  ACLoggerInstance->printToScreen(10.0f, FColor::Yellow, TEXT("Called AC_MyGameStateBase::HandleBeginPlay (HandleBeginPlay)"));
  UE_LOG(LogTemp, Warning, TEXT("Called AC_MyGameStateBase::HandleBeginPlay"));
  playerLocation = FVector(6170.0f, -1400.0f, 502.0f);
  ACharacter* MyCharacter = static_cast<AC_EpicCharacter_LD*>(UGameplayStatics::GetPlayerCharacter(this, 0));
  if (IsValid(MyCharacter)){
    MyCharacter->OnDestroyed.AddDynamic(this, &AC_MyGameStateBase::WhenPlayerDestroyed);
    MyCharacter->SetActorLocation(playerLocation);
  }

}

void AC_MyGameStateBase::WhenPlayerDestroyed(AActor* DestroyedActor){
  ACLoggerInstance->printToScreen(10.0f, FColor::Yellow, TEXT("Called AC_MyGameStateBase::WhenPlayerDestroyed (WhenPlayerDestroyed)"));
  //DestroyedActor->SetActorLocation(playerLocation);

  //AC_EpicCharacter_LD* SpawnedActor = GetWorld()->SpawnActor<AC_EpicCharacter_LD>(playerLocation, DestroyedActor->GetActorRotation(), SpawnInfo);
  //GetWorld()->GetFirstPlayerController()->Possess(SpawnedActor);
  FTimerHandle TimerHandle;
  GetWorldTimerManager().SetTimer(TimerHandle, this, &AC_MyGameStateBase::respawn, 0.25f, false);

}

void AC_MyGameStateBase::setPlayerSpawnLocation(FVector location)
{
  playerLocation = location;
}

void AC_MyGameStateBase::respawn()
{

  FActorSpawnParameters SpawnInfo;
  SpawnInfo.Owner = this;
  FStringAssetReference itemRef = "Blueprint'/Game/ThirdPersonBP/Blueprints/EpicCharacter.EpicCharacter'";
  ACLoggerInstance->printToScreen(10.0f, FColor::Yellow, FString::Printf(TEXT("Called AC_MyGameStateBase::respawn (playerLocation): %s"), *playerLocation.ToString()) );
  UObject* itemObj = itemRef.ResolveObject();
  UBlueprint* gen = Cast<UBlueprint>(itemObj);
  //UClass* MyItemBlueprintClass = StaticLoadClass(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/ThirdPersonBP/Blueprints/EpicCharacter.EpicCharacter'"), NULL, LOAD_None, NULL);
  //AC_EpicCharacter_LD* SpawnedActor = GetWorld()->SpawnActor<AC_EpicCharacter_LD>(MyItemBlueprintClass, playerLocation, FRotator(), SpawnInfo);
  AC_EpicCharacter_LD* SpawnedActor = GetWorld()->SpawnActor<AC_EpicCharacter_LD>(gen->GeneratedClass, playerLocation, FRotator(), SpawnInfo);

  //AC_EpicCharacter_LD* SpawnedActor = GetWorld()->SpawnActor<AC_EpicCharacter_LD>(playerLocation, DestroyedActor->GetActorRotation(), SpawnInfo);
  GetWorld()->GetFirstPlayerController()->Possess(SpawnedActor);
  SpawnedActor->OnDestroyed.AddDynamic(this, &AC_MyGameStateBase::WhenPlayerDestroyed);
}


// In proper builds, this wouldn't be necessary (I'll explain this further down)
AC_Logger *AC_MyGameStateBase::getLogger()
{

  if (ACLoggerInstance) {
    return ACLoggerInstance;
  }
  else {
    ACLoggerInstance = NewObject<AC_Logger>(this, FName("getLogger"));
  }
  return ACLoggerInstance;
}

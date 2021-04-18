// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_MyCheckpoint.generated.h"

class USphereComponent;
//class USceneComponent;
class UPaperSpriteComponent;
class AC_Logger;
class USoundCue;
class UAudioComponent;

UCLASS()
class UNREALENGINEHOUROFCODE_API AC_MyCheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_MyCheckpoint();

protected:

  UPROPERTY(EditAnywhere, Category = "Components")
  UAudioComponent* audioComponent;

  UPROPERTY(EditAnywhere, Category = "Components")
  USoundCue* soundCue;

  UPROPERTY(EditAnywhere)
  UPaperSpriteComponent* paperSpriteTransformLocation;


  UPROPERTY(EditAnywhere)
  UMaterialInstanceDynamic* Material;

  UPROPERTY(EditAnywhere)
  bool isCheckPointEnabled = false;
  //UPROPERTY(VisibleAnywhere, Category = "Components")
  //USceneComponent* SceneComp;

  UPROPERTY(VisibleAnywhere, Category = "Components")
  UStaticMeshComponent* MeshComp;

  UPROPERTY(VisibleAnywhere, Category = "Components")
  UStaticMeshComponent* MeshComp2;

  UPROPERTY(VisibleAnywhere, Category = "Components")
  USphereComponent* SphereComp;

  UFUNCTION()
  void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private: 
  void dumpMaterial(UMaterialInstanceDynamic* Material);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

  virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;


private:
  AC_Logger* ACLoggerInstance;

};



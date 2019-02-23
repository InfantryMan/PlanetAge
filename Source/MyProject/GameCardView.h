// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "PlanetCoefficientValues.h"

#include "GameCardView.generated.h"

UCLASS()
class MYPROJECT_API AGameCardView : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameCardView();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Size of GameCard
	static const int xCardSize = 488;
	static const int yCardSize = 302;
	static const int zCardSize = 30;
	static const int xLeftSideCardSize = 182;
	static const int xRightSizeCardSize = xCardSize - xLeftSideCardSize;

	// Meshes:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		UStaticMeshComponent* CardMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		UStaticMeshComponent* PlanetMesh;

	UPROPERTY(EditAnywhere)
		FPlanetCoefficientValues Coeffs;

};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TargetBox.generated.h"

UCLASS()
class CYRUSFPSASSIGNMENT_API ATargetBox : public AActor
{
	GENERATED_BODY()

public:
	ATargetBox();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// Material reference
	UPROPERTY(EditAnywhere)
	UMaterialInterface* BaseMaterial;

	// Dynamic material instance
	UMaterialInstanceDynamic* DynamicMaterial;
	
	// Box mesh
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BoxMesh;

	// Health of the box
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box")
	int32 Health;

	// Score awarded when destroyed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box")
	int32 Score;

	// Function to apply damage
	UFUNCTION(BlueprintCallable)
	int32 TakeBoxDamage(int32 DamageAmount);

	void SetBoxColor(FColor NewColor);
};
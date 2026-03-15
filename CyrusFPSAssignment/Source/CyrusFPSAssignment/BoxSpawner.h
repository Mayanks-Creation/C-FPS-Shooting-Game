#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Http.h"
#include "BoxSpawner.generated.h"

USTRUCT()
struct FBoxTypeData
{
	GENERATED_BODY()

	FColor Color;
	int32 Health;
	int32 Score;
};

UCLASS()
class CYRUSFPSASSIGNMENT_API ABoxSpawner : public AActor
{
	GENERATED_BODY()

	TMap<FString, FBoxTypeData> TypeDataMap;

	

public:
	ABoxSpawner();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TSubclassOf<class ATargetBox> TargetBoxClass;
protected:
	virtual void BeginPlay() override;

private:

	// Function that sends HTTP request
	void FetchJSONData();

	// Callback when request finishes
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
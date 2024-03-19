#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Pawns/Player/Components/Draggable.h"
#include "../Pawns/Unit/UnitReport.h"
#include "Report.generated.h"

UCLASS()
class GAME1812_API AReport : public AActor, public IDraggable
{
	GENERATED_BODY()
	
public:	

	AReport();

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* PaperMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FUnitReport Report;

public:	

	UFUNCTION(BlueprintNativeEvent)
	void SetReportData(const FUnitReport& ReportData);

	//IDraggable Interface
	void StartDragging() override;
	void StopDragging() override;
	FVector GetDragOffset() override;
	//
};

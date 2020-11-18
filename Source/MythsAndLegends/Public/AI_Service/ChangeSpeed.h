#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "ChangeSpeed.generated.h"

UCLASS()
class MYTHSANDLEGENDS_API UChangeSpeed : public UBTService_BlackboardBase
{
    GENERATED_BODY()
public:
    UChangeSpeed();
    virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
    virtual FString GetStaticServiceDescription() const override;

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI", meta=(AllowPrivateAccess="true"))
    float Speed = 600.0f;
};

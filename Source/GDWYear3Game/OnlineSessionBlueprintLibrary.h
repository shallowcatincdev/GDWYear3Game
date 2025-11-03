#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionBlueprintLibrary.generated.h"

UCLASS()
class GDWYEAR3GAME_API UOnlineSessionBlueprintLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /**
     * Creates an EOS online session.
     * @param WorldContextObject - Blueprint context.
     * @param PlayerController - Player creating the session.
     * @param SessionName - Name of the session.
     * @param NumPublicConnections - Number of public players allowed.
     * @param bIsLAN - If true, creates a LAN session.
     * @return True if creation started successfully.
     */
    UFUNCTION(BlueprintCallable, Category = "Online|Session", meta = (WorldContext = "WorldContextObject"))
    static bool CreateEOSSession(UObject* WorldContextObject, APlayerController* PlayerController, FName SessionName, int32 NumPublicConnections, bool bIsLAN);
};
#include "OnlineSessionBlueprintLibrary.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Engine/LocalPlayer.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"


bool UOnlineSessionBlueprintLibrary::CreateEOSSession(UObject* WorldContextObject, APlayerController* PlayerController, FName SessionName, int32 NumPublicConnections, bool bIsLAN)
{
    if(!PlayerController)
    {
        UE_LOG(LogTemp, Warning, TEXT("CreateEOSSession failed: PlayerController is null."));
        return false;
    }

    UWorld* World = WorldContextObject ? WorldContextObject->GetWorld() : nullptr;
    if(!World)
    {
        UE_LOG(LogTemp, Warning, TEXT("CreateEOSSession failed: WorldContextObject is invalid."));
        return false;
    }

    IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get(TEXT("EOS"));
    if(!OnlineSub)
    {
        UE_LOG(LogTemp, Warning, TEXT("CreateEOSSession failed: EOS OnlineSubsystem not found."));
        return false;
    }

    IOnlineSessionPtr SessionInterface = OnlineSub->GetSessionInterface();
    if(!SessionInterface.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("CreateEOSSession failed: Session interface invalid."));
        return false;
    }

    // Prepare session settings
    FOnlineSessionSettings SessionSettings;
    SessionSettings.bIsLANMatch = bIsLAN;
    SessionSettings.NumPublicConnections = NumPublicConnections;
    SessionSettings.bShouldAdvertise = true;
    SessionSettings.bAllowJoinInProgress = true;
    SessionSettings.bUsesPresence = true;
    SessionSettings.bAllowJoinViaPresence = true;
    SessionSettings.bAllowJoinViaPresenceFriendsOnly = false;

    // Get the user's unique ID
    ULocalPlayer* LocalPlayer = PlayerController ? PlayerController->GetLocalPlayer() : nullptr;
    FUniqueNetIdRepl UniqueNetIdRepl = LocalPlayer ? LocalPlayer->GetPreferredUniqueNetId() : FUniqueNetIdRepl();
    TSharedPtr<const FUniqueNetId> UserId = UniqueNetIdRepl.IsValid() ? UniqueNetIdRepl.GetUniqueNetId() : nullptr;
    if(!UserId.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("CreateEOSSession failed: UserId invalid."));
        return false;
    }

    bool bStarted = SessionInterface->CreateSession(*UserId, SessionName, SessionSettings);
    if(!bStarted)
    {
        UE_LOG(LogTemp, Warning, TEXT("CreateEOSSession call to CreateSession failed to start."));
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("CreateEOSSession call to CreateSession started."));
    }

    return bStarted;
}
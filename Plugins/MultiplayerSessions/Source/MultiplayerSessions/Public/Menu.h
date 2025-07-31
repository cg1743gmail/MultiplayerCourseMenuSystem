"""// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Menu.generated.h"

/**
 * 这是一个UMG（Unreal Motion Graphics）用户界面控件，用于提供一个简单的菜单，
 * 让玩家可以创建（主持）或加入游戏会话。
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	// 设置菜单，可以在蓝图中调用此函数来初始化菜单
	void MenuSetup(int32 NumberOfPublicConnections = 4, FString TypeOfMatch = FString(TEXT("FreeForAll")), FString LobbyPath = FString(TEXT("/Game/ThirdPersonCPP/Maps/Lobby")));

protected:

	virtual bool Initialize() override;
	virtual void NativeDestruct() override;

	//
	// MultiplayerSessionsSubsystem上自定义委托的回调函数
	//
	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);
	void OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);
	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);
	UFUNCTION()
	void OnDestroySession(bool bWasSuccessful);
	UFUNCTION()
	void OnStartSession(bool bWasSuccessful);

private:

	// 绑定到UMG设计器中的“主持”按钮
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;

	// 绑定到UMG设计器中的“加入”按钮
	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;

	// “主持”按钮的点击事件处理函数
	UFUNCTION()
	void HostButtonClicked();

	// “加入”按钮的点击事件处理函数
	UFUNCTION()
	void JoinButtonClicked();

	// 移除菜单并恢复游戏输入模式
	void MenuTearDown();

	// 用于处理所有在线会话功能的子系统
	class UMultiplayerSessionsSubsystem* MultiplayerSessionsSubsystem;

	// 会话的公共连接数
	int32 NumPublicConnections{4};
	// 匹配类型
	FString MatchType{TEXT("FreeForAll")};
	// 成功创建/加入会话后要前往的大厅地图路径
	FString PathToLobby{TEXT("")};
};
""

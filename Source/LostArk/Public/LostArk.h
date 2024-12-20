// Copyright Epic Games, Inc. All Rights Reserved.

// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(Msg, Log, All)

// 호출된 함수위치, 줄번호까지 문자열로 가져오기
#define APPINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))

// 호출된 정보만 찍는 매크로
#define PRINT_INFO() UE_LOG(Msg, Warning, TEXT("%s"), *APPINFO)

// 주어진 포맷으로 메시지를 찍는 매크로
#define PRINT_LOG(fmt, ...) UE_LOG(Msg, Warning, TEXT("%s %s"), *APPINFO, *FString::Printf(fmt, ##__VA_ARGS__))
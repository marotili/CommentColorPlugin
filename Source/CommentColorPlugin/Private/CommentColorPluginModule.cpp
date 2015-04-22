// The MIT License(MIT)
//
// Copyright(c) 2015 Marco Fruhwirth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

#include "CommentColorPluginPrivatePCH.h"
#include "CommentColorSettings.h"

#include "ISettingsModule.h"
#include "BlueprintEditorModule.h"
#include "BlueprintEditor.h"
#include "GraphEditorSettings.h"

#define LOCTEXT_NAMESPACE "CommentColor"

DEFINE_LOG_CATEGORY(CommentColorPlugin)

class FCommentColorEditorCommands : public TCommands < FCommentColorEditorCommands >
{
public:
	FCommentColorEditorCommands()
		: TCommands<FCommentColorEditorCommands>(
		TEXT("CommentColorEditor"), // Context name for fast lookup
		NSLOCTEXT("Contexts", "CommentColorEditor", "CommentColor"), // Localized context name for displaying
		NAME_None, // Parent
		FEditorStyle::GetStyleSetName()
		)
	{
	}

	// TCommand<> interface
	virtual void RegisterCommands() override
	{
		FText CommandLabelText;
		FText Description = FText::Format(NSLOCTEXT("BlueprintEditor", "Comment color", "Set the comment color."), CommandLabelText);
		TSharedPtr< FUICommandInfo > CommandInfo;
		CommandLabelText = FText::FromString("CommentColor1");
		FUICommandInfo::MakeCommandInfo(this->AsShared(), CommandInfo, FName("CommentColor1"), CommandLabelText, Description, FSlateIcon(), EUserInterfaceActionType::Button, FInputGesture(EKeys::One));
		SetCommentColor.Add(CommandInfo);
		CommandLabelText = FText::FromString("CommentColor2");
		FUICommandInfo::MakeCommandInfo(this->AsShared(), CommandInfo, FName("CommentColor2"), CommandLabelText, Description, FSlateIcon(), EUserInterfaceActionType::Button, FInputGesture(EKeys::Two));
		SetCommentColor.Add(CommandInfo);
		CommandLabelText = FText::FromString("CommentColor3");
		FUICommandInfo::MakeCommandInfo(this->AsShared(), CommandInfo, FName("CommentColor3"), CommandLabelText, Description, FSlateIcon(), EUserInterfaceActionType::Button, FInputGesture(EKeys::Three));
		SetCommentColor.Add(CommandInfo);
		CommandLabelText = FText::FromString("CommentColor4");
		FUICommandInfo::MakeCommandInfo(this->AsShared(), CommandInfo, FName("CommentColor4"), CommandLabelText, Description, FSlateIcon(), EUserInterfaceActionType::Button, FInputGesture(EKeys::Four));
		SetCommentColor.Add(CommandInfo);
		CommandLabelText = FText::FromString("CommentColor5");
		FUICommandInfo::MakeCommandInfo(this->AsShared(), CommandInfo, FName("CommentColor5"), CommandLabelText, Description, FSlateIcon(), EUserInterfaceActionType::Button, FInputGesture(EKeys::Five));
		SetCommentColor.Add(CommandInfo);
		CommandLabelText = FText::FromString("CommentColor6");
		FUICommandInfo::MakeCommandInfo(this->AsShared(), CommandInfo, FName("CommentColor6"), CommandLabelText, Description, FSlateIcon(), EUserInterfaceActionType::Button, FInputGesture(EKeys::Six));
		SetCommentColor.Add(CommandInfo);
		CommandLabelText = FText::FromString("CommentColor7");
		FUICommandInfo::MakeCommandInfo(this->AsShared(), CommandInfo, FName("CommentColor7"), CommandLabelText, Description, FSlateIcon(), EUserInterfaceActionType::Button, FInputGesture(EKeys::Seven));
		SetCommentColor.Add(CommandInfo);
		CommandLabelText = FText::FromString("CommentColor8");
		FUICommandInfo::MakeCommandInfo(this->AsShared(), CommandInfo, FName("CommentColor8"), CommandLabelText, Description, FSlateIcon(), EUserInterfaceActionType::Button, FInputGesture(EKeys::Eight));
		SetCommentColor.Add(CommandInfo);
		CommandLabelText = FText::FromString("CommentColor9");
		FUICommandInfo::MakeCommandInfo(this->AsShared(), CommandInfo, FName("CommentColor9"), CommandLabelText, Description, FSlateIcon(), EUserInterfaceActionType::Button, FInputGesture(EKeys::Nine));
		SetCommentColor.Add(CommandInfo);
		CommandLabelText = FText::FromString("CommentColor0");
		FUICommandInfo::MakeCommandInfo(this->AsShared(), CommandInfo, FName("CommentColor0"), CommandLabelText, Description, FSlateIcon(), EUserInterfaceActionType::Button, FInputGesture(EKeys::Zero));
		SetCommentColor.Add(CommandInfo);
	}
	// End of TCommand<> interface

public:
	// Show toggles
	TArray< TSharedPtr<FUICommandInfo> > SetCommentColor;
};
class FCommentColorModule : public ICommentColorModule
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE(FCommentColorModule, CommentColorModule)

TArray<FLinearColor> Colors;


void SetCommentColor(int index)
{
	check(index >= 0);
	FBlueprintEditorModule& BlueprintEditorModule = FModuleManager::GetModuleChecked<FBlueprintEditorModule>("Kismet");
	UGraphEditorSettings* Settings = GetMutableDefault<UGraphEditorSettings>();

	if (Colors.Num() > index)
	{
		Settings->DefaultCommentNodeTitleColor = Colors[index];
	}
}

void FCommentColorModule::StartupModule()
{
	Colors.Add(FLinearColor(0.0f, 0.0f, 0.0f));
	Colors.Add(FLinearColor(1.0f, 1.0f, 1.0f));
	Colors.Add(FLinearColor(1.0f, 0.0f, 0.0f));
	Colors.Add(FLinearColor(0.0f, 1.0f, 0.0f));
	Colors.Add(FLinearColor(0.0f, 0.0f, 1.0f));
	Colors.Add(FLinearColor(1.0f, 1.0f, 0.0f));
	Colors.Add(FLinearColor(1.0f, 0.0f, 1.0f));
	Colors.Add(FLinearColor(0.0f, 1.0f, 1.0f));

	FCommentColorEditorCommands::Register();
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
	SettingsModule->RegisterSettings("Editor", "ContentEditors", "CommentColor",
		LOCTEXT("CommentColorSettingsName", "CommentColor"),
		LOCTEXT("CommentColorSettingsDescription", "Set comment colors"),
		GetMutableDefault<UCommentColorSettings>());

	FBlueprintEditorModule& BlueprintEditorModule = FModuleManager::LoadModuleChecked<FBlueprintEditorModule>("Kismet");
	const TSharedRef<FUICommandList> CommandList = BlueprintEditorModule.GetsSharedBlueprintEditorCommands();

	for (int32 ColorIndex = 0; ColorIndex < Colors.Num(); ColorIndex++)
	{
		CommandList->MapAction(FCommentColorEditorCommands::Get().SetCommentColor[ColorIndex],
			FExecuteAction::CreateStatic(SetCommentColor, ColorIndex));
	}
}


void FCommentColorModule::ShutdownModule()
{
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
	SettingsModule->UnregisterSettings("Editor", "ContentEditors", "CommentColor");
}

#undef LOCTEXT_NAMESPACE

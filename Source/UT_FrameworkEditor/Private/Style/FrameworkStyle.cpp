/************************************************************************/
/* UMBRA TOOLS                                                          */
/* Maxwell - Axel Clerget   											*/
/************************************************************************/

#include "FrameworkStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Styling/SlateTypes.h"
#include "EditorStyleSet.h"
#include "Interfaces/IPluginManager.h"
#include "SlateOptMacros.h"

#define IMAGE_PLUGIN_BRUSH( RelativePath, ... ) FSlateImageBrush( FFrameworkStyle::InContent( RelativePath, ".png" ), __VA_ARGS__ )
#define IMAGE_BRUSH(RelativePath, ...) FSlateImageBrush(StyleSet->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)
#define BOX_BRUSH(RelativePath, ...) FSlateBoxBrush(StyleSet->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)
#define TTF_FONT(RelativePath, ...) FSlateFontInfo(StyleSet->RootToContentDir(RelativePath, TEXT(".ttf")), __VA_ARGS__)
#define TTF_CORE_FONT(RelativePath, ...) FSlateFontInfo(StyleSet->RootToCoreContentDir(RelativePath, TEXT(".ttf") ), __VA_ARGS__)
#define PLUGIN_BRUSH(RelativePath,...) FSlateImageBrush(FFrameworkStyle::InContent(RelativePath,TEXT(".png")),__VA_ARGS__)

TSharedPtr< FSlateStyleSet > FFrameworkStyle::StyleSet = nullptr;

TSharedPtr<class ISlateStyle> FFrameworkStyle::Get()
{
	return StyleSet;
}

FName FFrameworkStyle::GetStyleSetName()
{
	static FName PaperStyleName(TEXT("FrameworkStyle"));
	return PaperStyleName;
}

FString FFrameworkStyle::InContent(const FString& RelativePath, const TCHAR* Extension)
{
	static FString ContentDir = IPluginManager::Get().FindPlugin(TEXT("UT_Framework"))->GetContentDir();
	return (ContentDir / RelativePath) + Extension;
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void FFrameworkStyle::Initialize()
{
	// Const icon sizes
	const FVector2D Icon8x8(8.0f, 8.0f);
	const FVector2D Icon16x16(16.0f, 16.0f);
	const FVector2D Icon20x20(20.0f, 20.0f);
	const FVector2D Icon40x40(40.0f, 40.0f);
	const FVector2D Generic10x10(10.0f, 10.0f);
	const FVector2D NodeBody64x64(64.0f, 64.0f);

	// Only register once
	if (StyleSet.IsValid())
		return;

	StyleSet = MakeShareable(new FSlateStyleSet(GetStyleSetName()));
	StyleSet->SetContentRoot(IPluginManager::Get().FindPlugin(TEXT("UT_Framework"))->GetContentDir());
	
	// Icons 
	StyleSet->Set("ClassIcon.NpcBehavior", new PLUGIN_BRUSH(TEXT("Icons/NpcBehavior-16"), Icon16x16));
	StyleSet->Set("ClassThumbnail.NpcBehavior", new PLUGIN_BRUSH(TEXT("Icons/NpcBehavior-40"), Icon40x40));
	StyleSet->Set("ClassIcon.StateMachineBlueprint", new PLUGIN_BRUSH(TEXT("Icons/StateMachine-16"), Icon16x16));
	StyleSet->Set("ClassThumbnail.StateMachineBlueprint", new PLUGIN_BRUSH(TEXT("Icons/StateMachine-40"), Icon40x40));

	// Toolbar
	StyleSet->Set("FrameworkGraphToolbar.Bp", new IMAGE_BRUSH("Icons/Graph-ToolbarBp-40", Icon40x40));
	StyleSet->Set("FrameworkGraphToolbar.BpSmall", new IMAGE_BRUSH("Icons/Graph-ToolbarBp-20", Icon20x20));
	StyleSet->Set("FrameworkNpcToolbar.Npc", new IMAGE_BRUSH("Icons/NpcBehavior-ToolbarNpc-40", Icon40x40));
	StyleSet->Set("FrameworkNpcToolbar.NpcSmall", new IMAGE_BRUSH("Icons/NpcBehavior-ToolbarNpc-20", Icon20x20));
	StyleSet->Set("FrameworkStateMachineToolbar.StateMachine", new IMAGE_BRUSH("Icons/StateMachine-ToolbarStateMachine-40", Icon40x40));
	StyleSet->Set("FrameworkStateMachineToolbar.StateMachineSmall", new IMAGE_BRUSH("Icons/StateMachine-ToolbarStateMachine-20", Icon20x20));

	// Graph
	StyleSet->Set("FrameworkGraph.NodeBody", new BOX_BRUSH(TEXT("Graph/NodeBody"), FMargin(4.f / 64.f, 4.f / 64.f, 4.f / 64.f, 4.f / 64.f)));
	StyleSet->Set("FrameworkGraph.NodeBodySelected", new BOX_BRUSH(TEXT("Graph/NodeBodySelected"), FMargin(18.0f / 64.0f)));
	StyleSet->Set("FrameworkGraph.NodePin", new IMAGE_BRUSH(TEXT("Graph/NodePin"), Generic10x10));
	StyleSet->Set("FrameworkGraph.NodePinHoverCue", new IMAGE_BRUSH(TEXT("Graph/NodePinHoverCue"), Generic10x10));
	StyleSet->Set("FrameworkGraph.RegularNodeShadow", new BOX_BRUSH(TEXT("Graph/RegularNodeShadow"), FMargin(18.0f / 64.0f)));
	StyleSet->Set("FrameworkGraph.RegularNodeTitleNormal", new BOX_BRUSH(TEXT("Graph/RegularNodeTitleNormal"), FMargin(12.0f / 64.0f)));
	StyleSet->Set("FrameworkGraph.RegularNodeTitleHighlight", new BOX_BRUSH(TEXT("Graph/RegularNodeTitleHighlight"), FMargin(16.0f / 64.0f, 1.0f, 16.0f / 64.0f, 0.0f)));

	// State Machine 
	StyleSet->Set("FrameworkGraph.StateMachine.NodeBody", new BOX_BRUSH(TEXT("Graph/StateMachine/NodeBody"), FMargin(16.f / 64.f, 25.f / 64.f, 16.f / 64.f, 16.f / 64.f)));
	StyleSet->Set("FrameworkGraph.StateMachine.NodeBodySelected", new BOX_BRUSH(TEXT("Graph/StateMachine/NodeBodySelected"), FMargin(18.0f / 64.0f)));
	StyleSet->Set("FrameworkGraph.StateMachine.NodeBodyColorSpill", new BOX_BRUSH(TEXT("Graph/StateMachine/NodeBodyColorSpill"), FMargin(4.0f / 64.0f, 4.0f / 32.0f)));
	StyleSet->Set("FrameworkGraph.StateMachine.NodePinHoverCue", new BOX_BRUSH(TEXT("Graph/StateMachine/NodePinHoverCue"), FMargin(12.0f / 64.0f, 12.0f / 64.0f, 12.0f / 64.0f, 12.0f / 64.0f)));
	StyleSet->Set("FrameworkGraph.StateMachine.Icon", new IMAGE_BRUSH("Graph/StateMachine/NodeIcon", Icon16x16));
	StyleSet->Set("FrameworkGraph.StateMachine.TransitionNodeBody", new BOX_BRUSH("Graph/StateMachine/TransNodeBody", FMargin(16.f / 64.f, 12.f / 28.f)));
	StyleSet->Set("FrameworkGraph.StateMachine.TransitionNodeColorSpill", new BOX_BRUSH("Graph/StateMachine/TransNodeColorSpill", (16.f / 64.f, 16.f / 28.f, 16.f / 64.f, 4.f / 28.f)));
	StyleSet->Set("FrameworkGraph.StateMachine.TransitionNodeIcon", new IMAGE_BRUSH("Graph/StateMachine/TransNodeIcon", FVector2D(25, 25)));

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}

const FSlateBrush* FFrameworkStyle::GetBrush(FName PropertyName, const ANSICHAR* Specifier /*= NULL*/)
{
	return FFrameworkStyle::Get()->GetBrush(PropertyName, Specifier);
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef IMAGE_PLUGIN_BRUSH
#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef TTF_FONT
#undef TTF_CORE_FONT
#undef PLUGIN_BRUSH

void FFrameworkStyle::Shutdown()
{
	if (StyleSet.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
		ensure(StyleSet.IsUnique());
		StyleSet.Reset();
	}
}

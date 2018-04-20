// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "OptionsCLI.h"
#include "OptionsView.h"
#include "WindowsAppThreadAssertionMacros.h"

namespace ExampleApp
{
	void OptionsViewCLIMethods::CloseButtonSelected(System::IntPtr nativeObjectPtr)
	{
		Options::View::OptionsView* pView = reinterpret_cast<Options::View::OptionsView*>(nativeObjectPtr.ToPointer());
		pView->HandleCloseSelected();
	}

	void OptionsViewCLIMethods::StreamOverWifiToggled(System::IntPtr nativeObjectPtr)
    {
        Options::View::OptionsView* pView = reinterpret_cast<Options::View::OptionsView*>(nativeObjectPtr.ToPointer());
        pView->HandleStreamOverWifiOnlySelectionStateChanged();
    }

    void OptionsViewCLIMethods::CachingEnabledToggled(System::IntPtr nativeObjectPtr)
    {
        Options::View::OptionsView* pView = reinterpret_cast<Options::View::OptionsView*>(nativeObjectPtr.ToPointer());
        pView->HandleCacheEnabledSelectionStateChanged();
    }

    void OptionsViewCLIMethods::ClearCacheSelected(System::IntPtr nativeObjectPtr)
    {
        Options::View::OptionsView* pView = reinterpret_cast<Options::View::OptionsView*>(nativeObjectPtr.ToPointer());
        pView->HandleClearCacheSelected();
    }

	void OptionsViewCLIMethods::ClearCacheTriggered(System::IntPtr nativeObjectPtr)
	{
		Options::View::OptionsView* pView = reinterpret_cast<Options::View::OptionsView*>(nativeObjectPtr.ToPointer());
		pView->HandleClearCacheTriggered();
	}

    void OptionsViewCLIMethods::ReplayTutorialsSelected(System::IntPtr nativeObjectPtr)
    {
        Options::View::OptionsView* pView = reinterpret_cast<Options::View::OptionsView*>(nativeObjectPtr.ToPointer());
        pView->HandleReplayTutorialsSelected();
    }
}

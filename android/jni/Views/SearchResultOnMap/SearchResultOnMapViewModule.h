// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "SearchResultOnMap.h"
#include "ISearchResultOnMapViewModule.h"
#include "IScreenControlViewModel.h"
#include "ISearchResultPoiViewModel.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        class SearchResultOnMapViewModule: public ISearchResultOnMapViewModule, private Eegeo::NonCopyable
        {
        private:
            SearchResultOnMapViewController* m_pSearchResultOnMapViewController;
            
        public:
            SearchResultOnMapViewModule(
				AndroidNativeState& nativeState,
				ISearchResultOnMapInFocusViewModel& searchResultOnMapInFocusViewModel,
				ScreenControlViewModel::IScreenControlViewModel& searchResultOnMapInFocusScreenControlViewModel,
				SearchResultPoi::ISearchResultPoiViewModel& searchResultPoiViewModel,
    			float pinDiameter
			);
            
            ~SearchResultOnMapViewModule();
            
            SearchResultOnMapViewController& GetSearchResultOnMapViewController() const;
        };
    }
}

// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SwallowPoiDbServiceProvider.h"

#include "SwallowPoiDbCombinedService.H"

namespace ExampleApp
{
    namespace SwallowPoiDb
    {
        SwallowPoiDbServiceProvider::SwallowPoiDbServiceProvider()
        : m_pSwallowPoiDbService(NULL)
        , Eegeo::Helpers::TCallback1<SwallowPoiDbServiceProvider, SwallowPoiDbCombinedService*>(this, &SwallowPoiDbServiceProvider::SwallowPoiDbWebLoaderCompleted)
        {
            
        }
        
        SwallowPoiDbServiceProvider::~SwallowPoiDbServiceProvider()
        {
            Eegeo_DELETE m_pSwallowPoiDbService;
        }
        
        
        void SwallowPoiDbServiceProvider::SwallowPoiDbWebLoaderCompleted(SwallowPoiDbCombinedService*& pSwallowPoiDbService)
        {
            Eegeo_DELETE m_pSwallowPoiDbService;
            m_pSwallowPoiDbService = pSwallowPoiDbService;
        }
        
        bool SwallowPoiDbServiceProvider::TryGetSwallowPoiDbService(SwallowPoiDbCombinedService*& out_pService) const
        {
            out_pService = m_pSwallowPoiDbService;
            return (m_pSwallowPoiDbService != NULL);
        }
    }
}

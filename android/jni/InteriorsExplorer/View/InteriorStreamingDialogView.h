// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IInteriorStreamingDialogView.h"
#include "InteriorsExplorerViewIncludes.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            class InteriorStreamingDialogView : public IInteriorStreamingDialogView
            {
            public:

                InteriorStreamingDialogView();

                void Show();
                void Hide();
            };

        }

    }
}
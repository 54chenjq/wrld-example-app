// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IInitialExperienceIntroViewModule.h"
#include "InitialExperience.h"
#include "InitialExperienceIntroViewIncludes.h"
#include "BidirectionalBus.h"
#include "CameraTransitions.h"
#include "Compass.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace View
        {
            class InitialExperienceIntroViewModule : public IInitialExperienceIntroViewModule
            {
            public:
                
                InitialExperienceIntroViewModule(ExampleAppMessaging::TMessageBus& messageBus, CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController, const Compass::SdkModel::ICompassModule& compassModule);
                ~InitialExperienceIntroViewModule();
                
                InitialExperienceIntroController& GetIntroViewController() const
                {
                    return *m_pController;
                }
                
                InitialExperienceIntroView& GetIntroView() const
                {
                    return *m_pView;
                }
                
                InitialExperienceIntroBackgroundView& GetIntroBackgroundView() const
                {
                    return *m_pBackgroundView;
                }
                
            private:
                
                InitialExperienceIntroController* m_pController;
                InitialExperienceIntroView* m_pView;
                InitialExperienceIntroBackgroundView* m_pBackgroundView;
            };
        }
    }
}

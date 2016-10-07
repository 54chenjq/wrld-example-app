// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InitialExperienceIntroViewModule.h"
#include "InitialExperienceIntroView.h"
#include "InitialExperienceIntroController.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
	namespace InitialExperience
	{
		namespace View
		{
			void InitialExperienceIntroViewModule::Register(const TContainerBuilder& builder)
			{
				builder->registerType<InitialExperienceIntroView>().as<IInitialExperienceIntroView>().singleInstance();
				builder->registerType<InitialExperienceIntroController>().singleInstance();
			}

			void InitialExperienceIntroViewModule::RegisterUiLeaves()
			{
				ASSERT_UI_THREAD
				RegisterLeaf<IInitialExperienceIntroView>();
				RegisterLeaf<InitialExperienceIntroController>();
			}
		}
	}
}

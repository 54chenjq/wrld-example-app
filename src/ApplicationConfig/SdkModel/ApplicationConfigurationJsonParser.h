// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ApplicationConfig.h"
#include "IApplicationConfigurationBuilder.h"
#include "IApplicationConfigurationParser.h"
#include "Types.h"
#include "document.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            class ApplicationConfigurationJsonParser : public IApplicationConfigurationParser, private Eegeo::NonCopyable
            {
            public:
                ApplicationConfigurationJsonParser(const ApplicationConfiguration& defaultConfig,
                                                   IApplicationConfigurationBuilder& builder);

                ApplicationConfiguration ParseConfiguration(const std::string& serialized);
                bool IsValidConfig(const std::string& serialized);
                bool HasKey(const std::string& serialized, const std::string& key);
            private:
                const ApplicationConfiguration m_defaultConfig;
                IApplicationConfigurationBuilder& m_builder;
                
                void ParseIndoorTrackingInfo(std::map<std::string, SdkModel::ApplicationInteriorTrackingInfo>& interiorTrackingInfoList,
                                             const rapidjson::Value& indoorTrackedBuildingsArray);

                void ParseFixedIndoorLocation(const rapidjson::Value& fixedIndoorLocation);

                Eegeo::Space::LatLongAltitude ParseLatLongAltitude(const rapidjson::Value& location);

                std::vector<Eegeo::Space::LatLongAltitude> ParseLatLongAltitudeArray(rapidjson::Value& pointsAst);
            };
        }
    }
}

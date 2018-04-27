// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "LatLongAltitude.h"
#include "ApplicationConfiguration.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            class IApplicationConfigurationBuilder
            {
            public:
                virtual ~IApplicationConfigurationBuilder() { } 
                
                virtual IApplicationConfigurationBuilder& SetApplicationName(const std::string& name) = 0;
                
                virtual IApplicationConfigurationBuilder& SetEegeoApiKey(const std::string& eegeoApiKey) = 0;
                
                virtual IApplicationConfigurationBuilder& SetStartInterestPointLocation(const Eegeo::Space::LatLongAltitude& location) = 0;
                
                virtual IApplicationConfigurationBuilder& SetStartDistanceFromInterestPoint(float distanceMetres) = 0;
                
                virtual IApplicationConfigurationBuilder& SetStartOrientationAboutInterestPoint(float degrees) = 0;
                
                virtual IApplicationConfigurationBuilder& SetIndoorId(const std::string& indoorId) = 0;
                
                virtual IApplicationConfigurationBuilder& SetFloorIndex(const int floorIndex) = 0;
                
                virtual IApplicationConfigurationBuilder& SetTryStartAtGpsLocation(bool tryStartAtGpsLocation) = 0;
                
                virtual IApplicationConfigurationBuilder& SetTryStartAtGpsTimeout(const double tryStartAtGpsTimeout) = 0;
                
                virtual IApplicationConfigurationBuilder& SetPerformStartupSearch(bool performStartupSearch) = 0;
                
                virtual IApplicationConfigurationBuilder& SetStartupSearchTag(std::string startupSearchTag) = 0;
                
                virtual IApplicationConfigurationBuilder& SetGoogleAnalyticsReferrerToken(const std::string& googleAnalyticsReferrerToken) = 0;
                
                virtual IApplicationConfigurationBuilder& SetYelpConsumerKey(const std::string& yelpConsumerKey) = 0;
                
                virtual IApplicationConfigurationBuilder& SetYelpConsumerSecret(const std::string& yelpConsumerSecret) = 0;
                
                virtual IApplicationConfigurationBuilder& SetYelpOAuthToken(const std::string& yelpOAuthToken) = 0;
                
                virtual IApplicationConfigurationBuilder& SetYelpOAuthTokenSecret(const std::string& yelpOAuthTokenSecret) = 0;
                
                virtual IApplicationConfigurationBuilder& SetGeoNamesUserName(const std::string& geoNamesUserName) = 0;
                
                virtual IApplicationConfigurationBuilder& SetCoverageTreeManifestURL(const std::string& coverageTreeManifestUrl) = 0;
                
                virtual IApplicationConfigurationBuilder& SetThemeManifestURL(const std::string& themesManifestUrl) = 0;

                virtual IApplicationConfigurationBuilder& SetSearchServiceUrl(const std::string& searchServiceUrl) = 0;
                
                virtual IApplicationConfigurationBuilder& SetMyPinsWebServiceUrl(const std::string& myPinsWebServiceUrl) = 0;
                
                virtual IApplicationConfigurationBuilder& SetMyPinsWebServiceAuthToken(const std::string& myPinsWebServiceAuthToken) = 0;
                
                virtual IApplicationConfigurationBuilder& SetProductVersion(const std::string& productVersion) = 0;
                
                virtual IApplicationConfigurationBuilder& SetBuildNumber(const std::string& buildNumber) = 0;
                
                virtual IApplicationConfigurationBuilder& SetCombinedVersionString(const std::string& combinedVersionString) = 0;
                
                virtual IApplicationConfigurationBuilder& SetWebProxyEnabled(bool webProxyEnabled) = 0;
                
                virtual IApplicationConfigurationBuilder& SetWebProxyIpAddress(const std::string& webProxyIpAddress) = 0;
                
                virtual IApplicationConfigurationBuilder& SetWebProxyPort(int webProxyPort) = 0;

                virtual IApplicationConfigurationBuilder& SetWebProxyIgnorePattern(const std::string& webProxyIgnorePattern) = 0;
                
                virtual IApplicationConfigurationBuilder& SetSSLEnabled(bool setSSLEnabled) = 0;
                
                virtual IApplicationConfigurationBuilder& SetSSLIgnorePattern(const std::string& sslIgnorePattern) = 0;

                virtual IApplicationConfigurationBuilder& SetShouldStartFullscreen(bool startFullscreen) = 0;

                virtual IApplicationConfigurationBuilder& SetIsKioskTouchInputEnabled(bool kioskTouchInputEnabled) = 0;

				virtual IApplicationConfigurationBuilder& SetIsInKioskMode(bool isInKioskMode) = 0;

                virtual IApplicationConfigurationBuilder& SetEmbeddedThemeTexturePath(const std::string& embeddedThemeTexturePath) = 0;

                virtual IApplicationConfigurationBuilder& SetTwitterAuthCode(const std::string& twitterAuthCode) = 0;

                virtual IApplicationConfigurationBuilder& SetUseLabels(bool useLabels) = 0;

                virtual IApplicationConfigurationBuilder& SetInteriorTrackingInfo(const std::map<std::string, SdkModel::ApplicationInteriorTrackingInfo>& interiorTrackingInfo) = 0;

                virtual std::string Decrypt(const std::string& value) const = 0;

                virtual bool ValidateHMAC(const std::string& message, const std::string& hmac) const = 0;
                
                virtual ApplicationConfiguration Build() = 0;
                
                virtual IApplicationConfigurationBuilder& SetBuildingInfoArray(const std::vector<ExampleApp::ApplicationConfig::ApplicationBuildingInfo*>&infoBuildingList) = 0;
                virtual IApplicationConfigurationBuilder& SetRestrictedBuildingInfoArray(const std::vector<ExampleApp::ApplicationConfig::RestrictedBuildingInfo*>&restrictedBuildingInfo) = 0;

                virtual IApplicationConfigurationBuilder& SetBuildingsSearchViewLocationAvailable(bool available) = 0;
                virtual IApplicationConfigurationBuilder& SetBuildingsSearchViewLocation(const Eegeo::Space::LatLongAltitude latLongAltitude, const float distanceToInterest, const float orientationDegrees) = 0;

                virtual IApplicationConfigurationBuilder& SetFixedIndoorLocation(const Eegeo::Space::LatLong latlong, const std::string& interiorId, const int floorIndex, const double headingDegrees) = 0;

                virtual IApplicationConfigurationBuilder& SetAttractModeTargetSplinePoints(std::vector<Eegeo::Space::LatLongAltitude> points) = 0;
                virtual IApplicationConfigurationBuilder& SetAttractModePositionSplinePoints(std::vector<Eegeo::Space::LatLongAltitude> points) = 0;
                virtual IApplicationConfigurationBuilder& SetAttractModeTimeoutMs(const long long timeoutMs) = 0;
                virtual IApplicationConfigurationBuilder& SetAttractModePlaybackSpeed(const double playbackSpeed) = 0;

                virtual IApplicationConfigurationBuilder& SetAdminPassword(const std::string& adminPassword) = 0;

                virtual IApplicationConfigurationBuilder& SetCustomKeyboardLayout(const std::vector<std::vector<std::string>>& customKeyboardLayout) = 0;

                virtual IApplicationConfigurationBuilder& SetCompassCameraOffset(const float compassCameraOffset) = 0;
                virtual IApplicationConfigurationBuilder& SetCompassCameraOffsetTopDown(const float compassCameraOffsetTopDown) = 0;
                virtual IApplicationConfigurationBuilder& SetCompassCameraDampingEnabled(const bool compassCameraDampingEnabled) = 0;

                virtual IApplicationConfigurationBuilder& SetOutdoorSearchMenuItemJson(const std::string& outdoorSearchMenuItemJson) = 0;
            };
        }
    }
}

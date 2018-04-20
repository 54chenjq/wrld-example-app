// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include <string>
#include <vector>

#include "Helpers.h"
#include "TagSearchModel.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace View
        {
            std::vector<TagSearch::View::TagSearchModel> CreateTagSearchModelsFromFile(const std::string& json, const std::string& jsonAttributeName);
        }
    }
}

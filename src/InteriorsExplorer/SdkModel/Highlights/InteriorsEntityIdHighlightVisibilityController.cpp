// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsEntityIdHighlightVisibilityController.h"
#include "ISearchService.h"
#include "ISearchQueryPerformer.h"
#include "ISearchResultRepository.h"
#include "InteriorController.h"
#include "InteriorsModel.h"
#include "InteriorsFloorModel.h"
#include "IInteriorsLabelController.h"
#include "SwallowSearchConstants.h"
#include "SwallowSearchParser.h"
#include "VectorMath.h"
#include "InteriorHighlightRenderable.h"
#include "InteriorsLabelParser.h"
#include "InteriorsFloorCells.h"
#include "InteriorsFloorCell.h"
#include "PlaceNameModel.h"
#include "SwallowDepartmentResultModel.h"
#include "InstancedInteriorFloorRenderable.h"
#include "InteriorsCellResource.h"
#include "InteriorsCellResourceObserver.h"
#include "SearchResultSectionItemSelectedMessage.h"
#include "InteriorsEntityIdHighlightController.h"

#include <algorithm>

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace Highlights
            {
                namespace
                {
                    std::vector<std::string> GetDeskIdsFromSearchResultModel(const Search::SdkModel::SearchResultModel& selectedSearchResult)
                    {
                        if (selectedSearchResult.GetCategory() == Search::Swallow::SearchConstants::DEPARTMENT_CATEGORY_NAME)
                        {
                            const Search::Swallow::SdkModel::SwallowDepartmentResultModel& department = Search::Swallow::SdkModel::SearchParser::TransformToSwallowDepartmentResult(selectedSearchResult);

                            return department.GetAllDesks();
                        }
                        else if (selectedSearchResult.GetCategory() == Search::Swallow::SearchConstants::PERSON_CATEGORY_NAME)
                        {
                            const Search::Swallow::SdkModel::SwallowPersonResultModel& person = Search::Swallow::SdkModel::SearchParser::TransformToSwallowPersonResult(selectedSearchResult);

                            return std::vector<std::string>(1, person.GetDeskCode());
                        }

                        return std::vector<std::string>();
                    }

                }

                InteriorsEntityIdHighlightVisibilityController::InteriorsEntityIdHighlightVisibilityController(
                    Eegeo::Resources::Interiors::InteriorsEntityIdHighlightController& interiorsEntityIdHighlightController,
                    Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                    Search::SdkModel::ISearchResultRepository& searchResultRepository,
                    ExampleAppMessaging::TMessageBus& messageBus,
                    Eegeo::Resources::Interiors::InteriorsCellResourceObserver& cellResourceObserver)
                : m_interiorsEntityIdHighlightController(interiorsEntityIdHighlightController)
                , m_searchQueryPerformer(searchQueryPerformer)
                , m_searchResultsHandler(this, &InteriorsEntityIdHighlightVisibilityController::OnSearchResultsLoaded)
                , m_searchResultsClearedHandler(this, &InteriorsEntityIdHighlightVisibilityController::OnSearchResultsCleared)
                , m_handleSearchResultSectionItemSelectedMessageBinding(this, &InteriorsEntityIdHighlightVisibilityController::OnSearchItemSelected)
                , m_messageBus(messageBus)
                , m_cellResourceObserver(cellResourceObserver)
                , m_cellResourceDeletedCallback(this, &InteriorsEntityIdHighlightVisibilityController::HandleFloorCellDeleted)
                {
                    m_searchQueryPerformer.InsertOnSearchResultsClearedCallback(m_searchResultsClearedHandler);
                    m_messageBus.SubscribeNative(m_handleSearchResultSectionItemSelectedMessageBinding);
                    m_messageBus.SubscribeUi(m_searchResultsHandler);
                    
                    m_cellResourceObserver.RegisterResourceDeletedCallback(m_cellResourceDeletedCallback);
                }
                
                InteriorsEntityIdHighlightVisibilityController::~InteriorsEntityIdHighlightVisibilityController()
                {
                    m_searchQueryPerformer.RemoveOnSearchResultsClearedCallback(m_searchResultsClearedHandler);
                    m_messageBus.UnsubscribeNative(m_handleSearchResultSectionItemSelectedMessageBinding);
                    m_messageBus.UnsubscribeUi(m_searchResultsHandler);
                    
                    m_cellResourceObserver.UnregisterResourceDeletedCallback(m_cellResourceDeletedCallback);
                }
                
                void InteriorsEntityIdHighlightVisibilityController::OnSearchResultsCleared()
                {
                    m_searchResults.clear();
                    ClearHighlights();
                }

                void InteriorsEntityIdHighlightVisibilityController::ClearHighlights()
                {
                    for (InstancedRenderableVector::const_iterator iter = m_lastHighlightedRenderables.begin(); iter != m_lastHighlightedRenderables.end(); ++iter)
                    {
                        Eegeo::Rendering::Renderables::InstancedInteriorFloorRenderable& currentRenderable = **iter;
                        Eegeo::Rendering::Renderables::InstancedRenderState currentState = currentRenderable.GetInstancedRenderState();

                        currentState.IsHighlightingActive = false;

                        currentRenderable.SetInstancedRenderState(currentState);
                    }

                    m_lastHighlightedRenderables.clear();
                }

                void InteriorsEntityIdHighlightVisibilityController::OnSearchItemSelected(const SearchResultSection::SearchResultSectionItemSelectedMessage& message)
                {
                    ClearHighlights();

                    Eegeo_ASSERT(!m_searchResults.empty());
                    const Search::SdkModel::SearchResultModel& selectedSearchResult = m_searchResults.at(message.ItemIndex());

                    const std::vector<std::string>& deskIds = GetDeskIdsFromSearchResultModel(selectedSearchResult);

                    m_interiorsEntityIdHighlightController.HighlightEntityIds(deskIds, m_lastHighlightedRenderables);
                }

                
                void InteriorsEntityIdHighlightVisibilityController::HandleFloorCellDeleted(const Eegeo::Resources::Interiors::InteriorsCellResource& interiorCellResource)
                {
                    std::vector<Eegeo::Rendering::Renderables::InstancedInteriorFloorRenderable*> instancedRenderablesToRemove;

                    const std::vector<Eegeo::Resources::Interiors::InteriorsFloorCell*>& floorCells = interiorCellResource.GetFloorCells();
                    
                    for (std::vector<Eegeo::Resources::Interiors::InteriorsFloorCell*>::const_iterator floorCellIter = floorCells.begin();
                         floorCellIter != floorCells.end();
                         ++floorCellIter)
                    {
                        const std::vector<Eegeo::Rendering::Renderables::InstancedInteriorFloorRenderable*>& instancedRenderablesForDeletedFloor = (*floorCellIter)->GetInstancedRenderables();
                        instancedRenderablesToRemove.insert(instancedRenderablesToRemove.end(), instancedRenderablesForDeletedFloor.begin(), instancedRenderablesForDeletedFloor.end());
                    }

                    std::sort(m_lastHighlightedRenderables.begin(), m_lastHighlightedRenderables.end());
                    std::sort(instancedRenderablesToRemove.begin(), instancedRenderablesToRemove.end());

                    m_lastHighlightedRenderables.erase(
                        std::set_difference(m_lastHighlightedRenderables.begin(), m_lastHighlightedRenderables.end(), instancedRenderablesToRemove.begin(), instancedRenderablesToRemove.end(), m_lastHighlightedRenderables.begin()), 
                        m_lastHighlightedRenderables.end());
                }

                void InteriorsEntityIdHighlightVisibilityController::OnSearchResultsLoaded(const Search::SearchQueryResponseReceivedMessage& message)
                {
                    m_searchResults = message.GetResults();
                }
            }
        }
    }
}
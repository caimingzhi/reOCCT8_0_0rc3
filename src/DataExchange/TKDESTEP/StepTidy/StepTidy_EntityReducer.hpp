#pragma once

#include <Interface_Graph.hpp>
#include <NCollection_Allocator.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_HashUtils.hpp>
#include <XSControl_WorkSession.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Map.hpp>

#include <functional>

template <typename ProcessedType, typename ProcessedTypeHasher>
class StepTidy_EntityReducer
{
protected:
  using DuplicateMap = NCollection_DataMap<occ::handle<ProcessedType>,
                                           std::vector<occ::handle<ProcessedType>>,
                                           ProcessedTypeHasher>;

  using ReplacerFunction = std::function<bool(const occ::handle<ProcessedType>&,
                                              const occ::handle<ProcessedType>&,
                                              const occ::handle<Standard_Transient>)>;

  using ReplacerMap = NCollection_DataMap<occ::handle<Standard_Type>, ReplacerFunction>;

protected:
  StepTidy_EntityReducer(const occ::handle<XSControl_WorkSession>& theWS);

public:
  Standard_EXPORT bool ProcessEntity(const occ::handle<Standard_Transient>& theEntity);

  Standard_EXPORT void Perform(
    NCollection_Map<occ::handle<Standard_Transient>>& theReplacedEntities);

protected:
  void registerReplacer(const occ::handle<Standard_Type>& theType,
                        const ReplacerFunction&           theReplacer);

public:
  bool hasAllReplacers(
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& theSharings) const;

  bool replaceInSharings(
    const occ::handle<ProcessedType>&                                          theOldEntity,
    const occ::handle<ProcessedType>&                                          theNewEntity,
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& theSharings) const;

private:
  occ::handle<XSControl_WorkSession> myWS;
  ReplacerMap                        myReplacerMap;
  DuplicateMap                       myDuplicateMap;
};

template <typename ProcessedType, typename ProcessedTypeHasher>
StepTidy_EntityReducer<ProcessedType, ProcessedTypeHasher>::StepTidy_EntityReducer(
  const occ::handle<XSControl_WorkSession>& theWS)
    : myWS(theWS),
      myReplacerMap(),
      myDuplicateMap()
{
}

template <typename ProcessedType, typename ProcessedTypeHasher>
bool StepTidy_EntityReducer<ProcessedType, ProcessedTypeHasher>::ProcessEntity(
  const occ::handle<Standard_Transient>& theEntity)
{
  const occ::handle<ProcessedType> anEntity = occ::down_cast<ProcessedType>(theEntity);
  if (anEntity.IsNull())
  {
    return false;
  }
  const Interface_Graph&                                                    aGraph = myWS->Graph();
  const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> aSharings =
    aGraph.GetSharings(anEntity);
  if (hasAllReplacers(aSharings))
  {
    std::vector<occ::handle<ProcessedType>>* anIter = myDuplicateMap.ChangeSeek(anEntity);
    if (anIter == nullptr)
    {

      myDuplicateMap.Bind(anEntity, std::vector<occ::handle<ProcessedType>>{});
    }
    else
    {

      anIter->push_back(anEntity);
    }
  }

  return true;
}

template <typename ProcessedType, typename ProcessedTypeHasher>
void StepTidy_EntityReducer<ProcessedType, ProcessedTypeHasher>::Perform(
  NCollection_Map<occ::handle<Standard_Transient>>& theReplacedEntities)
{
  for (typename DuplicateMap::Iterator anIter(myDuplicateMap); anIter.More(); anIter.Next())
  {
    const occ::handle<ProcessedType>&              anEntity    = anIter.Key();
    const std::vector<occ::handle<ProcessedType>>& aDuplicates = anIter.Value();
    if (aDuplicates.empty())
    {
      continue;
    }

    const Interface_Graph& aGraph = myWS->Graph();
    for (const auto& aDuplicate : aDuplicates)
    {
      occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> aSharings =
        aGraph.GetSharings(aDuplicate);
      if (aSharings.IsNull())
      {
        continue;
      }

      if (replaceInSharings(aDuplicate, anEntity, aSharings))
      {
        theReplacedEntities.Add(aDuplicate);
      }
    }
  }
}

template <typename ProcessedType, typename ProcessedTypeHasher>
void StepTidy_EntityReducer<ProcessedType, ProcessedTypeHasher>::registerReplacer(
  const occ::handle<Standard_Type>& theType,
  const ReplacerFunction&           theReplacer)
{
  myReplacerMap.Bind(theType, theReplacer);
}

template <typename ProcessedType, typename ProcessedTypeHasher>
bool StepTidy_EntityReducer<ProcessedType, ProcessedTypeHasher>::hasAllReplacers(
  const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& theSharings) const
{
  if (theSharings.IsNull())
  {
    return false;
  }
  return std::all_of(theSharings->cbegin(),
                     theSharings->cend(),
                     [this](const occ::handle<Standard_Transient>& theSharing)
                     { return myReplacerMap.IsBound(theSharing->DynamicType()); });
}

template <typename ProcessedType, typename ProcessedTypeHasher>
bool StepTidy_EntityReducer<ProcessedType, ProcessedTypeHasher>::replaceInSharings(
  const occ::handle<ProcessedType>&                                          theOldEntity,
  const occ::handle<ProcessedType>&                                          theNewEntity,
  const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& theSharings) const
{
  bool isAllReplaced = true;
  for (const auto& aSharing : *theSharings)
  {
    if (aSharing.IsNull())
    {
      continue;
    }

    const ReplacerFunction& aReplacer = myReplacerMap.Find(aSharing->DynamicType());
    if (!aReplacer(theOldEntity, theNewEntity, aSharing))
    {
      isAllReplaced = false;
    }
  }
  return isAllReplaced;
}

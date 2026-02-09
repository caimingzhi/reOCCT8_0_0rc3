#pragma once

namespace NCollection_MapAlgo
{

  template <class MapType>
  void Union(MapType& theMap, const MapType& theLeftMap, const MapType& theRightMap)
  {
    if (&theLeftMap == &theRightMap)
    {
      theMap.Assign(theLeftMap);
      return;
    }

    if (&theMap != &theLeftMap && &theMap != &theRightMap)
    {
      theMap.Clear();
    }

    if (&theMap != &theLeftMap)
    {
      for (typename MapType::Iterator anIter(theLeftMap); anIter.More(); anIter.Next())
      {
        theMap.Add(anIter.Key());
      }
    }
    if (&theMap != &theRightMap)
    {
      for (typename MapType::Iterator anIter(theRightMap); anIter.More(); anIter.Next())
      {
        theMap.Add(anIter.Key());
      }
    }
  }

  template <class MapType>
  bool Unite(MapType& theMap, const MapType& theOtherMap)
  {
    if (&theMap == &theOtherMap)
    {
      return false;
    }

    const int anOldExtent = theMap.Extent();
    Union<MapType>(theMap, theMap, theOtherMap);
    return anOldExtent != theMap.Extent();
  }

  template <class MapType>
  bool HasIntersection(const MapType& theMap, const MapType& theOtherMap)
  {
    const MapType* aMap1 = &theMap;
    const MapType* aMap2 = &theOtherMap;
    if (theOtherMap.Size() < theMap.Size())
    {
      aMap1 = &theOtherMap;
      aMap2 = &theMap;
    }

    for (typename MapType::Iterator aIt(*aMap1); aIt.More(); aIt.Next())
    {
      if (aMap2->Contains(aIt.Value()))
      {
        return true;
      }
    }

    return false;
  }

  template <class MapType>
  void Intersection(MapType& theMap, const MapType& theLeftMap, const MapType& theRightMap)
  {
    if (&theLeftMap == &theRightMap)
    {
      theMap.Assign(theLeftMap);
      return;
    }

    if (&theMap == &theLeftMap)
    {
      MapType aCopy(1, theMap.Allocator());
      theMap.Exchange(aCopy);
      Intersection<MapType>(theMap, aCopy, theRightMap);
      return;
    }
    else if (&theMap == &theRightMap)
    {
      MapType aCopy(1, theMap.Allocator());
      theMap.Exchange(aCopy);
      Intersection<MapType>(theMap, theLeftMap, aCopy);
      return;
    }

    theMap.Clear();
    if (theLeftMap.Extent() < theRightMap.Extent())
    {
      for (typename MapType::Iterator anIter(theLeftMap); anIter.More(); anIter.Next())
      {
        if (theRightMap.Contains(anIter.Key()))
        {
          theMap.Add(anIter.Key());
        }
      }
    }
    else
    {
      for (typename MapType::Iterator anIter(theRightMap); anIter.More(); anIter.Next())
      {
        if (theLeftMap.Contains(anIter.Key()))
        {
          theMap.Add(anIter.Key());
        }
      }
    }
  }

  template <class MapType>
  bool Intersect(MapType& theMap, const MapType& theOtherMap)
  {
    if (&theMap == &theOtherMap || theMap.IsEmpty())
    {
      return false;
    }

    const int anOldExtent = theMap.Extent();
    Intersection<MapType>(theMap, theMap, theOtherMap);
    return anOldExtent != theMap.Extent();
  }

  template <class MapType>
  bool Subtract(MapType& theMap, const MapType& theOtherMap)
  {
    if (&theMap == &theOtherMap)
    {
      if (theMap.IsEmpty())
      {
        return false;
      }

      theMap.Clear();
      return true;
    }

    const int anOldExtent = theMap.Extent();
    for (typename MapType::Iterator anIter(theOtherMap); anIter.More(); anIter.Next())
    {
      theMap.Remove(anIter.Key());
    }
    return anOldExtent != theMap.Extent();
  }

  template <class MapType>
  void Subtraction(MapType& theMap, const MapType& theLeftMap, const MapType& theRightMap)
  {
    if (&theMap == &theLeftMap)
    {
      Subtract<MapType>(theMap, theRightMap);
      return;
    }
    else if (&theMap == &theRightMap)
    {
      MapType aCopy(1, theMap.Allocator());
      theMap.Exchange(aCopy);
      Subtraction(theMap, theLeftMap, aCopy);
      return;
    }

    theMap.Assign(theLeftMap);
    Subtract<MapType>(theMap, theRightMap);
  }

  template <class MapType>
  void Difference(MapType& theMap, const MapType& theLeftMap, const MapType& theRightMap)
  {
    if (&theLeftMap == &theRightMap)
    {
      theMap.Clear();
      return;
    }
    else if (&theMap == &theLeftMap)
    {
      MapType aCopy(1, theMap.Allocator());
      theMap.Exchange(aCopy);
      Difference<MapType>(theMap, aCopy, theRightMap);
      return;
    }
    else if (&theMap == &theRightMap)
    {
      MapType aCopy(1, theMap.Allocator());
      theMap.Exchange(aCopy);
      Difference<MapType>(theMap, theLeftMap, aCopy);
      return;
    }

    theMap.Clear();
    for (typename MapType::Iterator anIter(theLeftMap); anIter.More(); anIter.Next())
    {
      if (!theRightMap.Contains(anIter.Key()))
      {
        theMap.Add(anIter.Key());
      }
    }
    for (typename MapType::Iterator anIter(theRightMap); anIter.More(); anIter.Next())
    {
      if (!theLeftMap.Contains(anIter.Key()))
      {
        theMap.Add(anIter.Key());
      }
    }
  }

  template <class MapType>
  bool Differ(MapType& theMap, const MapType& theOtherMap)
  {
    if (&theMap == &theOtherMap)
    {
      if (theMap.IsEmpty())
      {
        return false;
      }
      theMap.Clear();
      return true;
    }

    const int anOldExtent = theMap.Extent();
    Difference<MapType>(theMap, theMap, theOtherMap);
    return anOldExtent != theMap.Extent();
  }

  template <class MapType>
  bool Contains(const MapType& theMap, const MapType& theOtherMap)
  {
    if (&theMap == &theOtherMap || theOtherMap.IsEmpty())
    {
      return true;
    }
    else if (theMap.Extent() < theOtherMap.Extent())
    {
      return false;
    }

    for (typename MapType::Iterator anIter(theOtherMap); anIter.More(); anIter.Next())
    {
      if (!theMap.Contains(anIter.Key()))
      {
        return false;
      }
    }

    return true;
  }

  template <class MapType>
  bool IsEqual(const MapType& theMap, const MapType& theOtherMap)
  {
    if (&theMap == &theOtherMap)
    {
      return true;
    }
    return theMap.Extent() == theOtherMap.Extent() && Contains<MapType>(theMap, theOtherMap);
  }
} // namespace NCollection_MapAlgo

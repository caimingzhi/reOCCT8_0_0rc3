#pragma once

#include <Graphic3d_CLight.hpp>

class Graphic3d_LightSet : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_LightSet, Standard_Transient)
public:
  enum IterationFilter
  {
    IterationFilter_None            = 0x0000,
    IterationFilter_ExcludeAmbient  = 0x0002,
    IterationFilter_ExcludeDisabled = 0x0004,
    IterationFilter_ExcludeNoShadow = 0x0008,
    IterationFilter_ExcludeDisabledAndAmbient =
      IterationFilter_ExcludeAmbient | IterationFilter_ExcludeDisabled,
    IterationFilter_ActiveShadowCasters =
      IterationFilter_ExcludeDisabledAndAmbient | IterationFilter_ExcludeNoShadow,
  };

  class Iterator
  {
  public:
    Iterator()
        : myFilter(0)
    {
    }

    Iterator(const Graphic3d_LightSet& theSet, IterationFilter theFilter = IterationFilter_None)
        : myIter(theSet.myLights),
          myFilter(theFilter)
    {
      skipFiltered();
    }

    Iterator(const occ::handle<Graphic3d_LightSet>& theSet,
             IterationFilter                        theFilter = IterationFilter_None)
        : myFilter(theFilter)
    {
      if (!theSet.IsNull())
      {
        myIter = NCollection_IndexedDataMap<occ::handle<Graphic3d_CLight>, size_t>::Iterator(
          theSet->myLights);
        skipFiltered();
      }
    }

    bool More() const { return myIter.More(); }

    const occ::handle<Graphic3d_CLight>& Value() const { return myIter.Key(); }

    void Next()
    {
      myIter.Next();
      skipFiltered();
    }

  protected:
    void skipFiltered()
    {
      if (myFilter == 0)
      {
        return;
      }

      for (; myIter.More(); myIter.Next())
      {
        if ((myFilter & IterationFilter_ExcludeAmbient) != 0
            && myIter.Key()->Type() == Graphic3d_TypeOfLightSource_Ambient)
        {
          continue;
        }
        else if ((myFilter & IterationFilter_ExcludeDisabled) != 0 && !myIter.Key()->IsEnabled())
        {
          continue;
        }
        else if ((myFilter & IterationFilter_ExcludeNoShadow) != 0
                 && !myIter.Key()->ToCastShadows())
        {
          continue;
        }

        break;
      }
    }

  protected:
    NCollection_IndexedDataMap<occ::handle<Graphic3d_CLight>, size_t>::Iterator myIter;
    int                                                                         myFilter;
  };

public:
  Standard_EXPORT Graphic3d_LightSet();

  int Lower() const { return 1; }

  int Upper() const { return myLights.Extent(); }

  bool IsEmpty() const { return myLights.IsEmpty(); }

  int Extent() const { return myLights.Extent(); }

  const occ::handle<Graphic3d_CLight>& Value(int theIndex) const
  {
    return myLights.FindKey(theIndex);
  }

  bool Contains(const occ::handle<Graphic3d_CLight>& theLight) const
  {
    return myLights.Contains(theLight);
  }

  Standard_EXPORT bool Add(const occ::handle<Graphic3d_CLight>& theLight);

  Standard_EXPORT bool Remove(const occ::handle<Graphic3d_CLight>& theLight);

  int NbLightsOfType(Graphic3d_TypeOfLightSource theType) const { return myLightTypes[theType]; }

public:
  Standard_EXPORT size_t UpdateRevision();

  size_t Revision() const { return myRevision; }

  int NbEnabled() const { return myNbEnabled; }

  int NbEnabledLightsOfType(Graphic3d_TypeOfLightSource theType) const
  {
    return myLightTypesEnabled[theType];
  }

  int NbCastShadows() const { return myNbCastShadows; }

  const NCollection_Vec4<float>& AmbientColor() const { return myAmbient; }

  const TCollection_AsciiString& KeyEnabledLong() const { return myKeyEnabledLong; }

  const TCollection_AsciiString& KeyEnabledShort() const { return myKeyEnabledShort; }

protected:
  NCollection_IndexedDataMap<occ::handle<Graphic3d_CLight>, size_t>

                          myLights;
  NCollection_Vec4<float> myAmbient;
  TCollection_AsciiString myKeyEnabledLong;
  TCollection_AsciiString myKeyEnabledShort;
  int                     myLightTypes[Graphic3d_TypeOfLightSource_NB];
  int                     myLightTypesEnabled[Graphic3d_TypeOfLightSource_NB];
  int                     myNbEnabled;
  int                     myNbCastShadows;

  size_t myRevision;
  size_t myCacheRevision;
};

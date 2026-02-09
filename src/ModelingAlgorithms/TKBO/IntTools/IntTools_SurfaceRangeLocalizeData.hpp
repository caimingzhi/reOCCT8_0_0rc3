#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <IntTools_SurfaceRangeSample.hpp>
#include <NCollection_Map.hpp>
#include <Bnd_Box.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <NCollection_List.hpp>
class IntTools_SurfaceRangeSample;
class Bnd_Box;
class gp_Pnt;

class IntTools_SurfaceRangeLocalizeData
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntTools_SurfaceRangeLocalizeData();

  Standard_EXPORT IntTools_SurfaceRangeLocalizeData(const int    theNbSampleU,
                                                    const int    theNbSampleV,
                                                    const double theMinRangeU,
                                                    const double theMinRangeV);

  Standard_EXPORT IntTools_SurfaceRangeLocalizeData(const IntTools_SurfaceRangeLocalizeData& Other);

  Standard_EXPORT IntTools_SurfaceRangeLocalizeData& Assign(
    const IntTools_SurfaceRangeLocalizeData& Other);

  IntTools_SurfaceRangeLocalizeData& operator=(const IntTools_SurfaceRangeLocalizeData& Other)
  {
    return Assign(Other);
  }

  int GetNbSampleU() const;

  int GetNbSampleV() const;

  double GetMinRangeU() const;

  double GetMinRangeV() const;

  Standard_EXPORT void AddOutRange(const IntTools_SurfaceRangeSample& theRange);

  Standard_EXPORT void AddBox(const IntTools_SurfaceRangeSample& theRange, const Bnd_Box& theBox);

  Standard_EXPORT bool FindBox(const IntTools_SurfaceRangeSample& theRange, Bnd_Box& theBox) const;

  Standard_EXPORT bool IsRangeOut(const IntTools_SurfaceRangeSample& theRange) const;

  Standard_EXPORT void ListRangeOut(NCollection_List<IntTools_SurfaceRangeSample>& theList) const;

  Standard_EXPORT void RemoveRangeOutAll();

  void SetGridDeflection(const double theDeflection);

  double GetGridDeflection() const;

  Standard_EXPORT void SetRangeUGrid(const int theNbUGrid);

  int GetRangeUGrid() const;

  void SetUParam(const int theIndex, const double theUParam);

  double GetUParam(const int theIndex) const;

  Standard_EXPORT void SetRangeVGrid(const int theNbVGrid);

  int GetRangeVGrid() const;

  void SetVParam(const int theIndex, const double theVParam);

  double GetVParam(const int theIndex) const;

  void SetGridPoint(const int theUIndex, const int theVIndex, const gp_Pnt& thePoint);

  const gp_Pnt& GetGridPoint(const int theUIndex, const int theVIndex) const;

  Standard_EXPORT void SetFrame(const double theUMin,
                                const double theUMax,
                                const double theVMin,
                                const double theVMax);

  int GetNBUPointsInFrame() const;

  int GetNBVPointsInFrame() const;

  Standard_EXPORT const gp_Pnt& GetPointInFrame(const int theUIndex, const int theVIndex) const;

  Standard_EXPORT double GetUParamInFrame(const int theIndex) const;

  Standard_EXPORT double GetVParamInFrame(const int theIndex) const;

  Standard_EXPORT void ClearGrid();

private:
  int                                                       myNbSampleU;
  int                                                       myNbSampleV;
  double                                                    myMinRangeU;
  double                                                    myMinRangeV;
  NCollection_Map<IntTools_SurfaceRangeSample>              myMapRangeOut;
  NCollection_DataMap<IntTools_SurfaceRangeSample, Bnd_Box> myMapBox;
  occ::handle<NCollection_HArray1<double>>                  myUParams;
  occ::handle<NCollection_HArray1<double>>                  myVParams;
  occ::handle<NCollection_HArray2<gp_Pnt>>                  myGridPoints;
  int                                                       myUIndMin;
  int                                                       myUIndMax;
  int                                                       myVIndMin;
  int                                                       myVIndMax;
  double                                                    myDeflection;
};

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>

inline int IntTools_SurfaceRangeLocalizeData::GetNbSampleU() const
{
  return myNbSampleU;
}

inline int IntTools_SurfaceRangeLocalizeData::GetNbSampleV() const
{
  return myNbSampleV;
}

inline double IntTools_SurfaceRangeLocalizeData::GetMinRangeU() const
{
  return myMinRangeU;
}

inline double IntTools_SurfaceRangeLocalizeData::GetMinRangeV() const
{
  return myMinRangeV;
}

inline void IntTools_SurfaceRangeLocalizeData::SetGridDeflection(const double theDeflection)
{
  myDeflection = theDeflection;
}

inline double IntTools_SurfaceRangeLocalizeData::GetGridDeflection() const
{
  return myDeflection;
}

inline int IntTools_SurfaceRangeLocalizeData::GetRangeUGrid() const
{
  return (myUParams.IsNull()) ? 0 : myUParams->Length();
}

inline void IntTools_SurfaceRangeLocalizeData::SetUParam(const int theIndex, const double theUParam)
{
  myUParams->SetValue(theIndex, theUParam);
}

inline double IntTools_SurfaceRangeLocalizeData::GetUParam(const int theIndex) const
{
  return myUParams->Value(theIndex);
}

inline int IntTools_SurfaceRangeLocalizeData::GetRangeVGrid() const
{
  return (myVParams.IsNull()) ? 0 : myVParams->Length();
}

inline void IntTools_SurfaceRangeLocalizeData::SetVParam(const int theIndex, const double theVParam)
{
  myVParams->SetValue(theIndex, theVParam);
}

inline double IntTools_SurfaceRangeLocalizeData::GetVParam(const int theIndex) const
{
  return myVParams->Value(theIndex);
}

inline void IntTools_SurfaceRangeLocalizeData::SetGridPoint(const int     theUIndex,
                                                            const int     theVIndex,
                                                            const gp_Pnt& thePoint)
{
  myGridPoints->SetValue(theUIndex, theVIndex, thePoint);
}

inline const gp_Pnt& IntTools_SurfaceRangeLocalizeData::GetGridPoint(const int theUIndex,
                                                                     const int theVIndex) const
{
  return myGridPoints->Value(theUIndex, theVIndex);
}

inline int IntTools_SurfaceRangeLocalizeData::GetNBUPointsInFrame() const
{
  return myUIndMax - myUIndMin + 1;
}

inline int IntTools_SurfaceRangeLocalizeData::GetNBVPointsInFrame() const
{
  return myVIndMax - myVIndMin + 1;
}

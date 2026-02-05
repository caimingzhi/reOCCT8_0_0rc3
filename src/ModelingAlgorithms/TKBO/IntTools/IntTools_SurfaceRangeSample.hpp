#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <IntTools_CurveRangeSample.hpp>
#include <Standard_Integer.hpp>
class IntTools_Range;

//! class for range index management of surface
class IntTools_SurfaceRangeSample
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntTools_SurfaceRangeSample();

  Standard_EXPORT IntTools_SurfaceRangeSample(const int theIndexU,
                                              const int theDepthU,
                                              const int theIndexV,
                                              const int theDepthV);

  Standard_EXPORT IntTools_SurfaceRangeSample(const IntTools_CurveRangeSample& theRangeU,
                                              const IntTools_CurveRangeSample& theRangeV);

  Standard_EXPORT IntTools_SurfaceRangeSample(const IntTools_SurfaceRangeSample& Other);

  Standard_EXPORT IntTools_SurfaceRangeSample& Assign(const IntTools_SurfaceRangeSample& Other);

  IntTools_SurfaceRangeSample& operator=(const IntTools_SurfaceRangeSample& Other)
  {
    return Assign(Other);
  }

  void SetRanges(const IntTools_CurveRangeSample& theRangeU,
                 const IntTools_CurveRangeSample& theRangeV);

  void GetRanges(IntTools_CurveRangeSample& theRangeU, IntTools_CurveRangeSample& theRangeV) const;

  void SetIndexes(const int theIndexU, const int theIndexV);

  void GetIndexes(int& theIndexU, int& theIndexV) const;

  void GetDepths(int& theDepthU, int& theDepthV) const;

  void SetSampleRangeU(const IntTools_CurveRangeSample& theRangeSampleU);

  const IntTools_CurveRangeSample& GetSampleRangeU() const;

  void SetSampleRangeV(const IntTools_CurveRangeSample& theRangeSampleV);

  const IntTools_CurveRangeSample& GetSampleRangeV() const;

  void SetIndexU(const int theIndexU);

  int GetIndexU() const;

  void SetIndexV(const int theIndexV);

  int GetIndexV() const;

  void SetDepthU(const int theDepthU);

  int GetDepthU() const;

  void SetDepthV(const int theDepthV);

  int GetDepthV() const;

  Standard_EXPORT IntTools_Range GetRangeU(const double theFirstU,
                                           const double theLastU,
                                           const int    theNbSampleU) const;

  Standard_EXPORT IntTools_Range GetRangeV(const double theFirstV,
                                           const double theLastV,
                                           const int    theNbSampleV) const;

  bool IsEqual(const IntTools_SurfaceRangeSample& Other) const;

  int GetRangeIndexUDeeper(const int theNbSampleU) const;

  int GetRangeIndexVDeeper(const int theNbSampleV) const;

  bool operator==(const IntTools_SurfaceRangeSample& theOther) const { return IsEqual(theOther); }

private:
  IntTools_CurveRangeSample myRangeU;
  IntTools_CurveRangeSample myRangeV;
};

#include <Standard_HashUtils.hpp>

inline void IntTools_SurfaceRangeSample::SetRanges(const IntTools_CurveRangeSample& theRangeU,
                                                   const IntTools_CurveRangeSample& theRangeV)
{
  myRangeU = theRangeU;
  myRangeV = theRangeV;
}

inline void IntTools_SurfaceRangeSample::GetRanges(IntTools_CurveRangeSample& theRangeU,
                                                   IntTools_CurveRangeSample& theRangeV) const
{
  theRangeU = myRangeU;
  theRangeV = myRangeV;
}

inline void IntTools_SurfaceRangeSample::SetIndexes(const int theIndexU, const int theIndexV)
{
  myRangeU.SetRangeIndex(theIndexU);
  myRangeV.SetRangeIndex(theIndexV);
}

inline void IntTools_SurfaceRangeSample::GetIndexes(int& theIndexU, int& theIndexV) const
{
  theIndexU = myRangeU.GetRangeIndex();
  theIndexV = myRangeV.GetRangeIndex();
}

inline void IntTools_SurfaceRangeSample::GetDepths(int& theDepthU, int& theDepthV) const
{
  theDepthU = myRangeU.GetDepth();
  theDepthV = myRangeV.GetDepth();
}

inline void IntTools_SurfaceRangeSample::SetSampleRangeU(
  const IntTools_CurveRangeSample& theRangeSampleU)
{
  myRangeU = theRangeSampleU;
}

inline const IntTools_CurveRangeSample& IntTools_SurfaceRangeSample::GetSampleRangeU() const
{
  return myRangeU;
}

inline void IntTools_SurfaceRangeSample::SetSampleRangeV(
  const IntTools_CurveRangeSample& theRangeSampleV)
{
  myRangeV = theRangeSampleV;
}

inline const IntTools_CurveRangeSample& IntTools_SurfaceRangeSample::GetSampleRangeV() const
{
  return myRangeV;
}

inline void IntTools_SurfaceRangeSample::SetIndexU(const int theIndexU)
{
  myRangeU.SetRangeIndex(theIndexU);
}

inline int IntTools_SurfaceRangeSample::GetIndexU() const
{
  return myRangeU.GetRangeIndex();
}

inline void IntTools_SurfaceRangeSample::SetIndexV(const int theIndexV)
{
  myRangeV.SetRangeIndex(theIndexV);
}

inline int IntTools_SurfaceRangeSample::GetIndexV() const
{
  return myRangeV.GetRangeIndex();
}

inline void IntTools_SurfaceRangeSample::SetDepthU(const int theDepthU)
{
  myRangeU.SetDepth(theDepthU);
}

inline int IntTools_SurfaceRangeSample::GetDepthU() const
{
  return myRangeU.GetDepth();
}

inline void IntTools_SurfaceRangeSample::SetDepthV(const int theDepthV)
{
  myRangeV.SetDepth(theDepthV);
}

inline int IntTools_SurfaceRangeSample::GetDepthV() const
{
  return myRangeV.GetDepth();
}

inline bool IntTools_SurfaceRangeSample::IsEqual(const IntTools_SurfaceRangeSample& Other) const
{
  return (myRangeU.IsEqual(Other.myRangeU) && myRangeV.IsEqual(Other.myRangeV));
}

inline int IntTools_SurfaceRangeSample::GetRangeIndexUDeeper(const int theNbSampleU) const
{
  return myRangeU.GetRangeIndexDeeper(theNbSampleU);
}

inline int IntTools_SurfaceRangeSample::GetRangeIndexVDeeper(const int theNbSampleV) const
{
  return myRangeV.GetRangeIndexDeeper(theNbSampleV);
}

namespace std
{
  template <>
  struct hash<IntTools_SurfaceRangeSample>
  {
    size_t operator()(const IntTools_SurfaceRangeSample& theSurfaceRangeSample) const noexcept
    {
      // Combine two int values into a single hash value.
      size_t aCombination[2]{
        std::hash<IntTools_CurveRangeSample>{}(theSurfaceRangeSample.GetSampleRangeU()),
        std::hash<IntTools_CurveRangeSample>{}(theSurfaceRangeSample.GetSampleRangeV())};
      return opencascade::hashBytes(aCombination, sizeof(aCombination));
    }
  };
} // namespace std

#pragma once

#include <Standard.hpp>

#include <ChFiDS_CommonPoint.hpp>
#include <ChFiDS_FaceInterference.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <TopAbs_Orientation.hpp>
#include <Standard_Transient.hpp>

//! data structure for all information related to the
//! fillet and to 2 faces vis a vis
class ChFiDS_SurfData : public Standard_Transient
{

public:
  Standard_EXPORT ChFiDS_SurfData();

  Standard_EXPORT void Copy(const occ::handle<ChFiDS_SurfData>& Other);

  int IndexOfS1() const;

  int IndexOfS2() const;

  bool IsOnCurve1() const;

  bool IsOnCurve2() const;

  int IndexOfC1() const;

  int IndexOfC2() const;

  int Surf() const;

  TopAbs_Orientation Orientation() const;

  const ChFiDS_FaceInterference& InterferenceOnS1() const;

  const ChFiDS_FaceInterference& InterferenceOnS2() const;

  const ChFiDS_CommonPoint& VertexFirstOnS1() const;

  const ChFiDS_CommonPoint& VertexFirstOnS2() const;

  const ChFiDS_CommonPoint& VertexLastOnS1() const;

  const ChFiDS_CommonPoint& VertexLastOnS2() const;

  void ChangeIndexOfS1(const int Index);

  void ChangeIndexOfS2(const int Index);

  void ChangeSurf(const int Index);

  void SetIndexOfC1(const int Index);

  void SetIndexOfC2(const int Index);

  TopAbs_Orientation& ChangeOrientation();

  ChFiDS_FaceInterference& ChangeInterferenceOnS1();

  ChFiDS_FaceInterference& ChangeInterferenceOnS2();

  ChFiDS_CommonPoint& ChangeVertexFirstOnS1();

  ChFiDS_CommonPoint& ChangeVertexFirstOnS2();

  ChFiDS_CommonPoint& ChangeVertexLastOnS1();

  ChFiDS_CommonPoint& ChangeVertexLastOnS2();

  Standard_EXPORT const ChFiDS_FaceInterference& Interference(const int OnS) const;

  Standard_EXPORT ChFiDS_FaceInterference& ChangeInterference(const int OnS);

  Standard_EXPORT int Index(const int OfS) const;

  //! returns one of the four vertices whether First is true
  //! or wrong and OnS equals 1 or 2.
  Standard_EXPORT const ChFiDS_CommonPoint& Vertex(const bool First, const int OnS) const;

  //! returns one of the four vertices whether First is true
  //! or wrong and OnS equals 1 or 2.
  Standard_EXPORT ChFiDS_CommonPoint& ChangeVertex(const bool First, const int OnS);

  bool IsOnCurve(const int OnS) const;

  int IndexOfC(const int OnS) const;

  Standard_EXPORT double FirstSpineParam() const;

  Standard_EXPORT double LastSpineParam() const;

  Standard_EXPORT void FirstSpineParam(const double Par);

  Standard_EXPORT void LastSpineParam(const double Par);

  Standard_EXPORT double FirstExtensionValue() const;

  Standard_EXPORT double LastExtensionValue() const;

  Standard_EXPORT void FirstExtensionValue(const double Extend);

  Standard_EXPORT void LastExtensionValue(const double Extend);

  Standard_EXPORT occ::handle<Standard_Transient> Simul() const;

  Standard_EXPORT void SetSimul(const occ::handle<Standard_Transient>& S);

  Standard_EXPORT void ResetSimul();

  Standard_EXPORT gp_Pnt2d Get2dPoints(const bool First, const int OnS) const;

  Standard_EXPORT void Get2dPoints(gp_Pnt2d& P2df1,
                                   gp_Pnt2d& P2dl1,
                                   gp_Pnt2d& P2df2,
                                   gp_Pnt2d& P2dl2) const;

  Standard_EXPORT void Set2dPoints(const gp_Pnt2d& P2df1,
                                   const gp_Pnt2d& P2dl1,
                                   const gp_Pnt2d& P2df2,
                                   const gp_Pnt2d& P2dl2);

  bool TwistOnS1() const;

  bool TwistOnS2() const;

  void TwistOnS1(const bool T);

  void TwistOnS2(const bool T);

  DEFINE_STANDARD_RTTIEXT(ChFiDS_SurfData, Standard_Transient)

private:
  ChFiDS_CommonPoint              pfirstOnS1;
  ChFiDS_CommonPoint              plastOnS1;
  ChFiDS_CommonPoint              pfirstOnS2;
  ChFiDS_CommonPoint              plastOnS2;
  ChFiDS_FaceInterference         intf1;
  ChFiDS_FaceInterference         intf2;
  gp_Pnt2d                        p2df1;
  gp_Pnt2d                        p2dl1;
  gp_Pnt2d                        p2df2;
  gp_Pnt2d                        p2dl2;
  double                          ufspine;
  double                          ulspine;
  double                          myfirstextend;
  double                          mylastextend;
  occ::handle<Standard_Transient> simul;
  int                             indexOfS1;
  int                             indexOfC1;
  int                             indexOfS2;
  int                             indexOfC2;
  int                             indexOfConge;
  bool                            isoncurv1;
  bool                            isoncurv2;
  bool                            twistons1;
  bool                            twistons2;
  TopAbs_Orientation              orientation;
};

inline int ChFiDS_SurfData::IndexOfS1() const
{
  return indexOfS1;
}

//=================================================================================================

inline bool ChFiDS_SurfData::IsOnCurve1() const
{
  return isoncurv1;
}

//=================================================================================================

inline int ChFiDS_SurfData::IndexOfC1() const
{
  if (!isoncurv1)
    throw Standard_Failure("Interference pas sur courbe");
  return indexOfC1;
}

//=================================================================================================

inline void ChFiDS_SurfData::SetIndexOfC1(const int theIndex)
{
  indexOfC1 = theIndex;
  isoncurv1 = (theIndex != 0);
}

//=================================================================================================

inline int ChFiDS_SurfData::IndexOfS2() const
{
  return indexOfS2;
}

//=================================================================================================

inline bool ChFiDS_SurfData::IsOnCurve2() const
{
  return isoncurv2;
}

//=================================================================================================

inline int ChFiDS_SurfData::IndexOfC2() const
{
  if (!isoncurv2)
    throw Standard_Failure("Interference pas sur courbe");
  return indexOfC2;
}

//=================================================================================================

inline void ChFiDS_SurfData::SetIndexOfC2(const int theIndex)
{
  indexOfC2 = theIndex;
  isoncurv2 = (theIndex != 0);
}

//=================================================================================================

inline int ChFiDS_SurfData::Surf() const
{
  return indexOfConge;
}

//=================================================================================================

inline TopAbs_Orientation ChFiDS_SurfData::Orientation() const
{
  return orientation;
}

//=================================================================================================

inline const ChFiDS_FaceInterference& ChFiDS_SurfData::InterferenceOnS1() const
{
  return intf1;
}

//=================================================================================================

inline const ChFiDS_FaceInterference& ChFiDS_SurfData::InterferenceOnS2() const
{
  return intf2;
}

//=================================================================================================

inline const ChFiDS_CommonPoint& ChFiDS_SurfData::VertexFirstOnS1() const
{
  return pfirstOnS1;
}

//=================================================================================================

inline const ChFiDS_CommonPoint& ChFiDS_SurfData::VertexLastOnS1() const
{
  return plastOnS1;
}

//=================================================================================================

inline const ChFiDS_CommonPoint& ChFiDS_SurfData::VertexFirstOnS2() const
{
  return pfirstOnS2;
}

//=================================================================================================

inline const ChFiDS_CommonPoint& ChFiDS_SurfData::VertexLastOnS2() const
{
  return plastOnS2;
}

//=================================================================================================

inline void ChFiDS_SurfData::ChangeIndexOfS1(const int Index)
{
  indexOfS1 = Index;
}

//=================================================================================================

inline void ChFiDS_SurfData::ChangeIndexOfS2(const int Index)
{
  indexOfS2 = Index;
}

//=================================================================================================

inline void ChFiDS_SurfData::ChangeSurf(const int Index)
{
  indexOfConge = Index;
}

//=================================================================================================

inline TopAbs_Orientation& ChFiDS_SurfData::ChangeOrientation()
{
  return orientation;
}

//=================================================================================================

inline ChFiDS_FaceInterference& ChFiDS_SurfData::ChangeInterferenceOnS1()
{
  return intf1;
}

//=================================================================================================

inline ChFiDS_FaceInterference& ChFiDS_SurfData::ChangeInterferenceOnS2()
{
  return intf2;
}

//=================================================================================================

inline ChFiDS_CommonPoint& ChFiDS_SurfData::ChangeVertexFirstOnS1()
{
  return pfirstOnS1;
}

//=================================================================================================

inline ChFiDS_CommonPoint& ChFiDS_SurfData::ChangeVertexLastOnS1()
{
  return plastOnS1;
}

//=================================================================================================

inline ChFiDS_CommonPoint& ChFiDS_SurfData::ChangeVertexFirstOnS2()
{
  return pfirstOnS2;
}

//=================================================================================================

inline ChFiDS_CommonPoint& ChFiDS_SurfData::ChangeVertexLastOnS2()
{
  return plastOnS2;
}

//=================================================================================================

inline bool ChFiDS_SurfData::IsOnCurve(const int OnS) const
{
  if (OnS == 1)
    return isoncurv1;
  return isoncurv2;
}

//=================================================================================================

inline int ChFiDS_SurfData::IndexOfC(const int OnS) const
{
  if (OnS == 1)
  {
    if (!isoncurv1)
      throw Standard_Failure("Interference pas sur courbe");
    return indexOfC1;
  }
  if (!isoncurv2)
    throw Standard_Failure("Interference pas sur courbe");
  return indexOfC2;
}

//=================================================================================================

inline bool ChFiDS_SurfData::TwistOnS1() const
{
  return twistons1;
}

inline bool ChFiDS_SurfData::TwistOnS2() const
{
  return twistons2;
}

inline void ChFiDS_SurfData::TwistOnS1(const bool T)
{
  twistons1 = T;
}

inline void ChFiDS_SurfData::TwistOnS2(const bool T)
{
  twistons2 = T;
}

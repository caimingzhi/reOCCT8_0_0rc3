#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

class TopOpeBRep_FacesFiller;
typedef TopOpeBRep_FacesFiller* TopOpeBRep_PFacesFiller;

#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <Standard_Integer.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Transient.hpp>
#include <TopOpeBRepDS_Kind.hpp>
class TopOpeBRep_LineInter;
class TopOpeBRep_VPointInter;
class TopoDS_Shape;

class TopOpeBRep_FFDumper : public Standard_Transient
{

public:
  Standard_EXPORT TopOpeBRep_FFDumper(const TopOpeBRep_PFacesFiller& PFF);

  Standard_EXPORT void Init(const TopOpeBRep_PFacesFiller& PFF);

  Standard_EXPORT void DumpLine(const int I);

  Standard_EXPORT void DumpLine(const TopOpeBRep_LineInter& L);

  Standard_EXPORT void DumpVP(const TopOpeBRep_VPointInter& VP);

  Standard_EXPORT void DumpVP(const TopOpeBRep_VPointInter& VP, const int ISI);

  Standard_EXPORT int ExploreIndex(const TopoDS_Shape& S, const int ISI) const;

  Standard_EXPORT void DumpDSP(const TopOpeBRep_VPointInter& VP,
                               const TopOpeBRepDS_Kind       GK,
                               const int                     G,
                               const bool                    newinDS) const;

  Standard_EXPORT TopOpeBRep_PFacesFiller PFacesFillerDummy() const;

  DEFINE_STANDARD_RTTIEXT(TopOpeBRep_FFDumper, Standard_Transient)

private:
  TopOpeBRep_PFacesFiller                                         myPFF;
  TopoDS_Face                                                     myF1;
  TopoDS_Face                                                     myF2;
  NCollection_DataMap<TopoDS_Shape, int, TopTools_ShapeMapHasher> myEM1;
  NCollection_DataMap<TopoDS_Shape, int, TopTools_ShapeMapHasher> myEM2;
  int                                                             myEn1;
  int                                                             myEn2;
  int                                                             myLineIndex;
};

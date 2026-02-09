#pragma once

#include <BRepAdaptor_Surface.hpp>
#include <GeomAbs_SurfaceType.hpp>
#include <IntPatch_Intersection.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopOpeBRep_LineInter.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TopoDS_Face.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>

class BRepTopAdaptor_TopolTool;
class Bnd_Box;

class TopOpeBRep_FacesIntersector
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRep_FacesIntersector();

  Standard_EXPORT void Perform(const TopoDS_Shape& S1, const TopoDS_Shape& S2);

  Standard_EXPORT void Perform(const TopoDS_Shape& S1,
                               const TopoDS_Shape& S2,
                               const Bnd_Box&      B1,
                               const Bnd_Box&      B2);

  Standard_EXPORT bool IsEmpty();

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT bool SameDomain() const;

  Standard_EXPORT const TopoDS_Shape& Face(const int Index) const;

  Standard_EXPORT bool SurfacesSameOriented() const;

  Standard_EXPORT bool IsRestriction(const TopoDS_Shape& E) const;

  Standard_EXPORT const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>&
                        Restrictions() const;

  Standard_EXPORT void PrepareLines();

  Standard_EXPORT occ::handle<NCollection_HArray1<TopOpeBRep_LineInter>> Lines();

  Standard_EXPORT int NbLines() const;

  Standard_EXPORT void InitLine();

  Standard_EXPORT bool MoreLine() const;

  Standard_EXPORT void NextLine();

  Standard_EXPORT TopOpeBRep_LineInter& CurrentLine();

  Standard_EXPORT int CurrentLineIndex() const;

  Standard_EXPORT TopOpeBRep_LineInter& ChangeLine(const int IL);

  Standard_EXPORT void ForceTolerances(const double tolarc, const double toltang);

  Standard_EXPORT void GetTolerances(double& tolarc, double& toltang) const;

private:
  Standard_EXPORT void FindLine();

  Standard_EXPORT void ResetIntersection();

  Standard_EXPORT void ShapeTolerances(const TopoDS_Shape& S1, const TopoDS_Shape& S2);

  Standard_EXPORT double ToleranceMax(const TopoDS_Shape& S, const TopAbs_ShapeEnum T) const;

  IntPatch_Intersection                                         myIntersector;
  bool                                                          myIntersectionDone;
  double                                                        myTol1;
  double                                                        myTol2;
  bool                                                          myForceTolerances;
  occ::handle<NCollection_HArray1<TopOpeBRep_LineInter>>        myHAL;
  TopOpeBRep_LineInter                                          myLine;
  int                                                           myLineIndex;
  bool                                                          myLineFound;
  int                                                           myLineNb;
  TopoDS_Face                                                   myFace1;
  TopoDS_Face                                                   myFace2;
  occ::handle<BRepAdaptor_Surface>                              mySurface1;
  occ::handle<BRepAdaptor_Surface>                              mySurface2;
  GeomAbs_SurfaceType                                           mySurfaceType1;
  GeomAbs_SurfaceType                                           mySurfaceType2;
  bool                                                          mySurfacesSameOriented;
  occ::handle<BRepTopAdaptor_TopolTool>                         myDomain1;
  occ::handle<BRepTopAdaptor_TopolTool>                         myDomain2;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> myEdgeRestrictionMap;
  TopoDS_Shape                                                  myNullShape;
};

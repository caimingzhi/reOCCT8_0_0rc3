#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Wire.hpp>
#include <TopoDS_Shape.hpp>
#include <BRepFill_Section.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <GeomFill_Trihedron.hpp>
#include <BRepFill_TransitionStyle.hpp>
#include <GeomFill_PipeError.hpp>
#include <Standard_Transient.hpp>
#include <BRepFill_TypeOfContact.hpp>
class Law_Function;
class BRepFill_LocationLaw;
class BRepFill_SectionLaw;
class gp_Ax2;
class gp_Dir;
class TopoDS_Vertex;
class gp_Trsf;
class BRepFill_Sweep;

class BRepFill_PipeShell : public Standard_Transient
{

public:
  Standard_EXPORT BRepFill_PipeShell(const TopoDS_Wire& Spine);

  Standard_EXPORT void Set(const bool Frenet = false);

  Standard_EXPORT void SetDiscrete();

  Standard_EXPORT void Set(const gp_Ax2& Axe);

  Standard_EXPORT void Set(const gp_Dir& BiNormal);

  Standard_EXPORT bool Set(const TopoDS_Shape& SpineSupport);

  Standard_EXPORT void Set(const TopoDS_Wire&           AuxiliarySpine,
                           const bool                   CurvilinearEquivalence = true,
                           const BRepFill_TypeOfContact KeepContact = BRepFill_NoContact);

  Standard_EXPORT void SetMaxDegree(const int NewMaxDegree);

  Standard_EXPORT void SetMaxSegments(const int NewMaxSegments);

  Standard_EXPORT void SetForceApproxC1(const bool ForceApproxC1);

  inline void SetIsBuildHistory(const bool theIsBuildHistory)
  {
    myIsBuildHistory = theIsBuildHistory;
  }

  inline bool IsBuildHistory() const { return myIsBuildHistory; }

  Standard_EXPORT void Add(const TopoDS_Shape& Profile,
                           const bool          WithContact    = false,
                           const bool          WithCorrection = false);

  Standard_EXPORT void Add(const TopoDS_Shape&  Profile,
                           const TopoDS_Vertex& Location,
                           const bool           WithContact    = false,
                           const bool           WithCorrection = false);

  Standard_EXPORT void SetLaw(const TopoDS_Shape&              Profile,
                              const occ::handle<Law_Function>& L,
                              const bool                       WithContact    = false,
                              const bool                       WithCorrection = false);

  Standard_EXPORT void SetLaw(const TopoDS_Shape&              Profile,
                              const occ::handle<Law_Function>& L,
                              const TopoDS_Vertex&             Location,
                              const bool                       WithContact    = false,
                              const bool                       WithCorrection = false);

  Standard_EXPORT void DeleteProfile(const TopoDS_Shape& Profile);

  Standard_EXPORT bool IsReady() const;

  Standard_EXPORT GeomFill_PipeError GetStatus() const;

  Standard_EXPORT void SetTolerance(const double Tol3d      = 1.0e-4,
                                    const double BoundTol   = 1.0e-4,
                                    const double TolAngular = 1.0e-2);

  Standard_EXPORT void SetTransition(const BRepFill_TransitionStyle Mode   = BRepFill_Modified,
                                     const double                   Angmin = 1.0e-2,
                                     const double                   Angmax = 6.0);

  Standard_EXPORT void Simulate(const int                       NumberOfSection,
                                NCollection_List<TopoDS_Shape>& Sections);

  Standard_EXPORT bool Build();

  Standard_EXPORT bool MakeSolid();

  Standard_EXPORT const TopoDS_Shape& Shape() const;

  Standard_EXPORT double ErrorOnSurface() const;

  Standard_EXPORT const TopoDS_Shape& FirstShape() const;

  Standard_EXPORT const TopoDS_Shape& LastShape() const;

  void Profiles(NCollection_List<TopoDS_Shape>& theProfiles)
  {
    for (int i = 1; i <= mySeq.Length(); ++i)
      theProfiles.Append(mySeq(i).OriginalShape());
  }

  const TopoDS_Wire& Spine() { return mySpine; }

  Standard_EXPORT void Generated(const TopoDS_Shape& S, NCollection_List<TopoDS_Shape>& L);

  DEFINE_STANDARD_RTTIEXT(BRepFill_PipeShell, Standard_Transient)

private:
  Standard_EXPORT void Prepare();

  Standard_EXPORT void Place(const BRepFill_Section& Sec,
                             TopoDS_Wire&            W,
                             gp_Trsf&                Trsf,
                             double&                 param);

  Standard_EXPORT void ResetLoc();

  Standard_EXPORT void BuildHistory(const BRepFill_Sweep& theSweep);

  TopoDS_Wire                            mySpine;
  TopoDS_Shape                           myFirst;
  TopoDS_Shape                           myLast;
  TopoDS_Shape                           myShape;
  NCollection_Sequence<BRepFill_Section> mySeq;
  NCollection_Sequence<TopoDS_Shape>     WSeq;
  NCollection_Sequence<int>              myIndOfSec;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myEdgeNewEdges;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                                 myGenMap;
  double                                         myTol3d;
  double                                         myBoundTol;
  double                                         myTolAngular;
  double                                         angmin;
  double                                         angmax;
  int                                            myMaxDegree;
  int                                            myMaxSegments;
  bool                                           myForceApproxC1;
  occ::handle<Law_Function>                      myLaw;
  bool                                           myIsAutomaticLaw;
  occ::handle<BRepFill_LocationLaw>              myLocation;
  occ::handle<BRepFill_SectionLaw>               mySection;
  occ::handle<NCollection_HArray2<TopoDS_Shape>> myFaces;
  GeomFill_Trihedron                             myTrihedron;
  BRepFill_TransitionStyle                       myTransition;
  GeomFill_PipeError                             myStatus;
  double                                         myErrorOnSurf;
  bool                                           myIsBuildHistory;
};

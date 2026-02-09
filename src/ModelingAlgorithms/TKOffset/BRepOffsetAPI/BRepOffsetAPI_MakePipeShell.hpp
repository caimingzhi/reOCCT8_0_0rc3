#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepPrimAPI_MakeSweep.hpp>
#include <BRepFill_PipeShell.hpp>
#include <BRepFill_TypeOfContact.hpp>

enum BRepBuilderAPI_PipeError
{
  BRepBuilderAPI_PipeDone,
  BRepBuilderAPI_PipeNotDone,
  BRepBuilderAPI_PlaneNotIntersectGuide,
  BRepBuilderAPI_ImpossibleContact
};

#include <Standard_Integer.hpp>
#include <BRepBuilderAPI_TransitionMode.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
class TopoDS_Wire;
class gp_Ax2;
class gp_Dir;
class TopoDS_Shape;
class TopoDS_Vertex;
class Law_Function;

class BRepOffsetAPI_MakePipeShell : public BRepPrimAPI_MakeSweep
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepOffsetAPI_MakePipeShell(const TopoDS_Wire& Spine);

  Standard_EXPORT void SetMode(const bool IsFrenet = false);

  Standard_EXPORT void SetDiscreteMode();

  Standard_EXPORT void SetMode(const gp_Ax2& Axe);

  Standard_EXPORT void SetMode(const gp_Dir& BiNormal);

  Standard_EXPORT bool SetMode(const TopoDS_Shape& SpineSupport);

  Standard_EXPORT void SetMode(const TopoDS_Wire&           AuxiliarySpine,
                               const bool                   CurvilinearEquivalence,
                               const BRepFill_TypeOfContact KeepContact = BRepFill_NoContact);

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

  Standard_EXPORT void Delete(const TopoDS_Shape& Profile);

  Standard_EXPORT bool IsReady() const;

  Standard_EXPORT BRepBuilderAPI_PipeError GetStatus() const;

  Standard_EXPORT void SetTolerance(const double Tol3d      = 1.0e-4,
                                    const double BoundTol   = 1.0e-4,
                                    const double TolAngular = 1.0e-2);

  Standard_EXPORT void SetMaxDegree(const int NewMaxDegree);

  Standard_EXPORT void SetMaxSegments(const int NewMaxSegments);

  Standard_EXPORT void SetForceApproxC1(const bool ForceApproxC1);

  Standard_EXPORT void SetTransitionMode(
    const BRepBuilderAPI_TransitionMode Mode = BRepBuilderAPI_Transformed);

  Standard_EXPORT void Simulate(const int NumberOfSection, NCollection_List<TopoDS_Shape>& Result);

  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT bool MakeSolid();

  Standard_EXPORT TopoDS_Shape FirstShape() override;

  Standard_EXPORT TopoDS_Shape LastShape() override;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Generated(const TopoDS_Shape& S) override;

  Standard_EXPORT double ErrorOnSurface() const;

  inline void SetIsBuildHistory(const bool theIsBuildHistory)
  {
    myPipe->SetIsBuildHistory(theIsBuildHistory);
  }

  inline bool IsBuildHistory() const { return myPipe->IsBuildHistory(); }

  void Profiles(NCollection_List<TopoDS_Shape>& theProfiles) { myPipe->Profiles(theProfiles); }

  const TopoDS_Wire& Spine() { return myPipe->Spine(); }

private:
  occ::handle<BRepFill_PipeShell> myPipe;
};

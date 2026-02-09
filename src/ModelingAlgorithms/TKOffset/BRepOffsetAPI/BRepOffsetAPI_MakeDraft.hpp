#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepFill_Draft.hpp>
#include <BRepBuilderAPI_MakeShape.hpp>
#include <Standard_Real.hpp>
#include <BRepBuilderAPI_TransitionMode.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
class TopoDS_Shape;
class gp_Dir;
class Geom_Surface;
class TopoDS_Shell;

class BRepOffsetAPI_MakeDraft : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepOffsetAPI_MakeDraft(const TopoDS_Shape& Shape,
                                          const gp_Dir&       Dir,
                                          const double        Angle);

  Standard_EXPORT void SetOptions(
    const BRepBuilderAPI_TransitionMode Style    = BRepBuilderAPI_RightCorner,
    const double                        AngleMin = 0.01,
    const double                        AngleMax = 3.0);

  Standard_EXPORT void SetDraft(const bool IsInternal = false);

  Standard_EXPORT void Perform(const double LengthMax);

  Standard_EXPORT void Perform(const occ::handle<Geom_Surface>& Surface,
                               const bool                       KeepInsideSurface = true);

  Standard_EXPORT void Perform(const TopoDS_Shape& StopShape, const bool KeepOutSide = true);

  Standard_EXPORT TopoDS_Shell Shell() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Generated(const TopoDS_Shape& S) override;

private:
  BRepFill_Draft myDraft;
};

#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepSweep_Revol.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <BRepPrimAPI_MakeSweep.hpp>
#include <BRepTools_History.hpp>
class TopoDS_Shape;
class gp_Ax1;

class BRepPrimAPI_MakeRevol : public BRepPrimAPI_MakeSweep
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepPrimAPI_MakeRevol(const TopoDS_Shape& S,
                                        const gp_Ax1&       A,
                                        const double        D,
                                        const bool          Copy = false);

  Standard_EXPORT BRepPrimAPI_MakeRevol(const TopoDS_Shape& S,
                                        const gp_Ax1&       A,
                                        const bool          Copy = false);

  Standard_EXPORT const BRepSweep_Revol& Revol() const;

  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT TopoDS_Shape FirstShape() override;

  Standard_EXPORT TopoDS_Shape LastShape() override;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Generated(const TopoDS_Shape& S) override;

  Standard_EXPORT bool IsDeleted(const TopoDS_Shape& S) override;

  Standard_EXPORT TopoDS_Shape FirstShape(const TopoDS_Shape& theShape);

  Standard_EXPORT TopoDS_Shape LastShape(const TopoDS_Shape& theShape);

  Standard_EXPORT bool HasDegenerated() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Degenerated() const;

protected:
  Standard_EXPORT bool CheckValidity(const TopoDS_Shape& theShape, const gp_Ax1& theA);

private:
  BRepSweep_Revol                myRevol;
  NCollection_List<TopoDS_Shape> myDegenerated;
  occ::handle<BRepTools_History> myHist;
  bool                           myIsBuild;
};

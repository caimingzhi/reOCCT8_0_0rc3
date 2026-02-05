#pragma once

#include <TopoDS_Shape.hpp>
#include <PrsMgr_PresentableObject.hpp>

//! Presentable shape only for purpose of display for BRepOwner...
class StdSelect_Shape : public PrsMgr_PresentableObject
{
  DEFINE_STANDARD_RTTIEXT(StdSelect_Shape, PrsMgr_PresentableObject)
public:
  Standard_EXPORT StdSelect_Shape(
    const TopoDS_Shape&              theShape,
    const occ::handle<Prs3d_Drawer>& theDrawer = occ::handle<Prs3d_Drawer>());

  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  const TopoDS_Shape& Shape() const { return mysh; }

  void Shape(const TopoDS_Shape& theShape) { mysh = theShape; }

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

private:
  TopoDS_Shape mysh;
};

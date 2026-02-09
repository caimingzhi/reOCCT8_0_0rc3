#pragma once

#include <BRepLib_ToolTriangulatedShape.hpp>
#include <gp_Dir.hpp>
#include <NCollection_Array1.hpp>

class TopoDS_Shape;
class Prs3d_Drawer;

class StdPrs_ToolTriangulatedShape : public BRepLib_ToolTriangulatedShape
{
public:
  Standard_EXPORT static bool IsTriangulated(const TopoDS_Shape& theShape);

  Standard_EXPORT static bool IsClosed(const TopoDS_Shape& theShape);

  Standard_EXPORT static double GetDeflection(const TopoDS_Shape&              theShape,
                                              const occ::handle<Prs3d_Drawer>& theDrawer);

  Standard_EXPORT static bool IsTessellated(const TopoDS_Shape&              theShape,
                                            const occ::handle<Prs3d_Drawer>& theDrawer);

  Standard_EXPORT static bool Tessellate(const TopoDS_Shape&              theShape,
                                         const occ::handle<Prs3d_Drawer>& theDrawer);

  Standard_EXPORT static void ClearOnOwnDeflectionChange(const TopoDS_Shape&              theShape,
                                                         const occ::handle<Prs3d_Drawer>& theDrawer,
                                                         const bool theToResetCoeff);
};

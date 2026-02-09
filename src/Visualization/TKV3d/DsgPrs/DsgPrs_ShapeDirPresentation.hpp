#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Prs3d_Drawer.hpp>
#include <Prs3d_Presentation.hpp>

class TopoDS_Shape;

class DsgPrs_ShapeDirPresentation
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& prs,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const TopoDS_Shape&                    shape,
                                  const int                              mode);
};

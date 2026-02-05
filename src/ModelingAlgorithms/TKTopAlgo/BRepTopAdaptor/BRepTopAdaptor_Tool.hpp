#pragma once

#include <Adaptor3d_Surface.hpp>

class BRepTopAdaptor_TopolTool;
class TopoDS_Face;

class BRepTopAdaptor_Tool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepTopAdaptor_Tool();

  Standard_EXPORT BRepTopAdaptor_Tool(const TopoDS_Face& F, const double Tol2d);

  Standard_EXPORT BRepTopAdaptor_Tool(const occ::handle<Adaptor3d_Surface>& Surface,
                                      const double                          Tol2d);

  Standard_EXPORT void Init(const TopoDS_Face& F, const double Tol2d);

  Standard_EXPORT void Init(const occ::handle<Adaptor3d_Surface>& Surface, const double Tol2d);

  Standard_EXPORT occ::handle<BRepTopAdaptor_TopolTool> GetTopolTool();

  Standard_EXPORT void SetTopolTool(const occ::handle<BRepTopAdaptor_TopolTool>& TT);

  Standard_EXPORT occ::handle<Adaptor3d_Surface> GetSurface();

  Standard_EXPORT void Destroy();

  ~BRepTopAdaptor_Tool() { Destroy(); }

private:
  bool                                  myloaded;
  occ::handle<BRepTopAdaptor_TopolTool> myTopolTool;
  occ::handle<Adaptor3d_Surface>        myHSurface;
};

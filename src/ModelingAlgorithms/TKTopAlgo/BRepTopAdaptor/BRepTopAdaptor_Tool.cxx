#include <Adaptor3d_Surface.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <BRepTopAdaptor_Tool.hpp>
#include <BRepTopAdaptor_TopolTool.hpp>
#include <TopoDS_Face.hpp>

BRepTopAdaptor_Tool::BRepTopAdaptor_Tool()
{
  myTopolTool = new BRepTopAdaptor_TopolTool();

  myloaded = false;
}

BRepTopAdaptor_Tool::BRepTopAdaptor_Tool(const TopoDS_Face& F, const double)
{
  myTopolTool = new BRepTopAdaptor_TopolTool();

  occ::handle<BRepAdaptor_Surface> surface = new BRepAdaptor_Surface();
  surface->Initialize(F, true);
  const occ::handle<Adaptor3d_Surface>& aSurf = surface;
  myTopolTool->Initialize(aSurf);
  myHSurface = surface;
  myloaded   = true;
}

BRepTopAdaptor_Tool::BRepTopAdaptor_Tool(const occ::handle<Adaptor3d_Surface>& surface,
                                         const double)
{
  myTopolTool = new BRepTopAdaptor_TopolTool();
  myTopolTool->Initialize(surface);
  myHSurface = surface;
  myloaded   = true;
}

void BRepTopAdaptor_Tool::Init(const TopoDS_Face& F, const double)
{
  occ::handle<BRepAdaptor_Surface> surface = new BRepAdaptor_Surface();
  surface->Initialize(F);
  const occ::handle<Adaptor3d_Surface>& aSurf = surface;
  myTopolTool->Initialize(aSurf);
  myHSurface = surface;
  myloaded   = true;
}

void BRepTopAdaptor_Tool::Init(const occ::handle<Adaptor3d_Surface>& surface, const double)
{
  myTopolTool->Initialize(surface);
  myHSurface = surface;
  myloaded   = true;
}

occ::handle<BRepTopAdaptor_TopolTool> BRepTopAdaptor_Tool::GetTopolTool()
{
  if (myloaded)
  {
    return (myTopolTool);
  }
  else
  {
#ifdef OCCT_DEBUG
    std::cout << "\n*** Error ds occ::handle<BRepTopAdaptor_TopolTool> "
                 "BRepTopAdaptor_Tool::GetTopolTool()\n"
              << std::endl;
#endif
    return (myTopolTool);
  }
}

occ::handle<Adaptor3d_Surface> BRepTopAdaptor_Tool::GetSurface()
{
  if (myloaded)
  {
    return (myHSurface);
  }
  else
  {
#ifdef OCCT_DEBUG
    std::cout
      << "\n*** Error ds occ::handle<BRepTopAdaptor_TopolTool> BRepTopAdaptor_Tool::GetSurface()\n"
      << std::endl;
#endif
    return (myHSurface);
  }
}

void BRepTopAdaptor_Tool::SetTopolTool(const occ::handle<BRepTopAdaptor_TopolTool>& TT)
{
  myTopolTool = TT;
}

void BRepTopAdaptor_Tool::Destroy() {}

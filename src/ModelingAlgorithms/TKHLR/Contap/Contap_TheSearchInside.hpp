#pragma once

#include <Adaptor3d_Surface.hpp>
#include <IntSurf_InteriorPoint.hpp>
#include <NCollection_Sequence.hpp>

class Adaptor3d_HSurfaceTool;
class Adaptor3d_TopolTool;
class Contap_HContTool;
class Contap_SurfFunction;
class IntSurf_InteriorPoint;

class Contap_TheSearchInside
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Contap_TheSearchInside();

  Standard_EXPORT Contap_TheSearchInside(Contap_SurfFunction&                    F,
                                         const occ::handle<Adaptor3d_Surface>&   Surf,
                                         const occ::handle<Adaptor3d_TopolTool>& T,
                                         const double                            Epsilon);

  Standard_EXPORT void Perform(Contap_SurfFunction&                    F,
                               const occ::handle<Adaptor3d_Surface>&   Surf,
                               const occ::handle<Adaptor3d_TopolTool>& T,
                               const double                            Epsilon);

  Standard_EXPORT void Perform(Contap_SurfFunction&                  F,
                               const occ::handle<Adaptor3d_Surface>& Surf,
                               const double                          UStart,
                               const double                          VStart);

  bool IsDone() const;

  int NbPoints() const;

  const IntSurf_InteriorPoint& Value(const int Index) const;

private:
  bool                                        done;
  NCollection_Sequence<IntSurf_InteriorPoint> list;
};

#define ThePSurface occ::handle<Adaptor3d_Surface>
#define ThePSurface_hxx <Adaptor3d_Surface.hpp>
#define ThePSurfaceTool Adaptor3d_HSurfaceTool
#define ThePSurfaceTool_hxx <Adaptor3d_HSurfaceTool.hpp>
#define Handle_TheTopolTool occ::handle<Adaptor3d_TopolTool>
#define TheTopolTool Adaptor3d_TopolTool
#define TheTopolTool_hxx <Adaptor3d_TopolTool.hpp>
#define TheSITool Contap_HContTool
#define TheSITool_hxx <Contap_HContTool.hpp>
#define TheFunction Contap_SurfFunction
#define TheFunction_hxx <Contap_SurfFunction.hpp>
#define IntStart_SearchInside Contap_TheSearchInside
#define IntStart_SearchInside_hxx <Contap_TheSearchInside.hpp>

#include <IntStart_SearchInside_1.hpp>

#undef ThePSurface
#undef ThePSurface_hxx
#undef ThePSurfaceTool
#undef ThePSurfaceTool_hxx
#undef Handle_TheTopolTool
#undef TheTopolTool
#undef TheTopolTool_hxx
#undef TheSITool
#undef TheSITool_hxx
#undef TheFunction
#undef TheFunction_hxx
#undef IntStart_SearchInside
#undef IntStart_SearchInside_hxx

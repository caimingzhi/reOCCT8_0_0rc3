#pragma once


#include <Adaptor3d_Surface.hpp>
#include <IntSurf_InteriorPoint.hpp>
#include <NCollection_Sequence.hpp>

class Adaptor3d_HSurfaceTool;
class Adaptor3d_TopolTool;
class IntPatch_HInterTool;
class IntPatch_TheSurfFunction;

class IntPatch_TheSearchInside
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntPatch_TheSearchInside();

  Standard_EXPORT IntPatch_TheSearchInside(IntPatch_TheSurfFunction&               F,
                                           const occ::handle<Adaptor3d_Surface>&   Surf,
                                           const occ::handle<Adaptor3d_TopolTool>& T,
                                           const double                            Epsilon);

  Standard_EXPORT void Perform(IntPatch_TheSurfFunction&               F,
                               const occ::handle<Adaptor3d_Surface>&   Surf,
                               const occ::handle<Adaptor3d_TopolTool>& T,
                               const double                            Epsilon);

  Standard_EXPORT void Perform(IntPatch_TheSurfFunction&             F,
                               const occ::handle<Adaptor3d_Surface>& Surf,
                               const double                          UStart,
                               const double                          VStart);

  bool IsDone() const;

  //! Returns the number of points.
  //! The exception NotDone if raised if IsDone
  //! returns False.
  int NbPoints() const;

  //! Returns the point of range Index.
  //! The exception NotDone if raised if IsDone
  //! returns False.
  //! The exception OutOfRange if raised if
  //! Index <= 0 or Index > NbPoints.
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
#define TheSITool IntPatch_HInterTool
#define TheSITool_hxx <IntPatch_HInterTool.hpp>
#define TheFunction IntPatch_TheSurfFunction
#define TheFunction_hxx <IntPatch_TheSurfFunction.hpp>
#define IntStart_SearchInside IntPatch_TheSearchInside
#define IntStart_SearchInside_hxx <IntPatch_TheSearchInside.hpp>

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


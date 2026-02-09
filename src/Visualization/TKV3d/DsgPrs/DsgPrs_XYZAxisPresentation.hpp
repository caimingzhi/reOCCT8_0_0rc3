#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Prs3d_Presentation.hpp>

class Prs3d_LineAspect;
class gp_Dir;
class gp_Pnt;
class Prs3d_ArrowAspect;
class Prs3d_TextAspect;

class DsgPrs_XYZAxisPresentation
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_LineAspect>&   anLineAspect,
                                  const gp_Dir&                          aDir,
                                  const double                           aVal,
                                  const char*                            aText,
                                  const gp_Pnt&                          aPfirst,
                                  const gp_Pnt&                          aPlast);

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_LineAspect>&   aLineAspect,
                                  const occ::handle<Prs3d_ArrowAspect>&  anArrowAspect,
                                  const occ::handle<Prs3d_TextAspect>&   aTextAspect,
                                  const gp_Dir&                          aDir,
                                  const double                           aVal,
                                  const char*                            aText,
                                  const gp_Pnt&                          aPfirst,
                                  const gp_Pnt&                          aPlast);
};

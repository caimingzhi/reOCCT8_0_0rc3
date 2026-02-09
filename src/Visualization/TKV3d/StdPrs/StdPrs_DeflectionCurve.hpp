#pragma once

#include <Prs3d_Root.hpp>
#include <Prs3d_Drawer.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Sequence.hpp>

class Adaptor3d_Curve;

class StdPrs_DeflectionCurve : public Prs3d_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  Adaptor3d_Curve&                       aCurve,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const bool                             drawCurve = true);

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  Adaptor3d_Curve&                       aCurve,
                                  const double                           U1,
                                  const double                           U2,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const bool                             drawCurve = true);

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  Adaptor3d_Curve&                       aCurve,
                                  const double                           aDeflection,
                                  const double                           aLimit,
                                  const double                           anAngle   = 0.2,
                                  const bool                             drawCurve = true);

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  Adaptor3d_Curve&                       aCurve,
                                  const double                           aDeflection,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  NCollection_Sequence<gp_Pnt>&          Points,
                                  const bool                             drawCurve = true);

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  Adaptor3d_Curve&                       aCurve,
                                  const double                           U1,
                                  const double                           U2,
                                  const double                           aDeflection,
                                  NCollection_Sequence<gp_Pnt>&          Points,
                                  const double                           anAngle   = 0.2,
                                  const bool                             drawCurve = true);

  Standard_EXPORT static bool Match(const double                     X,
                                    const double                     Y,
                                    const double                     Z,
                                    const double                     aDistance,
                                    const Adaptor3d_Curve&           aCurve,
                                    const occ::handle<Prs3d_Drawer>& aDrawer);

  Standard_EXPORT static bool Match(const double                     X,
                                    const double                     Y,
                                    const double                     Z,
                                    const double                     aDistance,
                                    const Adaptor3d_Curve&           aCurve,
                                    const double                     U1,
                                    const double                     U2,
                                    const occ::handle<Prs3d_Drawer>& aDrawer);

  Standard_EXPORT static bool Match(const double           theX,
                                    const double           theY,
                                    const double           theZ,
                                    const double           theDistance,
                                    const Adaptor3d_Curve& theCurve,
                                    const double           theDeflection,
                                    const double           theLimit,
                                    const double           theAngle);

  Standard_EXPORT static bool Match(const double           theX,
                                    const double           theY,
                                    const double           theZ,
                                    const double           theDistance,
                                    const Adaptor3d_Curve& theCurve,
                                    const double           theU1,
                                    const double           theU2,
                                    const double           theDeflection,
                                    const double           theAngle);
};

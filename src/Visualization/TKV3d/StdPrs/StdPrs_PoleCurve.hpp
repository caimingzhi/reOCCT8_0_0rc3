#pragma once

#include <Prs3d_Root.hpp>
#include <Prs3d_Drawer.hpp>

class Adaptor3d_Curve;

class StdPrs_PoleCurve : public Prs3d_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const Adaptor3d_Curve&                 aCurve,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer);

  Standard_EXPORT static bool Match(const double                     X,
                                    const double                     Y,
                                    const double                     Z,
                                    const double                     aDistance,
                                    const Adaptor3d_Curve&           aCurve,
                                    const occ::handle<Prs3d_Drawer>& aDrawer);

  Standard_EXPORT static int Pick(const double                     X,
                                  const double                     Y,
                                  const double                     Z,
                                  const double                     aDistance,
                                  const Adaptor3d_Curve&           aCurve,
                                  const occ::handle<Prs3d_Drawer>& aDrawer);
};

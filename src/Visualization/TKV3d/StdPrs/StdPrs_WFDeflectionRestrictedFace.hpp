#pragma once

#include <BRepAdaptor_Surface.hpp>
#include <Prs3d_Root.hpp>
#include <Prs3d_Drawer.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <NCollection_List.hpp>

class StdPrs_WFDeflectionRestrictedFace : public Prs3d_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>&  aPresentation,
                                  const occ::handle<BRepAdaptor_Surface>& aFace,
                                  const occ::handle<Prs3d_Drawer>&        aDrawer);

  Standard_EXPORT static void AddUIso(const occ::handle<Prs3d_Presentation>&  aPresentation,
                                      const occ::handle<BRepAdaptor_Surface>& aFace,
                                      const occ::handle<Prs3d_Drawer>&        aDrawer);

  Standard_EXPORT static void AddVIso(const occ::handle<Prs3d_Presentation>&  aPresentation,
                                      const occ::handle<BRepAdaptor_Surface>& aFace,
                                      const occ::handle<Prs3d_Drawer>&        aDrawer);

  Standard_EXPORT static void Add(
    const occ::handle<Prs3d_Presentation>&                        aPresentation,
    const occ::handle<BRepAdaptor_Surface>&                       aFace,
    const bool                                                    DrawUIso,
    const bool                                                    DrawVIso,
    const double                                                  Deflection,
    const int                                                     NBUiso,
    const int                                                     NBViso,
    const occ::handle<Prs3d_Drawer>&                              aDrawer,
    NCollection_List<occ::handle<NCollection_HSequence<gp_Pnt>>>& Curves);

  Standard_EXPORT static bool Match(const double                            X,
                                    const double                            Y,
                                    const double                            Z,
                                    const double                            aDistance,
                                    const occ::handle<BRepAdaptor_Surface>& aFace,
                                    const occ::handle<Prs3d_Drawer>&        aDrawer);

  Standard_EXPORT static bool MatchUIso(const double                            X,
                                        const double                            Y,
                                        const double                            Z,
                                        const double                            aDistance,
                                        const occ::handle<BRepAdaptor_Surface>& aFace,
                                        const occ::handle<Prs3d_Drawer>&        aDrawer);

  Standard_EXPORT static bool MatchVIso(const double                            X,
                                        const double                            Y,
                                        const double                            Z,
                                        const double                            aDistance,
                                        const occ::handle<BRepAdaptor_Surface>& aFace,
                                        const occ::handle<Prs3d_Drawer>&        aDrawer);

  Standard_EXPORT static bool Match(const double                            X,
                                    const double                            Y,
                                    const double                            Z,
                                    const double                            aDistance,
                                    const occ::handle<BRepAdaptor_Surface>& aFace,
                                    const occ::handle<Prs3d_Drawer>&        aDrawer,
                                    const bool                              DrawUIso,
                                    const bool                              DrawVIso,
                                    const double                            aDeflection,
                                    const int                               NBUiso,
                                    const int                               NBViso);
};

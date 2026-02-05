#pragma once

#include <BRepAdaptor_Surface.hpp>
#include <Prs3d_Drawer.hpp>
#include <Prs3d_Root.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <NCollection_List.hpp>

// Computes the wireframe presentation of faces with
// restrictions by displaying a given number of U and/or
// V isoparametric curves. The isoparametric curves are
// drawn with a fixed number of points.
// The presentation includes the restriction curves.

class StdPrs_WFRestrictedFace : public Prs3d_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Add(
    const occ::handle<Prs3d_Presentation>&                        thePresentation,
    const occ::handle<BRepAdaptor_Surface>&                       theFace,
    const bool                                                    theDrawUIso,
    const bool                                                    theDrawVIso,
    const int                                                     theNbUIso,
    const int                                                     theNbVIso,
    const occ::handle<Prs3d_Drawer>&                              theDrawer,
    NCollection_List<occ::handle<NCollection_HSequence<gp_Pnt>>>& theCurves);

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>&  thePresentation,
                                  const occ::handle<BRepAdaptor_Surface>& theFace,
                                  const occ::handle<Prs3d_Drawer>&        theDrawer);

  Standard_EXPORT static bool Match(const double                            theX,
                                    const double                            theY,
                                    const double                            theZ,
                                    const double                            theDistance,
                                    const occ::handle<BRepAdaptor_Surface>& theFace,
                                    const bool                              theDrawUIso,
                                    const bool                              theDrawVIso,
                                    const double                            theDeflection,
                                    const int                               theNbUIso,
                                    const int                               theNbVIso,
                                    const occ::handle<Prs3d_Drawer>&        theDrawer);

  Standard_EXPORT static bool Match(const double                            theX,
                                    const double                            theY,
                                    const double                            theZ,
                                    const double                            theDistance,
                                    const occ::handle<BRepAdaptor_Surface>& theFace,
                                    const occ::handle<Prs3d_Drawer>&        theDrawer);

  Standard_EXPORT static bool MatchUIso(const double                            theX,
                                        const double                            theY,
                                        const double                            theZ,
                                        const double                            theDistance,
                                        const occ::handle<BRepAdaptor_Surface>& theFace,
                                        const occ::handle<Prs3d_Drawer>&        theDrawer);

  Standard_EXPORT static bool MatchVIso(const double                            theX,
                                        const double                            theY,
                                        const double                            theZ,
                                        const double                            theDistance,
                                        const occ::handle<BRepAdaptor_Surface>& theFace,
                                        const occ::handle<Prs3d_Drawer>&        theDrawer);

  Standard_EXPORT static void AddUIso(const occ::handle<Prs3d_Presentation>&  thePresentation,
                                      const occ::handle<BRepAdaptor_Surface>& theFace,
                                      const occ::handle<Prs3d_Drawer>&        theDrawer);

  Standard_EXPORT static void AddVIso(const occ::handle<Prs3d_Presentation>&  thePresentation,
                                      const occ::handle<BRepAdaptor_Surface>& theFace,
                                      const occ::handle<Prs3d_Drawer>&        theDrawer);
};

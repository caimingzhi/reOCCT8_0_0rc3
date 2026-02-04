#pragma once


#include <BRepAdaptor_Surface.hpp>
#include <Prs3d_Root.hpp>
#include <Prs3d_Drawer.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <NCollection_List.hpp>

//! A framework to provide display of U and V
//! isoparameters of faces, while allowing you to impose
//! a deflection on them.
//! Computes the wireframe presentation of faces with
//! restrictions by displaying a given number of U and/or
//! V isoparametric curves. The isoparametric curves are
//! drawn with respect to a maximal chordial deviation.
//! The presentation includes the restriction curves.
class StdPrs_WFDeflectionRestrictedFace : public Prs3d_Root
{
public:
  DEFINE_STANDARD_ALLOC

  //! Defines a display featuring U and V isoparameters.
  //! Adds the surface aFace to the
  //! StdPrs_WFRestrictedFace algorithm. This face is
  //! found in a shape in the presentation object
  //! aPresentation, and its display attributes - in
  //! particular, the number of U and V isoparameters - are
  //! set in the attribute manager aDrawer.
  //! aFace is BRepAdaptor_Surface surface created
  //! from a face in a topological shape. which is passed
  //! as an argument through the
  //! BRepAdaptor_Surface surface created from it.
  //! This is what allows the topological face to be treated
  //! as a geometric surface.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>&  aPresentation,
                                  const occ::handle<BRepAdaptor_Surface>& aFace,
                                  const occ::handle<Prs3d_Drawer>&        aDrawer);

  //! Defines a display featuring U isoparameters
  //! respectively. Add the surface aFace to the
  //! StdPrs_WFRestrictedFace algorithm. This face
  //! is found in a shape in the presentation object
  //! aPresentation, and its display attributes - in
  //! particular, the number of U isoparameters -
  //! are set in the attribute manager aDrawer.
  //! aFace is BRepAdaptor_Surface surface
  //! created from a face in a topological shape. which
  //! is passed to the function as an argument through
  //! the BRepAdaptor_Surface surface created from
  //! it. This is what allows the topological face to be
  //! treated as a geometric surface.
  Standard_EXPORT static void AddUIso(const occ::handle<Prs3d_Presentation>&  aPresentation,
                                      const occ::handle<BRepAdaptor_Surface>& aFace,
                                      const occ::handle<Prs3d_Drawer>&        aDrawer);

  //! Defines a display featuring V isoparameters
  //! respectively. Add the surface aFace to the
  //! StdPrs_WFRestrictedFace algorithm. This face
  //! is found in a shape in the presentation object
  //! aPresentation, and its display attributes - in
  //! particular, the number of V isoparameters -
  //! are set in the attribute manager aDrawer.
  //! aFace is BRepAdaptor_Surface surface
  //! created from a face in a topological shape. which
  //! is passed to the function as an argument through
  //! the BRepAdaptor_Surface surface created from
  //! it. This is what allows the topological face to be
  //! treated as a geometric surface.
  Standard_EXPORT static void AddVIso(const occ::handle<Prs3d_Presentation>&  aPresentation,
                                      const occ::handle<BRepAdaptor_Surface>& aFace,
                                      const occ::handle<Prs3d_Drawer>&        aDrawer);

  //! Defines a display of a delection-specified face. The
  //! display will feature U and V isoparameters.
  //! Adds the topology aShape to the
  //! StdPrs_WFRestrictedFace algorithm. This shape is
  //! found in the presentation object aPresentation, and
  //! its display attributes - except the number of U and V
  //! isoparameters - are set in the attribute manager aDrawer.
  //! The function sets the number of U and V
  //! isoparameters, NBUiso and NBViso, in the shape. To
  //! do this, the arguments DrawUIso and DrawVIso must be true.
  //! aFace is BRepAdaptor_Surface surface created
  //! from a face in a topological shape. which is passed
  //! as an argument through the
  //! BRepAdaptor_Surface surface created from it.
  //! This is what allows the topological face to be treated
  //! as a geometric surface.
  //! Curves give a sequence of face curves, it is used if the PrimitiveArray
  //! visualization approach is activated (it is activated by default).
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


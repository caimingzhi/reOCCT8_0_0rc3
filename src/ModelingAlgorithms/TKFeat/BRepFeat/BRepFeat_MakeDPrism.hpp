#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Real.hpp>
#include <BRepFeat_StatusError.hpp>
#include <BRepFeat_Form.hpp>
#include <Standard_Integer.hpp>
class Geom_Curve;
class TopoDS_Shape;
class TopoDS_Edge;

//! Describes functions to build draft
//! prism topologies from basis shape surfaces. These can be depressions or protrusions.
//! The semantics of draft prism feature creation is based on the
//! construction of shapes:
//! -          along a length
//! -          up to a limiting face
//! -          from a limiting face to a height.
//! The shape defining construction of the draft prism feature can be
//! either the supporting edge or the concerned area of a face.
//! In case of the supporting edge, this contour can be attached to a
//! face of the basis shape by binding. When the contour is bound to this
//! face, the information that the contour will slide on the face
//! becomes available to the relevant class methods.
//! In case of the concerned area of a face, you could, for example, cut
//! it out and move it to a different height which will define the
//! limiting face of a protrusion or depression.
class BRepFeat_MakeDPrism : public BRepFeat_Form
{
public:
  DEFINE_STANDARD_ALLOC

  //! A face Pbase is selected in the shape
  //! Sbase to serve as the basis for the draft prism. The
  //! draft will be defined by the angle Angle and Fuse offers a choice between:
  //! - removing matter with a Boolean cut using the setting 0
  //! - adding matter with Boolean fusion using the setting 1.
  //! The sketch face Skface serves to determine the type of
  //! operation. If it is inside the basis shape, a local
  //! operation such as glueing can be performed.
  //! Initializes the draft prism class
  BRepFeat_MakeDPrism(const TopoDS_Shape& Sbase,
                      const TopoDS_Face&  Pbase,
                      const TopoDS_Face&  Skface,
                      const double        Angle,
                      const int           Fuse,
                      const bool          Modify)
  {
    Init(Sbase, Pbase, Skface, Angle, Fuse, Modify);
  }

  BRepFeat_MakeDPrism()
      : myAngle(RealLast()),
        myStatusError(BRepFeat_OK)
  {
  }

  //! Initializes this algorithm for building draft prisms along surfaces.
  //! A face Pbase is selected in the basis shape Sbase to
  //! serve as the basis from the draft prism. The draft will be
  //! defined by the angle Angle and Fuse offers a choice between:
  //! -   removing matter with a Boolean cut using the setting 0
  //! -   adding matter with Boolean fusion using the setting 1.
  //! The sketch face Skface serves to determine the type of
  //! operation. If it is inside the basis shape, a local
  //! operation such as glueing can be performed.
  Standard_EXPORT void Init(const TopoDS_Shape& Sbase,
                            const TopoDS_Face&  Pbase,
                            const TopoDS_Face&  Skface,
                            const double        Angle,
                            const int           Fuse,
                            const bool          Modify);

  //! Indicates that the edge <E> will slide on the face
  //! <OnFace>.
  //! Raises ConstructionError if the face does not belong to the
  //! basis shape, or the edge to the prismed shape.
  Standard_EXPORT void Add(const TopoDS_Edge& E, const TopoDS_Face& OnFace);

  Standard_EXPORT void Perform(const double Height);

  Standard_EXPORT void Perform(const TopoDS_Shape& Until);

  //! Assigns one of the following semantics
  //! -   to a height Height
  //! -   to a face Until
  //! -   from a face From to a height Until.
  //! Reconstructs the feature topologically according to the semantic option chosen.
  Standard_EXPORT void Perform(const TopoDS_Shape& From, const TopoDS_Shape& Until);

  //! Realizes a semi-infinite prism, limited by the position of the prism base.
  Standard_EXPORT void PerformUntilEnd();

  //! Realizes a semi-infinite prism, limited by the face Funtil.
  Standard_EXPORT void PerformFromEnd(const TopoDS_Shape& FUntil);

  //! Builds an infinite prism. The infinite descendants will not be kept in the result.
  Standard_EXPORT void PerformThruAll();

  //! Assigns both a limiting shape, Until from
  //! TopoDS_Shape, and a height, Height at which to stop
  //! generation of the prism feature.
  Standard_EXPORT void PerformUntilHeight(const TopoDS_Shape& Until, const double Height);

  Standard_EXPORT void Curves(NCollection_Sequence<occ::handle<Geom_Curve>>& S) override;

  Standard_EXPORT occ::handle<Geom_Curve> BarycCurve() override;

  //! Determination of TopEdges and LatEdges.
  //! sig = 1 -> TopEdges = FirstShape of the DPrism
  //! sig = 2 -> TOpEdges = LastShape of the DPrism
  Standard_EXPORT void BossEdges(const int sig);

  //! Returns the list of TopoDS Edges of the top of the boss.
  Standard_EXPORT const NCollection_List<TopoDS_Shape>& TopEdges();

  //! Returns the list of TopoDS Edges of the bottom of the boss.
  Standard_EXPORT const NCollection_List<TopoDS_Shape>& LatEdges();

private:
  TopoDS_Face myPbase;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                                mySlface;
  double                                        myAngle;
  NCollection_Sequence<occ::handle<Geom_Curve>> myCurves;
  occ::handle<Geom_Curve>                       myBCurve;
  NCollection_List<TopoDS_Shape>                myTopEdges;
  NCollection_List<TopoDS_Shape>                myLatEdges;
  BRepFeat_StatusError                          myStatusError;
};


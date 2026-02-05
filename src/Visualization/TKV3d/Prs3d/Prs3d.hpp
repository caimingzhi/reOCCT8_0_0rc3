#pragma once

#include <Graphic3d_ArrayOfPrimitives.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Prs3d_Drawer.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <NCollection_List.hpp>
#include <Prs3d_Presentation.hpp>

class Poly_Triangulation;

//! The Prs3d package provides the following services
//! -   a presentation object (the context for all
//! modifications to the display, its presentation will be
//! displayed in every view of an active viewer)
//! -   an attribute manager governing how objects such
//! as color, width, and type of line are displayed;
//! these are generic objects, whereas those in
//! StdPrs are specific geometries and topologies.
//! -   generic algorithms providing default settings for
//! objects such as points, curves, surfaces and shapes
//! -   a root object which provides the abstract
//! framework for the DsgPrs definitions at work in
//! display of dimensions, relations and trihedra.
class Prs3d
{
public:
  DEFINE_STANDARD_ALLOC

  //! draws an arrow at a given location, with respect
  //! to a given direction.
  Standard_EXPORT static bool MatchSegment(const double  X,
                                           const double  Y,
                                           const double  Z,
                                           const double  aDistance,
                                           const gp_Pnt& p1,
                                           const gp_Pnt& p2,
                                           double&       dist);

  //! Computes the absolute deflection value based on relative deflection
  //! Prs3d_Drawer::DeviationCoefficient().
  //! @param[in] theBndMin  bounding box min corner
  //! @param[in] theBndMax  bounding box max corner
  //! @param[in] theDeviationCoefficient  relative deflection coefficient from
  //! Prs3d_Drawer::DeviationCoefficient()
  //! @return absolute deflection coefficient based on bounding box dimensions
  static double GetDeflection(const NCollection_Vec3<double>& theBndMin,
                              const NCollection_Vec3<double>& theBndMax,
                              const double                    theDeviationCoefficient)
  {
    const NCollection_Vec3<double> aDiag = theBndMax - theBndMin;
    return (std::max)(aDiag.maxComp() * theDeviationCoefficient * 4.0, Precision::Confusion());
  }

  //! Computes the absolute deflection value based on relative deflection
  //! Prs3d_Drawer::DeviationCoefficient().
  //! @param[in] theBndBox  bounding box
  //! @param[in] theDeviationCoefficient  relative deflection coefficient from
  //! Prs3d_Drawer::DeviationCoefficient()
  //! @param[in] theMaximalChordialDeviation  absolute deflection coefficient from
  //! Prs3d_Drawer::MaximalChordialDeviation()
  //! @return absolute deflection coefficient based on bounding box dimensions or
  //! theMaximalChordialDeviation if bounding box is Void or Infinite
  static double GetDeflection(const Bnd_Box& theBndBox,
                              const double   theDeviationCoefficient,
                              const double   theMaximalChordialDeviation)
  {
    if (theBndBox.IsVoid())
    {
      return theMaximalChordialDeviation;
    }

    Bnd_Box aBndBox = theBndBox;
    if (theBndBox.IsOpen())
    {
      if (!theBndBox.HasFinitePart())
      {
        return theMaximalChordialDeviation;
      }
      aBndBox = theBndBox.FinitePart();
    }

    NCollection_Vec3<double> aVecMin, aVecMax;
    aBndBox.Get(aVecMin.x(), aVecMin.y(), aVecMin.z(), aVecMax.x(), aVecMax.y(), aVecMax.z());
    return GetDeflection(aVecMin, aVecMax, theDeviationCoefficient);
  }

  //! Assembles array of primitives for sequence of polylines.
  //! @param[in] thePoints  the polylines sequence
  //! @return array of primitives
  Standard_EXPORT static occ::handle<Graphic3d_ArrayOfPrimitives> PrimitivesFromPolylines(
    const NCollection_List<occ::handle<NCollection_HSequence<gp_Pnt>>>& thePoints);

  //! Add primitives into new group in presentation and clear the list of polylines.
  Standard_EXPORT static void AddPrimitivesGroup(
    const occ::handle<Prs3d_Presentation>&                        thePrs,
    const occ::handle<Prs3d_LineAspect>&                          theAspect,
    NCollection_List<occ::handle<NCollection_HSequence<gp_Pnt>>>& thePolylines);

  //! Add triangulation free edges into sequence of line segments.
  //! @param[out] theSegments  sequence of line segments to fill
  //! @param[in] thePolyTri    triangulation to process
  //! @param[in] theLocation   transformation to apply
  Standard_EXPORT static void AddFreeEdges(NCollection_Sequence<gp_Pnt>&          theSegments,
                                           const occ::handle<Poly_Triangulation>& thePolyTri,
                                           const gp_Trsf&                         theLocation);
};

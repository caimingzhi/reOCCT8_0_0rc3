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

class Prs3d
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static bool MatchSegment(const double  X,
                                           const double  Y,
                                           const double  Z,
                                           const double  aDistance,
                                           const gp_Pnt& p1,
                                           const gp_Pnt& p2,
                                           double&       dist);

  static double GetDeflection(const NCollection_Vec3<double>& theBndMin,
                              const NCollection_Vec3<double>& theBndMax,
                              const double                    theDeviationCoefficient)
  {
    const NCollection_Vec3<double> aDiag = theBndMax - theBndMin;
    return (std::max)(aDiag.maxComp() * theDeviationCoefficient * 4.0, Precision::Confusion());
  }

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

  Standard_EXPORT static occ::handle<Graphic3d_ArrayOfPrimitives> PrimitivesFromPolylines(
    const NCollection_List<occ::handle<NCollection_HSequence<gp_Pnt>>>& thePoints);

  Standard_EXPORT static void AddPrimitivesGroup(
    const occ::handle<Prs3d_Presentation>&                        thePrs,
    const occ::handle<Prs3d_LineAspect>&                          theAspect,
    NCollection_List<occ::handle<NCollection_HSequence<gp_Pnt>>>& thePolylines);

  Standard_EXPORT static void AddFreeEdges(NCollection_Sequence<gp_Pnt>&          theSegments,
                                           const occ::handle<Poly_Triangulation>& thePolyTri,
                                           const gp_Trsf&                         theLocation);
};

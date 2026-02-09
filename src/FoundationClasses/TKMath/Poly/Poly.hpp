#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <Poly_Triangulation.hpp>
#include <Standard_OStream.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_IStream.hpp>
#include <Standard_Real.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Sequence.hpp>

class Poly_Triangulation;
class Poly_Polygon3D;
class Poly_Polygon2D;
class Poly_Triangle;

class Poly
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<Poly_Triangulation> Catenate(
    const NCollection_List<occ::handle<Poly_Triangulation>>& lstTri);

  Standard_EXPORT static void Write(const occ::handle<Poly_Triangulation>& T,
                                    Standard_OStream&                      OS,
                                    const bool                             Compact = true);

  Standard_EXPORT static void Write(const occ::handle<Poly_Polygon3D>& P,
                                    Standard_OStream&                  OS,
                                    const bool                         Compact = true);

  Standard_EXPORT static void Write(const occ::handle<Poly_Polygon2D>& P,
                                    Standard_OStream&                  OS,
                                    const bool                         Compact = true);

  Standard_EXPORT static void Dump(const occ::handle<Poly_Triangulation>& T, Standard_OStream& OS);

  Standard_EXPORT static void Dump(const occ::handle<Poly_Polygon3D>& P, Standard_OStream& OS);

  Standard_EXPORT static void Dump(const occ::handle<Poly_Polygon2D>& P, Standard_OStream& OS);

  Standard_EXPORT static occ::handle<Poly_Triangulation> ReadTriangulation(Standard_IStream& IS);

  Standard_EXPORT static occ::handle<Poly_Polygon3D> ReadPolygon3D(Standard_IStream& IS);

  Standard_EXPORT static occ::handle<Poly_Polygon2D> ReadPolygon2D(Standard_IStream& IS);

  Standard_EXPORT static void ComputeNormals(const occ::handle<Poly_Triangulation>& Tri);

  Standard_EXPORT static double PointOnTriangle(const gp_XY& P1,
                                                const gp_XY& P2,
                                                const gp_XY& P3,
                                                const gp_XY& P,
                                                gp_XY&       UV);

  Standard_EXPORT static bool Intersect(const occ::handle<Poly_Triangulation>& theTri,
                                        const gp_Ax1&                          theAxis,
                                        const bool                             theIsClosest,
                                        Poly_Triangle&                         theTriangle,
                                        double&                                theDistance);

  Standard_EXPORT static int IntersectTriLine(const gp_XYZ& theStart,
                                              const gp_Dir& theDir,
                                              const gp_XYZ& theV0,
                                              const gp_XYZ& theV1,
                                              const gp_XYZ& theV2,
                                              double&       theParam);

  template <class TypeSequencePnts>
  Standard_EXPORT static bool PolygonProperties(const TypeSequencePnts& theSeqPnts,
                                                double&                 theArea,
                                                double&                 thePerimeter)
  {
    if (theSeqPnts.Length() < 2)
    {
      theArea = thePerimeter = 0.0;
      return true;
    }

    int          aStartIndex = theSeqPnts.Lower();
    const gp_XY& aRefPnt     = theSeqPnts.Value(aStartIndex++).XY();
    gp_XY        aPrevPt     = theSeqPnts.Value(aStartIndex++).XY() - aRefPnt, aCurrPt;

    theArea      = 0.0;
    thePerimeter = aPrevPt.Modulus();

    for (int i = aStartIndex; i <= theSeqPnts.Upper(); i++)
    {
      aCurrPt             = theSeqPnts.Value(i).XY() - aRefPnt;
      const double aDelta = aPrevPt.Crossed(aCurrPt);

      theArea += aDelta;
      thePerimeter += (aPrevPt - aCurrPt).Modulus();
      aPrevPt = aCurrPt;
    }

    thePerimeter += aPrevPt.Modulus();
    theArea *= 0.5;
    return true;
  }
};

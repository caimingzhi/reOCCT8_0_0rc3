#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopAbs_Orientation.hpp>
#include <Standard_Boolean.hpp>
#include <ChFiDS_TypeOfConcavity.hpp>
#include <GeomAbs_Shape.hpp>
class BRepAdaptor_Surface;
class TopoDS_Edge;
class TopoDS_Face;

class ChFi3d
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static ChFiDS_TypeOfConcavity DefineConnectType(const TopoDS_Edge& E,
                                                                  const TopoDS_Face& F1,
                                                                  const TopoDS_Face& F2,
                                                                  const double       SinTol,
                                                                  const bool         CorrectPoint);

  Standard_EXPORT static bool IsTangentFaces(const TopoDS_Edge&  theEdge,
                                             const TopoDS_Face&  theFace1,
                                             const TopoDS_Face&  theFace2,
                                             const GeomAbs_Shape Order = GeomAbs_G1);

  Standard_EXPORT static int ConcaveSide(const BRepAdaptor_Surface& S1,
                                         const BRepAdaptor_Surface& S2,
                                         const TopoDS_Edge&         E,
                                         TopAbs_Orientation&        Or1,
                                         TopAbs_Orientation&        Or2);

  Standard_EXPORT static int NextSide(TopAbs_Orientation&      Or1,
                                      TopAbs_Orientation&      Or2,
                                      const TopAbs_Orientation OrSave1,
                                      const TopAbs_Orientation OrSave2,
                                      const int                ChoixSauv);

  Standard_EXPORT static void NextSide(TopAbs_Orientation&      Or,
                                       const TopAbs_Orientation OrSave,
                                       const TopAbs_Orientation OrFace);

  Standard_EXPORT static bool SameSide(const TopAbs_Orientation Or,
                                       const TopAbs_Orientation OrSave1,
                                       const TopAbs_Orientation OrSave2,
                                       const TopAbs_Orientation OrFace1,
                                       const TopAbs_Orientation OrFace2);
};

#pragma once

#include <GProp_GProps.hpp>
#include <TopAbs_Orientation.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>

class Poly_Triangulation;
class TopLoc_Location;

class BRepGProp_MeshProps : public GProp_GProps
{
public:
  DEFINE_STANDARD_ALLOC

  typedef enum
  {
    Vinert = 0,
    Sinert
  } BRepGProp_MeshObjType;

  BRepGProp_MeshProps(const BRepGProp_MeshObjType theType)
      : myType(theType)
  {
  }

  void SetLocation(const gp_Pnt& theLocation) { loc = theLocation; }

  Standard_EXPORT void Perform(const occ::handle<Poly_Triangulation>& theMesh,
                               const TopLoc_Location&                 theLoc,
                               const TopAbs_Orientation               theOri);

  Standard_EXPORT void Perform(const occ::handle<Poly_Triangulation>& theMesh,
                               const TopAbs_Orientation               theOri);

  Standard_EXPORT static void CalculateProps(const gp_Pnt& p1,
                                             const gp_Pnt& p2,
                                             const gp_Pnt& p3,
                                             const gp_Pnt& Apex,
                                             const bool    isVolume,
                                             double        GProps[10],
                                             const int     NbGaussPoints,
                                             const double* GaussPnts);

  BRepGProp_MeshObjType GetMeshObjType() const { return myType; }

private:
  BRepGProp_MeshObjType myType;
};

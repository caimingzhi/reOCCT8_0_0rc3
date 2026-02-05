#pragma once

#include <GProp_GProps.hpp>
#include <TopAbs_Orientation.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>

class Poly_Triangulation;
class TopLoc_Location;

//! Computes the global properties of a surface mesh. The mesh can be
//! interpreted as just a surface or as a piece of volume limited by this surface.
class BRepGProp_MeshProps : public GProp_GProps
{
public:
  DEFINE_STANDARD_ALLOC

  //! Describes types of geometric objects.
  //! - Vinert is 3D closed region of space delimited with
  //!   Point and surface mesh;
  //! - Sinert is surface mesh in 3D space.
  typedef enum
  {
    Vinert = 0,
    Sinert
  } BRepGProp_MeshObjType;

  //! Constructor takes the type of object.
  BRepGProp_MeshProps(const BRepGProp_MeshObjType theType)
      : myType(theType)
  {
  }

  //! Sets the point relative which the calculation is to be done
  void SetLocation(const gp_Pnt& theLocation) { loc = theLocation; }

  //! Computes the global properties of a surface mesh of 3D space.
  //! Calculation of surface properties is performed by numerical integration
  //! over triangle surfaces using Gauss cubature formulas.
  //! Depending on the mesh object type used in constructor this method can
  //! calculate the surface or volume properties of the mesh.
  Standard_EXPORT void Perform(const occ::handle<Poly_Triangulation>& theMesh,
                               const TopLoc_Location&                 theLoc,
                               const TopAbs_Orientation               theOri);

  Standard_EXPORT void Perform(const occ::handle<Poly_Triangulation>& theMesh,
                               const TopAbs_Orientation               theOri);

  //! Computes the global properties of triangle {p1, p2, p3} relatively
  //! point Apex
  //! If isVolume = true, volume properties are calculated
  //! otherwise - surface ones
  Standard_EXPORT static void CalculateProps(const gp_Pnt& p1,
                                             const gp_Pnt& p2,
                                             const gp_Pnt& p3,
                                             const gp_Pnt& Apex,
                                             const bool    isVolume,
                                             double        GProps[10],
                                             const int     NbGaussPoints,
                                             const double* GaussPnts);

  //! Get type of mesh object
  BRepGProp_MeshObjType GetMeshObjType() const { return myType; }

private:                        //! @name private fields
  BRepGProp_MeshObjType myType; //!< Type of geometric object
};

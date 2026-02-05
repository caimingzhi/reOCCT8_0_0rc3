#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <IFSelect_SelectExplore.hpp>
class Standard_Transient;
class Interface_Graph;
class Interface_EntityIterator;
class TCollection_AsciiString;
class IGESData_IGESEntity;

//! This selection returns the basic geometric elements
//! contained in an IGES Entity
//! Intended to run a "quick" transfer. I.E. :
//! - for a Group, considers its Elements
//! - for a Trimmed or Bounded Surface or a Face (BREP),
//! considers the 3D curves of each of its loops
//! - for a Plane (108), considers its Bounding Curve
//! - for a Curve itself, takes it
//!
//! Also, FREE surfaces are taken, because curve 3d is known for
//! them. (the ideal should be to have their natural bounds)
//!
//! If <curvesonly> is set, ONLY curves-3d are returned
class IGESSelect_SelectBasicGeom : public IFSelect_SelectExplore
{

public:
  //! Creates a SelectBasicGeom, which always works recursively
  //! mode = -1 : Returns Surfaces (without trimming)
  //! mode = +1 : Returns Curves 3D (free or bound of surface)
  //! mode = +2 : Returns Basic Curves 3D : as 1 but CompositeCurves
  //! are returned in detail
  //! mode = 0  : both
  Standard_EXPORT IGESSelect_SelectBasicGeom(const int mode);

  Standard_EXPORT bool CurvesOnly() const;

  //! Explores an entity, to take its contained Curves 3d
  //! Works recursively
  Standard_EXPORT bool Explore(const int                              level,
                               const occ::handle<Standard_Transient>& ent,
                               const Interface_Graph&                 G,
                               Interface_EntityIterator&              explored) const override;

  //! Returns a text defining the criterium : "Curves 3d" or
  //! "Basic Geometry"
  Standard_EXPORT TCollection_AsciiString ExploreLabel() const override;

  //! This method can be called from everywhere to get the curves
  //! as sub-elements of a given curve :
  //! CompositeCurve : explored lists its subs + returns True
  //! Any Curve : explored is not filled but returned is True
  //! Other : returned is False
  Standard_EXPORT static bool SubCurves(const occ::handle<IGESData_IGESEntity>& ent,
                                        Interface_EntityIterator&               explored);

  DEFINE_STANDARD_RTTIEXT(IGESSelect_SelectBasicGeom, IFSelect_SelectExplore)

private:
  int thegeom;
};

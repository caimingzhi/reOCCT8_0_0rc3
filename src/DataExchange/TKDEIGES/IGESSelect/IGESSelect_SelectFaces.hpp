#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectExplore.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class Interface_Graph;
class Interface_EntityIterator;
class TCollection_AsciiString;

//! This selection returns the faces contained in an IGES Entity
//! or itself if it is a Face
//! Face means :
//! - Face (510) of a ManifoldSolidBrep
//! - TrimmedSurface (144)
//! - BoundedSurface (143)
//! - Plane with a Bounding Curve (108, form not 0)
//! - Also, any Surface which is not in a TrimmedSurface, a
//! BoundedSurface, or a Face (FREE Surface)
//! -> i.e. a Face for which Natural Bounds will be considered
class IGESSelect_SelectFaces : public IFSelect_SelectExplore
{

public:
  Standard_EXPORT IGESSelect_SelectFaces();

  //! Explores an entity, to take its faces
  //! Works recursively
  Standard_EXPORT bool Explore(const int                              level,
                               const occ::handle<Standard_Transient>& ent,
                               const Interface_Graph&                 G,
                               Interface_EntityIterator&              explored) const override;

  //! Returns a text defining the criterium : "Faces"
  Standard_EXPORT TCollection_AsciiString ExploreLabel() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_SelectFaces, IFSelect_SelectExplore)
};


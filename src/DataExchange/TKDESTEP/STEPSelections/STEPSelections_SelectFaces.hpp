#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectExplore.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class Interface_Graph;
class Interface_EntityIterator;
class TCollection_AsciiString;

//! This selection returns "STEP faces"
class STEPSelections_SelectFaces : public IFSelect_SelectExplore
{

public:
  Standard_EXPORT STEPSelections_SelectFaces();

  //! Explores an entity, to take its faces
  //! Works recursively
  Standard_EXPORT bool Explore(const int                              level,
                               const occ::handle<Standard_Transient>& ent,
                               const Interface_Graph&                 G,
                               Interface_EntityIterator&              explored) const override;

  //! Returns a text defining the criterium : "Faces"
  Standard_EXPORT TCollection_AsciiString ExploreLabel() const override;

  DEFINE_STANDARD_RTTIEXT(STEPSelections_SelectFaces, IFSelect_SelectExplore)
};


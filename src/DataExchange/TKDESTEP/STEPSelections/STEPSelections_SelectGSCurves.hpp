#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectExplore.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class Interface_Graph;
class Interface_EntityIterator;
class TCollection_AsciiString;

//! This selection returns "curves in the geometric_set (except composite curves)"
class STEPSelections_SelectGSCurves : public IFSelect_SelectExplore
{

public:
  Standard_EXPORT STEPSelections_SelectGSCurves();

  Standard_EXPORT bool Explore(const int                              level,
                               const occ::handle<Standard_Transient>& ent,
                               const Interface_Graph&                 G,
                               Interface_EntityIterator&              explored) const override;

  //! Returns a text defining the criterium : "Curves"
  Standard_EXPORT TCollection_AsciiString ExploreLabel() const override;

  DEFINE_STANDARD_RTTIEXT(STEPSelections_SelectGSCurves, IFSelect_SelectExplore)
};

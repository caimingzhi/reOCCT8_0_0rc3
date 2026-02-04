#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectExplore.hpp>
#include <Standard_Integer.hpp>
class Interface_EntityIterator;
class Interface_Graph;
class Standard_Transient;
class TCollection_AsciiString;

class STEPSelections_SelectInstances : public IFSelect_SelectExplore
{

public:
  Standard_EXPORT STEPSelections_SelectInstances();

  Standard_EXPORT Interface_EntityIterator RootResult(const Interface_Graph& G) const override;

  Standard_EXPORT bool Explore(const int                              level,
                               const occ::handle<Standard_Transient>& ent,
                               const Interface_Graph&                 G,
                               Interface_EntityIterator&              explored) const override;

  //! Returns a text defining the criterium : "Instances"
  Standard_EXPORT TCollection_AsciiString ExploreLabel() const override;

  DEFINE_STANDARD_RTTIEXT(STEPSelections_SelectInstances, IFSelect_SelectExplore)

protected:
  Standard_EXPORT bool HasUniqueResult() const override;
};


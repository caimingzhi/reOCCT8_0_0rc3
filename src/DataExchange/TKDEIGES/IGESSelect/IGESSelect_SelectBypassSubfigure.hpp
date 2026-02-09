#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectExplore.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class Interface_Graph;
class Interface_EntityIterator;
class TCollection_AsciiString;

class IGESSelect_SelectBypassSubfigure : public IFSelect_SelectExplore
{

public:
  Standard_EXPORT IGESSelect_SelectBypassSubfigure(const int level = 0);

  Standard_EXPORT bool Explore(const int                              level,
                               const occ::handle<Standard_Transient>& ent,
                               const Interface_Graph&                 G,
                               Interface_EntityIterator&              explored) const override;

  Standard_EXPORT TCollection_AsciiString ExploreLabel() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_SelectBypassSubfigure, IFSelect_SelectExplore)
};

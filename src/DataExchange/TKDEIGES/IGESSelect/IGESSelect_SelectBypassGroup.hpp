#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectExplore.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class Interface_Graph;
class Interface_EntityIterator;
class TCollection_AsciiString;

//! Selects a list built as follows :
//! Groups are entities type 402, forms 1,7,14,15 (Group,
//! Ordered or not, "WithoutBackPointer" or not)
//!
//! Entities which are not GROUP are taken as such
//! For Groups, their list of Elements is explore
//! Hence, level 0 (D) recursively explores a Group if some of
//! its Elements are Groups. level 1 explores just at first level
class IGESSelect_SelectBypassGroup : public IFSelect_SelectExplore
{

public:
  //! Creates a SelectBypassGroup, by default all level
  //! (level = 1 explores at first level)
  Standard_EXPORT IGESSelect_SelectBypassGroup(const int level = 0);

  //! Explores an entity : for a Group, gives its elements
  //! Else, takes the entity itself
  Standard_EXPORT bool Explore(const int                              level,
                               const occ::handle<Standard_Transient>& ent,
                               const Interface_Graph&                 G,
                               Interface_EntityIterator&              explored) const override;

  //! Returns a text defining the criterium : "Content of Group"
  Standard_EXPORT TCollection_AsciiString ExploreLabel() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_SelectBypassGroup, IFSelect_SelectExplore)
};


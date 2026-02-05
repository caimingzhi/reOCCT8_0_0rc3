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
//! Subfigures correspond to
//! * Definition (basic : type 308, or Network : type 320)
//! * Instance (Singular : type 408, or Network : 420, or
//! patterns : 412,414)
//!
//! Entities which are not Subfigure are taken as such
//! For Subfigures Instances, their definition is taken, then
//! explored itself
//! For Subfigures Definitions, the list of "Associated Entities"
//! is explored
//! Hence, level 0 (D) recursively explores a Subfigure if some of
//! its Elements are Subfigures. level 1 explores just at first
//! level (i.e. for an instance, returns its definition)
class IGESSelect_SelectBypassSubfigure : public IFSelect_SelectExplore
{

public:
  //! Creates a SelectBypassSubfigure, by default all level
  //! (level = 1 explores at first level)
  Standard_EXPORT IGESSelect_SelectBypassSubfigure(const int level = 0);

  //! Explores an entity : for a Subfigure, gives its elements
  //! Else, takes the entity itself
  Standard_EXPORT bool Explore(const int                              level,
                               const occ::handle<Standard_Transient>& ent,
                               const Interface_Graph&                 G,
                               Interface_EntityIterator&              explored) const override;

  //! Returns a text defining the criterium : "Content of Subfigure"
  Standard_EXPORT TCollection_AsciiString ExploreLabel() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_SelectBypassSubfigure, IFSelect_SelectExplore)
};

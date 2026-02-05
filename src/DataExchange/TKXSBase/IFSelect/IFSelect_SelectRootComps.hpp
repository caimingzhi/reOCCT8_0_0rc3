#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectExtract.hpp>
#include <Standard_Integer.hpp>
class Interface_EntityIterator;
class Interface_Graph;
class Standard_Transient;
class Interface_InterfaceModel;
class TCollection_AsciiString;

//! A SelectRootComps sorts the Entities which are part of Strong
//! Components, local roots of a set of Entities : they can be
//! Single Components (containing one Entity) or Cycles
//! This class gives a more secure result than SelectRoots (which
//! considers only Single Components) but is longer to work : it
//! can be used when there can be or there are cycles in a Model
//! For each cycle, one Entity is given arbitrarily
//! Reject works as for SelectRoots : Strong Components defined in
//! the input list which are not local roots are given
class IFSelect_SelectRootComps : public IFSelect_SelectExtract
{

public:
  //! Creates a SelectRootComps
  Standard_EXPORT IFSelect_SelectRootComps();

  //! Returns the list of local root strong components, by one Entity per component.
  //! It is redefined for a purpose of efficiency : calling a Sort routine for each Entity would
  //! cost more resources than to work in once using a Map
  //! RootResult takes in account the Direct status
  Standard_EXPORT Interface_EntityIterator RootResult(const Interface_Graph& G) const override;

  //! Returns always True, because RootResult has done work
  Standard_EXPORT bool Sort(const int                                    rank,
                            const occ::handle<Standard_Transient>&       ent,
                            const occ::handle<Interface_InterfaceModel>& model) const override;

  //! Returns a text defining the criterium : "Local Root Components"
  Standard_EXPORT TCollection_AsciiString ExtractLabel() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectRootComps, IFSelect_SelectExtract)

protected:
  //! Returns True, RootResult assuring uniqueness
  Standard_EXPORT bool HasUniqueResult() const override;
};

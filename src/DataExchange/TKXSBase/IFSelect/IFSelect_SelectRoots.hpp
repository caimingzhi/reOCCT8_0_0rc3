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

//! A SelectRoots sorts the Entities which are local roots of a
//! set of Entities (not shared by other Entities inside this set,
//! even if they are shared by other Entities outside it)
class IFSelect_SelectRoots : public IFSelect_SelectExtract
{

public:
  //! Creates a SelectRoots
  Standard_EXPORT IFSelect_SelectRoots();

  //! Returns the list of local roots.
  //! It is redefined for a purpose of efficiency:
  //! calling a Sort routine for each Entity would cost more resources
  //! than to work in once using a Map RootResult takes in account the Direct status.
  Standard_EXPORT Interface_EntityIterator RootResult(const Interface_Graph& G) const override;

  //! Returns always True, because RootResult has done work
  Standard_EXPORT bool Sort(const int                                    rank,
                            const occ::handle<Standard_Transient>&       ent,
                            const occ::handle<Interface_InterfaceModel>& model) const override;

  //! Returns a text defining the criterium : "Local Root Entities"
  Standard_EXPORT TCollection_AsciiString ExtractLabel() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectRoots, IFSelect_SelectExtract)

protected:
  //! Returns True, because RootResult assures uniqueness
  Standard_EXPORT bool HasUniqueResult() const override;
};

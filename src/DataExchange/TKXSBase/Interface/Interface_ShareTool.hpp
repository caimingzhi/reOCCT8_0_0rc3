#pragma once


#include <Standard_Type.hpp>

class Interface_HGraph;
class Interface_InterfaceModel;
class Interface_GeneralLib;
class Interface_GTool;
class Interface_Protocol;
class Interface_Graph;
class Interface_EntityIterator;

//! Builds the Graph of Dependencies, from the General Service
//! "Shared" -> builds for each Entity of a Model, the Shared and
//! Sharing Lists, and gives access to them.
//! Allows to complete with Implied References (which are not
//! regarded as Shared Entities, but are nevertheless Referenced),
//! this can be useful for Reference Checking
class Interface_ShareTool
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a ShareTool from a Model and builds all required data,
  //! by calling the General Service Library and Modules
  //! (GeneralLib given as an argument)
  Standard_EXPORT Interface_ShareTool(const occ::handle<Interface_InterfaceModel>& amodel,
                                      const Interface_GeneralLib&                  lib);

  //! Same a above, but GeneralLib is detained by a GTool
  Standard_EXPORT Interface_ShareTool(const occ::handle<Interface_InterfaceModel>& amodel,
                                      const occ::handle<Interface_GTool>&          gtool);

  //! Same a above, but GeneralLib is defined through a Protocol
  //! Protocol is used to build the working library
  Standard_EXPORT Interface_ShareTool(const occ::handle<Interface_InterfaceModel>& amodel,
                                      const occ::handle<Interface_Protocol>&       protocol);

  //! Same as above, but works with the GTool of the Model
  Standard_EXPORT Interface_ShareTool(const occ::handle<Interface_InterfaceModel>& amodel);

  //! Creates a ShareTool from an already defined Graph
  //! Remark that the data of the Graph are copied
  Standard_EXPORT Interface_ShareTool(const Interface_Graph& agraph);

  //! Completes the Graph by Adding Implied References. Hence, they
  //! are considered as Sharing References in all the other queries
  Standard_EXPORT Interface_ShareTool(const occ::handle<Interface_HGraph>& ahgraph);

  //! Returns the Model used for Creation (directly or for Graph)
  Standard_EXPORT occ::handle<Interface_InterfaceModel> Model() const;

  //! Returns the data used by the ShareTool to work
  //! Can then be used directly (read only)
  Standard_EXPORT const Interface_Graph& Graph() const;

  //! Returns the Entities which are not Shared (their Sharing List
  //! is empty) in the Model
  Standard_EXPORT Interface_EntityIterator RootEntities() const;

  //! Returns True if <ent> is Shared by other Entities in the Model
  Standard_EXPORT bool IsShared(const occ::handle<Standard_Transient>& ent) const;

  //! Returns the List of Entities Shared by a given Entity <ent>
  Standard_EXPORT Interface_EntityIterator
    Shareds(const occ::handle<Standard_Transient>& ent) const;

  //! Returns the List of Entities Sharing a given Entity <ent>
  Standard_EXPORT Interface_EntityIterator
    Sharings(const occ::handle<Standard_Transient>& ent) const;

  //! Returns the count of Sharing Entities of an Entity, which
  //! are Kind of a given Type
  Standard_EXPORT int NbTypedSharings(const occ::handle<Standard_Transient>& ent,
                                      const occ::handle<Standard_Type>&      atype) const;

  //! Returns the Sharing Entity of an Entity, which is Kind of a
  //! given Type. Allows to access a Sharing Entity of a given type
  //! when there is one and only one (current case)
  Standard_EXPORT occ::handle<Standard_Transient> TypedSharing(
    const occ::handle<Standard_Transient>& ent,
    const occ::handle<Standard_Type>&      atype) const;

  //! Returns the complete list of entities shared by <ent> at any
  //! level, including <ent> itself
  //! If <ent> is the Model, considers the concatenation of
  //! AllShared for each root
  //! If <rootlast> is True (D), the list starts with lower level
  //! entities and ends by the root. Else, the root is first and
  //! the lower level entities are at end
  Standard_EXPORT Interface_EntityIterator All(const occ::handle<Standard_Transient>& ent,
                                               const bool rootlast = true) const;

  //! Utility method which Prints the content of an iterator
  //! (by their Numbers)
  Standard_EXPORT void Print(const Interface_EntityIterator& iter, Standard_OStream& S) const;

private:
  occ::handle<Interface_HGraph> theHGraph;
};


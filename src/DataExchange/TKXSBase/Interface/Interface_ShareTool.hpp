#pragma once

#include <Standard_Type.hpp>

class Interface_HGraph;
class Interface_InterfaceModel;
class Interface_GeneralLib;
class Interface_GTool;
class Interface_Protocol;
class Interface_Graph;
class Interface_EntityIterator;

class Interface_ShareTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Interface_ShareTool(const occ::handle<Interface_InterfaceModel>& amodel,
                                      const Interface_GeneralLib&                  lib);

  Standard_EXPORT Interface_ShareTool(const occ::handle<Interface_InterfaceModel>& amodel,
                                      const occ::handle<Interface_GTool>&          gtool);

  Standard_EXPORT Interface_ShareTool(const occ::handle<Interface_InterfaceModel>& amodel,
                                      const occ::handle<Interface_Protocol>&       protocol);

  Standard_EXPORT Interface_ShareTool(const occ::handle<Interface_InterfaceModel>& amodel);

  Standard_EXPORT Interface_ShareTool(const Interface_Graph& agraph);

  Standard_EXPORT Interface_ShareTool(const occ::handle<Interface_HGraph>& ahgraph);

  Standard_EXPORT occ::handle<Interface_InterfaceModel> Model() const;

  Standard_EXPORT const Interface_Graph& Graph() const;

  Standard_EXPORT Interface_EntityIterator RootEntities() const;

  Standard_EXPORT bool IsShared(const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT Interface_EntityIterator
    Shareds(const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT Interface_EntityIterator
    Sharings(const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT int NbTypedSharings(const occ::handle<Standard_Transient>& ent,
                                      const occ::handle<Standard_Type>&      atype) const;

  Standard_EXPORT occ::handle<Standard_Transient> TypedSharing(
    const occ::handle<Standard_Transient>& ent,
    const occ::handle<Standard_Type>&      atype) const;

  Standard_EXPORT Interface_EntityIterator All(const occ::handle<Standard_Transient>& ent,
                                               const bool rootlast = true) const;

  Standard_EXPORT void Print(const Interface_EntityIterator& iter, Standard_OStream& S) const;

private:
  occ::handle<Interface_HGraph> theHGraph;
};

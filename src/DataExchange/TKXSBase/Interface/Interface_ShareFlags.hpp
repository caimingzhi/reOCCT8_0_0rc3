#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Interface_BitMap.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Integer.hpp>
class Interface_InterfaceModel;
class Interface_GeneralLib;
class Interface_GTool;
class Interface_Protocol;
class Interface_Graph;
class Standard_Transient;
class Interface_EntityIterator;

class Interface_ShareFlags
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Interface_ShareFlags(const occ::handle<Interface_InterfaceModel>& amodel,
                                       const Interface_GeneralLib&                  lib);

  Standard_EXPORT Interface_ShareFlags(const occ::handle<Interface_InterfaceModel>& amodel,
                                       const occ::handle<Interface_GTool>&          gtool);

  Standard_EXPORT Interface_ShareFlags(const occ::handle<Interface_InterfaceModel>& amodel,
                                       const occ::handle<Interface_Protocol>&       protocol);

  Standard_EXPORT Interface_ShareFlags(const occ::handle<Interface_InterfaceModel>& amodel);

  Standard_EXPORT Interface_ShareFlags(const Interface_Graph& agraph);

  Standard_EXPORT occ::handle<Interface_InterfaceModel> Model() const;

  Standard_EXPORT bool IsShared(const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT Interface_EntityIterator RootEntities() const;

  Standard_EXPORT int NbRoots() const;

  Standard_EXPORT occ::handle<Standard_Transient> Root(const int num = 1) const;

private:
  Standard_EXPORT void Evaluate(const Interface_GeneralLib&         lib,
                                const occ::handle<Interface_GTool>& gtool);

  occ::handle<Interface_InterfaceModel>                               themodel;
  Interface_BitMap                                                    theflags;
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> theroots;
};

#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Interface_BitMap.hpp>
#include <Interface_GeneralLib.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>
class Interface_InterfaceModel;
class Interface_CopyControl;
class Interface_CopyMap;
class Standard_Transient;
class Interface_GeneralModule;
class Interface_Protocol;
class Interface_EntityIterator;

class Interface_CopyTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Interface_CopyTool(const occ::handle<Interface_InterfaceModel>& amodel,
                                     const Interface_GeneralLib&                  lib);

  Standard_EXPORT Interface_CopyTool(const occ::handle<Interface_InterfaceModel>& amodel,
                                     const occ::handle<Interface_Protocol>&       protocol);

  Standard_EXPORT Interface_CopyTool(const occ::handle<Interface_InterfaceModel>& amodel);

  Standard_EXPORT occ::handle<Interface_InterfaceModel> Model() const;

  Standard_EXPORT void SetControl(const occ::handle<Interface_CopyControl>& othermap);

  Standard_EXPORT occ::handle<Interface_CopyControl> Control() const;

  Standard_EXPORT virtual void Clear();

  Standard_EXPORT virtual bool Copy(const occ::handle<Standard_Transient>& entfrom,
                                    occ::handle<Standard_Transient>&       entto,
                                    const bool                             mapped,
                                    const bool                             errstat);

  Standard_EXPORT occ::handle<Standard_Transient> Transferred(
    const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT void Bind(const occ::handle<Standard_Transient>& ent,
                            const occ::handle<Standard_Transient>& res);

  Standard_EXPORT bool Search(const occ::handle<Standard_Transient>& ent,
                              occ::handle<Standard_Transient>&       res) const;

  Standard_EXPORT void ClearLastFlags();

  Standard_EXPORT int LastCopiedAfter(const int                        numfrom,
                                      occ::handle<Standard_Transient>& ent,
                                      occ::handle<Standard_Transient>& res) const;

  Standard_EXPORT void TransferEntity(const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT void RenewImpliedRefs();

  Standard_EXPORT void FillModel(const occ::handle<Interface_InterfaceModel>& bmodel);

  Standard_EXPORT Interface_EntityIterator CompleteResult(const bool withreports = false) const;

  Standard_EXPORT Interface_EntityIterator RootResult(const bool withreports = false) const;
  Standard_EXPORT virtual ~Interface_CopyTool();

protected:
  Standard_EXPORT virtual bool NewVoid(const occ::handle<Standard_Transient>& entfrom,
                                       occ::handle<Standard_Transient>&       entto);

  Interface_GeneralLib thelib;

private:
  Standard_EXPORT virtual void Implied(const occ::handle<Standard_Transient>& entfrom,
                                       const occ::handle<Standard_Transient>& entto);

  occ::handle<Interface_InterfaceModel> themod;
  occ::handle<Interface_CopyControl>    themap;
  occ::handle<Interface_CopyMap>        therep;
  Interface_BitMap                      thelst;
  int                                   thelev;
  NCollection_Sequence<int>             therts;
  bool                                  theimp;
  occ::handle<Standard_Transient>       theent;
  occ::handle<Interface_GeneralModule>  themdu;
  int                                   theCN;
};

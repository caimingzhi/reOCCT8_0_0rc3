#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_Map.hpp>
#include <Standard_Integer.hpp>
#include <IFSelect_SignatureList.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
class IFSelect_Signature;
class IFSelect_Selection;
class Standard_Transient;
class Interface_InterfaceModel;
class Interface_Graph;
class TCollection_HAsciiString;

class IFSelect_SignCounter : public IFSelect_SignatureList
{

public:
  Standard_EXPORT IFSelect_SignCounter(const bool withmap = true, const bool withlist = false);

  Standard_EXPORT IFSelect_SignCounter(const occ::handle<IFSelect_Signature>& matcher,
                                       const bool                             withmap  = true,
                                       const bool                             withlist = false);

  Standard_EXPORT occ::handle<IFSelect_Signature> Signature() const;

  Standard_EXPORT void SetMap(const bool withmap);

  Standard_EXPORT virtual bool AddEntity(const occ::handle<Standard_Transient>&       ent,
                                         const occ::handle<Interface_InterfaceModel>& model);

  Standard_EXPORT virtual void AddSign(const occ::handle<Standard_Transient>&       ent,
                                       const occ::handle<Interface_InterfaceModel>& model);

  Standard_EXPORT void AddList(
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list,
    const occ::handle<Interface_InterfaceModel>&                               model);

  Standard_EXPORT virtual void AddWithGraph(
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list,
    const Interface_Graph&                                                     graph);

  Standard_EXPORT void AddModel(const occ::handle<Interface_InterfaceModel>& model);

  Standard_EXPORT void AddFromSelection(const occ::handle<IFSelect_Selection>& sel,
                                        const Interface_Graph&                 G);

  Standard_EXPORT void SetSelection(const occ::handle<IFSelect_Selection>& sel);

  Standard_EXPORT occ::handle<IFSelect_Selection> Selection() const;

  Standard_EXPORT void SetSelMode(const int selmode);

  Standard_EXPORT int SelMode() const;

  Standard_EXPORT bool ComputeSelected(const Interface_Graph& G, const bool forced = false);

  Standard_EXPORT virtual occ::handle<TCollection_HAsciiString> Sign(
    const occ::handle<Standard_Transient>&       ent,
    const occ::handle<Interface_InterfaceModel>& model) const;

  Standard_EXPORT const char* ComputedSign(const occ::handle<Standard_Transient>& ent,
                                           const Interface_Graph&                 G);

  DEFINE_STANDARD_RTTIEXT(IFSelect_SignCounter, IFSelect_SignatureList)

private:
  bool                                             themapstat;
  NCollection_Map<occ::handle<Standard_Transient>> themap;
  occ::handle<IFSelect_Signature>                  thematcher;
  occ::handle<IFSelect_Selection>                  theselect;
  int                                              theselmode;
  int                                              thenbcomp1;
  int                                              thenbcomp2;
};

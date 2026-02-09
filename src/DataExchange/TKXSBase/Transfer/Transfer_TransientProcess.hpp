#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Transfer_ProcessForTransient.hpp>
#include <Standard_Integer.hpp>
#include <Standard_CString.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_DataMap.hpp>
class Interface_InterfaceModel;
class Interface_HGraph;
class Interface_Graph;
class Interface_EntityIterator;

class Transfer_TransientProcess : public Transfer_ProcessForTransient
{

public:
  Standard_EXPORT Transfer_TransientProcess(const int nb = 10000);

  Standard_EXPORT void SetModel(const occ::handle<Interface_InterfaceModel>& model);

  Standard_EXPORT occ::handle<Interface_InterfaceModel> Model() const;

  Standard_EXPORT void SetGraph(const occ::handle<Interface_HGraph>& HG);

  Standard_EXPORT bool HasGraph() const;

  Standard_EXPORT occ::handle<Interface_HGraph> HGraph() const;

  Standard_EXPORT const Interface_Graph& Graph() const;

  Standard_EXPORT void SetContext(const char* name, const occ::handle<Standard_Transient>& ctx);

  Standard_EXPORT bool GetContext(const char*                       name,
                                  const occ::handle<Standard_Type>& type,
                                  occ::handle<Standard_Transient>&  ctx) const;

  Standard_EXPORT NCollection_DataMap<TCollection_AsciiString, occ::handle<Standard_Transient>>&
                  Context();

  Standard_EXPORT void PrintTrace(const occ::handle<Standard_Transient>& start,
                                  Standard_OStream&                      S) const override;

  Standard_EXPORT int CheckNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT Interface_EntityIterator
    TypedSharings(const occ::handle<Standard_Transient>& start,
                  const occ::handle<Standard_Type>&      type) const;

  Standard_EXPORT bool IsDataLoaded(const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT bool IsDataFail(const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT void PrintStats(const int mode, Standard_OStream& S) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>
                  RootsForTransfer();

  DEFINE_STANDARD_RTTIEXT(Transfer_TransientProcess, Transfer_ProcessForTransient)

private:
  occ::handle<Interface_InterfaceModel>                                         themodel;
  occ::handle<Interface_HGraph>                                                 thegraph;
  NCollection_DataMap<TCollection_AsciiString, occ::handle<Standard_Transient>> thectx;
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>           thetrroots;
};

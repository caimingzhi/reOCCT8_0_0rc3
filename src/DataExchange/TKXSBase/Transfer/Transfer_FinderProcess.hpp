#pragma once

#include <Transfer_ProcessForFinder.hpp>
#include <Interface_InterfaceModel.hpp>

class Interface_InterfaceModel;
class Transfer_TransientMapper;
class Transfer_Finder;

class Transfer_FinderProcess : public Transfer_ProcessForFinder
{

public:
  Standard_EXPORT Transfer_FinderProcess(const int nb = 10000);

  Standard_EXPORT void SetModel(const occ::handle<Interface_InterfaceModel>& model);

  Standard_EXPORT occ::handle<Interface_InterfaceModel> Model() const;

  Standard_EXPORT int NextMappedWithAttribute(const char* name, const int num0) const;

  Standard_EXPORT occ::handle<Transfer_TransientMapper> TransientMapper(
    const occ::handle<Standard_Transient>& obj) const;

  Standard_EXPORT void PrintTrace(const occ::handle<Transfer_Finder>& start,
                                  Standard_OStream&                   S) const override;

  Standard_EXPORT void PrintStats(const int mode, Standard_OStream& S) const;

  DEFINE_STANDARD_RTTIEXT(Transfer_FinderProcess, Transfer_ProcessForFinder)

private:
  occ::handle<Interface_InterfaceModel> themodel;
};

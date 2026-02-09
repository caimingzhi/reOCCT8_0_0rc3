#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Interface_ShareTool.hpp>
#include <Standard_Integer.hpp>
class Interface_GTool;
class Interface_InterfaceModel;
class Interface_Protocol;
class Interface_Graph;
class Interface_HGraph;
class Standard_Transient;
class Interface_Check;
class Interface_CheckIterator;
class Interface_EntityIterator;

class Interface_CheckTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Interface_CheckTool(const occ::handle<Interface_InterfaceModel>& model,
                                      const occ::handle<Interface_Protocol>&       protocol);

  Standard_EXPORT Interface_CheckTool(const occ::handle<Interface_InterfaceModel>& model);

  Standard_EXPORT Interface_CheckTool(const Interface_Graph& graph);

  Standard_EXPORT Interface_CheckTool(const occ::handle<Interface_HGraph>& hgraph);

  Standard_EXPORT void FillCheck(const occ::handle<Standard_Transient>& ent,
                                 const Interface_ShareTool&             sh,
                                 occ::handle<Interface_Check>&          ach);

  Standard_EXPORT void Print(const occ::handle<Interface_Check>& ach, Standard_OStream& S) const;

  Standard_EXPORT void Print(const Interface_CheckIterator& list, Standard_OStream& S) const;

  Standard_EXPORT occ::handle<Interface_Check> Check(const int num);

  Standard_EXPORT void CheckSuccess(const bool reset = false);

  Standard_EXPORT Interface_CheckIterator CompleteCheckList();

  Standard_EXPORT Interface_CheckIterator CheckList();

  Standard_EXPORT Interface_CheckIterator AnalyseCheckList();

  Standard_EXPORT Interface_CheckIterator VerifyCheckList();

  Standard_EXPORT Interface_CheckIterator WarningCheckList();

  Standard_EXPORT Interface_EntityIterator UnknownEntities();

private:
  occ::handle<Interface_GTool> thegtool;
  Interface_ShareTool          theshare;
  int                          thestat;
};

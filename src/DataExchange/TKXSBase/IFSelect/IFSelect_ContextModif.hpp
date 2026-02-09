#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Interface_Graph.hpp>
#include <TCollection_AsciiString.hpp>
#include <Interface_CheckIterator.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Integer.hpp>
class Interface_Protocol;
class Interface_CopyControl;
class Interface_CopyTool;
class Interface_EntityIterator;
class Interface_InterfaceModel;
class Standard_Transient;
class IFSelect_GeneralModifier;
class Interface_Check;

class IFSelect_ContextModif
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IFSelect_ContextModif(const Interface_Graph&    graph,
                                        const Interface_CopyTool& TC,
                                        const char*               filename = "");

  Standard_EXPORT IFSelect_ContextModif(const Interface_Graph& graph, const char* filename = "");

  Standard_EXPORT void Select(Interface_EntityIterator& list);

  Standard_EXPORT const Interface_Graph& OriginalGraph() const;

  Standard_EXPORT occ::handle<Interface_InterfaceModel> OriginalModel() const;

  Standard_EXPORT void SetProtocol(const occ::handle<Interface_Protocol>& proto);

  Standard_EXPORT occ::handle<Interface_Protocol> Protocol() const;

  Standard_EXPORT bool HasFileName() const;

  Standard_EXPORT const char* FileName() const;

  Standard_EXPORT occ::handle<Interface_CopyControl> Control() const;

  Standard_EXPORT bool IsForNone() const;

  Standard_EXPORT bool IsForAll() const;

  Standard_EXPORT bool IsTransferred(const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT bool IsSelected(const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT bool Search(const occ::handle<Standard_Transient>& ent,
                              occ::handle<Standard_Transient>&       res) const;

  Standard_EXPORT Interface_EntityIterator SelectedOriginal() const;

  Standard_EXPORT Interface_EntityIterator SelectedResult() const;

  Standard_EXPORT int SelectedCount() const;

  Standard_EXPORT void Start();

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT occ::handle<Standard_Transient> ValueOriginal() const;

  Standard_EXPORT occ::handle<Standard_Transient> ValueResult() const;

  Standard_EXPORT void TraceModifier(const occ::handle<IFSelect_GeneralModifier>& modif);

  Standard_EXPORT void Trace(const char* mess = "");

  Standard_EXPORT void AddCheck(const occ::handle<Interface_Check>& check);

  Standard_EXPORT void AddWarning(const occ::handle<Standard_Transient>& start,
                                  const char*                            mess,
                                  const char*                            orig = "");

  Standard_EXPORT void AddFail(const occ::handle<Standard_Transient>& start,
                               const char*                            mess,
                               const char*                            orig = "");

  Standard_EXPORT occ::handle<Interface_Check> CCheck(const int num = 0);

  Standard_EXPORT occ::handle<Interface_Check> CCheck(const occ::handle<Standard_Transient>& start);

  Standard_EXPORT Interface_CheckIterator CheckList() const;

private:
  Interface_Graph                    thegraf;
  occ::handle<Interface_Protocol>    theprot;
  occ::handle<Interface_CopyControl> themap;
  TCollection_AsciiString            thefile;
  TCollection_AsciiString            thelist;
  Interface_CheckIterator            thechek;
  bool                               thesel;
  int                                thecurr;
  int                                thecurt;
};

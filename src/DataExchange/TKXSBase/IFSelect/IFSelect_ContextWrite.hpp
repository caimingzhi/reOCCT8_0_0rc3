#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Interface_CheckIterator.hpp>
#include <Standard_Integer.hpp>
#include <Standard_CString.hpp>
class Interface_InterfaceModel;
class Interface_Protocol;
class IFSelect_AppliedModifiers;
class Interface_HGraph;
class IFSelect_GeneralModifier;
class Interface_Graph;
class Standard_Transient;
class Interface_Check;

class IFSelect_ContextWrite
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IFSelect_ContextWrite(const occ::handle<Interface_InterfaceModel>&  model,
                                        const occ::handle<Interface_Protocol>&        proto,
                                        const occ::handle<IFSelect_AppliedModifiers>& applieds,
                                        const char*                                   filename);

  Standard_EXPORT IFSelect_ContextWrite(const occ::handle<Interface_HGraph>&          hgraph,
                                        const occ::handle<Interface_Protocol>&        proto,
                                        const occ::handle<IFSelect_AppliedModifiers>& applieds,
                                        const char*                                   filename);

  Standard_EXPORT occ::handle<Interface_InterfaceModel> Model() const;

  Standard_EXPORT occ::handle<Interface_Protocol> Protocol() const;

  Standard_EXPORT const char* FileName() const;

  Standard_EXPORT occ::handle<IFSelect_AppliedModifiers> AppliedModifiers() const;

  Standard_EXPORT const Interface_Graph& Graph();

  Standard_EXPORT int NbModifiers() const;

  Standard_EXPORT bool SetModifier(const int numod);

  Standard_EXPORT occ::handle<IFSelect_GeneralModifier> FileModifier() const;

  Standard_EXPORT bool IsForNone() const;

  Standard_EXPORT bool IsForAll() const;

  Standard_EXPORT int NbEntities() const;

  Standard_EXPORT void Start();

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT occ::handle<Standard_Transient> Value() const;

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
  occ::handle<Interface_InterfaceModel>  themodel;
  occ::handle<Interface_Protocol>        theproto;
  TCollection_AsciiString                thefile;
  occ::handle<IFSelect_AppliedModifiers> theapply;
  occ::handle<Interface_HGraph>          thehgraf;
  Interface_CheckIterator                thecheck;
  int                                    thenumod;
  int                                    thenbent;
  int                                    thecurr;
  occ::handle<IFSelect_GeneralModifier>  themodif;
};

#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_CString.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <Standard_Integer.hpp>
#include <Draw_Interpretor.hpp>
class TopoDS_Shape;
class TDF_Data;
class TCollection_AsciiString;
class TDF_Label;

class QADNaming
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static TopoDS_Shape CurrentShape(const char*                  ShapeEntry,
                                                   const occ::handle<TDF_Data>& Data);

  Standard_EXPORT static void GetShape(const char*                     ShapeEntry,
                                       const occ::handle<TDF_Data>&    Data,
                                       NCollection_List<TopoDS_Shape>& Shapes);

  Standard_EXPORT static TCollection_AsciiString GetEntry(const TopoDS_Shape&          Shape,
                                                          const occ::handle<TDF_Data>& Data,
                                                          int&                         theStatus);

  Standard_EXPORT static bool Entry(void* const theArguments, TDF_Label& theLabel);

  Standard_EXPORT static void AllCommands(Draw_Interpretor& DI);

  Standard_EXPORT static void BasicCommands(Draw_Interpretor& DI);

  Standard_EXPORT static void BuilderCommands(Draw_Interpretor& DI);

  Standard_EXPORT static void IteratorsCommands(Draw_Interpretor& DI);

  Standard_EXPORT static void ToolsCommands(Draw_Interpretor& DI);

  Standard_EXPORT static void SelectionCommands(Draw_Interpretor& DI);
};

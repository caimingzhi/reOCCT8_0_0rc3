#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Draw_Interpretor.hpp>
class TDocStd_Application;
class TDocStd_Document;
class TDF_Label;
class Standard_GUID;
class TDF_Attribute;

class DDocStd
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static const occ::handle<TDocStd_Application>& GetApplication();

  Standard_EXPORT static bool GetDocument(const char*&                   Name,
                                          occ::handle<TDocStd_Document>& Doc,
                                          const bool                     Complain = true);

  Standard_EXPORT static bool Find(const occ::handle<TDocStd_Document>& Document,
                                   const char*                          Entry,
                                   TDF_Label&                           Label,
                                   const bool                           Complain = true);

  Standard_EXPORT static bool Find(const occ::handle<TDocStd_Document>& Document,
                                   const char*                          Entry,
                                   const Standard_GUID&                 ID,
                                   occ::handle<TDF_Attribute>&          A,
                                   const bool                           Complain = true);

  template <class T>
  static bool Find(const occ::handle<TDocStd_Document>& Document,
                   const char*                          Entry,
                   const Standard_GUID&                 ID,
                   occ::handle<T>&                      A,
                   const bool                           Complain = true)
  {
    occ::handle<TDF_Attribute> anAttr = A;
    return Find(Document, Entry, ID, anAttr, Complain) && !(A = occ::down_cast<T>(anAttr)).IsNull();
  }

  Standard_EXPORT static Draw_Interpretor& ReturnLabel(Draw_Interpretor& theCommands,
                                                       const TDF_Label&  L);

  Standard_EXPORT static void AllCommands(Draw_Interpretor& theCommands);

  Standard_EXPORT static void ApplicationCommands(Draw_Interpretor& theCommands);

  Standard_EXPORT static void DocumentCommands(Draw_Interpretor& theCommands);

  Standard_EXPORT static void ToolsCommands(Draw_Interpretor& theCommands);

  Standard_EXPORT static void MTMCommands(Draw_Interpretor& theCommands);

  Standard_EXPORT static void ShapeSchemaCommands(Draw_Interpretor& theCommands);
};

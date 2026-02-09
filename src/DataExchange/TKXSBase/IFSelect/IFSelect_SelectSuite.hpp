#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TCollection_AsciiString.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <IFSelect_SelectDeduct.hpp>
#include <Standard_Integer.hpp>
#include <Standard_CString.hpp>
class IFSelect_Selection;
class Interface_EntityIterator;
class Interface_Graph;

class IFSelect_SelectSuite : public IFSelect_SelectDeduct
{

public:
  Standard_EXPORT IFSelect_SelectSuite();

  Standard_EXPORT bool AddInput(const occ::handle<IFSelect_Selection>& item);

  Standard_EXPORT void AddPrevious(const occ::handle<IFSelect_SelectDeduct>& item);

  Standard_EXPORT void AddNext(const occ::handle<IFSelect_SelectDeduct>& item);

  Standard_EXPORT int NbItems() const;

  Standard_EXPORT occ::handle<IFSelect_SelectDeduct> Item(const int num) const;

  Standard_EXPORT void SetLabel(const char* lab);

  Standard_EXPORT Interface_EntityIterator RootResult(const Interface_Graph& G) const override;

  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectSuite, IFSelect_SelectDeduct)

private:
  TCollection_AsciiString                               thelab;
  NCollection_Sequence<occ::handle<Standard_Transient>> thesel;
};

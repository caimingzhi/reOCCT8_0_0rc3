#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class IFSelect_Selection;
class IFSelect_Dispatch;
class TCollection_AsciiString;

class IFSelect_GeneralModifier : public Standard_Transient
{

public:
  Standard_EXPORT bool MayChangeGraph() const;

  Standard_EXPORT void SetDispatch(const occ::handle<IFSelect_Dispatch>& disp);

  Standard_EXPORT occ::handle<IFSelect_Dispatch> Dispatch() const;

  Standard_EXPORT bool Applies(const occ::handle<IFSelect_Dispatch>& disp) const;

  Standard_EXPORT void SetSelection(const occ::handle<IFSelect_Selection>& sel);

  Standard_EXPORT void ResetSelection();

  Standard_EXPORT bool HasSelection() const;

  Standard_EXPORT occ::handle<IFSelect_Selection> Selection() const;

  Standard_EXPORT virtual TCollection_AsciiString Label() const = 0;

  DEFINE_STANDARD_RTTIEXT(IFSelect_GeneralModifier, Standard_Transient)

protected:
  Standard_EXPORT IFSelect_GeneralModifier(const bool maychangegraph);

private:
  occ::handle<IFSelect_Selection> thesel;
  occ::handle<IFSelect_Dispatch>  thedisp;
  bool                            thechgr;
};

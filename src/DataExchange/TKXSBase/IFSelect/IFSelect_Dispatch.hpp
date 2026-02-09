#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class IFSelect_Selection;
class IFSelect_SelectionIterator;
class TCollection_AsciiString;
class Interface_EntityIterator;
class Interface_Graph;
class IFGraph_SubPartsIterator;

class IFSelect_Dispatch : public Standard_Transient
{

public:
  Standard_EXPORT void SetRootName(const occ::handle<TCollection_HAsciiString>& name);

  Standard_EXPORT bool HasRootName() const;

  Standard_EXPORT const occ::handle<TCollection_HAsciiString>& RootName() const;

  Standard_EXPORT void SetFinalSelection(const occ::handle<IFSelect_Selection>& sel);

  Standard_EXPORT occ::handle<IFSelect_Selection> FinalSelection() const;

  Standard_EXPORT IFSelect_SelectionIterator Selections() const;

  Standard_EXPORT virtual bool CanHaveRemainder() const;

  Standard_EXPORT virtual bool LimitedMax(const int nbent, int& max) const;

  Standard_EXPORT virtual TCollection_AsciiString Label() const = 0;

  Standard_EXPORT Interface_EntityIterator GetEntities(const Interface_Graph& G) const;

  Standard_EXPORT virtual void Packets(const Interface_Graph&    G,
                                       IFGraph_SubPartsIterator& packs) const = 0;

  Standard_EXPORT Interface_EntityIterator Packeted(const Interface_Graph& G) const;

  Standard_EXPORT virtual Interface_EntityIterator Remainder(const Interface_Graph& G) const;

  DEFINE_STANDARD_RTTIEXT(IFSelect_Dispatch, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> thename;
  occ::handle<IFSelect_Selection>       thefinal;
};

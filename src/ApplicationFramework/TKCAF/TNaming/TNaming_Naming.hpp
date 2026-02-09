#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TNaming_Name.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_Label.hpp>
#include <NCollection_Map.hpp>
#include <Standard_OStream.hpp>
#include <NCollection_IndexedMap.hpp>

class TDF_Attribute;
class Standard_GUID;
class TDF_Label;
class TNaming_NamedShape;
class TopoDS_Shape;
class TDF_RelocationTable;
class TDF_DataSet;
class TDF_IDFilter;

class TNaming_Naming : public TDF_Attribute
{

public:
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<TNaming_Naming> Insert(const TDF_Label& under);

  Standard_EXPORT static occ::handle<TNaming_NamedShape> Name(const TDF_Label&    where,
                                                              const TopoDS_Shape& Selection,
                                                              const TopoDS_Shape& Context,
                                                              const bool          Geometry = false,
                                                              const bool KeepOrientation   = false,
                                                              const bool BNproblem         = false);

  Standard_EXPORT TNaming_Naming();

  Standard_EXPORT bool IsDefined() const;

  Standard_EXPORT const TNaming_Name& GetName() const;

  Standard_EXPORT TNaming_Name& ChangeName();

  Standard_EXPORT bool Regenerate(NCollection_Map<TDF_Label>& scope);

  Standard_EXPORT bool Solve(NCollection_Map<TDF_Label>& scope);

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& With) override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       Into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT void References(const occ::handle<TDF_DataSet>& aDataSet) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  Standard_EXPORT void ExtendedDump(
    Standard_OStream&                                   anOS,
    const TDF_IDFilter&                                 aFilter,
    NCollection_IndexedMap<occ::handle<TDF_Attribute>>& aMap) const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(TNaming_Naming, TDF_Attribute)

private:
  TNaming_Name myName;
};

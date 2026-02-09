#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <TDF_Label.hpp>
#include <NCollection_DoubleMap.hpp>
#include <TFunction_Logbook.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_OStream.hpp>
class TDF_Label;
class Standard_GUID;
class TFunction_Logbook;
class TDF_RelocationTable;

class TFunction_Scope : public TDF_Attribute
{

public:
  Standard_EXPORT static occ::handle<TFunction_Scope> Set(const TDF_Label& Access);

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT TFunction_Scope();

  Standard_EXPORT bool AddFunction(const TDF_Label& L);

  Standard_EXPORT bool RemoveFunction(const TDF_Label& L);

  Standard_EXPORT bool RemoveFunction(const int ID);

  Standard_EXPORT void RemoveAllFunctions();

  Standard_EXPORT bool HasFunction(const int ID) const;

  Standard_EXPORT bool HasFunction(const TDF_Label& L) const;

  Standard_EXPORT int GetFunction(const TDF_Label& L) const;

  Standard_EXPORT const TDF_Label& GetFunction(const int ID) const;

  Standard_EXPORT occ::handle<TFunction_Logbook> GetLogbook() const;

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& with) override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  Standard_EXPORT const NCollection_DoubleMap<int, TDF_Label>& GetFunctions() const;

  Standard_EXPORT NCollection_DoubleMap<int, TDF_Label>& ChangeFunctions();

  Standard_EXPORT void SetFreeID(const int ID);

  Standard_EXPORT int GetFreeID() const;

  DEFINE_STANDARD_RTTIEXT(TFunction_Scope, TDF_Attribute)

private:
  NCollection_DoubleMap<int, TDF_Label> myFunctions;
  int                                   myFreeID;
};

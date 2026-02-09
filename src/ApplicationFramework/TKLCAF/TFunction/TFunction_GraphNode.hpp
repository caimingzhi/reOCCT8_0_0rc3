#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Map.hpp>
#include <TFunction_ExecutionStatus.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_OStream.hpp>
class TDF_Label;
class Standard_GUID;
class TDF_RelocationTable;
class TDF_DataSet;

class TFunction_GraphNode : public TDF_Attribute
{

public:
  Standard_EXPORT static occ::handle<TFunction_GraphNode> Set(const TDF_Label& L);

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT TFunction_GraphNode();

  Standard_EXPORT bool AddPrevious(const int funcID);

  Standard_EXPORT bool AddPrevious(const TDF_Label& func);

  Standard_EXPORT bool RemovePrevious(const int funcID);

  Standard_EXPORT bool RemovePrevious(const TDF_Label& func);

  Standard_EXPORT const NCollection_Map<int>& GetPrevious() const;

  Standard_EXPORT void RemoveAllPrevious();

  Standard_EXPORT bool AddNext(const int funcID);

  Standard_EXPORT bool AddNext(const TDF_Label& func);

  Standard_EXPORT bool RemoveNext(const int funcID);

  Standard_EXPORT bool RemoveNext(const TDF_Label& func);

  Standard_EXPORT const NCollection_Map<int>& GetNext() const;

  Standard_EXPORT void RemoveAllNext();

  Standard_EXPORT TFunction_ExecutionStatus GetStatus() const;

  Standard_EXPORT void SetStatus(const TFunction_ExecutionStatus status);

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& with) override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void References(const occ::handle<TDF_DataSet>& aDataSet) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  DEFINE_STANDARD_RTTIEXT(TFunction_GraphNode, TDF_Attribute)

private:
  NCollection_Map<int>      myPrevious;
  NCollection_Map<int>      myNext;
  TFunction_ExecutionStatus myStatus;
};

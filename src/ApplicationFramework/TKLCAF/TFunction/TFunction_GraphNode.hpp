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

//! Provides links between functions.
class TFunction_GraphNode : public TDF_Attribute
{

public:
  //! Static methods
  //! ==============
  //! Finds or Creates a graph node attribute at the label <L>.
  //! Returns the attribute.
  Standard_EXPORT static occ::handle<TFunction_GraphNode> Set(const TDF_Label& L);

  //! Returns the GUID for GraphNode attribute.
  //! Instant methods
  //! ===============
  //! Constructor (empty).
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT TFunction_GraphNode();

  //! Defines a reference to the function as a previous one.
  Standard_EXPORT bool AddPrevious(const int funcID);

  //! Defines a reference to the function as a previous one.
  Standard_EXPORT bool AddPrevious(const TDF_Label& func);

  //! Removes a reference to the function as a previous one.
  Standard_EXPORT bool RemovePrevious(const int funcID);

  //! Removes a reference to the function as a previous one.
  Standard_EXPORT bool RemovePrevious(const TDF_Label& func);

  //! Returns a map of previous functions.
  Standard_EXPORT const NCollection_Map<int>& GetPrevious() const;

  //! Clears a map of previous functions.
  Standard_EXPORT void RemoveAllPrevious();

  //! Defines a reference to the function as a next one.
  Standard_EXPORT bool AddNext(const int funcID);

  //! Defines a reference to the function as a next one.
  Standard_EXPORT bool AddNext(const TDF_Label& func);

  //! Removes a reference to the function as a next one.
  Standard_EXPORT bool RemoveNext(const int funcID);

  //! Removes a reference to the function as a next one.
  Standard_EXPORT bool RemoveNext(const TDF_Label& func);

  //! Returns a map of next functions.
  Standard_EXPORT const NCollection_Map<int>& GetNext() const;

  //! Clears a map of next functions.
  Standard_EXPORT void RemoveAllNext();

  //! Returns the execution status of the function.
  Standard_EXPORT TFunction_ExecutionStatus GetStatus() const;

  //! Defines an execution status for a function.
  //! Implementation of Attribute methods
  //! ===================================
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

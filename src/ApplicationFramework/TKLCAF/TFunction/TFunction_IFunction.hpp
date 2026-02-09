#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TDF_Label.hpp>
#include <NCollection_List.hpp>
#include <TFunction_ExecutionStatus.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_DoubleMap.hpp>
class Standard_GUID;
class TFunction_Logbook;
class TFunction_Driver;
class TFunction_GraphNode;

class TFunction_IFunction
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static bool NewFunction(const TDF_Label& L, const Standard_GUID& ID);

  Standard_EXPORT static bool DeleteFunction(const TDF_Label& L);

  Standard_EXPORT static bool UpdateDependencies(const TDF_Label& Access);

  Standard_EXPORT TFunction_IFunction();

  Standard_EXPORT TFunction_IFunction(const TDF_Label& L);

  Standard_EXPORT void Init(const TDF_Label& L);

  Standard_EXPORT const TDF_Label& Label() const;

  Standard_EXPORT bool UpdateDependencies() const;

  Standard_EXPORT void Arguments(NCollection_List<TDF_Label>& args) const;

  Standard_EXPORT void Results(NCollection_List<TDF_Label>& res) const;

  Standard_EXPORT void GetPrevious(NCollection_List<TDF_Label>& prev) const;

  Standard_EXPORT void GetNext(NCollection_List<TDF_Label>& prev) const;

  Standard_EXPORT TFunction_ExecutionStatus GetStatus() const;

  Standard_EXPORT void SetStatus(const TFunction_ExecutionStatus status) const;

  Standard_EXPORT const NCollection_DoubleMap<int, TDF_Label>& GetAllFunctions() const;

  Standard_EXPORT occ::handle<TFunction_Logbook> GetLogbook() const;

  Standard_EXPORT occ::handle<TFunction_Driver> GetDriver(const int thread = 0) const;

  Standard_EXPORT occ::handle<TFunction_GraphNode> GetGraphNode() const;

private:
  TDF_Label myLabel;
};

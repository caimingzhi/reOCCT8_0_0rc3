#pragma once

#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_IndexedMap.hpp>

class TObj_Model;

class TObj_Assistant
{
public:
  static Standard_EXPORT occ::handle<TObj_Model> FindModel(const char* theName);

  static Standard_EXPORT void BindModel(const occ::handle<TObj_Model>& theModel);

  static Standard_EXPORT void ClearModelMap();

public:
  static Standard_EXPORT occ::handle<Standard_Type> FindType(const int theTypeIndex);

  static Standard_EXPORT int FindTypeIndex(const occ::handle<Standard_Type>& theType);

  static Standard_EXPORT int BindType(const occ::handle<Standard_Type>& theType);

  static Standard_EXPORT void ClearTypeMap();

public:
  static Standard_EXPORT void SetCurrentModel(const occ::handle<TObj_Model>& theModel);

  static Standard_EXPORT occ::handle<TObj_Model> GetCurrentModel();

  static Standard_EXPORT void UnSetCurrentModel();

public:
  static Standard_EXPORT int GetAppVersion();

private:
  static Standard_EXPORT NCollection_Sequence<occ::handle<Standard_Transient>>& getModels();

  static Standard_EXPORT NCollection_IndexedMap<occ::handle<Standard_Transient>>& getTypes();

  static Standard_EXPORT occ::handle<TObj_Model>& getCurrentModel();

  static Standard_EXPORT int& getVersion();
};

#ifdef _MSC_VER
  #pragma once
#endif

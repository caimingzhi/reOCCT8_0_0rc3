#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Interface_GeneralLib.hpp>
#include <IGESData_SpecificLib.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
class IGESData_Protocol;
class IGESData_IGESModel;
class IGESData_IGESEntity;

class IGESData_BasicEditor
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IGESData_BasicEditor();

  Standard_EXPORT IGESData_BasicEditor(const occ::handle<IGESData_Protocol>& protocol);

  Standard_EXPORT IGESData_BasicEditor(const occ::handle<IGESData_IGESModel>& model,
                                       const occ::handle<IGESData_Protocol>&  protocol);

  Standard_EXPORT void Init(const occ::handle<IGESData_Protocol>& protocol);

  Standard_EXPORT void Init(const occ::handle<IGESData_IGESModel>& model,
                            const occ::handle<IGESData_Protocol>&  protocol);

  Standard_EXPORT occ::handle<IGESData_IGESModel> Model() const;

  Standard_EXPORT bool SetUnitFlag(const int flag);

  Standard_EXPORT bool SetUnitValue(const double val);

  Standard_EXPORT bool SetUnitName(const char* name);

  Standard_EXPORT void ApplyUnit(const bool enforce = false);

  Standard_EXPORT void ComputeStatus();

  Standard_EXPORT bool AutoCorrect(const occ::handle<IGESData_IGESEntity>& ent);

  Standard_EXPORT int AutoCorrectModel();

  Standard_EXPORT static int UnitNameFlag(const char* name);

  Standard_EXPORT static double UnitFlagValue(const int flag);

  Standard_EXPORT static const char* UnitFlagName(const int flag);

  Standard_EXPORT static const char* IGESVersionName(const int flag);

  Standard_EXPORT static int IGESVersionMax();

  Standard_EXPORT static const char* DraftingName(const int flag);

  Standard_EXPORT static int DraftingMax();

  Standard_EXPORT static int GetFlagByValue(const double theValue);

private:
  bool                            theunit;
  occ::handle<IGESData_Protocol>  theproto;
  occ::handle<IGESData_IGESModel> themodel;
  Interface_GeneralLib            theglib;
  IGESData_SpecificLib            theslib;
};

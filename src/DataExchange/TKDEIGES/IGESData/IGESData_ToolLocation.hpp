#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Interface_GeneralLib.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Transient.hpp>
class IGESData_IGESModel;
class IGESData_Protocol;
class IGESData_IGESEntity;
class gp_GTrsf;
class gp_Trsf;

class IGESData_ToolLocation : public Standard_Transient
{

public:
  Standard_EXPORT IGESData_ToolLocation(const occ::handle<IGESData_IGESModel>& amodel,
                                        const occ::handle<IGESData_Protocol>&  protocol);

  Standard_EXPORT void Load();

  Standard_EXPORT void SetPrecision(const double prec);

  Standard_EXPORT void SetReference(const occ::handle<IGESData_IGESEntity>& parent,
                                    const occ::handle<IGESData_IGESEntity>& child);

  Standard_EXPORT void SetParentAssoc(const occ::handle<IGESData_IGESEntity>& parent,
                                      const occ::handle<IGESData_IGESEntity>& child);

  Standard_EXPORT void ResetDependences(const occ::handle<IGESData_IGESEntity>& child);

  Standard_EXPORT void SetOwnAsDependent(const occ::handle<IGESData_IGESEntity>& ent);

  Standard_EXPORT bool IsTransf(const occ::handle<IGESData_IGESEntity>& ent) const;

  Standard_EXPORT bool IsAssociativity(const occ::handle<IGESData_IGESEntity>& ent) const;

  Standard_EXPORT bool HasTransf(const occ::handle<IGESData_IGESEntity>& ent) const;

  Standard_EXPORT gp_GTrsf ExplicitLocation(const occ::handle<IGESData_IGESEntity>& ent) const;

  Standard_EXPORT bool IsAmbiguous(const occ::handle<IGESData_IGESEntity>& ent) const;

  Standard_EXPORT bool HasParent(const occ::handle<IGESData_IGESEntity>& ent) const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> Parent(
    const occ::handle<IGESData_IGESEntity>& ent) const;

  Standard_EXPORT bool HasParentByAssociativity(const occ::handle<IGESData_IGESEntity>& ent) const;

  Standard_EXPORT gp_GTrsf ParentLocation(const occ::handle<IGESData_IGESEntity>& ent) const;

  Standard_EXPORT gp_GTrsf EffectiveLocation(const occ::handle<IGESData_IGESEntity>& ent) const;

  Standard_EXPORT bool AnalyseLocation(const gp_GTrsf& loc, gp_Trsf& result) const;

  Standard_EXPORT static bool ConvertLocation(const double    prec,
                                              const gp_GTrsf& loc,
                                              gp_Trsf&        result,
                                              const double    uni = 1);

  DEFINE_STANDARD_RTTIEXT(IGESData_ToolLocation, Standard_Transient)

private:
  double                          theprec;
  occ::handle<IGESData_IGESModel> themodel;
  Interface_GeneralLib            thelib;
  NCollection_Array1<int>         therefs;
  NCollection_Array1<int>         theassocs;
};

#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_GeneralModule.hpp>
#include <Standard_Integer.hpp>
class IGESData_IGESEntity;
class Interface_EntityIterator;
class IGESData_DirChecker;
class Interface_ShareTool;
class Interface_Check;
class Standard_Transient;
class Interface_CopyTool;

class IGESDimen_GeneralModule : public IGESData_GeneralModule
{

public:
  Standard_EXPORT IGESDimen_GeneralModule();

  Standard_EXPORT void OwnSharedCase(const int                               CN,
                                     const occ::handle<IGESData_IGESEntity>& ent,
                                     Interface_EntityIterator&               iter) const override;

  Standard_EXPORT IGESData_DirChecker
    DirChecker(const int CN, const occ::handle<IGESData_IGESEntity>& ent) const override;

  Standard_EXPORT void OwnCheckCase(const int                               CN,
                                    const occ::handle<IGESData_IGESEntity>& ent,
                                    const Interface_ShareTool&              shares,
                                    occ::handle<Interface_Check>&           ach) const override;

  Standard_EXPORT bool NewVoid(const int CN, occ::handle<Standard_Transient>& entto) const override;

  Standard_EXPORT void OwnCopyCase(const int                               CN,
                                   const occ::handle<IGESData_IGESEntity>& entfrom,
                                   const occ::handle<IGESData_IGESEntity>& entto,
                                   Interface_CopyTool&                     TC) const override;

  Standard_EXPORT int CategoryNumber(const int                              CN,
                                     const occ::handle<Standard_Transient>& ent,
                                     const Interface_ShareTool&             shares) const override;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_GeneralModule, IGESData_GeneralModule)
};

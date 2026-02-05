#pragma once

#include <Standard.hpp>

#include <IGESData_GeneralModule.hpp>
#include <Standard_Integer.hpp>
class IGESData_IGESEntity;
class Interface_EntityIterator;
class IGESData_DirChecker;
class Interface_ShareTool;
class Interface_Check;
class Standard_Transient;
class Interface_CopyTool;

//! Processes the specific case of UndefinedEntity from IGESData
//! (Case Number 1)
class IGESData_DefaultGeneral : public IGESData_GeneralModule
{

public:
  //! Creates a DefaultGeneral and puts it into GeneralLib,
  //! bound with a Protocol from IGESData
  Standard_EXPORT IGESData_DefaultGeneral();

  //! Lists the Entities shared by an IGESEntity, which must be
  //! an UndefinedEntity
  Standard_EXPORT void OwnSharedCase(const int                               CN,
                                     const occ::handle<IGESData_IGESEntity>& ent,
                                     Interface_EntityIterator&               iter) const override;

  //! Returns a DirChecker, specific for each type of Entity
  //! Here, Returns an empty DirChecker (no constraint to check)
  Standard_EXPORT IGESData_DirChecker
    DirChecker(const int CN, const occ::handle<IGESData_IGESEntity>& ent) const override;

  //! Performs Specific Semantic Check for each type of Entity
  //! Here, does nothing (no constraint to check)
  Standard_EXPORT void OwnCheckCase(const int                               CN,
                                    const occ::handle<IGESData_IGESEntity>& ent,
                                    const Interface_ShareTool&              shares,
                                    occ::handle<Interface_Check>&           ach) const override;

  //! Specific creation of a new void entity (UndefinedEntity only)
  Standard_EXPORT bool NewVoid(const int CN, occ::handle<Standard_Transient>& entto) const override;

  //! Copies parameters which are specific of each Type of Entity
  Standard_EXPORT void OwnCopyCase(const int                               CN,
                                   const occ::handle<IGESData_IGESEntity>& entfrom,
                                   const occ::handle<IGESData_IGESEntity>& entto,
                                   Interface_CopyTool&                     TC) const override;

  DEFINE_STANDARD_RTTIEXT(IGESData_DefaultGeneral, IGESData_GeneralModule)
};

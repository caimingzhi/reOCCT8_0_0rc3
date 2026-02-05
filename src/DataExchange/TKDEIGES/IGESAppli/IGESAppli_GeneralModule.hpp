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

//! Definition of General Services for IGESAppli (specific part)
//! This Services comprise : Shared & Implied Lists, Copy, Check
class IGESAppli_GeneralModule : public IGESData_GeneralModule
{

public:
  //! Creates a GeneralModule from IGESAppli and puts it into GeneralLib
  Standard_EXPORT IGESAppli_GeneralModule();

  //! Lists the Entities shared by a given IGESEntity <ent>, from
  //! its specific parameters : specific for each type
  Standard_EXPORT void OwnSharedCase(const int                               CN,
                                     const occ::handle<IGESData_IGESEntity>& ent,
                                     Interface_EntityIterator&               iter) const override;

  //! Returns a DirChecker, specific for each type of Entity
  //! (identified by its Case Number) : this DirChecker defines
  //! constraints which must be respected by the DirectoryPart
  Standard_EXPORT IGESData_DirChecker
    DirChecker(const int CN, const occ::handle<IGESData_IGESEntity>& ent) const override;

  //! Performs Specific Semantic Check for each type of Entity
  Standard_EXPORT void OwnCheckCase(const int                               CN,
                                    const occ::handle<IGESData_IGESEntity>& ent,
                                    const Interface_ShareTool&              shares,
                                    occ::handle<Interface_Check>&           ach) const override;

  //! Specific creation of a new void entity
  Standard_EXPORT bool NewVoid(const int CN, occ::handle<Standard_Transient>& entto) const override;

  //! Copies parameters which are specific of each Type of Entity
  Standard_EXPORT void OwnCopyCase(const int                               CN,
                                   const occ::handle<IGESData_IGESEntity>& entfrom,
                                   const occ::handle<IGESData_IGESEntity>& entto,
                                   Interface_CopyTool&                     TC) const override;

  //! Returns a category number which characterizes an entity
  //! FEA for : ElementResults,FiniteElement,Node&Co
  //! Piping for : Flow & Co
  //! Professional for : others (in fact Schematics)
  Standard_EXPORT int CategoryNumber(const int                              CN,
                                     const occ::handle<Standard_Transient>& ent,
                                     const Interface_ShareTool&             shares) const override;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_GeneralModule, IGESData_GeneralModule)
};

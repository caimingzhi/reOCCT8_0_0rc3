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

//! Definition of General Services for IGESDraw (specific part)
//! This Services comprise : Shared & Implied Lists, Copy, Check
class IGESDraw_GeneralModule : public IGESData_GeneralModule
{

public:
  //! Creates a GeneralModule from IGESDraw and puts it into GeneralLib
  Standard_EXPORT IGESDraw_GeneralModule();

  //! Lists the Entities shared by a given IGESEntity <ent>, from
  //! its specific parameters : specific for each type
  Standard_EXPORT void OwnSharedCase(const int                               CN,
                                     const occ::handle<IGESData_IGESEntity>& ent,
                                     Interface_EntityIterator&               iter) const override;

  //! Specific list of Entities implied by an IGESEntity <ent> (in
  //! addition to Associativities). Redefined for ViewsVisible ...
  Standard_EXPORT void OwnImpliedCase(const int                               CN,
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

  //! Renews parameters which are specific of each Type of Entity :
  //! redefined for ViewsVisible ... (takes only the implied ref.s
  //! which have also been copied)
  Standard_EXPORT void OwnRenewCase(const int                               CN,
                                    const occ::handle<IGESData_IGESEntity>& entfrom,
                                    const occ::handle<IGESData_IGESEntity>& entto,
                                    const Interface_CopyTool&               TC) const override;

  //! Clears parameters with can cause looping structures :
  //! redefined for ViewsVisible ... (clears the implied ref.s)
  Standard_EXPORT void OwnDeleteCase(const int                               CN,
                                     const occ::handle<IGESData_IGESEntity>& ent) const override;

  //! Returns a category number which characterizes an entity
  //! Planar : Auxiliary
  //! Subfigures and ConnectPoint : Structure
  //! others : Drawing
  Standard_EXPORT int CategoryNumber(const int                              CN,
                                     const occ::handle<Standard_Transient>& ent,
                                     const Interface_ShareTool&             shares) const override;

  DEFINE_STANDARD_RTTIEXT(IGESDraw_GeneralModule, IGESData_GeneralModule)
};

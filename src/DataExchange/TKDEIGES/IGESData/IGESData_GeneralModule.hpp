#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Interface_GeneralModule.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class Interface_EntityIterator;
class IGESData_IGESEntity;
class Interface_ShareTool;
class Interface_Check;
class IGESData_DirChecker;
class Interface_CopyTool;
class TCollection_HAsciiString;

class IGESData_GeneralModule : public Interface_GeneralModule
{

public:
  Standard_EXPORT void FillSharedCase(const int                              CN,
                                      const occ::handle<Standard_Transient>& ent,
                                      Interface_EntityIterator&              iter) const override;

  Standard_EXPORT virtual void OwnSharedCase(const int                               CN,
                                             const occ::handle<IGESData_IGESEntity>& ent,
                                             Interface_EntityIterator& iter) const = 0;

  Standard_EXPORT void ListImpliedCase(const int                              CN,
                                       const occ::handle<Standard_Transient>& ent,
                                       Interface_EntityIterator&              iter) const override;

  Standard_EXPORT virtual void OwnImpliedCase(const int                               CN,
                                              const occ::handle<IGESData_IGESEntity>& ent,
                                              Interface_EntityIterator&               iter) const;

  Standard_EXPORT void CheckCase(const int                              CN,
                                 const occ::handle<Standard_Transient>& ent,
                                 const Interface_ShareTool&             shares,
                                 occ::handle<Interface_Check>&          ach) const override;

  Standard_EXPORT virtual IGESData_DirChecker DirChecker(
    const int                               CN,
    const occ::handle<IGESData_IGESEntity>& ent) const = 0;

  Standard_EXPORT virtual void OwnCheckCase(const int                               CN,
                                            const occ::handle<IGESData_IGESEntity>& ent,
                                            const Interface_ShareTool&              shares,
                                            occ::handle<Interface_Check>&           ach) const = 0;

  Standard_EXPORT bool CanCopy(const int                              CN,
                               const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT bool NewVoid(const int                        CN,
                               occ::handle<Standard_Transient>& entto) const override = 0;

  Standard_EXPORT void CopyCase(const int                              CN,
                                const occ::handle<Standard_Transient>& entfrom,
                                const occ::handle<Standard_Transient>& entto,
                                Interface_CopyTool&                    TC) const override;

  Standard_EXPORT virtual void OwnCopyCase(const int                               CN,
                                           const occ::handle<IGESData_IGESEntity>& entfrom,
                                           const occ::handle<IGESData_IGESEntity>& entto,
                                           Interface_CopyTool&                     TC) const = 0;

  Standard_EXPORT void RenewImpliedCase(const int                              CN,
                                        const occ::handle<Standard_Transient>& entfrom,
                                        const occ::handle<Standard_Transient>& entto,
                                        const Interface_CopyTool&              TC) const override;

  Standard_EXPORT virtual void OwnRenewCase(const int                               CN,
                                            const occ::handle<IGESData_IGESEntity>& entfrom,
                                            const occ::handle<IGESData_IGESEntity>& entto,
                                            const Interface_CopyTool&               TC) const;

  Standard_EXPORT void WhenDeleteCase(const int                              CN,
                                      const occ::handle<Standard_Transient>& ent,
                                      const bool dispatched) const override;

  Standard_EXPORT virtual void OwnDeleteCase(const int                               CN,
                                             const occ::handle<IGESData_IGESEntity>& ent) const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name(
    const int                              CN,
    const occ::handle<Standard_Transient>& ent,
    const Interface_ShareTool&             shares) const override;

  DEFINE_STANDARD_RTTIEXT(IGESData_GeneralModule, Interface_GeneralModule)
};

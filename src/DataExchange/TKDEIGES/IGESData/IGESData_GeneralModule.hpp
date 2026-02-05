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

//! Definition of General Services adapted to IGES.
//! This Services comprise : Shared & Implied Lists, Copy, Check
//! They are adapted according to the organisation of IGES
//! Entities : Directory Part, Lists of Associativities and
//! Properties are specifically processed
class IGESData_GeneralModule : public Interface_GeneralModule
{

public:
  //! Fills the list of Entities shared by an IGESEntity <ent>,
  //! according a Case Number <CN> (formerly computed by CaseNum).
  //! Considers Properties and Directory Part, and calls
  //! OwnSharedCase (which is adapted to each Type of Entity)
  Standard_EXPORT void FillSharedCase(const int                              CN,
                                      const occ::handle<Standard_Transient>& ent,
                                      Interface_EntityIterator&              iter) const override;

  //! Lists the Entities shared by a given IGESEntity <ent>, from
  //! its specific parameters : specific for each type
  Standard_EXPORT virtual void OwnSharedCase(const int                               CN,
                                             const occ::handle<IGESData_IGESEntity>& ent,
                                             Interface_EntityIterator& iter) const = 0;

  //! Lists the Implied References of <ent>. Here, these are the
  //! Associativities, plus the Entities defined by OwnSharedCase
  Standard_EXPORT void ListImpliedCase(const int                              CN,
                                       const occ::handle<Standard_Transient>& ent,
                                       Interface_EntityIterator&              iter) const override;

  //! Specific list of Entities implied by a given IGESEntity <ent>
  //! (in addition to Associativities). By default, there are none,
  //! but this method can be redefined as required
  Standard_EXPORT virtual void OwnImpliedCase(const int                               CN,
                                              const occ::handle<IGESData_IGESEntity>& ent,
                                              Interface_EntityIterator&               iter) const;

  //! Semantic Checking of an IGESEntity. Performs general Checks,
  //! which use DirChecker, then call OwnCheck which does a check
  //! specific for each type of Entity
  Standard_EXPORT void CheckCase(const int                              CN,
                                 const occ::handle<Standard_Transient>& ent,
                                 const Interface_ShareTool&             shares,
                                 occ::handle<Interface_Check>&          ach) const override;

  //! Returns a DirChecker, specific for each type of Entity
  //! (identified by its Case Number) : this DirChecker defines
  //! constraints which must be respected by the DirectoryPart
  Standard_EXPORT virtual IGESData_DirChecker DirChecker(
    const int                               CN,
    const occ::handle<IGESData_IGESEntity>& ent) const = 0;

  //! Performs Specific Semantic Check for each type of Entity
  Standard_EXPORT virtual void OwnCheckCase(const int                               CN,
                                            const occ::handle<IGESData_IGESEntity>& ent,
                                            const Interface_ShareTool&              shares,
                                            occ::handle<Interface_Check>&           ach) const = 0;

  //! Specific answer to the question "is Copy properly implemented"
  //! For IGES, answer is always True
  Standard_EXPORT bool CanCopy(const int                              CN,
                               const occ::handle<Standard_Transient>& ent) const override;

  //! Specific creation of a new void entity
  Standard_EXPORT bool NewVoid(const int                        CN,
                               occ::handle<Standard_Transient>& entto) const override = 0;

  //! Copy ("Deep") from <entfrom> to <entto> (same type)
  //! by using a CopyTool which provides its working Map.
  //! For IGESEntities, Copies general data (Directory Part, List of
  //! Properties) and call OwnCopyCase
  Standard_EXPORT void CopyCase(const int                              CN,
                                const occ::handle<Standard_Transient>& entfrom,
                                const occ::handle<Standard_Transient>& entto,
                                Interface_CopyTool&                    TC) const override;

  //! Copies parameters which are specific of each Type of Entity
  Standard_EXPORT virtual void OwnCopyCase(const int                               CN,
                                           const occ::handle<IGESData_IGESEntity>& entfrom,
                                           const occ::handle<IGESData_IGESEntity>& entto,
                                           Interface_CopyTool&                     TC) const = 0;

  //! Renewing of Implied References.
  //! For IGESEntities, Copies general data(List of Associativities)
  //! and calls OwnRenewCase
  Standard_EXPORT void RenewImpliedCase(const int                              CN,
                                        const occ::handle<Standard_Transient>& entfrom,
                                        const occ::handle<Standard_Transient>& entto,
                                        const Interface_CopyTool&              TC) const override;

  //! Renews parameters which are specific of each Type of Entity :
  //! the provided default does nothing, but this method may be
  //! redefined as required
  Standard_EXPORT virtual void OwnRenewCase(const int                               CN,
                                            const occ::handle<IGESData_IGESEntity>& entfrom,
                                            const occ::handle<IGESData_IGESEntity>& entto,
                                            const Interface_CopyTool&               TC) const;

  //! Prepares an IGES Entity for delete : works on directory part
  //! then calls OwnDeleteCase
  //! While dispatch requires to copy the entities, <dispatched> is
  //! ignored, entities are cleared in any case
  Standard_EXPORT void WhenDeleteCase(const int                              CN,
                                      const occ::handle<Standard_Transient>& ent,
                                      const bool dispatched) const override;

  //! Specific preparation for delete, acts on own parameters
  //! Default does nothing, to be redefined as required
  Standard_EXPORT virtual void OwnDeleteCase(const int                               CN,
                                             const occ::handle<IGESData_IGESEntity>& ent) const;

  //! Returns the name of an IGES Entity (its NameValue)
  //! Can be redefined for an even more specific case ...
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name(
    const int                              CN,
    const occ::handle<Standard_Transient>& ent,
    const Interface_ShareTool&             shares) const override;

  DEFINE_STANDARD_RTTIEXT(IGESData_GeneralModule, Interface_GeneralModule)
};

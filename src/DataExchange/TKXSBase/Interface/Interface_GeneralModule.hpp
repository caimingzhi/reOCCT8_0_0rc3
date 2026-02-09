#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class Interface_InterfaceModel;
class Interface_EntityIterator;
class Interface_ShareTool;
class Interface_Check;
class Interface_CopyTool;
class TCollection_HAsciiString;

class Interface_GeneralModule : public Standard_Transient
{

public:
  Standard_EXPORT virtual void FillShared(const occ::handle<Interface_InterfaceModel>& model,
                                          const int                                    CN,
                                          const occ::handle<Standard_Transient>&       ent,
                                          Interface_EntityIterator&                    iter) const;

  Standard_EXPORT virtual void FillSharedCase(const int                              CN,
                                              const occ::handle<Standard_Transient>& ent,
                                              Interface_EntityIterator& iter) const = 0;

  Standard_EXPORT void Share(Interface_EntityIterator&              iter,
                             const occ::handle<Standard_Transient>& shared) const;

  Standard_EXPORT virtual void ListImplied(const occ::handle<Interface_InterfaceModel>& model,
                                           const int                                    CN,
                                           const occ::handle<Standard_Transient>&       ent,
                                           Interface_EntityIterator&                    iter) const;

  Standard_EXPORT virtual void ListImpliedCase(const int                              CN,
                                               const occ::handle<Standard_Transient>& ent,
                                               Interface_EntityIterator&              iter) const;

  Standard_EXPORT virtual void CheckCase(const int                              CN,
                                         const occ::handle<Standard_Transient>& ent,
                                         const Interface_ShareTool&             shares,
                                         occ::handle<Interface_Check>&          ach) const = 0;

  Standard_EXPORT virtual bool CanCopy(const int                              CN,
                                       const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT virtual bool Dispatch(const int                              CN,
                                        const occ::handle<Standard_Transient>& entfrom,
                                        occ::handle<Standard_Transient>&       entto,
                                        Interface_CopyTool&                    TC) const;

  Standard_EXPORT virtual bool NewVoid(const int                        CN,
                                       occ::handle<Standard_Transient>& entto) const = 0;

  Standard_EXPORT virtual void CopyCase(const int                              CN,
                                        const occ::handle<Standard_Transient>& entfrom,
                                        const occ::handle<Standard_Transient>& entto,
                                        Interface_CopyTool&                    TC) const = 0;

  Standard_EXPORT virtual bool NewCopiedCase(const int                              CN,
                                             const occ::handle<Standard_Transient>& entfrom,
                                             occ::handle<Standard_Transient>&       entto,
                                             Interface_CopyTool&                    TC) const;

  Standard_EXPORT virtual void RenewImpliedCase(const int                              CN,
                                                const occ::handle<Standard_Transient>& entfrom,
                                                const occ::handle<Standard_Transient>& entto,
                                                const Interface_CopyTool&              TC) const;

  Standard_EXPORT virtual void WhenDeleteCase(const int                              CN,
                                              const occ::handle<Standard_Transient>& ent,
                                              const bool dispatched) const;

  Standard_EXPORT virtual int CategoryNumber(const int                              CN,
                                             const occ::handle<Standard_Transient>& ent,
                                             const Interface_ShareTool&             shares) const;

  Standard_EXPORT virtual occ::handle<TCollection_HAsciiString> Name(
    const int                              CN,
    const occ::handle<Standard_Transient>& ent,
    const Interface_ShareTool&             shares) const;

  DEFINE_STANDARD_RTTIEXT(Interface_GeneralModule, Standard_Transient)
};

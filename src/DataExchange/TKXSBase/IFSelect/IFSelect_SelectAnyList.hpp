#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectDeduct.hpp>
#include <Standard_Integer.hpp>
class IFSelect_IntParam;
class Interface_EntityIterator;
class Standard_Transient;
class Interface_Graph;
class TCollection_AsciiString;

class IFSelect_SelectAnyList : public IFSelect_SelectDeduct
{

public:
  Standard_EXPORT virtual void KeepInputEntity(Interface_EntityIterator& iter) const = 0;

  Standard_EXPORT virtual int NbItems(const occ::handle<Standard_Transient>& ent) const = 0;

  Standard_EXPORT void SetRange(const occ::handle<IFSelect_IntParam>& rankfrom,
                                const occ::handle<IFSelect_IntParam>& rankto);

  Standard_EXPORT void SetOne(const occ::handle<IFSelect_IntParam>& rank);

  Standard_EXPORT void SetFrom(const occ::handle<IFSelect_IntParam>& rankfrom);

  Standard_EXPORT void SetUntil(const occ::handle<IFSelect_IntParam>& rankto);

  Standard_EXPORT bool HasLower() const;

  Standard_EXPORT occ::handle<IFSelect_IntParam> Lower() const;

  Standard_EXPORT int LowerValue() const;

  Standard_EXPORT bool HasUpper() const;

  Standard_EXPORT occ::handle<IFSelect_IntParam> Upper() const;

  Standard_EXPORT int UpperValue() const;

  Standard_EXPORT Interface_EntityIterator RootResult(const Interface_Graph& G) const override;

  Standard_EXPORT virtual void FillResult(const int                              n1,
                                          const int                              n2,
                                          const occ::handle<Standard_Transient>& ent,
                                          Interface_EntityIterator&              res) const = 0;

  Standard_EXPORT TCollection_AsciiString Label() const override;

  Standard_EXPORT virtual TCollection_AsciiString ListLabel() const = 0;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectAnyList, IFSelect_SelectDeduct)

private:
  occ::handle<IFSelect_IntParam> thelower;
  occ::handle<IFSelect_IntParam> theupper;
};

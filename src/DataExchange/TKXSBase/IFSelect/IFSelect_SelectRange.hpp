#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectExtract.hpp>
#include <Standard_Integer.hpp>
class IFSelect_IntParam;
class Standard_Transient;
class Interface_InterfaceModel;
class TCollection_AsciiString;

class IFSelect_SelectRange : public IFSelect_SelectExtract
{

public:
  Standard_EXPORT IFSelect_SelectRange();

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

  Standard_EXPORT bool Sort(const int                                    rank,
                            const occ::handle<Standard_Transient>&       ent,
                            const occ::handle<Interface_InterfaceModel>& model) const override;

  Standard_EXPORT TCollection_AsciiString ExtractLabel() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectRange, IFSelect_SelectExtract)

private:
  occ::handle<IFSelect_IntParam> thelower;
  occ::handle<IFSelect_IntParam> theupper;
};

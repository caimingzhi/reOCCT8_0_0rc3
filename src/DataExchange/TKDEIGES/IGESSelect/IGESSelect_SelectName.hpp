#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectExtract.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class Standard_Transient;
class Interface_InterfaceModel;
class TCollection_AsciiString;

class IGESSelect_SelectName : public IFSelect_SelectExtract
{

public:
  Standard_EXPORT IGESSelect_SelectName();

  Standard_EXPORT bool Sort(const int                                    rank,
                            const occ::handle<Standard_Transient>&       ent,
                            const occ::handle<Interface_InterfaceModel>& model) const override;

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& name);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT TCollection_AsciiString ExtractLabel() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_SelectName, IFSelect_SelectExtract)

private:
  occ::handle<TCollection_HAsciiString> thename;
};

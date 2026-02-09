#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <IFSelect_SelectExtract.hpp>
class Standard_Transient;
class Interface_InterfaceModel;
class TCollection_AsciiString;

#ifdef Status
  #undef Status
#endif

class IGESSelect_SelectSubordinate : public IFSelect_SelectExtract
{

public:
  Standard_EXPORT IGESSelect_SelectSubordinate(const int status);

  Standard_EXPORT int Status() const;

  Standard_EXPORT bool Sort(const int                                    rank,
                            const occ::handle<Standard_Transient>&       ent,
                            const occ::handle<Interface_InterfaceModel>& model) const override;

  Standard_EXPORT TCollection_AsciiString ExtractLabel() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_SelectSubordinate, IFSelect_SelectExtract)

private:
  int thestatus;
};

#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SessionDumper.hpp>
class IFSelect_SessionFile;
class Standard_Transient;
class TCollection_AsciiString;

class IFSelect_BasicDumper : public IFSelect_SessionDumper
{

public:
  Standard_EXPORT IFSelect_BasicDumper();

  Standard_EXPORT bool WriteOwn(IFSelect_SessionFile&                  file,
                                const occ::handle<Standard_Transient>& item) const override;

  Standard_EXPORT bool ReadOwn(IFSelect_SessionFile&            file,
                               const TCollection_AsciiString&   type,
                               occ::handle<Standard_Transient>& item) const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_BasicDumper, IFSelect_SessionDumper)
};

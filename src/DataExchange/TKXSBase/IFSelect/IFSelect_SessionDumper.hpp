#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class IFSelect_SessionFile;
class TCollection_AsciiString;

class IFSelect_SessionDumper : public Standard_Transient
{

public:
  Standard_EXPORT static occ::handle<IFSelect_SessionDumper> First();

  Standard_EXPORT occ::handle<IFSelect_SessionDumper> Next() const;

  Standard_EXPORT virtual bool WriteOwn(IFSelect_SessionFile&                  file,
                                        const occ::handle<Standard_Transient>& item) const = 0;

  Standard_EXPORT virtual bool ReadOwn(IFSelect_SessionFile&            file,
                                       const TCollection_AsciiString&   type,
                                       occ::handle<Standard_Transient>& item) const = 0;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SessionDumper, Standard_Transient)

protected:
  Standard_EXPORT IFSelect_SessionDumper();

private:
  occ::handle<IFSelect_SessionDumper> thenext;
};

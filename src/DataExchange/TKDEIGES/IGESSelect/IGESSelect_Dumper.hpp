#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SessionDumper.hpp>
class IFSelect_SessionFile;
class Standard_Transient;
class TCollection_AsciiString;

//! Dumper from IGESSelect takes into account, for SessionFile, the
//! classes defined in the package IGESSelect : Selections,
//! Dispatches, Modifiers
class IGESSelect_Dumper : public IFSelect_SessionDumper
{

public:
  //! Creates a Dumper and puts it into the Library of Dumper
  Standard_EXPORT IGESSelect_Dumper();

  //! Write the Own Parameters of Types defined in package IGESSelect
  //! Returns True if <item> has been processed, False else
  Standard_EXPORT bool WriteOwn(IFSelect_SessionFile&                  file,
                                const occ::handle<Standard_Transient>& item) const override;

  //! Recognizes and Read Own Parameters for Types of package
  //! IGESSelect. Returns True if done and <item> created, False else
  Standard_EXPORT bool ReadOwn(IFSelect_SessionFile&            file,
                               const TCollection_AsciiString&   type,
                               occ::handle<Standard_Transient>& item) const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_Dumper, IFSelect_SessionDumper)
};

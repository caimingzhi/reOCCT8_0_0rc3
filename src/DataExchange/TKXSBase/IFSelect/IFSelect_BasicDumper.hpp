#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SessionDumper.hpp>
class IFSelect_SessionFile;
class Standard_Transient;
class TCollection_AsciiString;

//! BasicDumper takes into account, for SessionFile, all the
//! classes defined in the package IFSelect : Selections,
//! Dispatches (there is no Modifier)
class IFSelect_BasicDumper : public IFSelect_SessionDumper
{

public:
  //! Creates a BasicDumper and puts it into the Library of Dumper
  Standard_EXPORT IFSelect_BasicDumper();

  //! Write the Own Parameters of Types defined in package IFSelect
  //! Returns True if <item> has been processed, False else
  Standard_EXPORT bool WriteOwn(IFSelect_SessionFile&                  file,
                                const occ::handle<Standard_Transient>& item) const override;

  //! Recognizes and Read Own Parameters for Types of package
  //! IFSelect. Returns True if done and <item> created, False else
  Standard_EXPORT bool ReadOwn(IFSelect_SessionFile&            file,
                               const TCollection_AsciiString&   type,
                               occ::handle<Standard_Transient>& item) const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_BasicDumper, IFSelect_SessionDumper)
};

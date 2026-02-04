#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_AsciiString;

//! Provides the basic service to get a text which identifies
//! an object in a context
//! It can be used for other classes (general signatures ...)
//! It can also be used to build a message in which an object
//! is to be identified
class MoniTool_SignText : public Standard_Transient
{

public:
  //! Returns an identification of the Signature (a word), given at
  //! initialization time
  Standard_EXPORT virtual const char* Name() const = 0;

  //! Gives a text as a signature for a transient object alone, i.e.
  //! without defined context.
  //! By default, calls Text with undefined context (Null Handle) and
  //! if empty, then returns DynamicType
  Standard_EXPORT virtual TCollection_AsciiString TextAlone(
    const occ::handle<Standard_Transient>& ent) const;

  //! Gives a text as a signature for a transient object in a context
  //! If the context is senseless, it can be given as Null Handle
  //! empty result if nothing to give (at least the DynamicType could
  //! be sent ?)
  Standard_EXPORT virtual TCollection_AsciiString Text(
    const occ::handle<Standard_Transient>& ent,
    const occ::handle<Standard_Transient>& context) const = 0;

  DEFINE_STANDARD_RTTIEXT(MoniTool_SignText, Standard_Transient)
};


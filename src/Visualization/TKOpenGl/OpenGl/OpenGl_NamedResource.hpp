#pragma once


#include <OpenGl_Resource.hpp>
#include <TCollection_AsciiString.hpp>

//! Named resource object.
class OpenGl_NamedResource : public OpenGl_Resource
{
  DEFINE_STANDARD_RTTIEXT(OpenGl_NamedResource, OpenGl_Resource)
public:
  //! Empty constructor
  OpenGl_NamedResource(const TCollection_AsciiString& theId)
      : myResourceId(theId)
  {
  }

  //! Return resource name.
  const TCollection_AsciiString& ResourceId() const { return myResourceId; }

protected:
  TCollection_AsciiString myResourceId; //!< resource name
};


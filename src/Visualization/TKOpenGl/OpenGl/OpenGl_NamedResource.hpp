#pragma once

#include <OpenGl_Resource.hpp>
#include <TCollection_AsciiString.hpp>

class OpenGl_NamedResource : public OpenGl_Resource
{
  DEFINE_STANDARD_RTTIEXT(OpenGl_NamedResource, OpenGl_Resource)
public:
  OpenGl_NamedResource(const TCollection_AsciiString& theId)
      : myResourceId(theId)
  {
  }

  const TCollection_AsciiString& ResourceId() const { return myResourceId; }

protected:
  TCollection_AsciiString myResourceId;
};

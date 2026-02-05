#include <OpenGl_Resource.hpp>
#include <OpenGl_NamedResource.hpp>

IMPLEMENT_STANDARD_RTTIEXT(OpenGl_Resource, Standard_Transient)
IMPLEMENT_STANDARD_RTTIEXT(OpenGl_NamedResource, OpenGl_Resource)

OpenGl_Resource::OpenGl_Resource() = default;

OpenGl_Resource::~OpenGl_Resource() = default;

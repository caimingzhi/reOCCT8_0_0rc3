#include <VrmlAPI.hpp>

#include <TopoDS_Shape.hpp>
#include <VrmlAPI_Writer.hpp>

bool VrmlAPI::Write(const TopoDS_Shape& aShape, const char* aFileName, const int aVersion)
{
  VrmlAPI_Writer writer;
  return writer.Write(aShape, aFileName, aVersion);
}

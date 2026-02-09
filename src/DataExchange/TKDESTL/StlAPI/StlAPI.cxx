

#include <StlAPI.hpp>

#include <StlAPI_Reader.hpp>
#include <StlAPI_Writer.hpp>
#include <TopoDS_Shape.hpp>

bool StlAPI::Write(const TopoDS_Shape& theShape, const char* theFile, const bool theAsciiMode)
{
  StlAPI_Writer aWriter;
  aWriter.ASCIIMode() = theAsciiMode;
  return aWriter.Write(theShape, theFile);
}

bool StlAPI::Read(TopoDS_Shape& theShape, const char* theFile)
{
  StlAPI_Reader aReader;
  return aReader.Read(theShape, theFile);
}

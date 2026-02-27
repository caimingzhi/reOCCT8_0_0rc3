

#include <RWObj.hpp>

#include <RWObj_TriangulationReader.hpp>

occ::handle<Poly_Triangulation> RWObj::ReadFile(const char*                  theFile,
                                                const System::log::Message_ProgressRange& theProgress)
{
  RWObj_TriangulationReader aReader;
  aReader.SetCreateShapes(false);
  aReader.Read(theFile, theProgress);

  return aReader.GetTriangulation();
}

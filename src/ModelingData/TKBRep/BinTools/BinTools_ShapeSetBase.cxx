

#include <BinTools.hpp>
#include <BinTools_ShapeSetBase.hpp>
#include <TopoDS_Shape.hpp>

const char* BinTools_ShapeSetBase::THE_ASCII_VERSIONS[BinTools_FormatVersion_UPPER + 1] = {
  "",
  "Open CASCADE Topology V1 (c)",
  "Open CASCADE Topology V2 (c)",
  "Open CASCADE Topology V3 (c)",
  "Open CASCADE Topology V4, (c) Open Cascade"};

Standard_OStream& operator<<(Standard_OStream& OS, const gp_Pnt& P)
{
  BinTools::PutReal(OS, P.X());
  BinTools::PutReal(OS, P.Y());
  BinTools::PutReal(OS, P.Z());
  return OS;
}

BinTools_ShapeSetBase::BinTools_ShapeSetBase()
    : myFormatNb(BinTools_FormatVersion_CURRENT),
      myWithTriangles(false),
      myWithNormals(false)
{
}

BinTools_ShapeSetBase::~BinTools_ShapeSetBase() = default;

void BinTools_ShapeSetBase::SetFormatNb(const int theFormatNb)
{
  Standard_ASSERT_RETURN(theFormatNb >= BinTools_FormatVersion_LOWER
                           && theFormatNb <= BinTools_FormatVersion_UPPER,
                         "Error: unsupported BinTools version.",
                         Standard_VOID_RETURN);

  myFormatNb = theFormatNb;
}

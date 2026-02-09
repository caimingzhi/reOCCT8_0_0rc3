

#include <MoniTool_SignShape.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TopoDS_HShape.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(MoniTool_SignShape, MoniTool_SignText)

MoniTool_SignShape::MoniTool_SignShape() = default;

const char* MoniTool_SignShape::Name() const
{
  return "SHAPE";
}

TCollection_AsciiString MoniTool_SignShape::Text(const occ::handle<Standard_Transient>& ent,
                                                 const occ::handle<Standard_Transient>&) const
{
  if (ent.IsNull())
    return "";
  occ::handle<TopoDS_HShape> HS = occ::down_cast<TopoDS_HShape>(ent);
  if (HS.IsNull())
    return ent->DynamicType()->Name();
  TopoDS_Shape sh = HS->Shape();
  if (sh.IsNull())
    return "SHAPE";
  return TopAbs::ShapeTypeToString(sh.ShapeType());
}

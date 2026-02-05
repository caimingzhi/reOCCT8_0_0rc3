#include <DBRep_Face.hpp>
#include <Draw_Color.hpp>
#include <Standard_Type.hpp>
#include <TopoDS_Face.hpp>

IMPLEMENT_STANDARD_RTTIEXT(DBRep_Face, Standard_Transient)

//=================================================================================================

DBRep_Face::DBRep_Face(const TopoDS_Face& F, const int N, const Draw_Color& C)
    : myFace(F),
      myColor(C),
      myTypes(N ? 1 : 0, N),
      myParams(N ? 1 : 0, 3 * N)
{
}

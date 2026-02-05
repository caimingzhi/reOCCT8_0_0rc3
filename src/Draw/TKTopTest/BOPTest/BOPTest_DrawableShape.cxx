#include <BOPTest_DrawableShape.hpp>
#include <BRep_Tool.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <BRepTools.hpp>
#include <DBRep_DrawableShape.hpp>
#include <Draw_Color.hpp>
#include <Draw_Display.hpp>
#include <Draw_Text3D.hpp>
#include <gp_Pnt.hpp>
#include <Standard_Type.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(BOPTest_DrawableShape, DBRep_DrawableShape)

//=================================================================================================

BOPTest_DrawableShape::BOPTest_DrawableShape(const TopoDS_Shape& aShape,
                                             const Draw_Color&   FreeCol,
                                             const Draw_Color&   ConnCol,
                                             const Draw_Color&   EdgeCol,
                                             const Draw_Color&   IsosCol,
                                             const double        size,
                                             const int           nbisos,
                                             const int           discret,
                                             const char*         Text,
                                             const Draw_Color&   TextColor)
    : DBRep_DrawableShape(aShape, FreeCol, ConnCol, EdgeCol, IsosCol, size, nbisos, discret)
{
  myText      = new Draw_Text3D(Pnt(), Text, TextColor);
  myTextColor = TextColor;
}

//=================================================================================================

BOPTest_DrawableShape::BOPTest_DrawableShape(const TopoDS_Shape& aShape,
                                             const char*         Text,
                                             const Draw_Color&   TextColor)
    : DBRep_DrawableShape(aShape,
                          Draw_vert,
                          Draw_jaune,
                          Draw_rouge,
                          Draw_bleu,
                          100., // size
                          2,    // nbIsos
                          30)   // discret
{
  myText      = new Draw_Text3D(Pnt(), Text, TextColor);
  myTextColor = TextColor;
}

//=================================================================================================

gp_Pnt BOPTest_DrawableShape::Pnt() const
{
  gp_Pnt          P(0, 0, 0);
  double          u, v, u1, u2, v1, v2, p;
  TopExp_Explorer ex;

  TopoDS_Shape     S      = Shape();
  TopAbs_ShapeEnum T      = S.ShapeType();
  double           facpar = 0.;

  while (T == TopAbs_COMPOUND)
  {
    TopoDS_Iterator ti(S);
    if (ti.More())
    {
      S = ti.Value();
      T = S.ShapeType();
    }
    else
    {
      break;
    }
  }
  // si S final = compound --> P = 0 0 0

  switch (T)
  {
    case TopAbs_VERTEX:
      P = BRep_Tool::Pnt(TopoDS::Vertex(S));
      break;

    case TopAbs_EDGE:
    {
      BRepAdaptor_Curve CU(TopoDS::Edge(S));
      u1 = CU.FirstParameter();
      u2 = CU.LastParameter();
      if (facpar == 0.)
        facpar = 0.20;
      p = u1 + (u2 - u1) * facpar;
      P = CU.Value(p);
    }
    break;

    case TopAbs_WIRE:
    {
      NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aME;
      TopExp::MapShapes(S, TopAbs_EDGE, aME);
      const TopoDS_Edge& anEdge = TopoDS::Edge(aME(1));
      BRepAdaptor_Curve  CU(anEdge);
      u1 = CU.FirstParameter();
      u2 = CU.LastParameter();
      if (facpar == 0.)
        facpar = 0.40;
      p = u1 + (u2 - u1) * facpar;
      P = CU.Value(p);
    }
    break;

    case TopAbs_FACE:
    {
      BRepAdaptor_Surface SU(TopoDS::Face(S));
      BRepTools::UVBounds(TopoDS::Face(S), u1, u2, v1, v2);
      //
      facpar = .2;
      u      = u1 + (u2 - u1) * facpar;
      v      = v1 + (v2 - v1) * facpar;
      P      = SU.Value(u, v);
    }
    break;

    case TopAbs_SHELL:
    case TopAbs_SOLID:
    {
      NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aMF;
      TopExp::MapShapes(S, TopAbs_FACE, aMF);
      const TopoDS_Face& aF = TopoDS::Face(aMF(1));

      BRepAdaptor_Surface SU(TopoDS::Face(aF));
      BRepTools::UVBounds(aF, u1, u2, v1, v2);
      facpar = .4;
      u      = u1 + (u2 - u1) * facpar;
      v      = v1 + (v2 - v1) * facpar;
      P      = SU.Value(u, v);
    }
    break;

    default:
      break;
  }
  return P;
}

//=================================================================================================

void BOPTest_DrawableShape::DrawOn(Draw_Display& dis) const
{
  DBRep_DrawableShape::DrawOn(dis);
  myText->SetPnt(Pnt());
  myText->DrawOn(dis);
}

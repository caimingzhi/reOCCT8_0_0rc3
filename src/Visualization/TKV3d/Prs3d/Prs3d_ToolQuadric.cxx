#include <Prs3d_ToolQuadric.hpp>

#include <Graphic3d_ArrayOfTriangles.hpp>
#include <Poly_Triangle.hpp>
#include <NCollection_Array1.hpp>

//=================================================================================================

void Prs3d_ToolQuadric::FillArray(occ::handle<Graphic3d_ArrayOfTriangles>& theArray,
                                  const gp_Trsf&                           theTrsf) const
{
  if (theArray.IsNull())
  {
    theArray = new Graphic3d_ArrayOfTriangles(VerticesNb(),
                                              TrianglesNb() * 3,
                                              Graphic3d_ArrayFlags_VertexNormal);
  }

  const double aStepU = 1.0f / mySlicesNb;
  const double aStepV = 1.0f / myStacksNb;
  if (theArray->EdgeNumberAllocated() > 0)
  {
    // indexed array
    for (int aU = 0; aU <= mySlicesNb; ++aU)
    {
      const double aParamU = aU * aStepU;
      for (int aV = 0; aV <= myStacksNb; ++aV)
      {
        const double aParamV = aV * aStepV;
        const gp_Pnt aVertex = Vertex(aParamU, aParamV).Transformed(theTrsf);
        const gp_Dir aNormal = Normal(aParamU, aParamV).Transformed(theTrsf);
        theArray->AddVertex(aVertex, aNormal);

        if (aU != 0 && aV != 0)
        {
          const int aVertId = theArray->VertexNumber();
          theArray->AddTriangleEdges(aVertId, aVertId - myStacksNb - 2, aVertId - 1);
          theArray->AddTriangleEdges(aVertId - myStacksNb - 2, aVertId, aVertId - myStacksNb - 1);
        }
      }
    }
  }
  else
  {
    // non-indexed array
    for (int aU = 0; aU < mySlicesNb; ++aU)
    {
      const double aParamU = aU * aStepU;
      for (int aV = 0; aV < myStacksNb; ++aV)
      {
        const double aParamV = aV * aStepV;
        theArray->AddVertex(Vertex(aParamU, aParamV).Transformed(theTrsf),
                            Normal(aParamU, aParamV).Transformed(theTrsf));
        theArray->AddVertex(Vertex(aParamU + aStepU, aParamV).Transformed(theTrsf),
                            Normal(aParamU + aStepU, aParamV).Transformed(theTrsf));
        theArray->AddVertex(Vertex(aParamU + aStepU, aParamV + aStepV).Transformed(theTrsf),
                            Normal(aParamU + aStepU, aParamV + aStepV).Transformed(theTrsf));
        theArray->AddVertex(Vertex(aParamU + aStepU, aParamV + aStepV).Transformed(theTrsf),
                            Normal(aParamU + aStepU, aParamV + aStepV).Transformed(theTrsf));
        theArray->AddVertex(Vertex(aParamU, aParamV + aStepV).Transformed(theTrsf),
                            Normal(aParamU, aParamV + aStepV).Transformed(theTrsf));
        theArray->AddVertex(Vertex(aParamU, aParamV).Transformed(theTrsf),
                            Normal(aParamU, aParamV).Transformed(theTrsf));
      }
    }
  }
}

//=================================================================================================

occ::handle<Graphic3d_ArrayOfTriangles> Prs3d_ToolQuadric::CreateTriangulation(
  const gp_Trsf& theTrsf) const
{
  occ::handle<Graphic3d_ArrayOfTriangles> aTriangulation;
  FillArray(aTriangulation, theTrsf);
  return aTriangulation;
}

//=================================================================================================

occ::handle<Poly_Triangulation> Prs3d_ToolQuadric::CreatePolyTriangulation(
  const gp_Trsf& theTrsf) const
{
  occ::handle<Poly_Triangulation> aTriangulation =
    new Poly_Triangulation(VerticesNb(), TrianglesNb(), false);
  float aStepU = 1.0f / mySlicesNb;
  float aStepV = 1.0f / myStacksNb;

  // Fill triangles
  for (int aU = 0, anIndex = 0; aU <= mySlicesNb; ++aU)
  {
    const double aParamU = aU * aStepU;
    for (int aV = 0; aV <= myStacksNb; ++aV)
    {
      const float aParamV = aV * aStepV;
      const int   aVertId = aU * (myStacksNb + 1) + (aV + 1);
      gp_Pnt      aVertex = Vertex(aParamU, aParamV).Transformed(theTrsf);

      aTriangulation->SetNode(aVertId, aVertex);
      if (aU != 0 && aV != 0)
      {
        aTriangulation->SetTriangle(++anIndex,
                                    Poly_Triangle(aVertId, aVertId - myStacksNb - 2, aVertId - 1));
        aTriangulation->SetTriangle(
          ++anIndex,
          Poly_Triangle(aVertId - myStacksNb - 2, aVertId, aVertId - myStacksNb - 1));
      }
    }
  }
  return aTriangulation;
}

//=================================================================================================

void Prs3d_ToolQuadric::FillArray(occ::handle<Graphic3d_ArrayOfTriangles>& theArray,
                                  occ::handle<Poly_Triangulation>&         theTriangulation,
                                  const gp_Trsf&                           theTrsf) const
{
  theArray         = CreateTriangulation(theTrsf);
  theTriangulation = CreatePolyTriangulation(theTrsf);
}

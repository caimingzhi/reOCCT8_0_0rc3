#define _POLYGONES_

#include <Graphic3d_ArrayOfPolygons.hpp>
#include <Graphic3d_ArrayOfPrimitives.hpp>
#include <Graphic3d_ArrayOfSegments.hpp>
#include <Graphic3d_ArrayOfTriangles.hpp>
#include <Graphic3d_Texture2D.hpp>
#include <Image_PixMap.hpp>
#include <MeshVS_Buffer.hpp>
#include <MeshVS_DataSource.hpp>
#include <MeshVS_Drawer.hpp>
#include <MeshVS_DrawerAttribute.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <MeshVS_Mesh.hpp>
#include <MeshVS_MeshPrsBuilder.hpp>
#include <MeshVS_NodalColorPrsBuilder.hpp>
#include <MeshVS_SymmetricPairHasher.hpp>
#include <MeshVS_Tool.hpp>
#include <NCollection_Map.hpp>
#include <Prs3d_Drawer.hpp>
#include <Prs3d_LineAspect.hpp>
#include <Prs3d_Presentation.hpp>
#include <Prs3d_ShadingAspect.hpp>
#include <PrsMgr_PresentationManager.hpp>
#include <Quantity_Color.hpp>
#include <Standard_Type.hpp>
#include <TColStd_HPackedMapOfInteger.hpp>
#include <TColStd_MapIteratorOfPackedMapOfInteger.hpp>

IMPLEMENT_STANDARD_RTTIEXT(MeshVS_NodalColorPrsBuilder, MeshVS_PrsBuilder)

class MeshVS_ImageTexture2D : public Graphic3d_Texture2D
{
public:
  MeshVS_ImageTexture2D(const occ::handle<Image_PixMap>& theImg)
      : Graphic3d_Texture2D(theImg, Graphic3d_TypeOfTexture_2D)
  {
    myParams->SetModulate(true);
    myParams->SetFilter(Graphic3d_TOTF_BILINEAR);
  }

public:
  DEFINE_STANDARD_RTTI_INLINE(MeshVS_ImageTexture2D, Graphic3d_Texture2D)
};

static inline int getNearestPow2(int theValue)
{

  constexpr int aHalfMax = IntegerLast() >> 1;
  int           aRes     = 1;
  if (theValue > aHalfMax)
    theValue = aHalfMax;
  while (aRes < theValue)
    aRes <<= 1;
  return aRes;
}

MeshVS_NodalColorPrsBuilder::MeshVS_NodalColorPrsBuilder(const occ::handle<MeshVS_Mesh>& Parent,
                                                         const MeshVS_DisplayModeFlags&  Flags,
                                                         const occ::handle<MeshVS_DataSource>& DS,
                                                         const int                             Id,
                                                         const MeshVS_BuilderPriority& Priority)
    : MeshVS_PrsBuilder(Parent, Flags, DS, Id, Priority),
      myUseTexture(false),
      myInvalidColor(Quantity_NOC_GRAY)
{
  SetExcluding(true);
}

void MeshVS_NodalColorPrsBuilder::Build(const occ::handle<Prs3d_Presentation>& Prs,
                                        const TColStd_PackedMapOfInteger&      IDs,
                                        TColStd_PackedMapOfInteger&            IDsToExclude,
                                        const bool                             IsElement,
                                        const int                              DisplayMode) const
{
  occ::handle<MeshVS_DataSource> aSource = GetDataSource();
  occ::handle<MeshVS_Drawer>     aDrawer = GetDrawer();
  if (aSource.IsNull() || aDrawer.IsNull())
    return;

  int aMaxFaceNodes;
  if (!aDrawer->GetInteger(MeshVS_DA_MaxFaceNodes, aMaxFaceNodes) || aMaxFaceNodes <= 0)
    return;

  MeshVS_Buffer              aCoordsBuf(3 * aMaxFaceNodes * sizeof(double));
  NCollection_Array1<double> aCoords(aCoordsBuf, 1, 3 * aMaxFaceNodes);
  int                        NbNodes;
  MeshVS_EntityType          aType;

  if (!(DisplayMode & GetFlags()) || !IsElement)
    return;

  if ((myUseTexture && (!myTextureCoords.Extent() || !myTextureColorMap.Length()))
      || (!myUseTexture && !myNodeColorMap.Extent()))
    return;

  TColStd_PackedMapOfInteger anIDs;
  anIDs.Assign(IDs);
  occ::handle<TColStd_HPackedMapOfInteger> aHiddenElems = myParentMesh->GetHiddenElems();
  if (!aHiddenElems.IsNull())
    anIDs.Subtract(aHiddenElems->Map());
  anIDs.Subtract(IDsToExclude);

  bool IsReflect = false, IsMeshSmoothShading = false;
  aDrawer->GetBoolean(MeshVS_DA_ColorReflection, IsReflect);
  aDrawer->GetBoolean(MeshVS_DA_SmoothShading, IsMeshSmoothShading);

  int nbColors        = 0;
  int nbTextureColors = 0;
  if (myUseTexture)
  {
    nbColors        = myTextureColorMap.Length();
    nbTextureColors = getNearestPow2(nbColors);
  }

  int aSize = anIDs.Extent();

  occ::handle<NCollection_HArray1<NCollection_Sequence<int>>> aTopo;
  int                                     PolygonVerticesFor3D = 0, PolygonBoundsFor3D = 0;
  TColStd_MapIteratorOfPackedMapOfInteger it(anIDs);
  for (; it.More(); it.Next())
  {
    int aKey = it.Key();
    if (aSource->Get3DGeom(aKey, NbNodes, aTopo))
      MeshVS_MeshPrsBuilder::HowManyPrimitives(aTopo,
                                               true,
                                               false,
                                               NbNodes,
                                               PolygonVerticesFor3D,
                                               PolygonBoundsFor3D);
  }

  Graphic3d_MaterialAspect aMaterial[2] = {Graphic3d_NameOfMaterial_Plastified,
                                           Graphic3d_NameOfMaterial_Plastified};
  for (int i = 0; i < 2; ++i)
  {
    aMaterial[i].SetSpecularColor(Quantity_NOC_BLACK);
    aMaterial[i].SetEmissiveColor(Quantity_NOC_BLACK);
    if (!IsReflect)
    {
      aMaterial[i].SetAmbientColor(Quantity_NOC_BLACK);
      aMaterial[i].SetDiffuseColor(Quantity_NOC_BLACK);
    }
    else
    {

      aMaterial[i].SetAmbientColor(Quantity_Color(NCollection_Vec3<float>(0.5f)));
      aMaterial[i].SetDiffuseColor(Quantity_Color(NCollection_Vec3<float>(0.5f)));
    }
  }

  occ::handle<Graphic3d_ArrayOfPolygons> aCPolyArr =
    new Graphic3d_ArrayOfPolygons(aMaxFaceNodes * aSize + PolygonVerticesFor3D,
                                  aSize + PolygonBoundsFor3D,
                                  0,
                                  myUseTexture || IsReflect,
                                  !myUseTexture,
                                  false,
                                  myUseTexture);

  int aNbFacePrimitives = 0;
  int aNbVolmPrimitives = 0;
  int aNbEdgePrimitives = 0;

  for (it.Reset(); it.More(); it.Next())
  {
    int aNbNodes = 0;

    if (!aSource->GetGeom(it.Key(), true, aCoords, aNbNodes, aType))
      continue;

    if (aType == MeshVS_ET_Volume)
    {
      if (aSource->Get3DGeom(it.Key(), aNbNodes, aTopo))
      {
        for (int aFaceIdx = aTopo->Lower(); aFaceIdx <= aTopo->Upper(); ++aFaceIdx)
        {
          const NCollection_Sequence<int>& aFaceNodes = aTopo->Value(aFaceIdx);

          aNbEdgePrimitives += aFaceNodes.Length();
          aNbVolmPrimitives += aFaceNodes.Length() - 2;
        }
      }
    }
    else if (aType == MeshVS_ET_Link)
    {
    }
    else if (aType == MeshVS_ET_Face)
    {
      aNbEdgePrimitives += aNbNodes;
      aNbFacePrimitives += aNbNodes - 2;
    }
  }

  occ::handle<Graphic3d_ArrayOfTriangles> aFaceTriangles =
    new Graphic3d_ArrayOfTriangles((aNbFacePrimitives + aNbVolmPrimitives) * 3,
                                   0,
                                   myUseTexture || IsReflect,
                                   !myUseTexture,
                                   myUseTexture);

  occ::handle<Graphic3d_ArrayOfSegments> anEdgeSegments =
    new Graphic3d_ArrayOfSegments(aNbEdgePrimitives * 2);

  double aMin = gp::Resolution() * gp::Resolution();
  gp_Dir aDefNorm(gp_Dir::D::Z);

  const double anColorRatio = 1.0;

  for (it.Reset(); it.More(); it.Next())
  {
    int aKey = it.Key();

    if (aSource->GetGeom(aKey, true, aCoords, NbNodes, aType))
    {
      NCollection_Array1<int> aNodes(1, NbNodes);

      if (!aSource->GetNodesByElement(aKey, aNodes, NbNodes))
        continue;

      Quantity_Color aNColor;

      bool isValid = true;

      if (myUseTexture)
      {
        for (int k = 1; k <= NbNodes && isValid; ++k)
          isValid = myTextureCoords.IsBound(aNodes(k));
      }
      else
      {
        for (int k = 1; k <= NbNodes && isValid; ++k)
          isValid = GetColor(aNodes(k), aNColor);
      }

      if (!isValid)
        continue;

      occ::handle<NCollection_HArray1<double>> aNormals;

      bool hasNormals =
        (IsReflect
         && aSource->GetNormalsByElement(aKey, IsMeshSmoothShading, aMaxFaceNodes, aNormals));

      if (aType == MeshVS_ET_Face)
      {

        for (int aNodeIdx = 0; aNodeIdx < NbNodes - 2; ++aNodeIdx)

        {
          for (int aSubIdx = 0; aSubIdx < 3; ++aSubIdx)
          {
            gp_XYZ aPnt(aCoords(3 * (aSubIdx == 0 ? 0 : (aNodeIdx + aSubIdx)) + 1),
                        aCoords(3 * (aSubIdx == 0 ? 0 : (aNodeIdx + aSubIdx)) + 2),
                        aCoords(3 * (aSubIdx == 0 ? 0 : (aNodeIdx + aSubIdx)) + 3));

            gp_Vec aNorm = aDefNorm;

            if (hasNormals)
            {
              gp_Vec aTestNorm(aNormals->Value(3 * (aSubIdx == 0 ? 0 : (aNodeIdx + aSubIdx)) + 1),
                               aNormals->Value(3 * (aSubIdx == 0 ? 0 : (aNodeIdx + aSubIdx)) + 2),
                               aNormals->Value(3 * (aSubIdx == 0 ? 0 : (aNodeIdx + aSubIdx)) + 3));

              if (aTestNorm.SquareMagnitude() > aMin)
              {
                aNorm = gp_Dir(aTestNorm);
              }
            }

            if (myUseTexture)
            {
              const double aTexCoord =
                myTextureCoords(aNodes(aSubIdx == 0 ? 1 : (aNodeIdx + aSubIdx + 1)));

              aFaceTriangles->AddVertex(
                aPnt,
                aNorm,
                gp_Pnt2d((aTexCoord * (nbColors - 1.0) + 0.5) / nbTextureColors,
                         aTexCoord < 0 || aTexCoord > 1 ? 0.25 : 0.75));
            }
            else
            {
              GetColor(aNodes(aSubIdx == 0 ? 1 : (aNodeIdx + aSubIdx + 1)), aNColor);

              if (IsReflect)
              {
                aNColor.SetValues(anColorRatio * aNColor.Red(),
                                  anColorRatio * aNColor.Green(),
                                  anColorRatio * aNColor.Blue(),
                                  Quantity_TOC_RGB);

                aFaceTriangles->AddVertex(aPnt, aNorm, aNColor);
              }
              else
              {
                aFaceTriangles->AddVertex(aPnt, aNColor);
              }
            }
          }
        }

        for (int aNodeIdx = 0; aNodeIdx < NbNodes; ++aNodeIdx)
        {
          const int aNextIdx = (aNodeIdx + 1) % NbNodes;

          anEdgeSegments->AddVertex(aCoords(3 * aNodeIdx + 1),
                                    aCoords(3 * aNodeIdx + 2),
                                    aCoords(3 * aNodeIdx + 3));

          anEdgeSegments->AddVertex(aCoords(3 * aNextIdx + 1),
                                    aCoords(3 * aNextIdx + 2),
                                    aCoords(3 * aNextIdx + 3));
        }

        if (IsExcludingOn())
        {
          IDsToExclude.Add(aKey);
        }
      }
      else if (aType == MeshVS_ET_Volume)
      {
        if (!aSource->Get3DGeom(aKey, NbNodes, aTopo))
          continue;

        AddVolumePrs(aTopo,
                     aNodes,
                     aCoords,
                     aFaceTriangles,
                     IsReflect,
                     nbColors,
                     nbTextureColors,
                     anColorRatio);

        AddVolumePrs(aTopo,
                     aNodes,
                     aCoords,
                     anEdgeSegments,
                     IsReflect,
                     nbColors,
                     nbTextureColors,
                     anColorRatio);

        if (IsExcludingOn())
          IDsToExclude.Add(aKey);
      }
    }
  }

  occ::handle<Graphic3d_AspectFillArea3d> anAsp;

  Aspect_TypeOfLine anEdgeType  = Aspect_TOL_SOLID;
  double            anEdgeWidth = 1.0;
  Quantity_Color    anInteriorColor;
  Quantity_Color    anEdgeColor, aLineColor;
  bool              aShowEdges = true;

  aDrawer->GetColor(MeshVS_DA_InteriorColor, anInteriorColor);
  aDrawer->GetColor(MeshVS_DA_EdgeColor, anEdgeColor);
  aDrawer->GetColor(MeshVS_DA_BeamColor, aLineColor);
  aDrawer->GetDouble(MeshVS_DA_EdgeWidth, anEdgeWidth);
  aDrawer->GetBoolean(MeshVS_DA_ShowEdges, aShowEdges);

  int anEdgeInt = Aspect_TOL_SOLID;
  if (aDrawer->GetInteger(MeshVS_DA_EdgeType, anEdgeInt))
    anEdgeType = (Aspect_TypeOfLine)anEdgeInt;

  if (myUseTexture)
  {
    occ::handle<Prs3d_Drawer> aPrsDrawer = myParentMesh->Attributes();
    if (aPrsDrawer.IsNull())
      return;

    aPrsDrawer->SetShadingAspect(new Prs3d_ShadingAspect());
    anAsp = aPrsDrawer->ShadingAspect()->Aspect();
    if (anAsp.IsNull())
      return;

    anAsp->SetFrontMaterial(aMaterial[0]);
    anAsp->SetBackMaterial(aMaterial[1]);

    occ::handle<Graphic3d_Texture2D> aTexture = CreateTexture();
    if (aTexture.IsNull())
      return;

    anAsp->SetTextureMapOn();
    anAsp->SetTextureMap(aTexture);
    anAsp->SetInteriorColor(Quantity_NOC_WHITE);
  }
  else
  {

    anAsp = new Graphic3d_AspectFillArea3d(Aspect_IS_SOLID,
                                           Quantity_NOC_WHITE,
                                           anEdgeColor,
                                           anEdgeType,
                                           anEdgeWidth,
                                           aMaterial[0],
                                           aMaterial[1]);
  }

  anAsp->SetDistinguishOff();
  anAsp->SetEdgeOff();

  occ::handle<Graphic3d_AspectLine3d> anLAsp =
    new Graphic3d_AspectLine3d(anEdgeColor, anEdgeType, anEdgeWidth);

  occ::handle<Graphic3d_Group> aGroup1 = Prs->NewGroup();

  bool toSupressBackFaces = false;
  aDrawer->GetBoolean(MeshVS_DA_SupressBackFaces, toSupressBackFaces);
  aGroup1->SetClosed(toSupressBackFaces);

  aGroup1->SetPrimitivesAspect(anAsp);
  aGroup1->AddPrimitiveArray(aFaceTriangles);

  if (aShowEdges)
  {
    occ::handle<Graphic3d_Group> aGroup2 = Prs->NewGroup();

    occ::handle<Graphic3d_AspectFillArea3d> anAspCopy = new Graphic3d_AspectFillArea3d(*anAsp);
    anAspCopy->SetTextureMapOff();
    aGroup2->SetPrimitivesAspect(anAspCopy);
    aGroup2->SetPrimitivesAspect(anLAsp);
    aGroup2->AddPrimitiveArray(anEdgeSegments);
  }
}

void MeshVS_NodalColorPrsBuilder::AddVolumePrs(
  const occ::handle<NCollection_HArray1<NCollection_Sequence<int>>>& theTopo,
  const NCollection_Array1<int>&                                     theNodes,
  const NCollection_Array1<double>&                                  theCoords,
  const occ::handle<Graphic3d_ArrayOfPrimitives>&                    theArray,
  const bool                                                         theIsShaded,
  const int                                                          theNbColors,
  const int                                                          theNbTexColors,
  const double                                                       theColorRatio) const
{
  int aLow = theCoords.Lower();

  if (theTopo.IsNull() || theArray.IsNull())
    return;

  bool aIsPolygons = theArray->IsKind(STANDARD_TYPE(Graphic3d_ArrayOfTriangles));

  if (aIsPolygons)
  {
    for (int aFaceIdx = theTopo->Lower(), topoup = theTopo->Upper(); aFaceIdx <= topoup; ++aFaceIdx)
    {
      const NCollection_Sequence<int>& aFaceNodes = theTopo->Value(aFaceIdx);

      NCollection_Array1<double> aPolyNodes(0, 3 * aFaceNodes.Length());

      for (int aNodeIdx = 0; aNodeIdx < aFaceNodes.Length(); ++aNodeIdx)
      {
        int anIdx = aFaceNodes.Value(aNodeIdx + 1);

        double aX = theCoords.Value(aLow + 3 * anIdx + 0);
        double aY = theCoords.Value(aLow + 3 * anIdx + 1);
        double aZ = theCoords.Value(aLow + 3 * anIdx + 2);

        aPolyNodes.SetValue(3 * aNodeIdx + 1, aX);
        aPolyNodes.SetValue(3 * aNodeIdx + 2, aY);
        aPolyNodes.SetValue(3 * aNodeIdx + 3, aZ);
      }

      gp_Vec aNorm(0.0, 0.0, 1.0);

      if (theIsShaded)
      {
        aPolyNodes.SetValue(0, aFaceNodes.Length());

        if (!MeshVS_Tool::GetAverageNormal(aPolyNodes, aNorm))
        {
          aNorm.SetCoord(0.0, 0.0, 1.0);
        }
      }

      for (int aNodeIdx = 0; aNodeIdx < aFaceNodes.Length() - 2; ++aNodeIdx)

      {
        for (int aSubIdx = 0; aSubIdx < 3; ++aSubIdx)
        {
          gp_Pnt aPnt(aPolyNodes.Value(3 * (aSubIdx == 0 ? 0 : (aNodeIdx + aSubIdx)) + 1),
                      aPolyNodes.Value(3 * (aSubIdx == 0 ? 0 : (aNodeIdx + aSubIdx)) + 2),
                      aPolyNodes.Value(3 * (aSubIdx == 0 ? 0 : (aNodeIdx + aSubIdx)) + 3));

          if (myUseTexture)
          {
            const double aTexCoord = myTextureCoords(
              theNodes(aFaceNodes(aSubIdx == 0 ? 1 : (aNodeIdx + aSubIdx + 1)) + 1));

            theArray->AddVertex(aPnt,
                                aNorm,
                                gp_Pnt2d((aTexCoord * (theNbColors - 1.0) + 0.5) / theNbTexColors,
                                         aTexCoord < 0 || aTexCoord > 1 ? 0.25 : 0.75));
          }
          else
          {
            Quantity_Color aNColor;
            GetColor(theNodes((aFaceNodes(aSubIdx == 0 ? 1 : (aNodeIdx + aSubIdx + 1)) + 1)),
                     aNColor);

            if (theIsShaded)
            {
              aNColor.SetValues(theColorRatio * aNColor.Red(),
                                theColorRatio * aNColor.Green(),
                                theColorRatio * aNColor.Blue(),
                                Quantity_TOC_RGB);

              theArray->AddVertex(aPnt, aNorm, aNColor);
            }
            else
            {
              theArray->AddVertex(aPnt, aNColor);
            }
          }
        }
      }
    }
  }
  else
  {

    NCollection_Map<MeshVS_NodePair, MeshVS_SymmetricPairHasher> aEdgeMap;

    for (int aFaceIdx = theTopo->Lower(), topoup = theTopo->Upper(); aFaceIdx <= topoup; ++aFaceIdx)
    {
      const NCollection_Sequence<int>& aFaceNodes = theTopo->Value(aFaceIdx);

      for (int aNodeIdx = 0, aNbNodes = aFaceNodes.Length(); aNodeIdx < aNbNodes; ++aNodeIdx)
      {
        const int aNextIdx = (aNodeIdx + 1) % aNbNodes;

        aEdgeMap.Add(
          MeshVS_NodePair(aFaceNodes.Value(aNodeIdx + 1), aFaceNodes.Value(aNextIdx + 1)));
      }
    }

    for (NCollection_Map<MeshVS_NodePair, MeshVS_SymmetricPairHasher>::Iterator anIt(aEdgeMap);
         anIt.More();
         anIt.Next())
    {
      const int anIdx1 = aLow + 3 * anIt.Key().first;
      const int anIdx2 = aLow + 3 * anIt.Key().second;

      double aX[] = {theCoords.Value(anIdx1 + 0), theCoords.Value(anIdx2 + 0)};
      double aY[] = {theCoords.Value(anIdx1 + 1), theCoords.Value(anIdx2 + 1)};
      double aZ[] = {theCoords.Value(anIdx1 + 2), theCoords.Value(anIdx2 + 2)};

      theArray->AddVertex(aX[0], aY[0], aZ[0]);
      theArray->AddVertex(aX[1], aY[1], aZ[1]);
    }
  }
}

void MeshVS_NodalColorPrsBuilder::SetColors(
  const NCollection_DataMap<int, Quantity_Color>& theColorMap)
{
  myNodeColorMap = theColorMap;
}

const NCollection_DataMap<int, Quantity_Color>& MeshVS_NodalColorPrsBuilder::GetColors() const
{
  return myNodeColorMap;
}

bool MeshVS_NodalColorPrsBuilder::HasColors() const
{
  return (myNodeColorMap.Extent() > 0);
}

bool MeshVS_NodalColorPrsBuilder::GetColor(const int ID, Quantity_Color& theColor) const
{
  bool aRes = myNodeColorMap.IsBound(ID);
  if (aRes)
    theColor = myNodeColorMap.Find(ID);
  return aRes;
}

void MeshVS_NodalColorPrsBuilder::SetColor(const int theID, const Quantity_Color& theCol)
{
  bool aRes = myNodeColorMap.IsBound(theID);
  if (aRes)
    myNodeColorMap.ChangeFind(theID) = theCol;
  else
    myNodeColorMap.Bind(theID, theCol);
}

void MeshVS_NodalColorPrsBuilder::UseTexture(const bool theToUse)
{
  myUseTexture = theToUse;
  if (myUseTexture)
    myNodeColorMap.Clear();
  else
    myTextureColorMap.Clear();
}

bool MeshVS_NodalColorPrsBuilder::IsUseTexture() const
{
  return myUseTexture;
}

void MeshVS_NodalColorPrsBuilder::SetColorMap(const NCollection_Sequence<Quantity_Color>& theColors)
{
  myTextureColorMap = theColors;
}

const NCollection_Sequence<Quantity_Color>& MeshVS_NodalColorPrsBuilder::GetColorMap() const
{
  return myTextureColorMap;
}

void MeshVS_NodalColorPrsBuilder::SetInvalidColor(const Quantity_Color& theInvalidColor)
{
  myInvalidColor = theInvalidColor;
}

Quantity_Color MeshVS_NodalColorPrsBuilder::GetInvalidColor() const
{
  return myInvalidColor;
}

void MeshVS_NodalColorPrsBuilder::SetTextureCoords(const NCollection_DataMap<int, double>& theMap)
{
  myTextureCoords = theMap;
}

const NCollection_DataMap<int, double>& MeshVS_NodalColorPrsBuilder::GetTextureCoords() const
{
  return myTextureCoords;
}

void MeshVS_NodalColorPrsBuilder::SetTextureCoord(const int theID, const double theCoord)
{
  myTextureCoords.Bind(theID, theCoord);
}

double MeshVS_NodalColorPrsBuilder::GetTextureCoord(const int theID)
{
  return myTextureCoords.IsBound(theID) ? myTextureCoords(theID) : -1;
}

occ::handle<Graphic3d_Texture2D> MeshVS_NodalColorPrsBuilder::CreateTexture() const
{
  const int aColorsNb = myTextureColorMap.Length();
  if (aColorsNb == 0)
  {
    return nullptr;
  }

  occ::handle<Image_PixMap> anImage = new Image_PixMap();
  if (!anImage->InitTrash(Image_Format_RGBA, size_t(getNearestPow2(aColorsNb)), 2))
  {
    return nullptr;
  }

  anImage->SetTopDown(false);
  for (size_t aCol = 0; aCol < size_t(aColorsNb); ++aCol)
  {
    const Quantity_Color& aSrcColor = myTextureColorMap.Value(int(aCol) + 1);
    Image_ColorRGBA&      aColor    = anImage->ChangeValue<Image_ColorRGBA>(0, aCol);
    aColor.r()                      = static_cast<uint8_t>(255.0 * aSrcColor.Red());
    aColor.g()                      = static_cast<uint8_t>(255.0 * aSrcColor.Green());
    aColor.b()                      = static_cast<uint8_t>(255.0 * aSrcColor.Blue());
    aColor.a()                      = 0xFF;
  }

  const Quantity_Color& aLastColorSrc = myTextureColorMap.Last();
  const Image_ColorRGBA aLastColor    = {{static_cast<uint8_t>(255.0 * aLastColorSrc.Red()),
                                          static_cast<uint8_t>(255.0 * aLastColorSrc.Green()),
                                          static_cast<uint8_t>(255.0 * aLastColorSrc.Blue()),
                                          0xFF}};

  for (size_t aCol = (size_t)aColorsNb; aCol < anImage->SizeX(); ++aCol)
  {
    anImage->ChangeValue<Image_ColorRGBA>(0, aCol) = aLastColor;
  }

  const Image_ColorRGBA anInvalidColor = {{static_cast<uint8_t>(255.0 * myInvalidColor.Red()),
                                           static_cast<uint8_t>(255.0 * myInvalidColor.Green()),
                                           static_cast<uint8_t>(255.0 * myInvalidColor.Blue()),
                                           0xFF}};
  for (size_t aCol = 0; aCol < anImage->SizeX(); ++aCol)
  {
    anImage->ChangeValue<Image_ColorRGBA>(1, aCol) = anInvalidColor;
  }

  return new MeshVS_ImageTexture2D(anImage);
}

#include <BRep_Builder.hpp>
#include <IGESBasic_SubfigureDef.hpp>
#include <IGESCAFControl.hpp>
#include <IGESCAFControl_Reader.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESData_IGESModel.hpp>
#include <IGESData_LevelListEntity.hpp>
#include <IGESGraph_Color.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Quantity_Color.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_HAsciiString.hpp>
#include <TDataStd_Name.hpp>
#include <TDocStd_Document.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>
#include <Transfer_TransientProcess.hpp>
#include <TransferBRep.hpp>
#include <XCAFDoc_ColorTool.hpp>
#include <XCAFDoc_DocumentTool.hpp>
#include <XCAFDoc_LayerTool.hpp>
#include <XCAFDoc_ShapeTool.hpp>
#include <XSAlgo.hpp>
#include <XSAlgo_ShapeProcessor.hpp>
#include <XSControl_TransferReader.hpp>
#include <XSControl_WorkSession.hpp>
#include <UnitsMethods.hpp>

static void checkColorRange(double& theCol)
{
  if (theCol < 0.)
    theCol = 0.;
  if (theCol > 100.)
    theCol = 100.;
}

static inline bool IsComposite(const TopoDS_Shape& theShape)
{
  if (theShape.ShapeType() == TopAbs_COMPOUND)
  {
    if (!theShape.Location().IsIdentity())
      return true;
    TopoDS_Iterator anIt(theShape, false, false);

    for (; anIt.More(); anIt.Next())
    {
      if (IsComposite(anIt.Value()))
        return true;
    }
  }
  return false;
}

static void AddCompositeShape(const occ::handle<XCAFDoc_ShapeTool>& theSTool,
                              const TopoDS_Shape&                   theShape,
                              bool                                  theConsiderLoc,
                              NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theMap)
{
  TopoDS_Shape           aShape = theShape;
  const TopLoc_Location& aLoc   = theShape.Location();
  if (!theConsiderLoc && !aLoc.IsIdentity())
    aShape.Location(TopLoc_Location());
  if (!theMap.Add(aShape))
    return;

  TopoDS_Iterator anIt(theShape, false, false);
  bool            aHasCompositeSubShape = false;
  TopoDS_Compound aSimpleShape;
  BRep_Builder    aB;
  aB.MakeCompound(aSimpleShape);
  TopoDS_Compound aCompShape;
  aB.MakeCompound(aCompShape);
  int nbSimple = 0;

  for (; anIt.More(); anIt.Next())
  {
    const TopoDS_Shape& aSubShape = anIt.Value();
    if (IsComposite(aSubShape))
    {
      aHasCompositeSubShape = true;
      AddCompositeShape(theSTool, aSubShape, false, theMap);
      aB.Add(aCompShape, aSubShape);
    }
    else
    {
      aB.Add(aSimpleShape, aSubShape);
      nbSimple++;
    }
  }

  if (nbSimple && aHasCompositeSubShape)
  {
    theSTool->AddShape(aSimpleShape, false, false);

    TopoDS_Compound aNewShape;
    aB.MakeCompound(aNewShape);
    aB.Add(aNewShape, aSimpleShape);
    aB.Add(aNewShape, aCompShape);

    if (!aLoc.IsIdentity())
      aNewShape.Location(aLoc);
    aNewShape.Orientation(theShape.Orientation());
    theSTool->AddShape(aNewShape, aHasCompositeSubShape, false);
  }
  else
    theSTool->AddShape(aShape, aHasCompositeSubShape, false);
  return;
}

bool IGESCAFControl_Reader::Transfer(const occ::handle<TDocStd_Document>& doc,
                                     const Message_ProgressRange&         theProgress)
{

  int num;

  occ::handle<IGESData_IGESModel> aModel = occ::down_cast<IGESData_IGESModel>(WS()->Model());

  double aScaleFactorMM = 1.;
  if (!XCAFDoc_DocumentTool::GetLengthUnit(doc, aScaleFactorMM, UnitsMethods_LengthUnit_Millimeter))
  {
    XSAlgo_ShapeProcessor::PrepareForTransfer();
    aScaleFactorMM = UnitsMethods::GetCasCadeLengthUnit();

    XCAFDoc_DocumentTool::SetLengthUnit(doc, aScaleFactorMM, UnitsMethods_LengthUnit_Millimeter);
  }
  aModel->ChangeGlobalSection().SetCascadeUnit(aScaleFactorMM);
  TransferRoots(theProgress);
  num = NbShapes();
  if (num <= 0)
    return false;

  occ::handle<XCAFDoc_ShapeTool> STool = XCAFDoc_DocumentTool::ShapeTool(doc->Main());
  if (STool.IsNull())
    return false;
  int i;
  for (i = 1; i <= num; i++)
  {
    TopoDS_Shape sh = Shape(i);

    if (!IsComposite(sh))
      STool->AddShape(sh, false);
    else
    {
      NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMap;
      AddCompositeShape(STool, sh, true, aMap);
    }
  }

  const occ::handle<XSControl_TransferReader>&  TR      = WS()->TransferReader();
  const occ::handle<Transfer_TransientProcess>& TP      = TR->TransientProcess();
  bool                                          IsCTool = true;
  occ::handle<XCAFDoc_ColorTool> CTool = XCAFDoc_DocumentTool::ColorTool(doc->Main());
  if (CTool.IsNull())
    IsCTool = false;
  bool                           IsLTool = true;
  occ::handle<XCAFDoc_LayerTool> LTool   = XCAFDoc_DocumentTool::LayerTool(doc->Main());
  if (LTool.IsNull())
    IsLTool = false;

  int nb = aModel->NbEntities();
  for (i = 1; i <= nb; i++)
  {
    occ::handle<IGESData_IGESEntity> ent = occ::down_cast<IGESData_IGESEntity>(aModel->Value(i));
    if (ent.IsNull())
      continue;
    occ::handle<Transfer_Binder> binder = TP->Find(ent);
    if (binder.IsNull())
      continue;
    TopoDS_Shape S = TransferBRep::ShapeResult(binder);
    if (S.IsNull())
      continue;

    bool           IsColor = false;
    Quantity_Color col;
    if (GetColorMode() && IsCTool)
    {

      if (ent->DefColor() == IGESData_DefValue || ent->DefColor() == IGESData_DefReference)
      {

        IsColor = true;
        if (ent->DefColor() == IGESData_DefValue)
        {
          col = IGESCAFControl::DecodeColor(ent->RankColor());
        }
        else
        {
          occ::handle<IGESGraph_Color> color = occ::down_cast<IGESGraph_Color>(ent->Color());
          if (color.IsNull())
          {
#ifdef OCCT_DEBUG
            std::cout << "Error: Unrecognized type of color definition" << std::endl;
#endif
            IsColor = false;
          }
          else
          {
            double r, g, b;
            color->RGBIntensity(r, g, b);
            checkColorRange(r);
            checkColorRange(g);
            checkColorRange(b);
            col.SetValues(0.01 * r, 0.01 * g, 0.01 * b, Quantity_TOC_sRGB);
          }
        }
      }
    }

    TDF_Label L;

    bool IsFound;
    if (IsColor)
    {
      CTool->AddColor(col);
      IsFound = STool->SearchUsingMap(S, L, false, true);
    }
    else
    {
      IsFound = STool->SearchUsingMap(S, L, false, false);
    }
    if (!IsFound)
    {
      if (IsColor)
      {
        for (TopoDS_Iterator it(S); it.More(); it.Next())
        {
          if (STool->SearchUsingMap(it.Value(), L, false, true))
          {
            CTool->SetColor(L, col, XCAFDoc_ColorGen);
            if (GetLayerMode() && IsLTool)
            {

              IGESData_DefList aDeflist = ent->DefLevel();
              switch (aDeflist)
              {
                case IGESData_DefOne:
                {
                  TCollection_ExtendedString aLayerName(ent->Level());
                  LTool->SetLayer(L, aLayerName);
                  break;
                }
                case IGESData_DefSeveral:
                {
                  occ::handle<IGESData_LevelListEntity> aLevelList = ent->LevelList();
                  int                                   layerNb    = aLevelList->NbLevelNumbers();
                  for (int ilev = 1; ilev <= layerNb; ilev++)
                  {
                    TCollection_ExtendedString aLayerName(aLevelList->LevelNumber(ilev));
                    LTool->SetLayer(L, aLayerName);
                  }
                  break;
                }
                default:
                  break;
              }
            }
          }
        }
      }
    }
    else
    {
      if (IsColor)
      {
        CTool->SetColor(L, col, XCAFDoc_ColorGen);
      }
      if (GetNameMode())
      {

        if (ent->HasName())
        {
          TCollection_AsciiString string = ent->NameValue()->String();
          string.LeftAdjust();
          string.RightAdjust();
          TCollection_ExtendedString str(string);
          TDataStd_Name::Set(L, str);
        }
      }
      if (GetLayerMode() && IsLTool)
      {

        IGESData_DefList aDeflist = ent->DefLevel();
        switch (aDeflist)
        {
          case IGESData_DefOne:
          {
            TCollection_ExtendedString aLayerName(ent->Level());
            LTool->SetLayer(L, aLayerName);
            break;
          }
          case IGESData_DefSeveral:
          {
            occ::handle<IGESData_LevelListEntity> aLevelList = ent->LevelList();
            int                                   layerNb    = aLevelList->NbLevelNumbers();
            for (int ilev = 1; ilev <= layerNb; ilev++)
            {
              TCollection_ExtendedString aLayerName(aLevelList->LevelNumber(ilev));
              LTool->SetLayer(L, aLayerName);
            }
            break;
          }
          default:
            break;
        }
      }
    }

    occ::handle<IGESBasic_SubfigureDef> aSubfigure = occ::down_cast<IGESBasic_SubfigureDef>(ent);
    if (GetNameMode() && !aSubfigure.IsNull() && !aSubfigure->Name().IsNull()
        && STool->Search(S, L, true, true))
    {

      occ::handle<TCollection_HAsciiString> aName = aSubfigure->Name();
      aName->LeftAdjust();
      aName->RightAdjust();
      TCollection_ExtendedString anExtStrName(aName->ToCString());
      TDataStd_Name::Set(L, anExtStrName);
    }
  }

  CTool->ReverseChainsOfTreeNodes();

  STool->UpdateAssemblies();

  return true;
}

bool IGESCAFControl_Reader::Perform(const char*                          filename,
                                    const occ::handle<TDocStd_Document>& doc,
                                    const Message_ProgressRange&         theProgress)
{
  if (ReadFile(filename) != IFSelect_RetDone)
    return false;
  return Transfer(doc, theProgress);
}

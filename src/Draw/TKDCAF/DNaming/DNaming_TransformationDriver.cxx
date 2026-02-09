#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepBuilderAPI_Transform.hpp>
#include <DNaming.hpp>
#include <DNaming_TransformationDriver.hpp>
#include <GeomLib_IsPlanarSurface.hpp>
#include <gp_Ax1.hpp>
#include <gp_Ax2.hpp>
#include <gp_Pln.hpp>
#include <gp_Trsf.hpp>
#include <gp_Vec.hpp>
#include <ModelDefinitions.hpp>
#include <NCollection_Handle.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_Real.hpp>
#include <TDF_Label.hpp>
#include <TFunction_Function.hpp>
#include <TFunction_Logbook.hpp>
#include <TNaming_Builder.hpp>
#include <TNaming_Tool.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <Standard_Integer.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_Map.hpp>

IMPLEMENT_STANDARD_RTTIEXT(DNaming_TransformationDriver, TFunction_Driver)

#ifdef _WIN32
  #define EXCEPTION ...
#else
  #define EXCEPTION Standard_Failure const&
#endif

#define FACES_TAG 1
#define EDGES_TAG 2
#define VERTEX_TAG 3

#ifdef OCCT_DEBUG_TRSF
  #include <TCollection_AsciiString.hpp>
  #include <BRepTools.hpp>
  #include <TDF_Tool.hpp>

void PrintE(const TDF_Label& label)
{
  TCollection_AsciiString entry;
  TDF_Tool::Entry(label, entry);
  std::cout << "LabelEntry = " << entry << std::endl;
}
#endif

DNaming_TransformationDriver::DNaming_TransformationDriver() = default;

void DNaming_TransformationDriver::Validate(occ::handle<TFunction_Logbook>&) const {}

bool DNaming_TransformationDriver::MustExecute(const occ::handle<TFunction_Logbook>&) const
{
  return true;
}

int DNaming_TransformationDriver::Execute(occ::handle<TFunction_Logbook>& theLog) const
{
  occ::handle<TFunction_Function> aFunction;
  Label().FindAttribute(TFunction_Function::GetID(), aFunction);
  if (aFunction.IsNull())
    return -1;

  occ::handle<TFunction_Function> aPrevFun = DNaming::GetPrevFunction(aFunction);
  if (aPrevFun.IsNull())
    return -1;
  const TDF_Label&                aLab = RESPOSITION(aPrevFun);
  occ::handle<TNaming_NamedShape> aContextNS;
  aLab.FindAttribute(TNaming_NamedShape::GetID(), aContextNS);
  if (aContextNS.IsNull() || aContextNS->IsEmpty())
  {
#ifdef OCCT_DEBUG
    std::cout << "TransformationDriver:: Context is empty" << std::endl;
#endif
    aFunction->SetFailure(WRONG_CONTEXT);
    return -1;
  }

  gp_Trsf              aTransformation;
  const Standard_GUID& aGUID = aFunction->GetDriverGUID();

  try
  {
    if (aGUID == PTXYZ_GUID)
    {
      double aDX = DNaming::GetReal(aFunction, PTRANSF_DX)->Get();
      double aDY = DNaming::GetReal(aFunction, PTRANSF_DY)->Get();
      double aDZ = DNaming::GetReal(aFunction, PTRANSF_DZ)->Get();
      gp_Vec aVector(aDX, aDY, aDZ);
      aTransformation.SetTranslation(aVector);
    }
    else if (aGUID == PTALINE_GUID)
    {
      occ::handle<TDataStd_UAttribute> aLineObj = DNaming::GetObjectArg(aFunction, PTRANSF_LINE);
      occ::handle<TNaming_NamedShape>  aLineNS  = DNaming::GetObjectValue(aLineObj);
      gp_Ax1                           anAxis;
      if (!DNaming::ComputeAxis(aLineNS, anAxis))
        throw Standard_Failure();
      gp_Vec aVector(anAxis.Direction());
      aVector.Normalize();
      double anOffset = DNaming::GetReal(aFunction, PTRANSF_OFF)->Get();
      aVector *= anOffset;
      aTransformation.SetTranslation(aVector);
    }
    else if (aGUID == PRRLINE_GUID)
    {
      occ::handle<TDataStd_UAttribute> aLineObj = DNaming::GetObjectArg(aFunction, PTRANSF_LINE);
      occ::handle<TNaming_NamedShape>  aLineNS  = DNaming::GetObjectValue(aLineObj);
      gp_Ax1                           anAxis;
      if (!DNaming::ComputeAxis(aLineNS, anAxis))
        throw Standard_Failure();

      double anAngle = DNaming::GetReal(aFunction, PTRANSF_ANG)->Get();
      aTransformation.SetRotation(anAxis, anAngle);
    }
    else if (aGUID == PMIRR_GUID)
    {
      occ::handle<TDataStd_UAttribute> aPlaneObj = DNaming::GetObjectArg(aFunction, PTRANSF_PLANE);
      occ::handle<TNaming_NamedShape>  aNS       = DNaming::GetObjectValue(aPlaneObj);

      if (aNS.IsNull() || aNS->IsEmpty() || aNS->Get().IsNull()
          || aNS->Get().ShapeType() != TopAbs_FACE)
        throw Standard_Failure();
      TopoDS_Face               aFace = TopoDS::Face(aNS->Get());
      occ::handle<Geom_Surface> aSurf = BRep_Tool::Surface(aFace);
      GeomLib_IsPlanarSurface   isPlanarSurface(aSurf);
      if (!isPlanarSurface.IsPlanar())
        throw Standard_Failure();
      gp_Pln aPlane     = isPlanarSurface.Plan();
      gp_Ax2 aMirrorAx2 = aPlane.Position().Ax2();
      aTransformation.SetMirror(aMirrorAx2);
    }
    else
    {
      aFunction->SetFailure(UNSUPPORTED_FUNCTION);
      return -1;
    }
  }
  catch (EXCEPTION)
  {
    aFunction->SetFailure(WRONG_ARGUMENT);
    return -1;
  }

  LoadNamingDS(RESPOSITION(aFunction), aContextNS, aTransformation);

  theLog->SetValid(RESPOSITION(aFunction), true);
  aFunction->SetFailure(DONE);
  return 0;
}

static void BuildMap(const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& SMap,
                     BRepBuilderAPI_Transform&                                     Transformer,
                     NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& M)
{
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator anIt(SMap);
  for (; anIt.More(); anIt.Next())
  {
    if (!anIt.Key().IsNull())
    {
      const TopoDS_Shape& aS = anIt.Key();
      M.Bind(aS, Transformer.ModifiedShape(aS));
    }
  }
}

static void CollectShapes(const TopoDS_Shape&                                              SSh,
                          TopoDS_Compound&                                                 C,
                          NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>&          SMap,
                          const TDF_Label&                                                 theLab,
                          NCollection_DataMap<TopoDS_Shape, int, TopTools_ShapeMapHasher>& TagMap,
                          const bool isPrimitive)
{
  const TopAbs_ShapeEnum aType = SSh.ShapeType();
  BRep_Builder           aB;
  switch (aType)
  {
    case TopAbs_COMPOUND:
    {
      TopoDS_Iterator it(SSh);
      for (; it.More(); it.Next())
        CollectShapes(it.Value(), C, SMap, theLab, TagMap, isPrimitive);
    }
    break;
    case TopAbs_COMPSOLID:
    case TopAbs_SOLID:
    case TopAbs_SHELL:
    {
      TopExp_Explorer anEx(SSh, TopAbs_FACE);
      for (; anEx.More(); anEx.Next())
      {
        const occ::handle<TNaming_NamedShape> aNS =
          TNaming_Tool::NamedShape(anEx.Current(), theLab);
        if (aNS.IsNull())
          continue;
        if (SMap.Add(anEx.Current()))
        {
          aB.Add(C, anEx.Current());
          if (isPrimitive)
            TagMap.Bind(anEx.Current(), aNS->Label().Tag());
        }
      }
      anEx.Init(SSh, TopAbs_EDGE);
      for (; anEx.More(); anEx.Next())
      {
        const occ::handle<TNaming_NamedShape> aNS =
          TNaming_Tool::NamedShape(anEx.Current(), theLab);
        if (aNS.IsNull())
          continue;
        if (SMap.Add(anEx.Current()))
        {
          aB.Add(C, anEx.Current());
          if (isPrimitive)
            TagMap.Bind(anEx.Current(), aNS->Label().Tag());
        }
      }
      anEx.Init(SSh, TopAbs_VERTEX);
      for (; anEx.More(); anEx.Next())
      {
        const occ::handle<TNaming_NamedShape> aNS =
          TNaming_Tool::NamedShape(anEx.Current(), theLab);
        if (aNS.IsNull())
          continue;
        if (SMap.Add(anEx.Current()))
        {
          aB.Add(C, anEx.Current());
          if (isPrimitive)
            TagMap.Bind(anEx.Current(), aNS->Label().Tag());
        }
      }
    }
    break;
    case TopAbs_FACE:
    {
      const occ::handle<TNaming_NamedShape> aNamedShape = TNaming_Tool::NamedShape(SSh, theLab);
      if (!aNamedShape.IsNull())
        if (SMap.Add(SSh))
          aB.Add(C, SSh);
      TopExp_Explorer anEx(SSh, TopAbs_EDGE);
      for (; anEx.More(); anEx.Next())
      {
        const occ::handle<TNaming_NamedShape> aNS =
          TNaming_Tool::NamedShape(anEx.Current(), theLab);
        if (aNS.IsNull())
          continue;
        if (SMap.Add(anEx.Current()))
        {
          aB.Add(C, anEx.Current());
          if (isPrimitive)
            TagMap.Bind(anEx.Current(), aNS->Label().Tag());
        }
      }
      anEx.Init(SSh, TopAbs_VERTEX);
      for (; anEx.More(); anEx.Next())
      {
        const occ::handle<TNaming_NamedShape> aNS =
          TNaming_Tool::NamedShape(anEx.Current(), theLab);
        if (aNS.IsNull())
          continue;
        if (SMap.Add(anEx.Current()))
        {
          aB.Add(C, anEx.Current());
          if (isPrimitive)
            TagMap.Bind(anEx.Current(), aNS->Label().Tag());
        }
      }
    }
    break;
    case TopAbs_WIRE:
    {
      TopExp_Explorer anEx(SSh, TopAbs_EDGE);
      for (; anEx.More(); anEx.Next())
      {
        const occ::handle<TNaming_NamedShape> aNS =
          TNaming_Tool::NamedShape(anEx.Current(), theLab);
        if (aNS.IsNull())
          continue;
        if (SMap.Add(anEx.Current()))
        {
          aB.Add(C, anEx.Current());
          if (isPrimitive)
            TagMap.Bind(anEx.Current(), aNS->Label().Tag());
        }
      }
      anEx.Init(SSh, TopAbs_VERTEX);
      for (; anEx.More(); anEx.Next())
      {
        const occ::handle<TNaming_NamedShape> aNS =
          TNaming_Tool::NamedShape(anEx.Current(), theLab);
        if (aNS.IsNull())
          continue;
        if (SMap.Add(anEx.Current()))
        {
          aB.Add(C, anEx.Current());
          if (isPrimitive)
            TagMap.Bind(anEx.Current(), aNS->Label().Tag());
        }
      }
    }
    break;

    case TopAbs_EDGE:
    {
      const occ::handle<TNaming_NamedShape> aNamedShape = TNaming_Tool::NamedShape(SSh, theLab);
      if (!aNamedShape.IsNull())
        if (SMap.Add(SSh))
          aB.Add(C, SSh);
      TopExp_Explorer anEx(SSh, TopAbs_VERTEX);
      anEx.Init(SSh, TopAbs_VERTEX);
      for (; anEx.More(); anEx.Next())
      {
        const occ::handle<TNaming_NamedShape> aNS =
          TNaming_Tool::NamedShape(anEx.Current(), theLab);
        if (aNS.IsNull())
          continue;
        if (SMap.Add(anEx.Current()))
        {
          aB.Add(C, anEx.Current());
          if (isPrimitive)
            TagMap.Bind(anEx.Current(), aNS->Label().Tag());
        }
      }
    }
    break;
    case TopAbs_VERTEX:
    {
      const occ::handle<TNaming_NamedShape> aNS = TNaming_Tool::NamedShape(SSh, theLab);
      if (!aNS.IsNull())
        if (SMap.Add(SSh))
        {
          aB.Add(C, SSh);
        }
    }
    break;
    default:
      break;
  }
}

void DNaming_TransformationDriver::LoadNamingDS(const TDF_Label& theResultLabel,
                                                const occ::handle<TNaming_NamedShape>& theSourceNS,
                                                const gp_Trsf& theTrsf) const
{
  if (theSourceNS.IsNull() || theSourceNS->IsEmpty())
    return;
  const TopoDS_Shape& aSrcShape = theSourceNS->Get();
  if (aSrcShape.IsNull())
  {
#ifdef OCCT_DEBUG
    std::cout
      << "DNaming_TransformationDriver::LoadNamingDS: The result of the Transform operation is null"
      << std::endl;
#endif
    return;
  }
  bool isPrimitive(false);
  if (theSourceNS->Evolution() == TNaming_PRIMITIVE)
    isPrimitive = true;
  const TDF_Label& aSrcLabel = theSourceNS->Label();
#ifdef OCCT_DEBUG_TRSF
  std::cout << "TransformationDriver: ";
  PrintE(aSrcLabel);
#endif

  TopoDS_Compound aCompShape;
  BRep_Builder    aB;
  aB.MakeCompound(aCompShape);
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>          aSMap;
  NCollection_DataMap<TopoDS_Shape, int, TopTools_ShapeMapHasher> aTagMap;

  if (aSMap.Add(aSrcShape))
    aB.Add(aCompShape, aSrcShape);
  CollectShapes(aSrcShape, aCompShape, aSMap, aSrcLabel, aTagMap, isPrimitive);

  BRepBuilderAPI_Transform aTransformer(aCompShape, theTrsf, false);
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> aTMap;
  BuildMap(aSMap, aTransformer, aTMap);

  TopoDS_Shape aNewSh;
  if (aTMap.IsBound(aSrcShape))
    aNewSh = aTMap(aSrcShape);
  if (!aNewSh.IsNull())
  {
    TNaming_Builder aBuilder(theResultLabel);
    aBuilder.Modify(aSrcShape, aNewSh);
    aTMap.UnBind(aSrcShape);
  }

  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> SubShapes;
  TopExp_Explorer                                                          Exp(aNewSh, TopAbs_FACE);
  for (; Exp.More(); Exp.Next())
  {
    SubShapes.Bind(Exp.Current(), Exp.Current());
  }
  for (Exp.Init(aNewSh, TopAbs_EDGE); Exp.More(); Exp.Next())
  {
    SubShapes.Bind(Exp.Current(), Exp.Current());
  }
  for (Exp.Init(aNewSh, TopAbs_VERTEX); Exp.More(); Exp.Next())
  {
    SubShapes.Bind(Exp.Current(), Exp.Current());
  }

  int                                                                       aNextTag(0);
  NCollection_DataMap<TopoDS_Shape, int, TopTools_ShapeMapHasher>::Iterator it(aTagMap);
  for (; it.More(); it.Next())
  {
    if (it.Value() > aNextTag)
      aNextTag = it.Value();
  }
  NCollection_Handle<TNaming_Builder> aFBuilder, anEBuilder, aVBuilder;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator anIt(aTMap);
  for (; anIt.More(); anIt.Next())
  {
    const TopoDS_Shape& aKey     = anIt.Key();
    TopoDS_Shape        newShape = anIt.Value();
    if (SubShapes.IsBound(newShape))
    {
      newShape.Orientation((SubShapes(newShape)).Orientation());
    }
    if (isPrimitive)
    {
      if (aTagMap.IsBound(aKey))
      {
        const TDF_Label& aLabel = theResultLabel.FindChild(aTagMap.Find(aKey), true);
        TNaming_Builder  aBuilder(aLabel);
        aBuilder.Modify(aKey, newShape);
      }
      else
      {
        aNextTag++;
        const TDF_Label& aLabel = theResultLabel.FindChild(aNextTag, true);
        TNaming_Builder  aBuilder(aLabel);
        aBuilder.Modify(aKey, newShape);
      }
    }
    else
    {
      if (aKey.ShapeType() == TopAbs_FACE)
      {
        if (aFBuilder.IsNull())
        {
          const TDF_Label& aFLabel = theResultLabel.FindChild(FACES_TAG, true);
          aFBuilder                = new TNaming_Builder(aFLabel);
        }
        aFBuilder->Modify(anIt.Key(), newShape);
      }
      else if (aKey.ShapeType() == TopAbs_EDGE)
      {
        if (anEBuilder.IsNull())
        {
          const TDF_Label& aELabel = theResultLabel.FindChild(EDGES_TAG, true);
          anEBuilder               = new TNaming_Builder(aELabel);
        }
        anEBuilder->Modify(anIt.Key(), newShape);
      }
      else if (aKey.ShapeType() == TopAbs_VERTEX)
      {
        if (aVBuilder.IsNull())
        {
          const TDF_Label& aVLabel = theResultLabel.FindChild(VERTEX_TAG, true);
          aVBuilder                = new TNaming_Builder(aVLabel);
        }
        aVBuilder->Modify(anIt.Key(), newShape);
      }
    }
  }
}

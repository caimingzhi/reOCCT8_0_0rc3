#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BOPAlgo_Options.hpp>
#include <BOPAlgo_MakePeriodic.hpp>

#include <BRepTools_History.hpp>

#include <NCollection_DataMap.hpp>

class BOPAlgo_MakeConnected : public BOPAlgo_Options
{
public:
  DEFINE_STANDARD_ALLOC

public:
  BOPAlgo_MakeConnected()

    = default;

public:
  void SetArguments(const NCollection_List<TopoDS_Shape>& theArgs) { myArguments = theArgs; }

  void AddArgument(const TopoDS_Shape& theS) { myArguments.Append(theS); }

  const NCollection_List<TopoDS_Shape>& Arguments() const { return myArguments; }

public:
  Standard_EXPORT void Perform();

public:
  Standard_EXPORT void MakePeriodic(const BOPAlgo_MakePeriodic::PeriodicityParams& theParams);

  Standard_EXPORT void RepeatShape(const int theDirectionID, const int theTimes);

  Standard_EXPORT void ClearRepetitions();

  const BOPAlgo_MakePeriodic& PeriodicityTool() const { return myPeriodicityMaker; }

public:
  const NCollection_List<TopoDS_Shape>& MaterialsOnPositiveSide(const TopoDS_Shape& theS)
  {
    const NCollection_List<TopoDS_Shape>* pLM = myMaterials.Seek(theS.Oriented(TopAbs_FORWARD));
    return (pLM ? *pLM : EmptyList());
  }

  const NCollection_List<TopoDS_Shape>& MaterialsOnNegativeSide(const TopoDS_Shape& theS)
  {
    const NCollection_List<TopoDS_Shape>* pLM = myMaterials.Seek(theS.Oriented(TopAbs_REVERSED));
    return (pLM ? *pLM : EmptyList());
  }

public:
  const occ::handle<BRepTools_History>& History() const { return myHistory; }

  const NCollection_List<TopoDS_Shape>& GetModified(const TopoDS_Shape& theS)
  {
    return (myHistory.IsNull() ? EmptyList() : myHistory->Modified(theS));
  }

  const NCollection_List<TopoDS_Shape>& GetOrigins(const TopoDS_Shape& theS)
  {
    const NCollection_List<TopoDS_Shape>* pLOr = myOrigins.Seek(theS);
    return (pLOr ? *pLOr : EmptyList());
  }

public:
  const TopoDS_Shape& Shape() const { return myGlued; }

  const TopoDS_Shape& PeriodicShape() const { return myShape; }

public:
  void Clear() override
  {
    BOPAlgo_Options::Clear();
    myArguments.Clear();
    myAllInputsMap.Clear();
    myPeriodicityMaker.Clear();
    myOrigins.Clear();
    myMaterials.Clear();
    if (!myGlueHistory.IsNull())
      myGlueHistory->Clear();
    if (!myHistory.IsNull())
      myHistory->Clear();
    myGlued.Nullify();
    myShape.Nullify();
  }

protected:
  Standard_EXPORT void CheckData();

  Standard_EXPORT void MakeConnected();

  Standard_EXPORT void AssociateMaterials();

  Standard_EXPORT void FillOrigins();

  Standard_EXPORT void Update();

private:
  const NCollection_List<TopoDS_Shape>& EmptyList()
  {
    static const NCollection_List<TopoDS_Shape> anEmptyList;
    return anEmptyList;
  }

protected:
  NCollection_List<TopoDS_Shape>                                myArguments;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> myAllInputsMap;

  BOPAlgo_MakePeriodic myPeriodicityMaker;

  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>> myMaterials;

  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myOrigins;

  occ::handle<BRepTools_History> myGlueHistory;
  occ::handle<BRepTools_History> myHistory;

  TopoDS_Shape myGlued;
  TopoDS_Shape myShape;
};

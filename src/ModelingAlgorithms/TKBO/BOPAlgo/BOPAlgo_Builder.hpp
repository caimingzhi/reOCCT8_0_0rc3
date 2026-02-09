#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BOPAlgo_PPaveFiller.hpp>
#include <BOPAlgo_BuilderShape.hpp>
#include <BOPAlgo_GlueEnum.hpp>
#include <BOPAlgo_Operation.hpp>
#include <BOPDS_PDS.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_Map.hpp>
#include <TopAbs_ShapeEnum.hpp>
class IntTools_Context;
class TopoDS_Shape;

class BOPAlgo_Builder : public BOPAlgo_BuilderShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BOPAlgo_Builder();
  Standard_EXPORT ~BOPAlgo_Builder() override;

  Standard_EXPORT BOPAlgo_Builder(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  Standard_EXPORT void Clear() override;

  BOPAlgo_PPaveFiller PPaveFiller() { return myPaveFiller; }

  BOPDS_PDS PDS() { return myDS; }

  occ::handle<IntTools_Context> Context() const { return myContext; }

public:
  Standard_EXPORT virtual void AddArgument(const TopoDS_Shape& theShape);

  Standard_EXPORT virtual void SetArguments(const NCollection_List<TopoDS_Shape>& theLS);

  const NCollection_List<TopoDS_Shape>& Arguments() const { return myArguments; }

public:
  void SetNonDestructive(const bool theFlag) { myNonDestructive = theFlag; }

  bool NonDestructive() const { return myNonDestructive; }

  void SetGlue(const BOPAlgo_GlueEnum theGlue) { myGlue = theGlue; }

  BOPAlgo_GlueEnum Glue() const { return myGlue; }

  void SetCheckInverted(const bool theCheck) { myCheckInverted = theCheck; }

  bool CheckInverted() const { return myCheckInverted; }

public:
  Standard_EXPORT void Perform(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT virtual void PerformWithFiller(
    const BOPAlgo_PaveFiller&    theFiller,
    const Message_ProgressRange& theRange = Message_ProgressRange());

public:
  Standard_EXPORT virtual void BuildBOP(const NCollection_List<TopoDS_Shape>& theObjects,
                                        const TopAbs_State                    theObjState,
                                        const NCollection_List<TopoDS_Shape>& theTools,
                                        const TopAbs_State                    theToolsState,
                                        const Message_ProgressRange&          theRange,
                                        occ::handle<Message_Report>           theReport = nullptr);

  void BuildBOP(const NCollection_List<TopoDS_Shape>& theObjects,
                const NCollection_List<TopoDS_Shape>& theTools,
                const BOPAlgo_Operation               theOperation,
                const Message_ProgressRange&          theRange,
                occ::handle<Message_Report>           theReport = nullptr)
  {
    TopAbs_State anObjState, aToolsState;
    switch (theOperation)
    {
      case BOPAlgo_COMMON:
      {
        anObjState  = TopAbs_IN;
        aToolsState = TopAbs_IN;
        break;
      }
      case BOPAlgo_FUSE:
      {
        anObjState  = TopAbs_OUT;
        aToolsState = TopAbs_OUT;
        break;
      }
      case BOPAlgo_CUT:
      {
        anObjState  = TopAbs_OUT;
        aToolsState = TopAbs_IN;
        break;
      }
      case BOPAlgo_CUT21:
      {
        anObjState  = TopAbs_IN;
        aToolsState = TopAbs_OUT;
        break;
      }
      default:
      {
        anObjState  = TopAbs_UNKNOWN;
        aToolsState = TopAbs_UNKNOWN;
        break;
      }
    }
    BuildBOP(theObjects, anObjState, theTools, aToolsState, theRange, theReport);
  }

protected:
  Standard_EXPORT void PrepareHistory(const Message_ProgressRange& theRange);

  Standard_EXPORT virtual const NCollection_List<TopoDS_Shape>* LocModified(
    const TopoDS_Shape& theS);

  Standard_EXPORT virtual const NCollection_List<TopoDS_Shape>& LocGenerated(
    const TopoDS_Shape& theS);

public:
  const NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
    Images() const
  {
    return myImages;
  }

  const NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
    Origins() const
  {
    return myOrigins;
  }

  const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& ShapesSD() const
  {
    return myShapesSD;
  }

protected:
  enum BOPAlgo_PIOperation
  {
    PIOperation_TreatVertices = 0,
    PIOperation_TreatEdges,
    PIOperation_TreatWires,
    PIOperation_TreatFaces,
    PIOperation_TreatShells,
    PIOperation_TreatSolids,
    PIOperation_TreatCompsolids,
    PIOperation_TreatCompounds,
    PIOperation_FillHistory,
    PIOperation_PostTreat,
    PIOperation_Last
  };

  class NbShapes
  {
  public:
    NbShapes()
    {
      for (int i = 0; i < 8; ++i)
      {
        myNbShapesArr[i] = 0;
      }
    }

    int NbVertices() const { return myNbShapesArr[0]; }

    int NbEdges() const { return myNbShapesArr[1]; }

    int NbWires() const { return myNbShapesArr[2]; }

    int NbFaces() const { return myNbShapesArr[3]; }

    int NbShells() const { return myNbShapesArr[4]; }

    int NbSolids() const { return myNbShapesArr[5]; }

    int NbCompsolids() const { return myNbShapesArr[6]; }

    int NbCompounds() const { return myNbShapesArr[7]; }

    int& NbVertices() { return myNbShapesArr[0]; }

    int& NbEdges() { return myNbShapesArr[1]; }

    int& NbWires() { return myNbShapesArr[2]; }

    int& NbFaces() { return myNbShapesArr[3]; }

    int& NbShells() { return myNbShapesArr[4]; }

    int& NbSolids() { return myNbShapesArr[5]; }

    int& NbCompsolids() { return myNbShapesArr[6]; }

    int& NbCompounds() { return myNbShapesArr[7]; }

  private:
    int myNbShapesArr[8];
  };

protected:
  Standard_EXPORT NbShapes getNbShapes() const;

  Standard_EXPORT void fillPIConstants(const double     theWhole,
                                       BOPAlgo_PISteps& theSteps) const override;

  Standard_EXPORT void fillPISteps(BOPAlgo_PISteps& theSteps) const override;

protected:
  Standard_EXPORT virtual void PerformInternal(const BOPAlgo_PaveFiller&    thePF,
                                               const Message_ProgressRange& theRange);

  Standard_EXPORT virtual void PerformInternal1(const BOPAlgo_PaveFiller&    thePF,
                                                const Message_ProgressRange& theRange);

  Standard_EXPORT virtual void BuildResult(const TopAbs_ShapeEnum theType);

protected:
  Standard_EXPORT void CheckData() override;

  Standard_EXPORT void CheckFiller();

  Standard_EXPORT virtual void Prepare();

protected:
  Standard_EXPORT void FillImagesVertices(const Message_ProgressRange& theRange);

protected:
  Standard_EXPORT void FillImagesEdges(const Message_ProgressRange& theRange);

protected:
  Standard_EXPORT void FillImagesContainers(const TopAbs_ShapeEnum       theType,
                                            const Message_ProgressRange& theRange);

  Standard_EXPORT void FillImagesContainer(const TopoDS_Shape&    theS,
                                           const TopAbs_ShapeEnum theType);

protected:
  Standard_EXPORT void FillImagesFaces(const Message_ProgressRange& theRange);

  Standard_EXPORT virtual void BuildSplitFaces(const Message_ProgressRange& theRange);

  Standard_EXPORT void FillSameDomainFaces(const Message_ProgressRange& theRange);

  Standard_EXPORT void FillInternalVertices(const Message_ProgressRange& theRange);

protected:
  Standard_EXPORT void FillImagesSolids(const Message_ProgressRange& theRange);

  Standard_EXPORT void BuildDraftSolid(const TopoDS_Shape&             theSolid,
                                       TopoDS_Shape&                   theDraftSolid,
                                       NCollection_List<TopoDS_Shape>& theLIF);

  Standard_EXPORT virtual void FillIn3DParts(
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& theDraftSolids,
    const Message_ProgressRange&                                              theRange);

  Standard_EXPORT void BuildSplitSolids(
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& theDraftSolids,
    const Message_ProgressRange&                                              theRange);

  Standard_EXPORT void FillInternalShapes(const Message_ProgressRange& theRange);

protected:
  Standard_EXPORT void FillImagesCompounds(const Message_ProgressRange& theRange);

  Standard_EXPORT void FillImagesCompound(
    const TopoDS_Shape&                                     theS,
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theMF);

protected:
  Standard_EXPORT virtual void PostTreat(const Message_ProgressRange& theRange);

protected:
  NCollection_List<TopoDS_Shape> myArguments;

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> myMapFence;
  BOPAlgo_PPaveFiller                                    myPaveFiller;
  BOPDS_PDS                                              myDS;
  occ::handle<IntTools_Context>                          myContext;
  int                                                    myEntryPoint;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                                                           myImages;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myShapesSD;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myOrigins;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                   myInParts;
  bool             myNonDestructive;
  BOPAlgo_GlueEnum myGlue;
  bool             myCheckInverted;
};

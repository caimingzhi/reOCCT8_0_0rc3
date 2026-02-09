#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Compound.hpp>
#include <TopoDS_Wire.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>

class BOPAlgo_MakerVolume;
class TopoDS_Face;

class BRepFill_AdvancedEvolved
{
public:
  DEFINE_STANDARD_ALLOC;

  Standard_EXPORT BRepFill_AdvancedEvolved()
      : myErrorStatus(BRepFill_AdvancedEvolved_Empty),
        myFuzzyValue(0.0),
        myIsParallel(true),
        myDebugShapesPath("C:\\Temp")
  {
  }

  Standard_EXPORT void Perform(const TopoDS_Wire& theSpine,
                               const TopoDS_Wire& theProfile,
                               const double       theTolerance,
                               const bool         theSolidReq = true);

  bool IsDone(unsigned int* theErrorCode = nullptr) const
  {
    if (theErrorCode)
      *theErrorCode = myErrorStatus;

    return (myErrorStatus == BRepFill_AdvancedEvolved_OK);
  }

  const TopoDS_Shape& Shape() const { return myResult; }

  void SetTemporaryDirectory(const char*& thePath) { myDebugShapesPath = thePath; }

  void SetParallelMode(const bool theVal) { myIsParallel = theVal; }

protected:
  Standard_EXPORT void PerformSweep();

  Standard_EXPORT void GetLids();

  Standard_EXPORT void BuildSolid();

  Standard_EXPORT void RemoveExcessSolids(const NCollection_List<TopoDS_Shape>& theLSplits,
                                          const TopoDS_Shape&                   theShape,
                                          NCollection_List<TopoDS_Shape>&       theArgsList,
                                          BOPAlgo_MakerVolume&                  theMV);

  Standard_EXPORT void ExtractOuterSolid(TopoDS_Shape&                   theShape,
                                         NCollection_List<TopoDS_Shape>& theArgsList);

  Standard_EXPORT void GetSpineAndProfile(const TopoDS_Wire& theSpine,
                                          const TopoDS_Wire& theProfile);

  Standard_EXPORT void UnifyShape();

  Standard_EXPORT bool PerformBoolean(const NCollection_List<TopoDS_Shape>& theArgsList,
                                      TopoDS_Shape&                         theResult) const;

  Standard_EXPORT bool CheckSingularityAndAdd(
    const TopoDS_Face&              theF,
    const double                    theFuzzyToler,
    NCollection_List<TopoDS_Shape>& theListOfFaces,
    NCollection_List<TopoDS_Shape>& theListOfSplits) const;

  Standard_EXPORT bool IsLid(
    const TopoDS_Face&                                                   theF,
    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theMapOfLids) const;

private:
  enum
  {
    BRepFill_AdvancedEvolved_Empty = 0,
    BRepFill_AdvancedEvolved_NotPlanarSpine,
    BRepFill_AdvancedEvolved_SweepError,
    BRepFill_AdvancedEvolved_NoLids,
    BRepFill_AdvancedEvolved_NotSolid,
    BRepFill_AdvancedEvolved_NotVolume,
    BRepFill_AdvancedEvolved_OK = UINT_MAX
  } myErrorStatus;

  TopoDS_Wire     mySpine;
  TopoDS_Wire     myProfile;
  TopoDS_Shape    myPipeShell;
  TopoDS_Compound myTopBottom;
  TopoDS_Shape    myResult;
  double          myFuzzyValue;
  bool            myIsParallel;
  const char*     myDebugShapesPath;
};

#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BOPAlgo_Options.hpp>
#include <BRepTools_History.hpp>
#include <Standard_Boolean.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>

class BOPAlgo_MakePeriodic : public BOPAlgo_Options
{
public:
  DEFINE_STANDARD_ALLOC

public:
  BOPAlgo_MakePeriodic() { myRepeatPeriod[0] = myRepeatPeriod[1] = myRepeatPeriod[2] = 0.0; }

public:
  void SetShape(const TopoDS_Shape& theShape) { myInputShape = theShape; }

public:
  struct PeriodicityParams
  {
    PeriodicityParams() { Clear(); }

    void Clear()
    {
      myPeriodic[0] = myPeriodic[1] = myPeriodic[2] = false;
      myPeriod[0] = myPeriod[1] = myPeriod[2] = 0.0;
      myIsTrimmed[0] = myIsTrimmed[1] = myIsTrimmed[2] = true;
      myPeriodFirst[0] = myPeriodFirst[1] = myPeriodFirst[2] = 0.0;
    }

    bool myPeriodic[3];

    double myPeriod[3];

    bool myIsTrimmed[3];

    double myPeriodFirst[3];
  };

public:
  void SetPeriodicityParameters(const PeriodicityParams& theParams)
  {
    myPeriodicityParams = theParams;
  }

  const PeriodicityParams& PeriodicityParameters() const { return myPeriodicityParams; }

public:
  void MakePeriodic(const int    theDirectionID,
                    const bool   theIsPeriodic,
                    const double thePeriod = 0.0)
  {
    int id                             = ToDirectionID(theDirectionID);
    myPeriodicityParams.myPeriodic[id] = theIsPeriodic;
    myPeriodicityParams.myPeriod[id]   = theIsPeriodic ? thePeriod : 0.0;
  }

  bool IsPeriodic(const int theDirectionID) const
  {
    return myPeriodicityParams.myPeriodic[ToDirectionID(theDirectionID)];
  }

  double Period(const int theDirectionID) const
  {
    int id = ToDirectionID(theDirectionID);
    return myPeriodicityParams.myPeriodic[id] ? myPeriodicityParams.myPeriod[id] : 0.0;
  }

public:
  void MakeXPeriodic(const bool theIsPeriodic, const double thePeriod = 0.0)
  {
    MakePeriodic(0, theIsPeriodic, thePeriod);
  }

  bool IsXPeriodic() const { return IsPeriodic(0); }

  double XPeriod() const { return Period(0); }

  void MakeYPeriodic(const bool theIsPeriodic, const double thePeriod = 0.0)
  {
    MakePeriodic(1, theIsPeriodic, thePeriod);
  }

  bool IsYPeriodic() const { return IsPeriodic(1); }

  double YPeriod() const { return Period(1); }

  void MakeZPeriodic(const bool theIsPeriodic, const double thePeriod = 0.0)
  {
    MakePeriodic(2, theIsPeriodic, thePeriod);
  }

  bool IsZPeriodic() const { return IsPeriodic(2); }

  double ZPeriod() const { return Period(2); }

public:
  void SetTrimmed(const int theDirectionID, const bool theIsTrimmed, const double theFirst = 0.0)
  {
    int id = ToDirectionID(theDirectionID);
    if (IsPeriodic(id))
    {
      myPeriodicityParams.myIsTrimmed[id]   = theIsTrimmed;
      myPeriodicityParams.myPeriodFirst[id] = !theIsTrimmed ? theFirst : 0.0;
    }
  }

  bool IsInputTrimmed(const int theDirectionID) const
  {
    return myPeriodicityParams.myIsTrimmed[ToDirectionID(theDirectionID)];
  }

  double PeriodFirst(const int theDirectionID) const
  {
    int id = ToDirectionID(theDirectionID);
    return !myPeriodicityParams.myIsTrimmed[id] ? myPeriodicityParams.myPeriodFirst[id] : 0.0;
  }

public:
  void SetXTrimmed(const bool theIsTrimmed, const bool theFirst = 0.0)
  {
    SetTrimmed(0, theIsTrimmed, theFirst);
  }

  bool IsInputXTrimmed() const { return IsInputTrimmed(0); }

  double XPeriodFirst() const { return PeriodFirst(0); }

  void SetYTrimmed(const bool theIsTrimmed, const bool theFirst = 0.0)
  {
    SetTrimmed(1, theIsTrimmed, theFirst);
  }

  bool IsInputYTrimmed() const { return IsInputTrimmed(1); }

  double YPeriodFirst() const { return PeriodFirst(1); }

  void SetZTrimmed(const bool theIsTrimmed, const bool theFirst = 0.0)
  {
    SetTrimmed(2, theIsTrimmed, theFirst);
  }

  bool IsInputZTrimmed() const { return IsInputTrimmed(2); }

  double ZPeriodFirst() const { return PeriodFirst(2); }

public:
  Standard_EXPORT void Perform();

public:
  Standard_EXPORT const TopoDS_Shape& RepeatShape(const int theDirectionID, const int theTimes);

  const TopoDS_Shape& XRepeat(const int theTimes) { return RepeatShape(0, theTimes); }

  const TopoDS_Shape& YRepeat(const int theTimes) { return RepeatShape(1, theTimes); }

  const TopoDS_Shape& ZRepeat(const int theTimes) { return RepeatShape(2, theTimes); }

public:
  const TopoDS_Shape& RepeatedShape() const { return myRepeatedShape; }

  void ClearRepetitions()
  {
    myRepeatPeriod[0] = myRepeatPeriod[1] = myRepeatPeriod[2] = 0.0;
    myRepeatedShape.Nullify();
    myRepeatedTwins.Clear();
    if (!myHistory.IsNull())
    {
      myHistory->Clear();
      if (!mySplitHistory.IsNull())
        myHistory->Merge(mySplitHistory);
    }
  }

public:
  const TopoDS_Shape& Shape() const { return myShape; }

public:
  const NCollection_List<TopoDS_Shape>& GetTwins(const TopoDS_Shape& theS) const
  {
    static NCollection_List<TopoDS_Shape> empty;
    const NCollection_List<TopoDS_Shape>* aTwins =
      myRepeatedTwins.IsEmpty() ? myTwins.Seek(theS) : myRepeatedTwins.Seek(theS);
    return (aTwins ? *aTwins : empty);
  }

public:
  const occ::handle<BRepTools_History>& History() const { return myHistory; }

public:
  void Clear() override
  {
    BOPAlgo_Options::Clear();
    myPeriodicityParams.Clear();
    myShape.Nullify();
    if (!mySplitHistory.IsNull())
      mySplitHistory->Clear();
    if (!myHistory.IsNull())
      myHistory->Clear();

    ClearRepetitions();
  }

public:
  static int ToDirectionID(const int theDirectionID) { return std::abs(theDirectionID % 3); }

protected:
  Standard_EXPORT void CheckData();

  Standard_EXPORT void Trim();

  Standard_EXPORT void MakeIdentical();

  Standard_EXPORT void SplitNegative();

  Standard_EXPORT void SplitPositive();

  Standard_EXPORT void SplitShape(
    const NCollection_List<TopoDS_Shape>& theTools,
    const occ::handle<BRepTools_History>& theSplitShapeHistory = nullptr,
    const occ::handle<BRepTools_History>& theSplitToolsHistory = nullptr);

  Standard_EXPORT void UpdateTwins(const BRepTools_History& theTranslationHistory,
                                   const BRepTools_History& theGluingHistory);

protected:
  TopoDS_Shape myInputShape;

  PeriodicityParams myPeriodicityParams;

  TopoDS_Shape myShape;
  TopoDS_Shape myRepeatedShape;
  double       myRepeatPeriod[3];

  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myRepeatedTwins;

  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myTwins;

  occ::handle<BRepTools_History> mySplitHistory;

  occ::handle<BRepTools_History> myHistory;
};

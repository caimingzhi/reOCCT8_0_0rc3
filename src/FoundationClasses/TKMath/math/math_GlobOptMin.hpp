#pragma once

#include <gp_Pnt.hpp>
#include <NCollection_CellFilter.hpp>
#include <math_MultipleVarFunction.hpp>
#include <NCollection_Sequence.hpp>

class math_GlobOptMin
{
public:
  Standard_EXPORT math_GlobOptMin(math_MultipleVarFunction* theFunc,
                                  const math_Vector&        theLowerBorder,
                                  const math_Vector&        theUpperBorder,
                                  const double              theC                 = 9,
                                  const double              theDiscretizationTol = 1.0e-2,
                                  const double              theSameTol           = 1.0e-7);

  Standard_EXPORT void SetGlobalParams(math_MultipleVarFunction* theFunc,
                                       const math_Vector&        theLowerBorder,
                                       const math_Vector&        theUpperBorder,
                                       const double              theC                 = 9,
                                       const double              theDiscretizationTol = 1.0e-2,
                                       const double              theSameTol           = 1.0e-7);

  Standard_EXPORT void SetLocalParams(const math_Vector& theLocalA, const math_Vector& theLocalB);

  Standard_EXPORT void SetTol(const double theDiscretizationTol, const double theSameTol);

  Standard_EXPORT void GetTol(double& theDiscretizationTol, double& theSameTol);

  Standard_EXPORT void Perform(const bool isFindSingleSolution = false);

  Standard_EXPORT void Points(const int theIndex, math_Vector& theSol);

  inline void SetContinuity(const int theCont) { myCont = theCont; }

  inline int GetContinuity() const { return myCont; }

  inline void SetFunctionalMinimalValue(const double theMinimalValue)
  {
    myFunctionalMinimalValue = theMinimalValue;
  }

  inline double GetFunctionalMinimalValue() const { return myFunctionalMinimalValue; }

  inline void SetLipConstState(const bool theFlag) { myIsConstLocked = theFlag; }

  inline bool GetLipConstState() const { return myIsConstLocked; }

  inline bool isDone() const { return myDone; }

  inline double GetF() const { return myF; }

  inline int NbExtrema() const { return mySolCount; }

private:
  class NCollection_CellFilter_Inspector
  {
  public:
    typedef math_Vector Point;
    typedef math_Vector Target;

    NCollection_CellFilter_Inspector(const int theDim, const double theTol)
        : myCurrent(1, theDim)
    {
      myTol     = theTol * theTol;
      myIsFind  = false;
      Dimension = theDim;
    }

    static double Coord(int i, const Point& thePnt) { return thePnt(i + 1); }

    void Shift(const Point&                      thePnt,
               const NCollection_Array1<double>& theTol,
               Point&                            theLowPnt,
               Point&                            theUppPnt) const
    {
      for (int anIdx = 1; anIdx <= Dimension; anIdx++)
      {
        theLowPnt(anIdx) = thePnt(anIdx) - theTol(anIdx - 1);
        theUppPnt(anIdx) = thePnt(anIdx) + theTol(anIdx - 1);
      }
    }

    void ClearFind() { myIsFind = false; }

    bool isFind() { return myIsFind; }

    void SetCurrent(const math_Vector& theCurPnt) { myCurrent = theCurPnt; }

    NCollection_CellFilter_Action Inspect(const Target& theObject)
    {
      double aSqDist = (myCurrent - theObject).Norm2();

      if (aSqDist < myTol)
      {
        myIsFind = true;
      }

      return CellFilter_Keep;
    }

  private:
    double      myTol;
    math_Vector myCurrent;
    bool        myIsFind;
    int         Dimension;
  };

  void initCellSize();

  void ComputeInitSol();

  math_GlobOptMin& operator=(const math_GlobOptMin& theOther) = delete;

  bool computeLocalExtremum(const math_Vector& thePnt, double& theVal, math_Vector& theOutPnt);

  void computeGlobalExtremum(int theIndex);

  bool CheckFunctionalStopCriteria();

  void computeInitialValues();

  bool isInside(const math_Vector& thePnt);

  bool isStored(const math_Vector& thePnt);

  void checkAddCandidate(const math_Vector& thePnt, const double theValue);

  math_MultipleVarFunction* myFunc;
  int                       myN;
  math_Vector               myA;
  math_Vector               myB;
  math_Vector               myGlobA;
  math_Vector               myGlobB;
  double                    myTol;
  double                    mySameTol;

  double myC;
  double myInitC;
  bool   myIsFindSingleSolution;
  double myFunctionalMinimalValue;
  bool   myIsConstLocked;

  bool                         myDone;
  NCollection_Sequence<double> myY;
  int                          mySolCount;

  double myZ;
  double myE1{};
  double myE2{};
  double myE3{};

  math_Vector myX;
  math_Vector myTmp;
  math_Vector myV;
  math_Vector myMaxV;
  double      myLastStep{};

  NCollection_Array1<double>                               myCellSize;
  int                                                      myMinCellFilterSol;
  bool                                                     isFirstCellFilterInvoke{};
  NCollection_CellFilter<NCollection_CellFilter_Inspector> myFilter;

  int myCont;

  double myF;
};

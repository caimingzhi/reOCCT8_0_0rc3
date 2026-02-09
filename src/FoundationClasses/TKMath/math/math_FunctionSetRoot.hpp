#pragma once

#include <math_IntegerVector.hpp>
#include <math_Matrix.hpp>
#include <math_Vector.hpp>
#include <Standard_OStream.hpp>
#include <Standard_DimensionError.hpp>
#include <StdFail_NotDone.hpp>

class math_FunctionSetWithDerivatives;

class math_FunctionSetRoot
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT math_FunctionSetRoot(math_FunctionSetWithDerivatives& F,
                                       const math_Vector&               Tolerance,
                                       const int                        NbIterations = 100);

  Standard_EXPORT math_FunctionSetRoot(math_FunctionSetWithDerivatives& F,
                                       const int                        NbIterations = 100);

  Standard_EXPORT virtual ~math_FunctionSetRoot();

  Standard_EXPORT void SetTolerance(const math_Vector& Tolerance);

  virtual bool IsSolutionReached(math_FunctionSetWithDerivatives&)
  {
    for (int i = 1; i <= Sol.Length(); ++i)
    {
      if (std::abs(Delta(i)) > Tol(i))
      {
        return false;
      }
    }
    return true;
  }

  Standard_EXPORT void Perform(math_FunctionSetWithDerivatives& theFunction,
                               const math_Vector&               theStartingPoint,
                               const bool                       theStopOnDivergent = false);

  Standard_EXPORT void Perform(math_FunctionSetWithDerivatives& theFunction,
                               const math_Vector&               theStartingPoint,
                               const math_Vector&               theInfBound,
                               const math_Vector&               theSupBound,
                               const bool                       theStopOnDivergent = false);

  bool IsDone() const { return Done; }

  int NbIterations() const
  {
    StdFail_NotDone_Raise_if(!Done, " ");
    return Kount;
  }

  int StateNumber() const
  {
    StdFail_NotDone_Raise_if(!Done, " ");
    return State;
  }

  const math_Vector& Root() const
  {
    StdFail_NotDone_Raise_if(!Done, " ");
    return Sol;
  }

  Standard_EXPORT void Root(math_Vector& Root) const;

  const math_Matrix& Derivative() const
  {
    StdFail_NotDone_Raise_if(!Done, " ");
    return DF;
  }

  void Derivative(math_Matrix& Der) const
  {
    StdFail_NotDone_Raise_if(!Done, " ");
    Standard_DimensionError_Raise_if(Der.ColNumber() != Sol.Length(), " ");
    Der = DF;
  }

  const math_Vector& FunctionSetErrors() const
  {
    StdFail_NotDone_Raise_if(!Done, " ");
    return Delta;
  }

  Standard_EXPORT void FunctionSetErrors(math_Vector& Err) const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

  bool IsDivergent() const { return myIsDivergent; }

protected:
  math_Vector Delta;
  math_Vector Sol;
  math_Matrix DF;
  math_Vector Tol;

private:
  bool               Done;
  int                Kount;
  int                State;
  int                Itermax;
  math_Vector        InfBound;
  math_Vector        SupBound;
  math_Vector        SolSave;
  math_Vector        GH;
  math_Vector        DH;
  math_Vector        DHSave;
  math_Vector        FF;
  math_Vector        PreviousSolution;
  math_Vector        Save;
  math_IntegerVector Constraints;
  math_Vector        Temp1;
  math_Vector        Temp2;
  math_Vector        Temp3;
  math_Vector        Temp4;
  bool               myIsDivergent;
};

inline Standard_OStream& operator<<(Standard_OStream& theStream, const math_FunctionSetRoot& theF)
{
  theF.Dump(theStream);
  return theStream;
}

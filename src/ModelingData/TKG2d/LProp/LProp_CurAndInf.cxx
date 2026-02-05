#include <LProp_CurAndInf.hpp>
#include <Standard_OutOfRange.hpp>

//=================================================================================================

LProp_CurAndInf::LProp_CurAndInf() = default;

//=================================================================================================

void LProp_CurAndInf::AddInflection(const double Param)
{
  if (theParams.IsEmpty())
  {
    theParams.Append(Param);
    theTypes.Append(LProp_Inflection);
    return;
  }
  if (Param > theParams.Last())
  {
    theParams.Append(Param);
    theTypes.Append(LProp_Inflection);
    return;
  }
  for (int i = 1; i <= theParams.Length(); i++)
  {
    if (theParams.Value(i) > Param)
    {
      theParams.InsertBefore(i, Param);
      theTypes.InsertBefore(i, LProp_Inflection);
      break;
    }
  }
}

//=================================================================================================

void LProp_CurAndInf::AddExtCur(const double Param, const bool IsMin)
{
  LProp_CIType TypePoint;
  if (IsMin)
    TypePoint = LProp_MinCur;
  else
    TypePoint = LProp_MaxCur;

  if (theParams.IsEmpty())
  {
    theParams.Append(Param);
    theTypes.Append(TypePoint);
    return;
  }
  if (Param > theParams.Last())
  {
    theParams.Append(Param);
    theTypes.Append(TypePoint);
    return;
  }
  for (int i = 1; i <= theParams.Length(); i++)
  {
    if (theParams.Value(i) > Param)
    {
      theParams.InsertBefore(i, Param);
      theTypes.InsertBefore(i, TypePoint);
      break;
    }
  }
}

//=================================================================================================

void LProp_CurAndInf::Clear()
{
  theParams.Clear();
  theTypes.Clear();
}

//=================================================================================================

bool LProp_CurAndInf::IsEmpty() const
{
  return theParams.IsEmpty();
}

//=================================================================================================

int LProp_CurAndInf::NbPoints() const
{
  return theParams.Length();
}

//=================================================================================================

double LProp_CurAndInf::Parameter(const int N) const
{
  if (N < 1 || N > NbPoints())
  {
    throw Standard_OutOfRange();
  }
  return theParams.Value(N);
}

//=================================================================================================

LProp_CIType LProp_CurAndInf::Type(const int N) const
{
  if (N < 1 || N > NbPoints())
  {
    throw Standard_OutOfRange();
  }
  return theTypes.Value(N);
}

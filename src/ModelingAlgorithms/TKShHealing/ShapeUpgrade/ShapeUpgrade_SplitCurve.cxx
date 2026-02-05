#include <Geom_BSplineCurve.hpp>
#include <Precision.hpp>
#include <ShapeExtend.hpp>
#include <ShapeUpgrade.hpp>
#include <ShapeUpgrade_SplitCurve.hpp>
#include <Standard_Type.hpp>
#include <Geom_Curve.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ShapeUpgrade_SplitCurve, Standard_Transient)

//=================================================================================================

ShapeUpgrade_SplitCurve::ShapeUpgrade_SplitCurve()
    : myNbCurves(0),
      myStatus(0)
{
}

//=================================================================================================

void ShapeUpgrade_SplitCurve::Init(const double First, const double Last)
{
  myStatus = ShapeExtend::EncodeStatus(ShapeExtend_OK);
  //  if (ShapeUpgrade::Debug()) std::cout << "SplitCurve::Init"<<std::endl;

  myNbCurves = 1;
  // mySplitValues.Clear();
  mySplitValues = new NCollection_HSequence<double>;
  mySplitValues->Append(First);
  mySplitValues->Append(Last);
}

//=================================================================================================

void ShapeUpgrade_SplitCurve::SetSplitValues(
  const occ::handle<NCollection_HSequence<double>>& SplitValues)
{
  constexpr double precision = Precision::PConfusion();
  if (SplitValues.IsNull())
    return;
  if (SplitValues->Length() == 0)
    return;

  double First = mySplitValues->Value(1), Last = mySplitValues->Value(mySplitValues->Length());
  int    i   = 1;
  int    len = SplitValues->Length();
  for (int k = 2; k <= mySplitValues->Length(); k++)
  {
    Last = mySplitValues->Value(k);
    for (; i <= len; i++)
    {
      if ((First + precision) >= SplitValues->Value(i))
        continue;
      if ((Last - precision) <= SplitValues->Value(i))
        break;
      mySplitValues->InsertBefore(k++, SplitValues->Value(i));
    }
    First = Last;
  }
}

//=================================================================================================

void ShapeUpgrade_SplitCurve::Build(const bool /*Segment*/)
{
  myStatus = ShapeExtend::EncodeStatus(ShapeExtend_OK);
}

//=================================================================================================

const occ::handle<NCollection_HSequence<double>>& ShapeUpgrade_SplitCurve::SplitValues() const
{
  return mySplitValues;
}

//=================================================================================================

void ShapeUpgrade_SplitCurve::Perform(const bool Segment)
{
  Compute();
  // if ( ! mySplitValues.IsNull() )
  //   SetSplitValues(mySplitValues);
  Build(Segment);
}

//=================================================================================================

void ShapeUpgrade_SplitCurve::Compute()
{
  myStatus = ShapeExtend::EncodeStatus(ShapeExtend_OK);
}

//=================================================================================================

bool ShapeUpgrade_SplitCurve::Status(const ShapeExtend_Status status) const
{
  return ShapeExtend::DecodeStatus(myStatus, status);
}

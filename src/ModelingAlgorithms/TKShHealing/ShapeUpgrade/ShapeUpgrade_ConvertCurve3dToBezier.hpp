#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Geom_Curve.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <ShapeUpgrade_SplitCurve3d.hpp>

class ShapeUpgrade_ConvertCurve3dToBezier : public ShapeUpgrade_SplitCurve3d
{

public:
  Standard_EXPORT ShapeUpgrade_ConvertCurve3dToBezier();

  void SetLineMode(const bool mode);

  bool GetLineMode() const;

  void SetCircleMode(const bool mode);

  bool GetCircleMode() const;

  void SetConicMode(const bool mode);

  bool GetConicMode() const;

  Standard_EXPORT void Compute() override;

  Standard_EXPORT void Build(const bool Segment) override;

  Standard_EXPORT occ::handle<NCollection_HSequence<double>> SplitParams() const;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_ConvertCurve3dToBezier, ShapeUpgrade_SplitCurve3d)

private:
  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Geom_Curve>>> Segments() const;

  occ::handle<NCollection_HSequence<occ::handle<Geom_Curve>>> mySegments;
  occ::handle<NCollection_HSequence<double>>                  mySplitParams;
  bool                                                        myLineMode;
  bool                                                        myCircleMode;
  bool                                                        myConicMode;
};

inline void ShapeUpgrade_ConvertCurve3dToBezier::SetLineMode(const bool mode)
{
  myLineMode = mode;
}

inline bool ShapeUpgrade_ConvertCurve3dToBezier::GetLineMode() const
{
  return myLineMode;
}

inline void ShapeUpgrade_ConvertCurve3dToBezier::SetCircleMode(const bool mode)
{
  myCircleMode = mode;
}

inline bool ShapeUpgrade_ConvertCurve3dToBezier::GetCircleMode() const
{
  return myCircleMode;
}

inline void ShapeUpgrade_ConvertCurve3dToBezier::SetConicMode(const bool mode)
{
  myConicMode = mode;
}

inline bool ShapeUpgrade_ConvertCurve3dToBezier::GetConicMode() const
{
  return myConicMode;
}

#pragma once

#include <Standard.hpp>

#include <gp_Lin2d.hpp>
#include <GccInt_Bisec.hpp>
#include <GccInt_IType.hpp>

//! Describes a line as a bisecting curve between two 2D
//! geometric objects (such as lines, circles or points).
class GccInt_BLine : public GccInt_Bisec
{

public:
  //! Constructs a bisecting line whose geometry is the 2D line Line.
  Standard_EXPORT GccInt_BLine(const gp_Lin2d& Line);

  //! Returns a 2D line which is the geometry of this bisecting line.
  Standard_EXPORT gp_Lin2d Line() const override;

  //! Returns GccInt_Lin, which is the type of any GccInt_BLine bisecting line.
  Standard_EXPORT GccInt_IType ArcType() const override;

  DEFINE_STANDARD_RTTIEXT(GccInt_BLine, GccInt_Bisec)

private:
  gp_Lin2d lin;
};

#pragma once

#include <Standard.hpp>

#include <Plate_D3.hpp>
#include <NLPlate_HPG2Constraint.hpp>
#include <Standard_Integer.hpp>
class gp_XY;
class Plate_D1;
class Plate_D2;

class NLPlate_HPG3Constraint : public NLPlate_HPG2Constraint
{

public:
  Standard_EXPORT NLPlate_HPG3Constraint(const gp_XY&    UV,
                                         const Plate_D1& D1T,
                                         const Plate_D2& D2T,
                                         const Plate_D3& D3T);

  Standard_EXPORT int ActiveOrder() const override;

  Standard_EXPORT const Plate_D3& G3Target() const override;

  DEFINE_STANDARD_RTTIEXT(NLPlate_HPG3Constraint, NLPlate_HPG2Constraint)

private:
  Plate_D3 myG3Target;
};

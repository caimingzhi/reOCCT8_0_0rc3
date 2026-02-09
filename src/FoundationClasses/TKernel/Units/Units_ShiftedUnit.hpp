#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Units_Unit.hpp>
#include <Standard_Integer.hpp>
class Units_Quantity;
class Units_Token;

class Units_ShiftedUnit : public Units_Unit
{

public:
  Standard_EXPORT Units_ShiftedUnit(const char*                        aname,
                                    const char*                        asymbol,
                                    const double                       avalue,
                                    const double                       amove,
                                    const occ::handle<Units_Quantity>& aquantity);

  Standard_EXPORT Units_ShiftedUnit(const char* aname, const char* asymbol);

  Standard_EXPORT Units_ShiftedUnit(const char* aname);

  Standard_EXPORT void Move(const double amove);

  Standard_EXPORT double Move() const;

  Standard_EXPORT occ::handle<Units_Token> Token() const override;

  Standard_EXPORT void Dump(const int ashift, const int alevel) const override;

  DEFINE_STANDARD_RTTIEXT(Units_ShiftedUnit, Units_Unit)

private:
  double themove;
};

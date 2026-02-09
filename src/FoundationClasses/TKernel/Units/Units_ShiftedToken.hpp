#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Units_Token.hpp>
#include <Standard_Integer.hpp>
class Units_Dimensions;

class Units_ShiftedToken : public Units_Token
{

public:
  Standard_EXPORT Units_ShiftedToken(const char*                          aword,
                                     const char*                          amean,
                                     const double                         avalue,
                                     const double                         amove,
                                     const occ::handle<Units_Dimensions>& adimensions);

  Standard_EXPORT occ::handle<Units_Token> Creates() const override;

  Standard_EXPORT double Move() const;

  Standard_EXPORT double Multiplied(const double avalue) const override;

  Standard_EXPORT double Divided(const double avalue) const override;

  Standard_EXPORT void Dump(const int ashift, const int alevel) const override;

  DEFINE_STANDARD_RTTIEXT(Units_ShiftedToken, Units_Token)

private:
  double themove;
};

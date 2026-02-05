#include <Geom2d_Curve.hpp>
#include <Geom_Surface.hpp>
#include <GeomTools_UndefinedTypeHandler.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(GeomTools_UndefinedTypeHandler, Standard_Transient)

GeomTools_UndefinedTypeHandler::GeomTools_UndefinedTypeHandler() = default;

//=================================================================================================

void GeomTools_UndefinedTypeHandler::PrintCurve(const occ::handle<Geom_Curve>& /*C*/,
                                                Standard_OStream& OS,
                                                const bool        compact) const
{
  if (!compact)
    OS << "****** UNKNOWN CURVE TYPE ******\n";
  else
    std::cout << "****** UNKNOWN CURVE TYPE ******" << std::endl;
}

//=================================================================================================

Standard_IStream& GeomTools_UndefinedTypeHandler::ReadCurve(const int /*ctype*/,
                                                            Standard_IStream& IS,
                                                            occ::handle<Geom_Curve>& /*C*/) const
{
  return IS;
}

//=================================================================================================

void GeomTools_UndefinedTypeHandler::PrintCurve2d(const occ::handle<Geom2d_Curve>& /*C*/,
                                                  Standard_OStream& OS,
                                                  const bool        compact) const
{
  if (!compact)
    OS << "****** UNKNOWN CURVE2d TYPE ******\n";
  else
    std::cout << "****** UNKNOWN CURVE2d TYPE ******" << std::endl;
}

//=================================================================================================

Standard_IStream& GeomTools_UndefinedTypeHandler::ReadCurve2d(
  const int /*ctype*/,
  Standard_IStream& IS,
  occ::handle<Geom2d_Curve>& /*C*/) const
{
  return IS;
}

//=================================================================================================

void GeomTools_UndefinedTypeHandler::PrintSurface(const occ::handle<Geom_Surface>& /*S*/,
                                                  Standard_OStream& OS,
                                                  const bool        compact) const
{
  if (!compact)
    OS << "****** UNKNOWN SURFACE TYPE ******\n";
  else
    std::cout << "****** UNKNOWN SURFACE TYPE ******" << std::endl;
}

Standard_IStream& GeomTools_UndefinedTypeHandler::ReadSurface(
  const int /*ctype*/,
  Standard_IStream& IS,
  occ::handle<Geom_Surface>& /*S*/) const
{
  return IS;
}

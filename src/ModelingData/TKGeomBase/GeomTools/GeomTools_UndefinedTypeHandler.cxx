#include <Geom2d_Curve.hpp>
#include <Geom_Surface.hpp>
#include <GeomTools_UndefinedTypeHandler.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(GeomTools_UndefinedTypeHandler, Standard_Transient)

GeomTools_UndefinedTypeHandler::GeomTools_UndefinedTypeHandler() = default;

void GeomTools_UndefinedTypeHandler::PrintCurve(const occ::handle<Geom_Curve>&,
                                                Standard_OStream& OS,
                                                const bool        compact) const
{
  if (!compact)
    OS << "****** UNKNOWN CURVE TYPE ******\n";
  else
    std::cout << "****** UNKNOWN CURVE TYPE ******" << std::endl;
}

Standard_IStream& GeomTools_UndefinedTypeHandler::ReadCurve(const int,
                                                            Standard_IStream& IS,
                                                            occ::handle<Geom_Curve>&) const
{
  return IS;
}

void GeomTools_UndefinedTypeHandler::PrintCurve2d(const occ::handle<Geom2d_Curve>&,
                                                  Standard_OStream& OS,
                                                  const bool        compact) const
{
  if (!compact)
    OS << "****** UNKNOWN CURVE2d TYPE ******\n";
  else
    std::cout << "****** UNKNOWN CURVE2d TYPE ******" << std::endl;
}

Standard_IStream& GeomTools_UndefinedTypeHandler::ReadCurve2d(const int,
                                                              Standard_IStream& IS,
                                                              occ::handle<Geom2d_Curve>&) const
{
  return IS;
}

void GeomTools_UndefinedTypeHandler::PrintSurface(const occ::handle<Geom_Surface>&,
                                                  Standard_OStream& OS,
                                                  const bool        compact) const
{
  if (!compact)
    OS << "****** UNKNOWN SURFACE TYPE ******\n";
  else
    std::cout << "****** UNKNOWN SURFACE TYPE ******" << std::endl;
}

Standard_IStream& GeomTools_UndefinedTypeHandler::ReadSurface(const int,
                                                              Standard_IStream& IS,
                                                              occ::handle<Geom_Surface>&) const
{
  return IS;
}

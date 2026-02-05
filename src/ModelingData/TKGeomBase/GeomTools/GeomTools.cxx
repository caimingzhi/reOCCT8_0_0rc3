#include <GeomTools.hpp>

#include <Geom2d_Curve.hpp>
#include <Geom_Surface.hpp>
#include <GeomTools_Curve2dSet.hpp>
#include <GeomTools_CurveSet.hpp>
#include <GeomTools_SurfaceSet.hpp>
#include <GeomTools_UndefinedTypeHandler.hpp>

static occ::handle<GeomTools_UndefinedTypeHandler> theActiveHandler =
  new GeomTools_UndefinedTypeHandler;

void GeomTools::Dump(const occ::handle<Geom_Surface>& S, Standard_OStream& OS)
{
  GeomTools_SurfaceSet::PrintSurface(S, OS);
}

void GeomTools::Write(const occ::handle<Geom_Surface>& S, Standard_OStream& OS)
{
  GeomTools_SurfaceSet::PrintSurface(S, OS, true);
}

void GeomTools::Read(occ::handle<Geom_Surface>& S, Standard_IStream& IS)
{
  S = GeomTools_SurfaceSet::ReadSurface(IS);
}

void GeomTools::Dump(const occ::handle<Geom_Curve>& C, Standard_OStream& OS)
{
  GeomTools_CurveSet::PrintCurve(C, OS);
}

void GeomTools::Write(const occ::handle<Geom_Curve>& C, Standard_OStream& OS)
{
  GeomTools_CurveSet::PrintCurve(C, OS, true);
}

void GeomTools::Read(occ::handle<Geom_Curve>& C, Standard_IStream& IS)
{
  C = GeomTools_CurveSet::ReadCurve(IS);
}

void GeomTools::Dump(const occ::handle<Geom2d_Curve>& C, Standard_OStream& OS)
{
  GeomTools_Curve2dSet::PrintCurve2d(C, OS);
}

void GeomTools::Write(const occ::handle<Geom2d_Curve>& C, Standard_OStream& OS)
{
  GeomTools_Curve2dSet::PrintCurve2d(C, OS, true);
}

void GeomTools::Read(occ::handle<Geom2d_Curve>& C, Standard_IStream& IS)
{
  C = GeomTools_Curve2dSet::ReadCurve2d(IS);
}

//=================================================================================================

void GeomTools::SetUndefinedTypeHandler(const occ::handle<GeomTools_UndefinedTypeHandler>& aHandler)
{
  if (!aHandler.IsNull())
    theActiveHandler = aHandler;
}

//=================================================================================================

occ::handle<GeomTools_UndefinedTypeHandler> GeomTools::GetUndefinedTypeHandler()
{
  return theActiveHandler;
}

//=================================================================================================

void GeomTools::GetReal(Standard_IStream& IS, double& theValue)
{
  theValue = 0.;
  if (IS.eof())
  {
    return;
  }
  // According IEEE-754 Specification and standard stream parameters
  // the most optimal buffer length not less then 25
  constexpr size_t THE_BUFFER_SIZE = 32;
  char             aBuffer[THE_BUFFER_SIZE];

  aBuffer[0]                = '\0';
  std::streamsize anOldWide = IS.width(THE_BUFFER_SIZE - 1);
  IS >> aBuffer;
  IS.width(anOldWide);
  theValue = Strtod(aBuffer, nullptr);
}

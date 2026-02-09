#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_OStream.hpp>
#include <Standard_IStream.hpp>
#include <Standard_Real.hpp>
class Geom_Surface;
class Geom_Curve;
class Geom2d_Curve;
class GeomTools_UndefinedTypeHandler;

class GeomTools
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Dump(const occ::handle<Geom_Surface>& S, Standard_OStream& OS);

  Standard_EXPORT static void Write(const occ::handle<Geom_Surface>& S, Standard_OStream& OS);

  Standard_EXPORT static void Read(occ::handle<Geom_Surface>& S, Standard_IStream& IS);

  Standard_EXPORT static void Dump(const occ::handle<Geom_Curve>& C, Standard_OStream& OS);

  Standard_EXPORT static void Write(const occ::handle<Geom_Curve>& C, Standard_OStream& OS);

  Standard_EXPORT static void Read(occ::handle<Geom_Curve>& C, Standard_IStream& IS);

  Standard_EXPORT static void Dump(const occ::handle<Geom2d_Curve>& C, Standard_OStream& OS);

  Standard_EXPORT static void Write(const occ::handle<Geom2d_Curve>& C, Standard_OStream& OS);

  Standard_EXPORT static void Read(occ::handle<Geom2d_Curve>& C, Standard_IStream& IS);

  Standard_EXPORT static void SetUndefinedTypeHandler(
    const occ::handle<GeomTools_UndefinedTypeHandler>& aHandler);

  Standard_EXPORT static occ::handle<GeomTools_UndefinedTypeHandler> GetUndefinedTypeHandler();

  Standard_EXPORT static void GetReal(Standard_IStream& IS, double& theValue);
};

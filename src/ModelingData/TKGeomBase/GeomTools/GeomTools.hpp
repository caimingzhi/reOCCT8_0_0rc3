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

//! The GeomTools package provides utilities for Geometry.
//!
//! * SurfaceSet, CurveSet, Curve2dSet : Tools used
//! for dumping, writing and reading.
//!
//! * Methods to dump, write, read curves and surfaces.
class GeomTools
{
public:
  DEFINE_STANDARD_ALLOC

  //! A set of Curves from Geom2d.
  //! Dumps the surface on the stream.
  Standard_EXPORT static void Dump(const occ::handle<Geom_Surface>& S, Standard_OStream& OS);

  //! Writes the surface on the stream.
  Standard_EXPORT static void Write(const occ::handle<Geom_Surface>& S, Standard_OStream& OS);

  //! Reads the surface from the stream.
  Standard_EXPORT static void Read(occ::handle<Geom_Surface>& S, Standard_IStream& IS);

  //! Dumps the Curve on the stream.
  Standard_EXPORT static void Dump(const occ::handle<Geom_Curve>& C, Standard_OStream& OS);

  //! Writes the Curve on the stream.
  Standard_EXPORT static void Write(const occ::handle<Geom_Curve>& C, Standard_OStream& OS);

  //! Reads the Curve from the stream.
  Standard_EXPORT static void Read(occ::handle<Geom_Curve>& C, Standard_IStream& IS);

  //! Dumps the Curve on the stream.
  Standard_EXPORT static void Dump(const occ::handle<Geom2d_Curve>& C, Standard_OStream& OS);

  //! Writes the Curve on the stream.
  Standard_EXPORT static void Write(const occ::handle<Geom2d_Curve>& C, Standard_OStream& OS);

  //! Reads the Curve from the stream.
  Standard_EXPORT static void Read(occ::handle<Geom2d_Curve>& C, Standard_IStream& IS);

  Standard_EXPORT static void SetUndefinedTypeHandler(
    const occ::handle<GeomTools_UndefinedTypeHandler>& aHandler);

  Standard_EXPORT static occ::handle<GeomTools_UndefinedTypeHandler> GetUndefinedTypeHandler();

  //! Reads the double value from the stream. Zero is read
  //! in case of error
  Standard_EXPORT static void GetReal(Standard_IStream& IS, double& theValue);
};


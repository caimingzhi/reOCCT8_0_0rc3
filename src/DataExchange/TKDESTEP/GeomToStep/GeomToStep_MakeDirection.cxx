#include <Geom2d_Direction.hpp>
#include <Geom_Direction.hpp>
#include <GeomToStep_MakeDirection.hpp>
#include <gp_Dir.hpp>
#include <gp_Dir2d.hpp>
#include <StdFail_NotDone.hpp>
#include <StepGeom_Direction.hpp>
#include <TCollection_HAsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

//=============================================================================
// Creation d' une direction de prostep a partir d' une Dir de gp
//=============================================================================
GeomToStep_MakeDirection::GeomToStep_MakeDirection(const gp_Dir& D)
{
  occ::handle<StepGeom_Direction>          Dir        = new StepGeom_Direction;
  occ::handle<NCollection_HArray1<double>> aDirRatios = new NCollection_HArray1<double>(1, 3);
  double                                   X, Y, Z;

  D.Coord(X, Y, Z);
  aDirRatios->SetValue(1, X);
  aDirRatios->SetValue(2, Y);
  aDirRatios->SetValue(3, Z);
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");
  Dir->Init(name, aDirRatios);
  theDirection = Dir;
  done         = true;
}

//=============================================================================
// Creation d' une direction de prostep a partir d' une Dir2d de gp
//=============================================================================

GeomToStep_MakeDirection::GeomToStep_MakeDirection(const gp_Dir2d& D)
{
  occ::handle<StepGeom_Direction>          Dir        = new StepGeom_Direction;
  occ::handle<NCollection_HArray1<double>> aDirRatios = new NCollection_HArray1<double>(1, 2);
  double                                   X, Y;

  D.Coord(X, Y);
  aDirRatios->SetValue(1, X);
  aDirRatios->SetValue(2, Y);
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");
  Dir->Init(name, aDirRatios);
  theDirection = Dir;
  done         = true;
}

//=============================================================================
// Creation d' une direction de prostep a partir d' une Direction de Geom
//=============================================================================

GeomToStep_MakeDirection::GeomToStep_MakeDirection(const occ::handle<Geom_Direction>& Direc)
{
  gp_Dir                                   D;
  occ::handle<StepGeom_Direction>          Dir        = new StepGeom_Direction;
  occ::handle<NCollection_HArray1<double>> aDirRatios = new NCollection_HArray1<double>(1, 3);
  double                                   X, Y, Z;

  D = Direc->Dir();
  D.Coord(X, Y, Z);
  aDirRatios->SetValue(1, X);
  aDirRatios->SetValue(2, Y);
  aDirRatios->SetValue(3, Z);
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");
  Dir->Init(name, aDirRatios);
  theDirection = Dir;
  done         = true;
}

//=============================================================================
// Creation d' une direction de prostep a partir d' une Direction de Geom2d
//=============================================================================

GeomToStep_MakeDirection::GeomToStep_MakeDirection(const occ::handle<Geom2d_Direction>& Direc)
{
  gp_Dir2d                                 D;
  occ::handle<StepGeom_Direction>          Dir        = new StepGeom_Direction;
  occ::handle<NCollection_HArray1<double>> aDirRatios = new NCollection_HArray1<double>(1, 2);
  double                                   X, Y;

  D = Direc->Dir2d();
  D.Coord(X, Y);
  aDirRatios->SetValue(1, X);
  aDirRatios->SetValue(2, Y);
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");
  Dir->Init(name, aDirRatios);
  theDirection = Dir;
  done         = true;
}

//=============================================================================
// renvoi des valeurs
//=============================================================================

const occ::handle<StepGeom_Direction>& GeomToStep_MakeDirection::Value() const
{
  StdFail_NotDone_Raise_if(!done, "GeomToStep_MakeDirection::Value() - no result");
  return theDirection;
}

#pragma once


#include <Standard.hpp>

#include <Standard_Boolean.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>
#include <STEPControl_ActorWrite.hpp>
class TopoDS_Shape;

//! Extends ActorWrite from STEPControl by analysis of
//! whether shape is assembly (based on information from DECAF)
class STEPCAFControl_ActorWrite : public STEPControl_ActorWrite
{

public:
  Standard_EXPORT STEPCAFControl_ActorWrite();

  //! Check whether shape S is assembly
  //! Returns True if shape is registered in assemblies map
  Standard_EXPORT bool IsAssembly(const occ::handle<StepData_StepModel>& theModel,
                                  TopoDS_Shape&                          S) const override;

  //! Set standard mode of work
  //! In standard mode Actor (default) behaves exactly as its
  //! ancestor, also map is cleared
  Standard_EXPORT void SetStdMode(const bool stdmode = true);

  //! Clears map of shapes registered as assemblies
  Standard_EXPORT void ClearMap();

  //! Registers shape to be written as assembly
  //! The shape should be TopoDS_Compound (else does nothing)
  Standard_EXPORT void RegisterAssembly(const TopoDS_Shape& S);

  DEFINE_STANDARD_RTTIEXT(STEPCAFControl_ActorWrite, STEPControl_ActorWrite)

private:
  bool                                                   myStdMode;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> myMap;
};


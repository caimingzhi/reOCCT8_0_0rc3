#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Draw_Interpretor.hpp>
class HLRAlgo_Projector;
class TopoDS_Shape;
class HLRTopoBRep_OutLiner;

//! This package is a test of the Hidden Lines
//! algorithms instantiated on the BRep Data Structure
//! and using the Draw package to display the results.
class HLRTest
{
public:
  DEFINE_STANDARD_ALLOC

  //! Draw Variable Outliner to test
  //! Set a Projector Variable
  Standard_EXPORT static void Set(const char* Name, const HLRAlgo_Projector& P);

  //! Get a projector variable
  //! Returns false if the variable is not a projector
  Standard_EXPORT static bool GetProjector(const char*& Name, HLRAlgo_Projector& P);

  //! Set a OutLiner Variable
  Standard_EXPORT static void Set(const char* Name, const TopoDS_Shape& S);

  //! Get a outliner variable
  //! Returns a null handle if the variable is not a outliner
  Standard_EXPORT static occ::handle<HLRTopoBRep_OutLiner> GetOutLiner(const char*& Name);

  //! Defines commands to test the Hidden Line Removal
  Standard_EXPORT static void Commands(Draw_Interpretor& I);
};

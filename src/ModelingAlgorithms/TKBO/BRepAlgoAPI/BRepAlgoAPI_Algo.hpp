#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <BRepBuilderAPI_MakeShape.hpp>
#include <BOPAlgo_Options.hpp>

class TopoDS_Shape;

class BRepAlgoAPI_Algo : public BRepBuilderAPI_MakeShape, protected BOPAlgo_Options
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT const TopoDS_Shape& Shape() override;

  using BOPAlgo_Options::Clear;
  using BOPAlgo_Options::ClearWarnings;
  using BOPAlgo_Options::DumpErrors;
  using BOPAlgo_Options::DumpWarnings;
  using BOPAlgo_Options::FuzzyValue;
  using BOPAlgo_Options::GetReport;
  using BOPAlgo_Options::HasError;
  using BOPAlgo_Options::HasErrors;
  using BOPAlgo_Options::HasWarning;
  using BOPAlgo_Options::HasWarnings;
  using BOPAlgo_Options::RunParallel;
  using BOPAlgo_Options::SetFuzzyValue;
  using BOPAlgo_Options::SetRunParallel;
  using BOPAlgo_Options::SetUseOBB;

protected:
  Standard_EXPORT BRepAlgoAPI_Algo();

  Standard_EXPORT ~BRepAlgoAPI_Algo() override;

  Standard_EXPORT BRepAlgoAPI_Algo(const occ::handle<NCollection_BaseAllocator>& theAllocator);
};

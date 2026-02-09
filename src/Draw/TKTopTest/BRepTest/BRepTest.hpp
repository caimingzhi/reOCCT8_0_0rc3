#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Draw_Interpretor.hpp>

class BRepTest
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void AllCommands(Draw_Interpretor& DI);

  Standard_EXPORT static void BasicCommands(Draw_Interpretor& DI);

  Standard_EXPORT static void CurveCommands(Draw_Interpretor& DI);

  Standard_EXPORT static void Fillet2DCommands(Draw_Interpretor& DI);

  Standard_EXPORT static void SurfaceCommands(Draw_Interpretor& DI);

  Standard_EXPORT static void PrimitiveCommands(Draw_Interpretor& DI);

  Standard_EXPORT static void FillingCommands(Draw_Interpretor& DI);

  Standard_EXPORT static void SweepCommands(Draw_Interpretor& DI);

  Standard_EXPORT static void TopologyCommands(Draw_Interpretor& DI);

  Standard_EXPORT static void FilletCommands(Draw_Interpretor& DI);

  Standard_EXPORT static void ChamferCommands(Draw_Interpretor& DI);

  Standard_EXPORT static void GPropCommands(Draw_Interpretor& DI);

  Standard_EXPORT static void MatCommands(Draw_Interpretor& DI);

  Standard_EXPORT static void DraftAngleCommands(Draw_Interpretor& DI);

  Standard_EXPORT static void FeatureCommands(Draw_Interpretor& DI);

  Standard_EXPORT static void OtherCommands(Draw_Interpretor& DI);

  Standard_EXPORT static void ExtremaCommands(Draw_Interpretor& DI);

  Standard_EXPORT static void CheckCommands(Draw_Interpretor& DI);

  Standard_EXPORT static void PlacementCommands(Draw_Interpretor& DI);

  Standard_EXPORT static void ProjectionCommands(Draw_Interpretor& DI);

  Standard_EXPORT static void HistoryCommands(Draw_Interpretor& DI);

  Standard_EXPORT static void HelixCommands(Draw_Interpretor& theCommands);
};

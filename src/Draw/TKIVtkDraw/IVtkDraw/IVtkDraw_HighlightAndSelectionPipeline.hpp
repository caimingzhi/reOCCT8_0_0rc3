#pragma once

#include <NCollection_DataMap.hpp>
#include <NCollection_Shared.hpp>
#include <Standard_Transient.hpp>
#include <TopoDS_Shape.hpp>

#include <Standard_WarningsDisable.hpp>
#include <vtkActor.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <Standard_WarningsRestore.hpp>

#include <IVtk_Types.hpp>
#include <IVtkTools_DisplayModeFilter.hpp>
#include <IVtkTools_SubPolyDataFilter.hpp>

class Prs3d_Drawer;

class IVtkDraw_HighlightAndSelectionPipeline : public Standard_Transient
{
public:
  DEFINE_STANDARD_RTTIEXT(IVtkDraw_HighlightAndSelectionPipeline, Standard_Transient)

public:
  enum FilterId
  {
    Filter_DM_Shape = 1,
    Filter_DM_Hili,
    Filter_DM_Sel,
    Filter_SUB_Hili,
    Filter_SUB_Sel
  };

public:
  IVtkDraw_HighlightAndSelectionPipeline(const TopoDS_Shape&              theShape,
                                         const int                        theShapeID,
                                         const occ::handle<Prs3d_Drawer>& theDrawerLink);

  ~IVtkDraw_HighlightAndSelectionPipeline() override = default;

public:
  void AddToRenderer(vtkRenderer* theRenderer);
  void RemoveFromRenderer(vtkRenderer* theRenderer);

  inline vtkActor* Actor() { return myActor; }

  inline vtkMapper* Mapper() { return myMapper; }

  void ClearHighlightFilters();
  void ClearSelectionFilters();

  IVtkTools_DisplayModeFilter* GetDisplayModeFilter();
  IVtkTools_SubPolyDataFilter* GetHighlightFilter();
  IVtkTools_SubPolyDataFilter* GetSelectionFilter();
  IVtkTools_DisplayModeFilter* GetHighlightDMFilter();
  IVtkTools_DisplayModeFilter* GetSelectionDMFilter();

  void SharedVerticesSelectionOn();
  void SharedVerticesSelectionOff();

private:
  typedef NCollection_DataMap<FilterId, vtkSmartPointer<vtkAlgorithm>> FilterMap;

private:
  vtkSmartPointer<vtkActor> myActor;

  vtkSmartPointer<vtkPolyDataMapper> myMapper;

  vtkSmartPointer<vtkActor> myHiliActor;

  vtkSmartPointer<vtkPolyDataMapper> myHiliMapper;

  vtkSmartPointer<vtkActor> mySelActor;

  vtkSmartPointer<vtkPolyDataMapper> mySelMapper;

  FilterMap myFilterMap;
};

typedef NCollection_Shared<
  NCollection_DataMap<IVtk_IdType, occ::handle<IVtkDraw_HighlightAndSelectionPipeline>>>
  ShapePipelineMap;

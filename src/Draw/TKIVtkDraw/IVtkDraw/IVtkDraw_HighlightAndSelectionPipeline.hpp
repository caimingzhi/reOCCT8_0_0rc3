#pragma once


#include <NCollection_DataMap.hpp>
#include <NCollection_Shared.hpp>
#include <Standard_Transient.hpp>
#include <TopoDS_Shape.hpp>

// prevent disabling some MSVC warning messages by VTK headers
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
  //! Filters comprising the pipeline.
  enum FilterId
  {
    Filter_DM_Shape = 1, //!< Display Mode filter for shape.
    Filter_DM_Hili,      //!< Display Mode filter for highlighting.
    Filter_DM_Sel,       //!< Display Mode filter for selection.
    Filter_SUB_Hili,     //!< Sub-shapes filter for highlighting.
    Filter_SUB_Sel       //!< Sub-shapes filter for selection.
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
  //! Auxiliary map of internal filters by their correspondent IDs.
  typedef NCollection_DataMap<FilterId, vtkSmartPointer<vtkAlgorithm>> FilterMap;

private:
  //! Actor.
  vtkSmartPointer<vtkActor> myActor;

  //! Polygonal mapper.
  vtkSmartPointer<vtkPolyDataMapper> myMapper;

  //! Actor for highlighting.
  vtkSmartPointer<vtkActor> myHiliActor;

  //! Polygonal mapper for highlighting.
  vtkSmartPointer<vtkPolyDataMapper> myHiliMapper;

  //! Actor for selection.
  vtkSmartPointer<vtkActor> mySelActor;

  //! Polygonal mapper for selection.
  vtkSmartPointer<vtkPolyDataMapper> mySelMapper;

  //! Map of involved VTK filters.
  FilterMap myFilterMap;
};

//! Mapping between OCCT topological shape IDs and their correspondent
//! visualization pipelines.
typedef NCollection_Shared<
  NCollection_DataMap<IVtk_IdType, occ::handle<IVtkDraw_HighlightAndSelectionPipeline>>>
  ShapePipelineMap;


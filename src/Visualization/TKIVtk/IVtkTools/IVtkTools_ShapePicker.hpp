#pragma once

#include <IVtkTools.hpp>
#include <IVtk_Types.hpp>
#include <IVtkOCC_ShapePickerAlgo.hpp>

#include <Standard_WarningsDisable.hpp>
#include <vtkAbstractPropPicker.h>
#include <vtkSmartPointer.h>
#include <Standard_WarningsRestore.hpp>

class vtkRenderer;
class vtkActorCollection;

#ifdef _MSC_VER
  #pragma warning(push)
  #pragma warning(disable : 4251)
#endif

class Standard_EXPORT IVtkTools_ShapePicker : public vtkAbstractPropPicker
{
public:
  vtkTypeMacro(IVtkTools_ShapePicker, vtkAbstractPropPicker)

    static IVtkTools_ShapePicker* New();

  int pick(double* thePos, vtkRenderer* theRenderer, const int theNbPoints = -1);

  int Pick(double theX, double theY, double theZ, vtkRenderer* theRenderer = nullptr) override;

  int Pick(double       theX0,
           double       theY0,
           double       theX1,
           double       theY1,
           vtkRenderer* theRenderer = nullptr);

  int Pick(double poly[][3], const int theNbPoints, vtkRenderer* theRenderer = nullptr);

  void SetTolerance(float theTolerance);

  float GetTolerance() const;

  void SetRenderer(vtkRenderer* theRenderer);

  void SetAreaSelection(bool theIsOn);

  NCollection_List<IVtk_SelectionMode> GetSelectionModes(const IVtk_IShape::Handle& theShape) const;

  NCollection_List<IVtk_SelectionMode> GetSelectionModes(vtkActor* theShapeActor) const;

  void SetSelectionMode(const IVtk_IShape::Handle& theShape,
                        const IVtk_SelectionMode   theMode,
                        const bool                 theIsTurnOn = true) const;

  void SetSelectionMode(vtkActor*                theShapeActor,
                        const IVtk_SelectionMode theMode,
                        const bool               theIsTurnOn = true) const;

  void SetSelectionMode(const IVtk_SelectionMode theMode, const bool theIsTurnOn = true) const;

  NCollection_List<IVtk_IdType> GetPickedShapesIds(bool theIsAll = false) const;

  NCollection_List<IVtk_IdType> GetPickedSubShapesIds(const IVtk_IdType theId,
                                                      bool              theIsAll = false) const;

  vtkSmartPointer<vtkActorCollection> GetPickedActors(bool theIsAll = false) const;

  void RemoveSelectableObject(const IVtk_IShape::Handle& theShape);

  void RemoveSelectableActor(vtkActor* theShapeActor);

protected:
  IVtkTools_ShapePicker();

  ~IVtkTools_ShapePicker() override;

  static bool convertDisplayToWorld(vtkRenderer* theRenderer,
                                    double       theDisplayCoord[3],
                                    double       theWorldCoord[3]);

private:
  IVtkTools_ShapePicker(const IVtkTools_ShapePicker&)            = delete;
  IVtkTools_ShapePicker& operator=(const IVtkTools_ShapePicker&) = delete;

  virtual void doPickImpl(double*, vtkRenderer* theRenderer, const int theNbPoints = -1);

private:
  IVtkOCC_ShapePickerAlgo::Handle myOccPickerAlgo;
  vtkSmartPointer<vtkRenderer>    myRenderer;
  bool                            myIsRectSelection;
  bool                            myIsPolySelection;
  float                           myTolerance;
};

#ifdef _MSC_VER
  #pragma warning(pop)
#endif

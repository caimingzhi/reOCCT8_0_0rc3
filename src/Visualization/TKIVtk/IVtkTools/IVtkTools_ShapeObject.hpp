#pragma once

#include <IVtkTools.hpp>
#include <IVtkOCC_Shape.hpp>

#include <Standard_WarningsDisable.hpp>
#include <vtkDataObject.h>
#include <vtkSetGet.h>
#include <vtkWeakPointer.h>
#include <Standard_WarningsRestore.hpp>

class vtkActor;
class vtkDataSet;
class vtkInformationObjectBaseKey;
class IVtkTools_ShapeDataSource;

#ifdef _MSC_VER
  #pragma warning(push)
  #pragma warning(disable : 4251)
#endif

class Standard_EXPORT IVtkTools_ShapeObject : public vtkDataObject
{
public:
  vtkTypeMacro(IVtkTools_ShapeObject, vtkDataObject)

    static IVtkTools_ShapeObject* New();

  static vtkSmartPointer<IVtkTools_ShapeDataSource> GetShapeSource(vtkActor* theActor);

  static IVtkOCC_Shape::Handle GetOccShape(vtkActor* theActor);

  static void SetShapeSource(IVtkTools_ShapeDataSource* theDataSource, vtkDataSet* theData);

  static void SetShapeSource(IVtkTools_ShapeDataSource* theDataSource, vtkActor* theActor);

  typedef vtkInformationObjectBaseKey* KeyPtr;

  static KeyPtr getKey();

  void SetShapeSource(IVtkTools_ShapeDataSource* theDataSource);

  IVtkTools_ShapeDataSource* GetShapeSource() const;

protected:
  IVtkTools_ShapeObject();
  ~IVtkTools_ShapeObject() override;

private:
  IVtkTools_ShapeObject(const IVtkTools_ShapeObject&)            = delete;
  IVtkTools_ShapeObject& operator=(const IVtkTools_ShapeObject&) = delete;

private:
  vtkWeakPointer<IVtkTools_ShapeDataSource> myShapeSource;

  static KeyPtr myKey;
};

#ifdef _MSC_VER
  #pragma warning(pop)
#endif

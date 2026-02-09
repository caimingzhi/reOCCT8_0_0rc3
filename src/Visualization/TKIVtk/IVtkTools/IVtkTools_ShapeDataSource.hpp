#pragma once

#include <IVtkTools.hpp>
#include <IVtkOCC_Shape.hpp>
#include <IVtkVTK_ShapeData.hpp>

#include <Standard_WarningsDisable.hpp>
#include <vtkPolyDataAlgorithm.h>
#include <Standard_WarningsRestore.hpp>

class vtkIdTypeArray;
class vtkPolyData;

#ifdef _MSC_VER
  #pragma warning(push)
  #pragma warning(disable : 4251)
#endif

class Standard_EXPORT IVtkTools_ShapeDataSource : public vtkPolyDataAlgorithm
{
public:
  vtkTypeMacro(IVtkTools_ShapeDataSource, vtkPolyDataAlgorithm)

    static IVtkTools_ShapeDataSource* New();

public:
  void SetShape(const IVtkOCC_Shape::Handle& theOccShape);

  const IVtkOCC_Shape::Handle& GetShape() { return myOccShape; }

  inline void FastTransformModeOn() { myIsFastTransformMode = true; }

  inline void FastTransformModeOff() { myIsFastTransformMode = false; }

public:
  IVtk_IdType GetId() const;

  bool Contains(const IVtkOCC_Shape::Handle& theOccShape) const;

  vtkSmartPointer<vtkIdTypeArray> SubShapeIDs();

protected:
  int RequestData(vtkInformation*        theRequest,
                  vtkInformationVector** theInputVector,
                  vtkInformationVector*  theOutputVector) override;

protected:
  vtkSmartPointer<vtkPolyData> transform(vtkPolyData* theSource, const gp_Trsf& theTrsf) const;

protected:
  IVtkTools_ShapeDataSource();
  ~IVtkTools_ShapeDataSource() override;

private:
  IVtkTools_ShapeDataSource(const IVtkTools_ShapeDataSource&)            = delete;
  IVtkTools_ShapeDataSource& operator=(const IVtkTools_ShapeDataSource&) = delete;

protected:
  IVtkOCC_Shape::Handle     myOccShape;
  IVtkVTK_ShapeData::Handle myPolyData;

  bool myIsFastTransformMode;

  bool myIsTransformOnly;
};

#ifdef _MSC_VER
  #pragma warning(pop)
#endif

#include <IVtkTools_ShapeObject.hpp>
#include <IVtkTools_ShapeDataSource.hpp>

#ifdef _MSC_VER
  #pragma warning(push)
#endif
#include <vtkActor.h>
#include <vtkObjectFactory.h>
#include <vtkDataSet.h>
#include <vtkInformation.h>
#include <vtkInformationObjectBaseKey.h>
#include <vtkPolyData.h>
#ifdef _MSC_VER
  #pragma warning(pop)
#endif

IVtkTools_ShapeObject::KeyPtr IVtkTools_ShapeObject::myKey = nullptr;

IVtkTools_ShapeObject::KeyPtr IVtkTools_ShapeObject::getKey()
{
  if (!myKey)
  {
    myKey = new vtkInformationObjectBaseKey("OccShapePtr", "IVtkTools_ShapeObject::Key");
  }

  return myKey;
}

IVtkOCC_Shape::Handle IVtkTools_ShapeObject::GetOccShape(vtkActor* theActor)
{
  IVtkOCC_Shape::Handle                      anOccShape;
  vtkSmartPointer<IVtkTools_ShapeDataSource> aSrc = IVtkTools_ShapeObject::GetShapeSource(theActor);
  if (aSrc.GetPointer() != nullptr)
  {
    anOccShape = aSrc->GetShape();
  }
  return anOccShape;
}

vtkSmartPointer<IVtkTools_ShapeDataSource> IVtkTools_ShapeObject ::GetShapeSource(
  vtkActor* theActor)
{
  vtkSmartPointer<IVtkTools_ShapeDataSource> anOccShapeSource;
  vtkSmartPointer<vtkInformation>            anInfo = theActor->GetPropertyKeys();
  if (anInfo.GetPointer() != nullptr)
  {
    KeyPtr aKey = getKey();
    if (aKey->Has(anInfo))
    {
      vtkSmartPointer<IVtkTools_ShapeObject> aShapeObj =
        IVtkTools_ShapeObject::SafeDownCast(aKey->Get(anInfo));
      anOccShapeSource = aShapeObj->GetShapeSource();
    }
  }
  return anOccShapeSource;
}

void IVtkTools_ShapeObject::SetShapeSource(IVtkTools_ShapeDataSource* theDataSource,
                                           vtkDataSet*                theDataSet)
{
  if (!theDataSet->GetInformation())
  {
    theDataSet->SetInformation(vtkSmartPointer<vtkInformation>::New());
  }
  vtkSmartPointer<vtkInformation>        aDatasetInfo = theDataSet->GetInformation();
  KeyPtr                                 aKey         = getKey();
  vtkSmartPointer<IVtkTools_ShapeObject> aShapeObj = vtkSmartPointer<IVtkTools_ShapeObject>::New();
  aShapeObj->SetShapeSource(theDataSource);
  aKey->Set(aDatasetInfo, aShapeObj);
}

void IVtkTools_ShapeObject::SetShapeSource(IVtkTools_ShapeDataSource* theDataSource,
                                           vtkActor*                  theActor)
{
  if (!theActor->GetPropertyKeys())
  {
    theActor->SetPropertyKeys(vtkSmartPointer<vtkInformation>::New());
  }

  vtkSmartPointer<vtkInformation>        anInfo    = theActor->GetPropertyKeys();
  KeyPtr                                 aKey      = getKey();
  vtkSmartPointer<IVtkTools_ShapeObject> aShapeObj = vtkSmartPointer<IVtkTools_ShapeObject>::New();
  aShapeObj->SetShapeSource(theDataSource);
  aKey->Set(anInfo, aShapeObj);
}

vtkStandardNewMacro(IVtkTools_ShapeObject)

  IVtkTools_ShapeObject::IVtkTools_ShapeObject() = default;

IVtkTools_ShapeObject::~IVtkTools_ShapeObject() = default;

void IVtkTools_ShapeObject::SetShapeSource(IVtkTools_ShapeDataSource* theDataSource)
{
  myShapeSource = theDataSource;
}

IVtkTools_ShapeDataSource* IVtkTools_ShapeObject::GetShapeSource() const
{
  return myShapeSource;
}

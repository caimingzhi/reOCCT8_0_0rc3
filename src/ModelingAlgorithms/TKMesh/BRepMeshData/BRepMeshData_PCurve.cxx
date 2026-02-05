#include <BRepMeshData_PCurve.hpp>
#include <gp_Pnt2d.hpp>
#include <BRepMesh_Vertex.hpp>
#include <Standard_OutOfRange.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepMeshData_PCurve, IMeshData_PCurve)

//=================================================================================================

BRepMeshData_PCurve::BRepMeshData_PCurve(const IMeshData::IFacePtr& theDFace,
                                         const TopAbs_Orientation   theOrientation,
                                         const occ::handle<NCollection_IncAllocator>& theAllocator)
    : IMeshData_PCurve(theDFace, theOrientation),
      myPoints2d(NCollection_OccAllocator<gp_Pnt2d>(theAllocator)),
      myParameters(NCollection_OccAllocator<double>(theAllocator)),
      myIndices(NCollection_OccAllocator<int>(theAllocator))
{
}

//=================================================================================================

BRepMeshData_PCurve::~BRepMeshData_PCurve() = default;

//=================================================================================================

void BRepMeshData_PCurve::InsertPoint(const int       thePosition,
                                      const gp_Pnt2d& thePoint,
                                      const double    theParamOnPCurve)
{
  myPoints2d.insert(myPoints2d.begin() + thePosition, thePoint);
  myParameters.insert(myParameters.begin() + thePosition, theParamOnPCurve);
  myIndices.insert(myIndices.begin() + thePosition, 0);
}

//=================================================================================================

void BRepMeshData_PCurve::AddPoint(const gp_Pnt2d& thePoint, const double theParamOnPCurve)
{
  myPoints2d.push_back(thePoint);
  myParameters.push_back(theParamOnPCurve);
  myIndices.push_back(0);
}

//=================================================================================================

gp_Pnt2d& BRepMeshData_PCurve::GetPoint(const int theIndex)
{
  Standard_OutOfRange_Raise_if(theIndex < 0 || theIndex >= static_cast<int>(myPoints2d.size()),
                               "BRepMeshData_PCurve::GetPoint");
  return myPoints2d[theIndex];
}

//=================================================================================================

int& BRepMeshData_PCurve::GetIndex(const int theIndex)
{
  Standard_OutOfRange_Raise_if(theIndex < 0 || theIndex >= static_cast<int>(myIndices.size()),
                               "BRepMeshData_PCurve::GetIndex");
  return myIndices[theIndex];
}

//=================================================================================================

double& BRepMeshData_PCurve::GetParameter(const int theIndex)
{
  Standard_OutOfRange_Raise_if(theIndex < 0 || theIndex >= ParametersNb(),
                               "BRepMeshData_PCurve::GetParameter");
  return myParameters[theIndex];
}

//=================================================================================================

int BRepMeshData_PCurve::ParametersNb() const
{
  return static_cast<int>(myParameters.size());
}

//=================================================================================================

void BRepMeshData_PCurve::RemovePoint(const int theIndex)
{
  myPoints2d.erase(myPoints2d.begin() + theIndex);
  myIndices.erase(myIndices.begin() + theIndex);
  removeParameter(theIndex);
}

//=================================================================================================

void BRepMeshData_PCurve::removeParameter(const int theIndex)
{
  myParameters.erase(myParameters.begin() + theIndex);
}

//=================================================================================================

void BRepMeshData_PCurve::Clear(const bool isKeepEndPoints)
{
  if (!isKeepEndPoints)
  {
    myPoints2d.clear();
    myParameters.clear();
    myIndices.clear();
  }
  else if (ParametersNb() > 2)
  {
    myPoints2d.erase(myPoints2d.begin() + 1, myPoints2d.begin() + (myPoints2d.size() - 1));
    myParameters.erase(myParameters.begin() + 1, myParameters.begin() + (myParameters.size() - 1));
    myIndices.erase(myIndices.begin() + 1, myIndices.begin() + (myIndices.size() - 1));
  }
}

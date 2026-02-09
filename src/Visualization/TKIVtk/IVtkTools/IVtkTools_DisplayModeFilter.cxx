#include <IVtkTools_DisplayModeFilter.hpp>
#include <IVtkVTK_ShapeData.hpp>

#ifdef _MSC_VER
  #pragma warning(push)
#endif
#include <vtkInformation.h>
#include <vtkInformationVector.h>
#include <vtkObjectFactory.h>
#ifdef _MSC_VER
  #pragma warning(pop)
#endif

vtkStandardNewMacro(IVtkTools_DisplayModeFilter)

  IVtkTools_DisplayModeFilter::IVtkTools_DisplayModeFilter()
    : myDisplayMode(DM_Wireframe),
      myDoDisplaySharedVertices(false),
      myDrawFaceBoundaries(false),
      myIsSmoothShading(true)
{

  myIdsArrayName = IVtkVTK_ShapeData::ARRNAME_MESH_TYPES();

  NCollection_Map<IVtk_IdType> aTypes;

  aTypes.Add(MT_IsoLine);
  aTypes.Add(MT_FreeVertex);
  aTypes.Add(MT_FreeEdge);
  aTypes.Add(MT_BoundaryEdge);
  aTypes.Add(MT_SharedEdge);
  aTypes.Add(MT_SeamEdge);
  aTypes.Add(MT_WireFrameFace);

  myModesDefinition[DM_Wireframe] = aTypes;

  aTypes.Clear();
  aTypes.Add(MT_FreeVertex);
  aTypes.Add(MT_ShadedFace);

  myModesDefinition[DM_Shading] = aTypes;
}

IVtkTools_DisplayModeFilter::~IVtkTools_DisplayModeFilter() = default;

int IVtkTools_DisplayModeFilter::RequestData(vtkInformation*        theRequest,
                                             vtkInformationVector** theInputVector,
                                             vtkInformationVector*  theOutputVector)
{
  SetData(myModesDefinition[myDisplayMode]);
  myToCopyNormals = myIsSmoothShading && (myDisplayMode == DM_Shading);
  return Superclass::RequestData(theRequest, theInputVector, theOutputVector);
}

void IVtkTools_DisplayModeFilter::PrintSelf(std::ostream& theOs, vtkIndent theIndent)
{
  this->Superclass::PrintSelf(theOs, theIndent);
  theOs << theIndent << "IVtkTools_DisplayModeFilter: display mode = ";
  if (myDisplayMode == DM_Wireframe)
  {
    theOs << "Wireframe\n";
  }
  else
  {
    theOs << "Shading\n";
  }
}

void IVtkTools_DisplayModeFilter::SetDisplaySharedVertices(const bool theDoDisplay)
{
  if (myDoDisplaySharedVertices != theDoDisplay)
  {
    myDoDisplaySharedVertices = theDoDisplay;
    NCollection_Map<IVtk_IdType> aModeTypes;
    for (int i = 0; i < 2; i++)
    {
      aModeTypes = myModesDefinition[i];
      if (theDoDisplay && !aModeTypes.Contains(MT_SharedVertex))
      {
        aModeTypes.Add(MT_SharedVertex);
      }
      else if (!theDoDisplay && aModeTypes.Contains(MT_SharedVertex))
      {
        aModeTypes.Remove(MT_SharedVertex);
      }
      myModesDefinition[i] = aModeTypes;
    }
    Modified();
  }
}

void IVtkTools_DisplayModeFilter::SetDisplayMode(const IVtk_DisplayMode theMode)
{
  if (myDisplayMode != theMode)
  {
    myDisplayMode = theMode;
    Modified();
  }
}

IVtk_DisplayMode IVtkTools_DisplayModeFilter::GetDisplayMode() const
{
  return myDisplayMode;
}

const NCollection_Map<IVtk_IdType>& IVtkTools_DisplayModeFilter::MeshTypesForMode(
  IVtk_DisplayMode theMode) const
{
  return myModesDefinition[theMode];
}

void IVtkTools_DisplayModeFilter::SetMeshTypesForMode(
  IVtk_DisplayMode                    theMode,
  const NCollection_Map<IVtk_IdType>& theMeshTypes)
{
  myModesDefinition[theMode] = theMeshTypes;
  Modified();
}

void IVtkTools_DisplayModeFilter::SetFaceBoundaryDraw(bool theToDraw)
{
  myDrawFaceBoundaries = theToDraw;
  if (theToDraw)
  {
    myModesDefinition[DM_Shading].Add(MT_BoundaryEdge);
    myModesDefinition[DM_Shading].Add(MT_SharedEdge);
  }
  else
  {
    myModesDefinition[DM_Shading].Remove(MT_BoundaryEdge);
    myModesDefinition[DM_Shading].Remove(MT_SharedEdge);
  }
  Modified();
}

void IVtkTools_DisplayModeFilter::SetSmoothShading(bool theIsSmooth)
{
  if (myIsSmoothShading != theIsSmooth)
  {
    myIsSmoothShading = theIsSmooth;
    Modified();
  }
}

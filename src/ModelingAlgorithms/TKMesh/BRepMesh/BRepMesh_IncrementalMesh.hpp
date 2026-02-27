#pragma once

#include <BRepMesh_DiscretRoot.hpp>
#include <IMeshTools_Context.hpp>
#include <Standard_NumericError.hpp>

class BRepMesh_IncrementalMesh : public BRepMesh_DiscretRoot
{
public:
  Standard_EXPORT BRepMesh_IncrementalMesh();

  Standard_EXPORT ~BRepMesh_IncrementalMesh() override;

  Standard_EXPORT BRepMesh_IncrementalMesh(const TopoDS_Shape& theShape,
                                           const double        theLinDeflection,
                                           const bool          isRelative       = false,
                                           const double        theAngDeflection = 0.5,
                                           const bool          isInParallel     = false);

  Standard_EXPORT BRepMesh_IncrementalMesh(
    const TopoDS_Shape&          theShape,
    const IMeshTools_Parameters& theParameters,
    const System::log::Message_ProgressRange& theRange = System::log::Message_ProgressRange());

  Standard_EXPORT void Perform(
    const System::log::Message_ProgressRange& theRange = System::log::Message_ProgressRange()) override;

  Standard_EXPORT void Perform(const occ::handle<IMeshTools_Context>& theContext,
                               const System::log::Message_ProgressRange& theRange = System::log::Message_ProgressRange());

public:
  const IMeshTools_Parameters& Parameters() const { return myParameters; }

  IMeshTools_Parameters& ChangeParameters() { return myParameters; }

  bool IsModified() const { return myModified; }

  int GetStatusFlags() const { return myStatus; }

private:
  void initParameters()
  {
    if (myParameters.Deflection < math::precision::Precision::Confusion())
    {
      throw Standard_NumericError(
        "BRepMesh_IncrementalMesh::initParameters : invalid parameter value");
    }
    if (myParameters.DeflectionInterior < math::precision::Precision::Confusion())
    {
      myParameters.DeflectionInterior = myParameters.Deflection;
    }

    if (myParameters.MinSize < math::precision::Precision::Confusion())
    {
      myParameters.MinSize =
        (std::max)(IMeshTools_Parameters::RelMinSize()
                     * (std::min)(myParameters.Deflection, myParameters.DeflectionInterior),
                   math::precision::Precision::Confusion());
    }

    if (myParameters.Angle < math::precision::Precision::Angular())
    {
      throw Standard_NumericError(
        "BRepMesh_IncrementalMesh::initParameters : invalid parameter value");
    }
    if (myParameters.AngleInterior < math::precision::Precision::Angular())
    {
      myParameters.AngleInterior = 2.0 * myParameters.Angle;
    }
  }

public:
  Standard_EXPORT static int Discret(const TopoDS_Shape&    theShape,
                                     const double           theLinDeflection,
                                     const double           theAngDeflection,
                                     BRepMesh_DiscretRoot*& theAlgo);

  Standard_EXPORT static bool IsParallelDefault();

  Standard_EXPORT static void SetParallelDefault(const bool isInParallel);

  DEFINE_STANDARD_RTTIEXT(BRepMesh_IncrementalMesh, BRepMesh_DiscretRoot)

protected:
  IMeshTools_Parameters myParameters;
  bool                  myModified;
  int                   myStatus;
};

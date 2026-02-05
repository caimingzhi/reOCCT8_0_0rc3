#pragma once

#include <Message_ProgressRange.hpp>
#include <ShapeProcess.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <Standard_Integer.hpp>
#include <Standard_CString.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <XSAlgo_ShapeProcessor.hpp>

struct DE_ShapeFixParameters;
class IGESData_IGESModel;
class IGESToBRep_Actor;
class Transfer_TransientProcess;
class TopoDS_Shape;

//! A simple way to read geometric IGES data.
//! Encapsulates reading file and calling transfer tools
class IGESToBRep_Reader
{
public:
  DEFINE_STANDARD_ALLOC

public:
  //! Creates a Reader
  Standard_EXPORT IGESToBRep_Reader();

  //! Loads a Model from a file.Returns 0 if success.
  //! returns 1 if the file could not be opened,
  //! returns -1 if an error occurred while the file was being loaded.
  Standard_EXPORT int LoadFile(const char* filename);

  //! Specifies a Model to work on
  //! Also clears the result and Done status, sets TransientProcess
  Standard_EXPORT void SetModel(const occ::handle<IGESData_IGESModel>& model);

  //! Returns the Model to be worked on.
  Standard_EXPORT occ::handle<IGESData_IGESModel> Model() const;

  //! Allows to set an already defined TransientProcess
  //! (to be called after LoadFile or SetModel)
  Standard_EXPORT void SetTransientProcess(const occ::handle<Transfer_TransientProcess>& TP);

  //! Returns the TransientProcess
  Standard_EXPORT occ::handle<Transfer_TransientProcess> TransientProcess() const;

  //! Returns "theActor"
  Standard_EXPORT occ::handle<IGESToBRep_Actor> Actor() const;

  //! Clears the results between two translation operations.
  Standard_EXPORT void Clear();

  //! Checks the IGES file that was
  //! loaded into memory. Displays error messages in the default
  //! message file if withprint is true. Returns True if no fail
  //! message was found and False if there was at least one fail message.
  Standard_EXPORT bool Check(const bool withprint) const;

  //! Translates root entities in an
  //! IGES file. true is the default value and means that only
  //! visible root entities are translated. false
  //! translates all of the roots (visible and invisible).
  Standard_EXPORT void TransferRoots(
    const bool                   onlyvisible = true,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Transfers an Entity given its rank in the Model (Root or not)
  //! Returns True if it is recognized as Geom-Topol.
  //! (But it can have failed : see IsDone)
  Standard_EXPORT bool Transfer(const int                    num,
                                const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Returns True if the LAST Transfer/TransferRoots was a success
  Standard_EXPORT bool IsDone() const;

  //! Returns the Tolerance which has been actually used, converted
  //! in millimeters
  //! (either that from File or that from Session, according the mode)
  Standard_EXPORT double UsedTolerance() const;

  //! Returns the number of shapes produced by the translation.
  Standard_EXPORT int NbShapes() const;

  //! Returns the num the resulting shape in a translation operation.
  Standard_EXPORT TopoDS_Shape Shape(const int num = 1) const;

  //! Returns all of the results in a
  //! single shape which is:
  //! - a null shape if there are no results,
  //! - a shape if there is one result,
  //! - a compound containing the resulting shapes if there are several.
  Standard_EXPORT TopoDS_Shape OneShape() const;

  //! Sets parameters for shape processing.
  //! @param theParameters the parameters for shape processing.
  Standard_EXPORT void SetShapeFixParameters(
    const XSAlgo_ShapeProcessor::ParameterMap& theParameters);

  //! Sets parameters for shape processing.
  //! Parameters are moved from the input map.
  //! @param theParameters the parameters for shape processing.
  Standard_EXPORT void SetShapeFixParameters(XSAlgo_ShapeProcessor::ParameterMap&& theParameters);

  //! Sets parameters for shape processing.
  //! Parameters from @p theParameters are copied to the internal map.
  //! Parameters from @p theAdditionalParameters are copied to the internal map
  //! if they are not present in @p theParameters.
  //! @param theParameters the parameters for shape processing.
  //! @param theAdditionalParameters the additional parameters for shape processing.
  Standard_EXPORT void SetShapeFixParameters(
    const DE_ShapeFixParameters&               theParameters,
    const XSAlgo_ShapeProcessor::ParameterMap& theAdditionalParameters = {});

  //! Returns parameters for shape processing that was set by SetParameters() method.
  //! @return the parameters for shape processing. Empty map if no parameters were set.
  inline const XSAlgo_ShapeProcessor::ParameterMap& GetShapeFixParameters() const
  {
    return myShapeProcParams;
  }

  //! Sets flags defining operations to be performed on shapes.
  //! @param theFlags The flags defining operations to be performed on shapes.
  Standard_EXPORT void SetShapeProcessFlags(const ShapeProcess::OperationsFlags& theFlags);

  //! Returns flags defining operations to be performed on shapes.
  //! @return The flags defining operations to be performed on shapes.
  inline const ShapeProcess::OperationsFlags& GetShapeProcessFlags() const
  {
    return myShapeProcFlags.first;
  }

private:
  //! If parameters haven't yet been provided, initializes them with default values.
  void InitializeMissingParameters();

private:
  occ::handle<IGESData_IGESModel>        theModel;
  bool                                   theDone;
  NCollection_Sequence<TopoDS_Shape>     theShapes;
  occ::handle<IGESToBRep_Actor>          theActor;
  occ::handle<Transfer_TransientProcess> theProc;
  // clang-format off
  XSAlgo_ShapeProcessor::ParameterMap myShapeProcParams; //!< Parameters for shape processing.
  XSAlgo_ShapeProcessor::ProcessingFlags myShapeProcFlags; //!< Flags defining operations to be performed on shapes.
  // clang-format on
};

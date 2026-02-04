#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Macro.hpp>

#include <Standard_Real.hpp>
#include <BRepMesh_CircleInspector.hpp>
#include <gp_XY.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Boolean.hpp>
#include <IMeshData_Types.hpp>
#include <NCollection_Array1.hpp>

class gp_Circ2d;

//! Create sort and destroy the circles used in triangulation.
class BRepMesh_CircleTool
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructor.
  //! @param theAllocator memory allocator to be used by internal structures.
  Standard_EXPORT BRepMesh_CircleTool(const occ::handle<NCollection_IncAllocator>& theAllocator);

  //! Constructor.
  //! @param theReservedSize size to be reserved for vector of circles.
  //! @param theAllocator memory allocator to be used by internal structures.
  Standard_EXPORT BRepMesh_CircleTool(const int                                    theReservedSize,
                                      const occ::handle<NCollection_IncAllocator>& theAllocator);

  //! Initializes the tool.
  //! @param theReservedSize size to be reserved for vector of circles.
  void Init(const int /*theReservedSize*/) { myTolerance = Precision::PConfusion(); }

  //! Sets new size for cell filter.
  //! @param theSize cell size to be set for X and Y dimensions.
  void SetCellSize(const double theSize) { myCellFilter.Reset(theSize, myAllocator); }

  //! Sets new size for cell filter.
  //! @param theSizeX cell size to be set for X dimension.
  //! @param theSizeY cell size to be set for Y dimension.
  void SetCellSize(const double theSizeX, const double theSizeY)
  {
    double                     aCellSizeC[2] = {theSizeX, theSizeY};
    NCollection_Array1<double> aCellSize(aCellSizeC[0], 1, 2);
    myCellFilter.Reset(aCellSize, myAllocator);
  }

  //! Sets limits of inspection area.
  //! @param theMin bottom left corner of inspection area.
  //! @param theMax top right corner of inspection area.
  void SetMinMaxSize(const gp_XY& theMin, const gp_XY& theMax)
  {
    myFaceMin = theMin;
    myFaceMax = theMax;
  }

  //! Returns true if cell filter contains no circle.
  bool IsEmpty() const { return mySelector.Circles().IsEmpty(); }

  //! Binds the circle to the tool.
  //! @param theIndex index a circle should be bound with.
  //! @param theCircle circle to be bound.
  Standard_EXPORT void Bind(const int theIndex, const gp_Circ2d& theCircle);

  //! Computes circle on three points.
  //! @param thePoint1 first point.
  //! @param thePoint2 second point.
  //! @param thePoint3 third point.
  //! @param[out] theLocation center of computed circle.
  //! @param[out] theRadius radius of computed circle.
  //! @return FALSE in case of impossibility to build a circle
  //! on the given points, TRUE elsewhere.
  Standard_EXPORT static bool MakeCircle(const gp_XY& thePoint1,
                                         const gp_XY& thePoint2,
                                         const gp_XY& thePoint3,
                                         gp_XY&       theLocation,
                                         double&      theRadius);

  //! Computes circle on three points and bind it to the tool.
  //! @param theIndex index a circle should be bound with.
  //! @param thePoint1 first point.
  //! @param thePoint2 second point.
  //! @param thePoint3 third point.
  //! @return FALSE in case of impossibility to build a circle
  //! on the given points, TRUE elsewhere.
  Standard_EXPORT bool Bind(const int    theIndex,
                            const gp_XY& thePoint1,
                            const gp_XY& thePoint2,
                            const gp_XY& thePoint3);

  //! Binds implicit zero circle.
  //! @param theIndex index a zero circle should be bound with.
  Standard_EXPORT void MocBind(const int theIndex);

  //! Deletes a circle from the tool.
  //! @param theIndex index of a circle to be removed.
  Standard_EXPORT void Delete(const int theIndex);

  //! Select the circles shot by the given point.
  //! @param thePoint bullet point.
  Standard_EXPORT IMeshData::ListOfInteger& Select(const gp_XY& thePoint);

private:
  //! Creates circle with the given parameters and binds it to the tool.
  //! @param theIndex index a circle should be bound with.
  //! @param theLocation location of a circle.
  //! @param theRadius radius of a circle.
  void bind(const int theIndex, const gp_XY& theLocation, const double theRadius);

private:
  double                                myTolerance;
  occ::handle<NCollection_IncAllocator> myAllocator;
  IMeshData::CircleCellFilter           myCellFilter;
  BRepMesh_CircleInspector              mySelector;
  gp_XY                                 myFaceMax;
  gp_XY                                 myFaceMin;
};


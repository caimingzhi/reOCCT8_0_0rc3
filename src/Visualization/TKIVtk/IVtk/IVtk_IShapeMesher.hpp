#pragma once


#include <IVtk_Interface.hpp>
#include <IVtk_IShape.hpp>
#include <IVtk_IShapeData.hpp>

//! @class  IVtk_IShapeMesher
//! @brief Interface for triangulator of 3D shapes.
class IVtk_IShapeMesher : public IVtk_Interface
{
public:
  typedef occ::handle<IVtk_IShapeMesher> Handle;

  ~IVtk_IShapeMesher() override = default;

  //! Main entry point for building shape representation
  //! @param[in]  shape IShape to be meshed
  //! @param[in]  data IShapeData interface visualization data is passed to.
  Standard_EXPORT void Build(const IVtk_IShape::Handle&     theShape,
                             const IVtk_IShapeData::Handle& theData);

  DEFINE_STANDARD_RTTIEXT(IVtk_IShapeMesher, IVtk_Interface)

protected:
  //! Executes the mesh generation algorithms. To be defined in implementation class.
  Standard_EXPORT virtual void initialize(const IVtk_IShape::Handle&     theShapeObj,
                                          const IVtk_IShapeData::Handle& theShapeData);
  virtual void                 internalBuild() = 0;

protected:
  IVtk_IShape::Handle     myShapeObj;
  IVtk_IShapeData::Handle myShapeData;
};


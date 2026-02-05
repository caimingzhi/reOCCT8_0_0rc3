#include <IVtk_IShapeMesher.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IVtk_IShapeMesher, IVtk_Interface)

//=================================================================================================

void IVtk_IShapeMesher::initialize(const IVtk_IShape::Handle&     theShape,
                                   const IVtk_IShapeData::Handle& theData)
{
  myShapeObj  = theShape;
  myShapeData = theData;
}

//=================================================================================================

void IVtk_IShapeMesher::Build(const IVtk_IShape::Handle&     theShape,
                              const IVtk_IShapeData::Handle& theData)
{
  if (!theShape.IsNull())
  {
    initialize(theShape, theData);
    internalBuild();
  }
}

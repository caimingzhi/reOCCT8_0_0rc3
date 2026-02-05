#pragma once

#define DISCRETPLUGIN(name)                                                                        \
  extern "C"                                                                                       \
  {                                                                                                \
    Standard_EXPORT int DISCRETALGO(const TopoDS_Shape&,                                           \
                                    const double,                                                  \
                                    const double,                                                  \
                                    BRepMesh_DiscretRoot*&);                                       \
  }                                                                                                \
                                                                                                   \
  int DISCRETALGO(const TopoDS_Shape&    theShape,                                                 \
                  const double           theLinDeflection,                                         \
                  const double           theAngDeflection,                                         \
                  BRepMesh_DiscretRoot*& theAlgo)                                                  \
  {                                                                                                \
    return name::Discret(theShape, theLinDeflection, theAngDeflection, theAlgo);                   \
  }

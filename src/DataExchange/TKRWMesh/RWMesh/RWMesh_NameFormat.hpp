#pragma once

//! Name format preference for XCAF shape labels.
enum RWMesh_NameFormat
{
  RWMesh_NameFormat_Empty,    //!< omit the name
  RWMesh_NameFormat_Product,  //!< return Product name
                              //!  (e.g. from XCAFDoc_ShapeTool::GetReferredShape(), which could be
                              //!  shared by multiple Instances)
  RWMesh_NameFormat_Instance, //!< return Instance name
  RWMesh_NameFormat_InstanceOrProduct,  //!< return Instance name when available and Product name
                                        //!< otherwise
  RWMesh_NameFormat_ProductOrInstance,  //!< return Product name when available and Instance name
                                        //!< otherwise
  RWMesh_NameFormat_ProductAndInstance, //!< generate "Product [Instance]" name
  RWMesh_NameFormat_ProductAndInstanceAndOcaf, //!< generate name combining Product+Instance+Ocaf
                                               //!< (useful for debugging purposes)
};

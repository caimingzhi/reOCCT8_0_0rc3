#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class gp_Pnt;

//! defines VertexList, Type <502> Form Number <1>
//! in package IGESSolid
//! A vertex is a point in R3. A vertex is the bound of an
//! edge and can participate in the bounds of a face.
//! It contains one or more vertices.
class IGESSolid_VertexList : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_VertexList();

  //! This method is used to set the fields of the class
  //! VertexList
  //! - vertices : the vertices in the list
  Standard_EXPORT void Init(const occ::handle<NCollection_HArray1<gp_XYZ>>& vertices);

  //! return the number of vertices in the list
  Standard_EXPORT int NbVertices() const;

  //! returns the num'th vertex in the list
  //! raises exception if num <= 0 or num > NbVertices()
  Standard_EXPORT gp_Pnt Vertex(const int num) const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_VertexList, IGESData_IGESEntity)

private:
  occ::handle<NCollection_HArray1<gp_XYZ>> theVertices;
};


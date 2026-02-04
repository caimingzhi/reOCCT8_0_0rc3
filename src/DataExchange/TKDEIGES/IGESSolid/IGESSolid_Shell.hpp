#pragma once


#include <Standard.hpp>

#include <IGESSolid_Face.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
class IGESSolid_Face;

//! defines Shell, Type <514> Form Number <1>
//! in package IGESSolid
//! Shell entity is a connected entity of dimensionality 2
//! which divides R3 into two arcwise connected open subsets,
//! one of which is finite. Inside of the shell is defined to
//! be the finite region.
//! From IGES-5.3, Form can be <1> for Closed or <2> for Open
class IGESSolid_Shell : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_Shell();

  //! This method is used to set the fields of the class Shell
  //! - allFaces  : the faces comprising the shell
  //! - allOrient : the orientation flags of the shell
  //! raises exception if length of allFaces & allOrient do not match
  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<occ::handle<IGESSolid_Face>>>& allFaces,
    const occ::handle<NCollection_HArray1<int>>&                         allOrient);

  //! Tells if a Shell is Closed, i.e. if its FormNumber is 1
  //! (this is the default)
  Standard_EXPORT bool IsClosed() const;

  //! Sets or Unsets the Closed status (FormNumber = 1 else 2)
  Standard_EXPORT void SetClosed(const bool closed);

  //! returns the number of the face entities in the shell
  Standard_EXPORT int NbFaces() const;

  //! returns the Index'th face entity of the shell
  //! raises exception if Index <= 0 or Index > NbFaces()
  Standard_EXPORT occ::handle<IGESSolid_Face> Face(const int Index) const;

  //! returns the orientation of Index'th face w.r.t the direction of
  //! the underlying surface
  //! raises exception if Index <= 0 or Index > NbFaces()
  Standard_EXPORT bool Orientation(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_Shell, IGESData_IGESEntity)

private:
  occ::handle<NCollection_HArray1<occ::handle<IGESSolid_Face>>> theFaces;
  occ::handle<NCollection_HArray1<int>>                         theOrientation;
};


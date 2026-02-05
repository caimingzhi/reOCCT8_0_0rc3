#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESAppli_Node.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;
class IGESAppli_Node;

//! defines FiniteElement, Type <136> Form <0>
//! in package IGESAppli
//! Used to define a finite element with the help of an
//! element topology.
class IGESAppli_FiniteElement : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_FiniteElement();

  //! This method is used to set the fields of the class
  //! FiniteElement
  //! - aType    : Indicates the topology type
  //! - allNodes : List of Nodes defining the element
  //! - aName    : Element type name
  Standard_EXPORT void Init(
    const int                                                            aType,
    const occ::handle<NCollection_HArray1<occ::handle<IGESAppli_Node>>>& allNodes,
    const occ::handle<TCollection_HAsciiString>&                         aName);

  //! returns Topology type
  Standard_EXPORT int Topology() const;

  //! returns the number of nodes defining the element
  Standard_EXPORT int NbNodes() const;

  //! returns Node defining element entity
  //! raises exception if Index <= 0 or Index > NbNodes()
  Standard_EXPORT occ::handle<IGESAppli_Node> Node(const int Index) const;

  //! returns Element Type Name
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_FiniteElement, IGESData_IGESEntity)

private:
  int                                                           theTopology;
  occ::handle<NCollection_HArray1<occ::handle<IGESAppli_Node>>> theNodes;
  occ::handle<TCollection_HAsciiString>                         theName;
};

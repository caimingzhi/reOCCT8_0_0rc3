#pragma once


#include <IVtk_Interface.hpp>
#include <IVtk_Types.hpp>

//! @class IVtk_IShape
//! @brief Interface for working with a shape and its sub-shapes ids.
class IVtk_IShape : public IVtk_Interface
{
public:
  typedef occ::handle<IVtk_IShape> Handle;

  ~IVtk_IShape() override = default;

  IVtk_IdType GetId() const { return myId; }

  void SetId(const IVtk_IdType theId) { myId = theId; }

  //! Get ids of sub-shapes composing a sub-shape with the given id
  virtual NCollection_List<IVtk_IdType> GetSubIds(const IVtk_IdType theId) const = 0;

  DEFINE_STANDARD_RTTIEXT(IVtk_IShape, IVtk_Interface)

private:
  IVtk_IdType myId;
};


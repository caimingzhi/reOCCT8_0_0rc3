#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <ShapeProcess_Context.hpp>
#include <Message_Gravity.hpp>
#include <GeomAbs_Shape.hpp>
class ShapeExtend_MsgRegistrator;
class ShapeBuild_ReShape;
class BRepTools_Modifier;
class Message_Msg;

class ShapeProcess_ShapeContext : public ShapeProcess_Context
{

public:
  Standard_EXPORT ShapeProcess_ShapeContext(const char* file, const char* seq = "");

  Standard_EXPORT ShapeProcess_ShapeContext(const TopoDS_Shape& S,
                                            const char*         file,
                                            const char*         seq = "");

  Standard_EXPORT void Init(const TopoDS_Shape& S);

  Standard_EXPORT const TopoDS_Shape& Shape() const;

  Standard_EXPORT const TopoDS_Shape& Result() const;

  Standard_EXPORT const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>&
                        Map() const;

  Standard_EXPORT const occ::handle<ShapeExtend_MsgRegistrator>& Messages() const;

  Standard_EXPORT occ::handle<ShapeExtend_MsgRegistrator>& Messages();

  Standard_EXPORT void SetDetalisation(const TopAbs_ShapeEnum level);

  Standard_EXPORT TopAbs_ShapeEnum GetDetalisation() const;

  Standard_EXPORT void SetResult(const TopoDS_Shape& S);

  Standard_EXPORT void RecordModification(
    const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& repl,
    const occ::handle<ShapeExtend_MsgRegistrator>&                                  msg = nullptr);

  Standard_EXPORT void RecordModification(const occ::handle<ShapeBuild_ReShape>&         repl,
                                          const occ::handle<ShapeExtend_MsgRegistrator>& msg);

  Standard_EXPORT void RecordModification(const occ::handle<ShapeBuild_ReShape>& repl);

  Standard_EXPORT void RecordModification(
    const TopoDS_Shape&                            sh,
    const BRepTools_Modifier&                      repl,
    const occ::handle<ShapeExtend_MsgRegistrator>& msg = nullptr);

  Standard_EXPORT void AddMessage(const TopoDS_Shape&   S,
                                  const Message_Msg&    msg,
                                  const Message_Gravity gravity = Message_Warning);

  Standard_EXPORT bool GetContinuity(const char* param, GeomAbs_Shape& val) const;

  Standard_EXPORT GeomAbs_Shape ContinuityVal(const char* param, const GeomAbs_Shape def) const;

  Standard_EXPORT void PrintStatistics() const;

  void SetNonManifold(bool theNonManifold) { myNonManifold = theNonManifold; }

  bool IsNonManifold() { return myNonManifold; }

  DEFINE_STANDARD_RTTIEXT(ShapeProcess_ShapeContext, ShapeProcess_Context)

private:
  TopoDS_Shape                                                             myShape;
  TopoDS_Shape                                                             myResult;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myMap;
  occ::handle<ShapeExtend_MsgRegistrator>                                  myMsg;
  TopAbs_ShapeEnum                                                         myUntil;
  bool                                                                     myNonManifold;
};

#pragma once

enum Graphic3d_TypeOfShaderObject
{

  Graphic3d_TOS_VERTEX          = 0x01,
  Graphic3d_TOS_TESS_CONTROL    = 0x02,
  Graphic3d_TOS_TESS_EVALUATION = 0x04,
  Graphic3d_TOS_GEOMETRY        = 0x08,
  Graphic3d_TOS_FRAGMENT        = 0x10,

  Graphic3d_TOS_COMPUTE = 0x20
};

#include <NCollection_Sequence.hpp>
#include <OSD_Path.hpp>
#include <TCollection_AsciiString.hpp>

class Graphic3d_ShaderObject : public Standard_Transient
{
public:
  struct ShaderVariable
  {
    TCollection_AsciiString Name;
    int                     Stages;

    ShaderVariable(const TCollection_AsciiString& theVarName, int theShaderStageBits)
        : Name(theVarName),
          Stages(theShaderStageBits)
    {
    }

    ShaderVariable()
        : Stages(0)
    {
    }
  };

  typedef NCollection_Sequence<ShaderVariable> ShaderVariableList;

public:
  Standard_EXPORT static occ::handle<Graphic3d_ShaderObject> CreateFromFile(
    const Graphic3d_TypeOfShaderObject theType,
    const TCollection_AsciiString&     thePath);

  Standard_EXPORT static occ::handle<Graphic3d_ShaderObject> CreateFromSource(
    const Graphic3d_TypeOfShaderObject theType,
    const TCollection_AsciiString&     theSource);

  Standard_EXPORT static occ::handle<Graphic3d_ShaderObject> CreateFromSource(
    TCollection_AsciiString&       theSource,
    Graphic3d_TypeOfShaderObject   theType,
    const ShaderVariableList&      theUniforms,
    const ShaderVariableList&      theStageInOuts,
    const TCollection_AsciiString& theInName           = TCollection_AsciiString::EmptyString(),
    const TCollection_AsciiString& theOutName          = TCollection_AsciiString::EmptyString(),
    int                            theNbGeomInputVerts = 0);

private:
  Standard_EXPORT Graphic3d_ShaderObject(const Graphic3d_TypeOfShaderObject theType);

public:
  Standard_EXPORT ~Graphic3d_ShaderObject() override;

  Standard_EXPORT virtual bool IsDone() const;

  const OSD_Path& Path() const { return myPath; }

  const TCollection_AsciiString& Source() const { return mySource; }

  Graphic3d_TypeOfShaderObject Type() const { return myType; }

  const TCollection_AsciiString& GetId() const { return myID; }

public:
  DEFINE_STANDARD_RTTIEXT(Graphic3d_ShaderObject, Standard_Transient)

protected:
  TCollection_AsciiString myID;
  TCollection_AsciiString mySource;
  OSD_Path                myPath;

private:
  Graphic3d_TypeOfShaderObject myType;
};

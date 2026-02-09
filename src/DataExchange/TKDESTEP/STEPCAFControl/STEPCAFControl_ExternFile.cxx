#include <STEPCAFControl_ExternFile.hpp>
#include <TDF_Label.hpp>
#include <XSControl_WorkSession.hpp>

IMPLEMENT_STANDARD_RTTIEXT(STEPCAFControl_ExternFile, Standard_Transient)

STEPCAFControl_ExternFile::STEPCAFControl_ExternFile()
    : myLoadStatus(IFSelect_RetVoid),
      myTransferStatus(false),
      myWriteStatus(IFSelect_RetVoid)
{
}

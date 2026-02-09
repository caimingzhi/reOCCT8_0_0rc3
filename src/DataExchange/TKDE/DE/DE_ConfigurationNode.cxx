

#include <DE_ConfigurationNode.hpp>

#include <DE_ConfigurationContext.hpp>
#include <DE_Provider.hpp>
#include <DE_Wrapper.hpp>
#include <Message.hpp>
#include <Standard_ErrorHandler.hpp>
#include <OSD_File.hpp>
#include <OSD_Path.hpp>
#include <OSD_Protection.hpp>

IMPLEMENT_STANDARD_RTTIEXT(DE_ConfigurationNode, Standard_Transient)

DE_ConfigurationNode::DE_ConfigurationNode()
    : myIsEnabled(true)
{
}

DE_ConfigurationNode::DE_ConfigurationNode(
  const occ::handle<DE_ConfigurationNode>& theConfigurationNode)
{
  GlobalParameters = theConfigurationNode->GlobalParameters;
  myIsEnabled      = theConfigurationNode->IsEnabled();
}

bool DE_ConfigurationNode::Load(const TCollection_AsciiString& theResourcePath)
{
  occ::handle<DE_ConfigurationContext> aResource = new DE_ConfigurationContext();
  aResource->LoadFile(theResourcePath);
  return Load(aResource);
}

bool DE_ConfigurationNode::Save(const TCollection_AsciiString& theResourcePath) const
{
  OSD_Path       aPath = theResourcePath;
  OSD_File       aFile(aPath);
  OSD_Protection aProt;
  {
    try
    {
      OCC_CATCH_SIGNALS
      aFile.Build(OSD_ReadWrite, aProt);
    }
    catch (Standard_Failure const&)
    {
      Message::SendFail() << "Error: Configuration writing process was stopped. Can't build file.";
      return false;
    }
  }
  if (aFile.Failed())
  {
    Message::SendFail() << "Error: Configuration writing process was stopped. Can't build file.";
    return false;
  }
  TCollection_AsciiString aResConfiguration = Save();
  aFile.Write(aResConfiguration, aResConfiguration.Length());
  aFile.Close();
  return true;
}

bool DE_ConfigurationNode::UpdateLoad(const bool theToImport, const bool theToKeep)
{
  (void)theToImport;
  (void)theToKeep;
  return true;
}

bool DE_ConfigurationNode::IsImportSupported() const
{
  return false;
}

bool DE_ConfigurationNode::IsExportSupported() const
{
  return false;
}

bool DE_ConfigurationNode::IsStreamSupported() const
{
  return false;
}

bool DE_ConfigurationNode::CheckExtension(const TCollection_AsciiString& theExtension) const
{
  TCollection_AsciiString anExtension(theExtension);
  if (anExtension.IsEmpty())
  {
    return false;
  }
  if (anExtension.Value(1) == '.')
  {
    anExtension.Remove(1);
  }
  const NCollection_List<TCollection_AsciiString>& anExtensions = GetExtensions();
  for (NCollection_List<TCollection_AsciiString>::Iterator anIter(anExtensions); anIter.More();
       anIter.Next())
  {
    if (TCollection_AsciiString::IsSameString(anIter.Value(), anExtension, false))
    {
      return true;
    }
  }
  return false;
}

bool DE_ConfigurationNode::CheckContent(const occ::handle<NCollection_Buffer>& theBuffer) const
{
  (void)theBuffer;
  return false;
}

void DE_ConfigurationNode::Register(const occ::handle<DE_Wrapper>& theWrapper) const
{
  theWrapper->Bind(this);
}

void DE_ConfigurationNode::UnRegister(const occ::handle<DE_Wrapper>& theWrapper) const
{
  theWrapper->UnBind(this);
}

#pragma once

#include <NCollection_Vec3.hpp>
#include <Standard_TypeDef.hpp>

#include <map>
#include <vector>
#include <set>
#include <string>

class gp_Vec;
class gp_Pnt;

typedef std::size_t ViewerTest_CommandOptionKey;

typedef std::set<ViewerTest_CommandOptionKey> ViewerTest_CommandOptionKeySet;

class ViewerTest_CmdParser
{
public:
  static const std::size_t THE_UNNAMED_COMMAND_OPTION_KEY;

  static const std::size_t THE_HELP_COMMAND_OPTION_KEY;

  ViewerTest_CmdParser(const std::string& theDescription = std::string());

  void SetDescription(const std::string& theDescription) { myDescription = theDescription; }

  ViewerTest_CommandOptionKey AddOption(const std::string& theOptionNames,
                                        const std::string& theOptionDescription = std::string());

  void PrintHelp() const;

  void Parse(int theArgsNb, const char* const* theArgVec);

  std::string GetOptionNameByKey(ViewerTest_CommandOptionKey theOptionKey) const;

  ViewerTest_CommandOptionKeySet GetUsedOptions() const;

  bool HasNoOption() const;

  bool HasUnnamedOption() const;

  bool HasOnlyUnnamedOption() const;

  bool HasOption(const std::string& theOptionName,
                 std::size_t        theMandatoryArgsNb = 0,
                 bool               isFatal            = false) const;

  bool HasOption(ViewerTest_CommandOptionKey theOptionKey,
                 std::size_t                 theMandatoryArgsNb = 0,
                 bool                        isFatal            = false) const;

  int GetNumberOfOptionArguments(const std::string& theOptionName) const;

  int GetNumberOfOptionArguments(ViewerTest_CommandOptionKey theOptionKey) const;

  bool Arg(const std::string& theOptionName,
           int                theArgumentIndex,
           std::string&       theOptionArgument) const;

  bool Arg(ViewerTest_CommandOptionKey theOptionKey,
           int                         theArgumentIndex,
           std::string&                theOptionArgument) const;

  std::string Arg(const std::string& theOptionName, int theArgumentIndex) const;

  std::string Arg(ViewerTest_CommandOptionKey theOptionKey, int theArgumentIndex) const;

  NCollection_Vec3<float> ArgVec3f(const std::string& theOptionName,
                                   const int          theArgumentIndex = 0) const;

  NCollection_Vec3<double> ArgVec3d(const std::string& theOptionName,
                                    const int          theArgumentIndex = 0) const;

  gp_Vec ArgVec(const std::string& theOptionName, const int theArgumentIndex = 0) const;

  gp_Pnt ArgPnt(const std::string& theOptionName, const int theArgumentIndex = 0) const;

  double ArgDouble(const std::string& theOptionName, const int theArgumentIndex = 0) const;

  float ArgFloat(const std::string& theOptionName, const int theArgumentIndex = 0) const;

  int ArgInt(const std::string& theOptionName, const int theArgumentIndex = 0) const;

  bool ArgBool(const std::string& theOptionName, const int theArgumentIndex = 0) const;

  template <typename TheColor>
  bool ArgColor(const std::string& theOptionName, int& theArgumentIndex, TheColor& theColor) const;

  template <typename TheColor>
  bool ArgColor(ViewerTest_CommandOptionKey theOptionKey,
                int&                        theArgumentIndex,
                TheColor&                   theColor) const;

private:
  typedef std::vector<std::string> OptionAliases;

  typedef std::map<std::string, ViewerTest_CommandOptionKey> OptionMap;

  typedef std::map<ViewerTest_CommandOptionKey, std::size_t> UsedOptionMap;

  typedef std::vector<std::string> OptionArguments;

  typedef std::vector<OptionArguments> OptionArgumentsStorage;

  struct CommandOption
  {
    std::string   Name;
    OptionAliases Aliases;
    std::string   Description;
  };

  typedef std::vector<CommandOption> CommandOptionStorage;

  typedef std::vector<const char*> RawStringArguments;

  std::string myDescription;

  std::vector<CommandOption> myOptionStorage;

  OptionMap myOptionMap;

  UsedOptionMap myUsedOptionMap;

  OptionArgumentsStorage myOptionArgumentStorage;

  bool findOptionKey(const std::string&           theOptionName,
                     ViewerTest_CommandOptionKey& theOptionKey) const;

  bool findUsedOptionIndex(ViewerTest_CommandOptionKey theOptionKey,
                           std::size_t&                theUsedOptionIndex) const;

  bool findUsedOptionIndex(const std::string& theOptionName, std::size_t& theUsedOptionIndex) const;

  std::size_t addUsedOption(ViewerTest_CommandOptionKey theNewUsedOptionKey);

  RawStringArguments getRawStringArguments(std::size_t theUsedOptionIndex) const;
};

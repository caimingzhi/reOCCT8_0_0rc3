#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <IFSelect_SelectExtract.hpp>
class Interface_EntityIterator;
class Interface_Graph;
class Standard_Transient;
class Interface_InterfaceModel;
class TCollection_AsciiString;

//! This class returns entities according sending to a file
//! Once a model has been loaded, further sendings are recorded
//! as status in the graph (for each value, a count of sendings)
//!
//! Hence, it is possible to query entities : sent ones (at least
//! once), non-sent (i.e. remaining) ones, duplicated ones, etc...
//!
//! This selection performs this query
class IFSelect_SelectSent : public IFSelect_SelectExtract
{

public:
  //! Creates a SelectSent :
  //! sentcount = 0 -> remaining (non-sent) entities
  //! sentcount = 1, atleast = True (D) -> sent (at least once)
  //! sentcount = 2, atleast = True -> duplicated (sent least twice)
  //! etc...
  //! sentcount = 1, atleast = False -> sent just once (non-dupl.d)
  //! sentcount = 2, atleast = False -> sent just twice
  //! etc...
  Standard_EXPORT IFSelect_SelectSent(const int sentcount = 1, const bool atleast = true);

  //! Returns the queried count of sending
  Standard_EXPORT int SentCount() const;

  //! Returns the <atleast> status, True for sending at least the
  //! sending count, False for sending exactly the sending count
  //! Remark : if SentCount is 0, AtLeast is ignored
  Standard_EXPORT bool AtLeast() const;

  //! Returns the list of selected entities. It is redefined to
  //! work on the graph itself (not queried by sort)
  //!
  //! An entity is selected if its count complies to the query in
  //! Direct Mode, rejected in Reversed Mode
  //!
  //! Query works on the sending count recorded as status in Graph
  Standard_EXPORT Interface_EntityIterator RootResult(const Interface_Graph& G) const override;

  //! Returns always False because RootResult has done the work
  Standard_EXPORT bool Sort(const int                                    rank,
                            const occ::handle<Standard_Transient>&       ent,
                            const occ::handle<Interface_InterfaceModel>& model) const override;

  //! Returns a text defining the criterium : query :
  //! SentCount = 0 -> "Remaining (non-sent) entities"
  //! SentCount = 1, AtLeast = True  -> "Sent entities"
  //! SentCount = 1, AtLeast = False -> "Sent once (no duplicated)"
  //! SentCount = 2, AtLeast = True  -> "Sent several times entities"
  //! SentCount = 2, AtLeast = False -> "Sent twice entities"
  //! SentCount > 2, AtLeast = True  -> "Sent at least <count> times entities"
  //! SentCount > 2, AtLeast = False -> "Sent <count> times entities"
  Standard_EXPORT TCollection_AsciiString ExtractLabel() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectSent, IFSelect_SelectExtract)

private:
  int  thecnt;
  bool thelst;
};



#include <Interface_STAT.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_HAsciiString.hpp>

static Interface_STAT statvoid("");
static Interface_STAT statact("");
static const char*    voidname = "";

Interface_STAT::Interface_STAT(const char* title)
{
  thetitle = new TCollection_HAsciiString(title);
  thetotal = 1.;
}

Interface_STAT::Interface_STAT(const Interface_STAT& other)
{
  other.Internals(thetitle, thetotal, thephnam, thephw, thephdeb, thephfin, thestw);
}

void Interface_STAT::Internals(occ::handle<TCollection_HAsciiString>&                       tit,
                               double&                                                      total,
                               occ::handle<NCollection_HSequence<TCollection_AsciiString>>& phn,
                               occ::handle<NCollection_HSequence<double>>&                  phw,
                               occ::handle<NCollection_HSequence<int>>&                     phdeb,
                               occ::handle<NCollection_HSequence<int>>&                     phfin,
                               occ::handle<NCollection_HSequence<double>>& stw) const
{
  tit   = thetitle;
  total = thetotal;
  phn   = thephnam;
  phw   = thephw;
  phdeb = thephdeb;
  phfin = thephfin;
  stw   = thestw;
}

void Interface_STAT::AddPhase(const double weight, const char* name)
{
  if (thephw.IsNull())
  {

    thetotal = 0.;
    thephnam = new NCollection_HSequence<TCollection_AsciiString>();
    thephw   = new NCollection_HSequence<double>();
    thephdeb = new NCollection_HSequence<int>();
    thephfin = new NCollection_HSequence<int>();
    thestw   = new NCollection_HSequence<double>();
  }
  thetotal += weight;
  thephnam->Append(TCollection_AsciiString(name));
  thephw->Append(weight);
  thephdeb->Append(thestw->Length() + 1);
  thephfin->Append(0);
  thestw->Append(0.);
}

void Interface_STAT::AddStep(const double weight)
{
  if (thephdeb.IsNull())
  {

    thephdeb = new NCollection_HSequence<int>();
    thephfin = new NCollection_HSequence<int>();
    thestw   = new NCollection_HSequence<double>();
    thephdeb->Append(thestw->Length() + 1);
    thephfin->Append(1);
    thestw->Append(0.);
  }

  int n0 = thephdeb->Value(thephdeb->Length());

  thestw->ChangeValue(n0) += weight;
  thestw->Append(weight);
  thephfin->ChangeValue(thephfin->Length())++;
}

void Interface_STAT::Description(int& nbphases, double& total, const char*& title) const
{
  nbphases = (thephw.IsNull() ? 1 : thephw->Length());
  total    = thetotal;
  title    = thetitle->ToCString();
}

void Interface_STAT::Phase(const int    num,
                           int&         n0step,
                           int&         nbstep,
                           double&      weight,
                           const char*& name) const
{
  if (thephdeb.IsNull())
  {

    n0step = -1;
    nbstep = 1;
    weight = 1.;
    name   = voidname;
  }
  if (thephw.IsNull())
  {

    weight = 1.;
    name   = voidname;
  }
  else if (num < 1 || num > thephdeb->Length())
    return;
  else
  {

    weight = thephw->Value(num);
    name   = thephnam->Value(num).ToCString();
    n0step = thephdeb->Value(num);
    nbstep = thephfin->Value(num);
  }
}

double Interface_STAT::Step(const int num) const
{
  if (thestw.IsNull())
    return 1.;
  if (num < 1 || num > thestw->Length())
    return 1.;
  return thestw->Value(num);
}

static struct zestat
{
  const char* itle;
  const char* name;
  double      otal, oldph, phw, otph, oldst, stw;
  int         nbph, numph, n0, n1, nbitp, nbcyc, olditp, numcyc, nbitc, numst, numitem;
} TheStat;

void Interface_STAT::Start(const int items, const int cycles) const
{
  statact = *this;
  statact.Description(TheStat.nbph, TheStat.otal, TheStat.itle);
  TheStat.oldph = TheStat.phw = 0.;
  TheStat.numph               = 0;
  NextPhase(items, cycles);
}

void Interface_STAT::StartCount(const int items, const char* name)
{
  Interface_STAT statcount(name);
  statcount.Start(items);
}

void Interface_STAT::NextPhase(const int items, const int cycles)
{

  TheStat.numcyc = TheStat.numst = TheStat.olditp = 0;
  TheStat.oldst = TheStat.stw = 0.;
  if (TheStat.numph >= TheStat.nbph)
  {
    End();
    return;
  }

  TheStat.numph++;
  TheStat.oldph += TheStat.phw;
  TheStat.nbitp = items;
  TheStat.nbcyc = cycles;
  statact.Phase(TheStat.numph, TheStat.n0, TheStat.n1, TheStat.phw, TheStat.name);
  TheStat.otph = (TheStat.n1 > 1 ? statact.Step(TheStat.n0) : 1.);

  TheStat.nbitc = 0;
  if (cycles == 1)
    NextCycle(items);
}

void Interface_STAT::SetPhase(const int items, const int cycles)
{
  TheStat.nbitp = items;
  TheStat.nbcyc = cycles;
}

void Interface_STAT::NextCycle(const int items)
{

  TheStat.numcyc++;
  TheStat.olditp += TheStat.nbitc;

  TheStat.numst   = 1;
  TheStat.oldst   = 0.;
  TheStat.stw     = (TheStat.n1 > 1 ? statact.Step(TheStat.n0 + 1) : TheStat.otph);
  TheStat.nbitc   = items;
  TheStat.numitem = 0;
}

void Interface_STAT::NextStep()
{
  if (TheStat.numst >= TheStat.n1)
    return;
  TheStat.numst++;
  TheStat.oldst += TheStat.stw;
  TheStat.numitem = 0;
  TheStat.stw     = statact.Step(TheStat.n0 + TheStat.numst);
}

void Interface_STAT::NextItem(const int nbitems)
{
  TheStat.numitem += nbitems;
}

void Interface_STAT::End()
{
  TheStat.oldph = TheStat.otal;
  TheStat.phw = TheStat.stw = 0.;
  TheStat.itle = TheStat.name = voidname;
}

const char* Interface_STAT::Where(const bool phase)
{
  return (phase ? TheStat.name : TheStat.itle);
}

int Interface_STAT::Percent(const bool phase)
{
  if (TheStat.numitem > TheStat.nbitc)
    TheStat.numitem = TheStat.nbitc;

  double enphase =
    TheStat.olditp * TheStat.otph + TheStat.nbitc * TheStat.oldst + TheStat.numitem * TheStat.stw;

  double prophase = enphase / (TheStat.nbitp * TheStat.otph);
  int    res      = int(prophase * 100.);
  if (phase)
    return res;

  double encours = (TheStat.oldph + TheStat.phw * prophase) / TheStat.otal;
  res            = int(encours * 100.);
  return res;
}

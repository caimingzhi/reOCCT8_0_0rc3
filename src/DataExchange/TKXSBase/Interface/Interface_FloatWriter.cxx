

#include <Interface_FloatWriter.hpp>

Interface_FloatWriter::Interface_FloatWriter(const int chars)
{
  SetDefaults(chars);
}

void Interface_FloatWriter::SetFormat(const char* form, const bool reset)
{
  strcpy(themainform, form);
  if (!reset)
    return;
  therange1 = therange2 = 0.;
  thezerosup            = false;
}

void Interface_FloatWriter::SetFormatForRange(const char* form, const double R1, const double R2)
{
  strcpy(therangeform, form);
  therange1 = R1;
  therange2 = R2;
}

void Interface_FloatWriter::SetZeroSuppress(const bool mode)
{
  thezerosup = mode;
}

void Interface_FloatWriter::SetDefaults(const int chars)
{
  if (chars <= 0)
  {
    strcpy(themainform, "%E");
    strcpy(therangeform, "%f");
  }
  else
  {
    char pourcent = '%';
    char point    = '.';
    Sprintf(themainform, "%c%d%c%dE", pourcent, chars + 2, point, chars);
    Sprintf(therangeform, "%c%d%c%df", pourcent, chars + 2, point, chars);
  }
  therange1  = 0.1;
  therange2  = 1000.;
  thezerosup = true;
}

void Interface_FloatWriter::Options(bool& zerosup, bool& range, double& R1, double& R2) const
{
  zerosup = thezerosup;
  range   = (therange2 >= therange1 && therange1 >= 0.);
  R1      = therange1;
  R2      = therange2;
}

const char* Interface_FloatWriter::MainFormat() const
{
  const char* mainform = static_cast<const char*>(&themainform[0]);
  return mainform;
}

const char* Interface_FloatWriter::FormatForRange() const
{
  const char* rangeform = static_cast<const char*>(&therangeform[0]);
  return rangeform;
}

int Interface_FloatWriter::Write(const double val, const char* text) const
{
  const char* mainform  = static_cast<const char*>(themainform);
  const char* rangeform = static_cast<const char*>(therangeform);
  return Convert(val, text, thezerosup, therange1, therange2, mainform, rangeform);
}

int Interface_FloatWriter::Convert(const double val,
                                   const char*  text,
                                   const bool   zsup,
                                   const double R1,
                                   const double R2,
                                   const char*  mainform,
                                   const char*  rangeform)
{

  const int anMasSize = 5;
  char      lxp[anMasSize], *pText;
  int       i0 = 0, j0 = 0;

  for (int i = 0; i < anMasSize; ++i)
    lxp[i] = '\0';

  pText = (char*)text;

  if ((val >= R1 && val < R2) || (val <= -R1 && val > -R2))
    Sprintf(pText, rangeform, val);
  else
    Sprintf(pText, mainform, val);

  if (zsup)
  {
    for (int i = 0; i < 16; i++)
    {
      i0 = i;
      if (text[i] == 'e' || text[i] == 'E')
      {
        lxp[0] = 'E';
        lxp[1] = text[i + 1];
        lxp[2] = text[i + 2];
        lxp[3] = text[i + 3];
        lxp[4] = text[i + 4];

        if (lxp[1] == '+' && lxp[2] == '0' && lxp[3] == '0' && lxp[4] == '\0')
          lxp[0] = '\0';

        pText[i] = '\0';
      }
      if (text[i] == '\0')
        break;
    }

    for (int j = i0 - 1; j >= 0; j--)
    {
      j0 = j;

      if (text[j] != '0')
        break;

      pText[j] = '\0';
    }

    pText[j0 + 1] = lxp[0];
    pText[j0 + 2] = lxp[1];
    pText[j0 + 3] = lxp[2];
    pText[j0 + 4] = lxp[3];
    pText[j0 + 5] = lxp[4];
    pText[j0 + 6] = '\0';
  }
  return (int)strlen(text);
}

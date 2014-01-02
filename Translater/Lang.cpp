#include "Lang.h"

Lang strToLang(const char* lang)
{
  if (strcmp(lang, "en") == 0)
  {
    return ENGLISH;
  } else if (strcmp(lang, "ru") == 0)
  {
    return RUSSIAN;
  }
  throw "Invalid argument";
}

const char* langToStr(Lang lang)
{
  if (lang == ENGLISH)
  {
      return "en";
  } else if (lang == RUSSIAN)
  {
      return "ru";
  }
  throw "Invalid argument";
}

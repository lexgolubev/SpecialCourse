#include "translater.h"

Translater::Translater()
{
  this->loadDb(ENGLISH, RUSSIAN);
  this->loadDb(RUSSIAN, ENGLISH);
}

void Translater::loadDb(Lang from, Lang to)
{
  DB db(from, to);
  vectorDb.push_back(db);
  std::string fileName;
  fileName += "./dict/";
  fileName += langToStr(from);
  fileName += "-";
  fileName += langToStr(to);
  fileName += ".txt";
  this->loadFile(fileName.c_str(), from, to);
}

void Translater::loadFile(const char* fileName, Lang from, Lang to)
{
  std::ifstream in;
  in.open(fileName);
  const int maxSymbols = 1000;
  char current[maxSymbols];
  while (!in.eof())
  {
    in.getline(current, maxSymbols);
    std::string str(current);
    while (str.size() > 0)
    {
        int ptr = str.find_first_of(' ');
        std::string word;
        word.assign(str, 0, ptr);
        str = str.erase(0, ptr + 1);
        std::vector<std::string> translations;
        bool exit = false;
        while (!exit)
        {
            ptr = str.find_first_of(' ');
            if (ptr < 0)
            {
              ptr = str.size() - 1;
              exit = true;
            }
            std::string translation;
            translation.assign(str, 0, ptr);
            str = str.erase(0, ptr + 1);
            translations.push_back(translation);
        }
        this->addWord(word, translations, from, to);
    }
  }
}

void Translater::addWord(std::string word, std::vector<std::string> translations, Lang from, Lang to)
{
  std::vector<DB>::iterator i = vectorDb.begin();
  while (i < vectorDb.end())
  {
      if ((*i).getLangFrom() == from && (*i).getLangTo() == to)
      {
          (*i).addWord(word, translations);
          break;
      }
      ++i;
  }
}

std::vector<std::string> Translater::translate(std::string word, Lang from, Lang to)
{
  std::vector<DB>::iterator i = vectorDb.begin();
  while (i < vectorDb.end())
  {
      if ((*i).getLangFrom() == from && (*i).getLangTo() == to)
      {
          return (*i).translate(word);
      }
      ++i;
  }
  std::vector<std::string> res;
  return res;
}

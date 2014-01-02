#ifndef TRANSLATER_H
#define TRANSLATER_H

#include "translater_global.h"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "db.h"

//Translater stores info about databases and delegates methods to DB
class TRANSLATERSHARED_EXPORT Translater
{
public:
  Translater();

  void loadDb(Lang from, Lang to);

  void addWord(std::string word, std::vector<std::string> translations, Lang from, Lang to);

  std::vector<std::string> translate(std::string word, Lang from, Lang to);

private:
  std::vector<DB> vectorDb;

  void loadFile(const char* fileName, Lang from, Lang to);
};

#endif // TRANSLATER_H

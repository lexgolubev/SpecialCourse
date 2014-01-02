#ifndef DB_H
#define DB_H

#include <vector>
#include <string>
#include <boost/unordered_map.hpp>
#include <map>

#include "Lang.h"

//DB is a representation of database, based on unordered_map<string, vector<string> >
class DB
{
public:
  DB(Lang from, Lang to);

  std::vector<std::string> translate(std::string word);

  void addWord(std::string word, std::vector<std::string> translations);

  Lang getLangFrom();

  Lang getLangTo();

  int size();

private:
  boost::unordered_map<std::string, std::vector<std::string> > db;

  Lang from;

  Lang to;

};

#endif // DB_H

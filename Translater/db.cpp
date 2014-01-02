#include "db.h"

DB::DB(Lang from, Lang to)
{
  this->from = from;
  this->to = to;
}

std::vector<std::string> DB::translate(std::string word)
{
  boost::unordered_map<std::string, std::vector<std::string> >::const_iterator i = db.find(word);
  if (i != db.end())
  {
      std::pair<std::string, std::vector<std::string> > entry = *i;
      return entry.second;
  }
  std::vector<std::string> res;
  return res;
}

void DB::addWord(std::string word, std::vector<std::string> translations)
{
  db[word] = translations;
}

Lang DB::getLangFrom()
{
  return from;
}

Lang DB::getLangTo()
{
  return to;
}

int DB::size()
{
  return db.size();
}

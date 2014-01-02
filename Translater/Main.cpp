#include <fastcgi2/component.h>
#include <fastcgi2/component_factory.h>
#include <fastcgi2/handler.h>
#include <fastcgi2/request.h>

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_guard.hpp>

#include "translater.h"
#include "Lang.h"

class Main : virtual public fastcgi::Component, virtual public fastcgi::Handler
{
private:
  Translater tr;
  boost::mutex mutex;

  std::string write_json(std::string word, std::vector<std::string> translations, Lang from, Lang to)
  {
    boost::property_tree::ptree root;
    boost::property_tree::ptree children;

    root.put("word", word);
    root.put("from", langToStr(from));
    root.put("to", langToStr(to));

    std::vector<std::string>::const_iterator  i;
    for (i = translations.begin(); i < translations.end(); ++i)
    {
      boost::property_tree::ptree child;
      child.put("", *i);
      children.push_back(std::make_pair("", child));
    }
    root.add_child("translations", children);

    std::stringstream json;
    boost::property_tree::write_json(json, root);
    return json.str();
  }

  void handleGetRequest(fastcgi::Request *request)
  {
    if (request->hasArg("from") && request->hasArg("to") && request->hasArg("word"))
    {
      std::string s;
      request->requestBody().toString(s);
      std::cout << std::endl << s  << std::endl;
      const char* strFrom = request->getArg("from").c_str();
      Lang from = strToLang(strFrom);
      const char* strTo = request->getArg("to").c_str();
      Lang to = strToLang(strTo);
      std::string word = request->getArg("word");
      std::vector<std::string> v = tr.translate(word, from, to);
      std::string res = write_json(word, v, from, to);
      const char* str = res.c_str();
      request->write(str, sizeof(char) * res.size());
    }
  }

  void handlePostRequest(fastcgi::Request *request)
  {
  }

public:
  Main(fastcgi::ComponentContext *context) : fastcgi::Component(context)
  {
  }
  virtual ~Main()
  {
  }

public:
  virtual void onLoad()
  {
  }
  virtual void onUnload()
  {
  }
  virtual void handleRequest(fastcgi::Request *request, fastcgi::HandlerContext *context)
  {
    if (request->getRequestMethod() == "GET")
    {
      handleGetRequest(request);
    } else if (request->getRequestMethod() == "POST")
    {
        handleGetRequest(request);
    }
  }

};

FCGIDAEMON_REGISTER_FACTORIES_BEGIN()
FCGIDAEMON_ADD_DEFAULT_FACTORY("main", Main)
FCGIDAEMON_REGISTER_FACTORIES_END()


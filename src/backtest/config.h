#ifndef CONFIG
#define CONFIG
#include "../rapidjson/document.h"
#include "ruleset.h"
#include <string>

class config {
  friend class portfolio;

  public:
    config(rapidjson::Value&);

  private:
    bool bvalue(rapidjson::Value&, std::string);

    static bool single_pos();
    static bool multiple_positions;
    static expression* slippage;
};

#endif
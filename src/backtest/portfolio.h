#ifndef PORTFOLIO
#define PORTFOLIO
#include "strategy.h"
#include "position.h"
#include "config.h"

class portfolio : public restrictor {

  public:
    void run();
    void print_state();
    void set_date_range(date, date);
    void set_universe(vector<std::string>);
    void set_long_strategies(std::vector<strategy>);
    bool skip_ticker(string);

  private:

    void close_positions(std::vector<std::string>*, date);
    void open_positions(std::vector<std::string>*, date);
    void entry_signals(date, std::vector<std::string>*);
    void exit_signals(date, std::vector<std::string>*);
    void update_equity_curve(date);
    void update_positions(date);

    std::vector<strategy> long_strategies;
    std::vector<string> stock_universe;

    std::vector<position> cur_positions;
    std::vector<position> old_positions;
    std::vector<float> equity_curve;

    date* firstdate;
    date* lastdate;
    float cur_cash;
};

#endif

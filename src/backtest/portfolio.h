#ifndef PORTFOLIO
#define PORTFOLIO
#include "strategy.h"
#include "position.h"
#include "config.h"
#include <set>

class target_list : public restrictor {
  public:
    target_list(string);
    target_list(vector<string>);
    bool skip_ticker(string);
  private:
    set<string> targets;
};

class archive {
  public:
    archive();
    void push(position*);
    void set_initial(float);
    void update_equity(float);
    void push_benchmark(float);
    void print_state(vector<position*>);
    float total_return();
    float current_equity();
  private:
    float cagr();
    float max_drawdown();
    float system_quality();
    float benchmark_return();
    void compute_basic_stats();
    float std_deviation(float*, int);
    float total_div_payout(vector<position*>);

    std::vector<position*> old_positions;
    std::vector<float> benchmark_curve;
    std::vector<float> equity_curve;

    float avgwin, avgloss, expectancy;
    float winpercent, losepercent;
    float initial_equity;
    int winners, losers;
};

class deposits {
  public:
    float update();
    void add_deposits(vector<string>);
  private:
    void process_deposit(string);
    vector<int> periods, counters;
    vector<float> amounts;
};

class portfolio : public restrictor, portfolio_metric {

  public:
    portfolio();
    ~portfolio();
    void run();
    void print_state();
    void set_date_range(date, date);
    void set_universe(vector<std::string>);
    void set_long_strategies(std::vector<strategy>);
    void set_deposit_schedule(vector<string>);
    bool skip_ticker(string);

    int position_count();
    float total_return();
    float equity();
    float cash();

  private:

    void close_positions(std::vector<std::string>*, date);
    void close_position(date, position*, std::vector<std::string>*, float p=0);
    void open_positions(std::vector<std::string>*, std::vector<strategy*>*, date);
    void entry_signals(date, std::vector<std::string>*, std::vector<strategy*>*);
    void exit_signals(date, std::vector<std::string>*);
    bool exit_pending(string, vector<string>*);
    target_list get_current_restrictor();
    void update_equity_curve(date);
    void update_positions(date);
    void update_benchmark(date);
    void process_stops(date);

    std::vector<strategy*> long_strategies;
    std::vector<string> stock_universe;
    std::vector<position*> cur_positions;

    archive past_performance;
    deposits* new_equity;
    date firstdate;
    date lastdate;
    float start_cash;
    float cur_cash;
};

#endif

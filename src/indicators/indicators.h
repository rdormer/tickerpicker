#ifndef INDICATORS
#define INDICATORS
#include "ptable.h"
#include <vector>
#include <string>
#include <map>

class portfolio_metric {
public:
  virtual int position_count() = 0;
  virtual float total_return() = 0;
  virtual float equity() = 0;
  virtual float cash() = 0;
};

class position_metric {
public:
  virtual float days_held() = 0;
  virtual int share_count() = 0;
  virtual float risk_return() = 0;
  virtual float percent_return() = 0;
  virtual float purchase_price() = 0;
};

//output buffer large enough to look back
//five years on functions that require 
//large pulls due to unstable periods

#define OUTPUT_BUFSIZE 5200

class indicators {

  public:

  indicators();
  static void set_position(position_metric*);
  static void set_portfolio(portfolio_metric*);
  int eval_lookback(std::string, std::vector<float>);
  float eval_indicator(std::string, std::vector<float>, pdata*, int offset=0);

  private:

  static portfolio_metric* fn_portfolio;
  static position_metric* fn_position;

  int offset;
  pdata *current_prices;
  std::vector<float> arglist;
  static std::map<std::string, float (*)(indicators*)> fn_table;
  static std::map<std::string, int (*)(indicators*)> lookback_table;

  void init_fntable(); 
  void init_lookback_table();

  //lookback period calculators
  static int null_lookback(indicators*);
  static int rsi_lookback(indicators*);
  static int obv_lookback(indicators*);
  static int roc_lookback(indicators*);
  static int ema_lookback(indicators*);
  static int accl_lookback(indicators*);
  static int natr_lookback(indicators*);
  static int ohlcv_lookback(indicators*);
  static int minimax_lookback(indicators*);
  static int identity_lookback(indicators*);
  static int bollinger_lookback(indicators*);
  static int aroon_osc_lookback(indicators*);
  static int avg_true_range_lookback(indicators*);
  static int age_lookback(indicators*);

  //actual indicator functions
  static float rsi(indicators*);
  static float obv(indicators*);
  static float roc(indicators*);
  static float avgc(indicators*);
  static float avgo(indicators*);
  static float avgh(indicators*);
  static float avgl(indicators*);
  static float avgv(indicators*);
  static float eavgc(indicators*);
  static float eavgo(indicators*);
  static float eavgh(indicators*);
  static float eavgl(indicators*);
  static float eavgv(indicators*);
  static float wmac(indicators*);
  static float wmao(indicators*);
  static float wmah(indicators*);
  static float wmal(indicators*);
  static float wmav(indicators*);
  static float natr(indicators*);
  static float aroon_osc(indicators*);
  static float volume_at(indicators*);
  static float close_at(indicators*);
  static float open_at(indicators*);
  static float high_at(indicators*);
  static float low_at(indicators*);
  static float date_at(indicators*);
  static float max_open(indicators*);
  static float max_high(indicators*);
  static float max_low(indicators*);
  static float max_close(indicators*);
  static float max_volume(indicators*);
  static float min_open(indicators*);
  static float min_high(indicators*);
  static float min_low(indicators*);
  static float min_close(indicators*);
  static float min_volume(indicators*);
  static float abs_value(indicators*);
  static float accl_upper(indicators*);
  static float accl_lower(indicators*);
  static float fractal_ratio(indicators*);
  static float avg_true_range(indicators*);
  static float bollinger_upper(indicators*);
  static float bollinger_lower(indicators*);
  static float sma(indicators*, vector<float>);
  static float wma(indicators*, vector<float>);
  static float eavg(indicators*, vector<float>);
  static void acceleration_bands(indicators*,float*, float*);
  static void bollinger_values(indicators*,double*, double*, int*);
  static float internal_minval(indicators*, vector<float>);
  static float internal_maxval(indicators*, vector<float>);
  static float data_age(indicators*);

  //mathematical functions
  static float largest(indicators*);
  static float smallest(indicators*);
  static float round(indicators*);
  static float floor(indicators*);
  static float ceil(indicators*);

  //metrics
  static float portfolio_equity(indicators*);
  static float portfolio_return(indicators*);
  static float portfolio_count(indicators*);
  static float portfolio_cash(indicators*);
  
  static float position_return_percent(indicators*);
  static float position_share_count(indicators*);
  static float position_buy_price(indicators*);
  static float position_days_held(indicators*);
  static float position_return_r(indicators*);
};

#endif

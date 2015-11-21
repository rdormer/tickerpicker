#include "screen.h"
#include <algorithm>
#include <iostream>

map<string, stock> screen::all;

screen::screen(vector<string> rules, vector<string> table) {
  srules = new ruleset(rules, table);
  sort = NULL;  
}

void screen::set_universe(vector<string> list) {
  universe = list;
}

vector<string> screen::eval(date curdate, restrictor* filter) {

  vector<string> results;

  for(int i = 0; i < universe.size(); i++) {

    string ticker = universe[i];

    if(filter != NULL && filter->skip_ticker(ticker)) {
      continue;
    }

    if(all.count(ticker) == 0) {

      try {
        stock cur(ticker);
        all.insert(std::pair<string, stock>(ticker, cur));
      } catch(exception e) {
        continue;
      }
      
    }

    stock cur = all.find(ticker)->second; 
    cur.onday(curdate);

    if(srules->eval(cur)) {
      results.push_back(ticker);
    }
  }

  return sort_set(results, curdate);
}

bool screen::eval(date curdate, string ticker) {
    if(all.count(ticker) == 0) {

      try {
        stock cur(ticker);
        all.insert(std::pair<string, stock>(ticker, cur));
      } catch(exception e) {}
    }

    stock cur = all.find(ticker)->second; 
    cur.onday(curdate);
    return srules->eval(cur);
}

void screen::set_sort_exp(vector<string> sexp, bool is_ascending) {
   sort = expression_parser::parse(sexp);
   sort_dflag = is_ascending;
}

vector<string> screen::sort_set(vector<string> inset, date d) {
  vector<pair<float, string> > sset;
  vector<string> rval;

  if(sort == NULL) {
    std::sort(inset.begin(), inset.end());
    return inset;
  }

  for(int i = 0; i < inset.size(); i++) {
    stock cur(inset[i]);
    cur.onday(d);

    float val = sort->eval(cur); 
    pair<float, string> p = make_pair(val, inset[i]);
    sset.push_back(p);
  }

  if(sort_dflag) {
    std::sort(sset.begin(), sset.end(), asc_pred());
  } else {
    std::sort(sset.begin(), sset.end(), desc_pred());
  }

  for(int i = 0; i < sset.size(); i++) {
    rval.push_back(sset[i].second);
  }

  return rval;
}

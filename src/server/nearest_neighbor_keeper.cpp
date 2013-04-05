// this program is automatically generated by jenerator. do not edit.
#include "../framework.hpp"
#include "../framework/aggregators.hpp"
#include "nearest_neighbor_types.hpp"
using namespace jubatus;
using namespace jubatus::framework;
int main(int args, char** argv){
  keeper k(keeper_argv(args,argv,"nearest_neighbor"));
  k.register_broadcast<bool, config_data >("set_config", pfi::lang::function<bool(bool,bool)>(&all_and)); //update
  k.register_random<config_data >("get_config"); //pass analysis
  k.register_broadcast<bool >("init_table", pfi::lang::function<bool(bool,bool)>(&pass<bool >)); //update
  k.register_broadcast<bool >("clear", pfi::lang::function<bool(bool,bool)>(&all_and)); //update
  k.register_cht<1, bool, datum >("set_row", pfi::lang::function<bool(bool,bool)>(&pass<bool >)); //update
  k.register_random<neighbor_result, std::string, unsigned int >("neighbor_row_from_id"); //pass analysis
  k.register_random<neighbor_result, datum, unsigned int >("neighbor_row_from_data"); //pass analysis
  k.register_random<neighbor_result, std::string, int >("similar_row_from_id"); //pass analysis
  k.register_random<neighbor_result, datum, int >("similar_row_from_data"); //pass analysis
  k.register_broadcast<bool, std::string >("save", pfi::lang::function<bool(bool,bool)>(&all_and)); //update
  k.register_broadcast<bool, std::string >("load", pfi::lang::function<bool(bool,bool)>(&all_and)); //update
  k.register_broadcast<std::map<std::string,std::map<std::string,std::string > > >("get_status", pfi::lang::function<std::map<std::string,std::map<std::string,std::string > >(std::map<std::string,std::map<std::string,std::string > >,std::map<std::string,std::map<std::string,std::string > >)>(&merge<std::string,std::map<std::string,std::string > >)); //analysis
  return k.run();
}
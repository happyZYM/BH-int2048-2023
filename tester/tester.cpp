#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "clipp.h"
#include "json.hpp"
std::string getDirectory(const std::string &filepath) {
  size_t found = filepath.find_last_of("/\\");
  return filepath.substr(0, found);
}
#define DeEscape std::string
int main(int argc, char *argv[]) {
  bool continuous = false;
  bool test_all = false;
  bool test_listed_cases = false;
  std::vector<std::string> listed_cases;
  std::string filePath(__FILE__);
  std::string directoryPath = getDirectory(filePath);
  std::string config_file = directoryPath + "/config.json";
  bool use_custoem_config = false;
  std::string new_config = "";
  bool test_sub_tree = false;
  std::string sub_tree;
  // clang-format off
  auto cli=(
    clipp::option("-f","--file").set(config_file).doc("config file path") & clipp::value("config file path",config_file),
    clipp::option("-c","--continuous").set(continuous).doc("continuous mode"),
    clipp::option("-a","--all").set(test_all).doc("test all"),
    clipp::option("-s","--subtree").set(test_sub_tree).doc("test subtree") & clipp::value("subtree",sub_tree),
    clipp::option("-l","--list").set(test_listed_cases).doc("test listed cases") & clipp::values("cases",listed_cases)
  );
  // clang-format on
  if (!parse(argc, argv, cli)) {
    std::cout << make_man_page(cli, argv[0]);
    return 0;
  }
  if (use_custoem_config) config_file = new_config;
  using json = nlohmann::json;
  std::ifstream conf(config_file);
  json config = json::parse(conf);
  std::unordered_map<std::string, std::string> index;
  for (int i = 0; i < config["Cases"].size(); i++) {
    index[DeEscape(config["Cases"][i]["tid"])] =
        DeEscape(config["Cases"][i]["command"]);
    index[DeEscape(config["Cases"][i]["uid"])] =
        DeEscape(config["Cases"][i]["command"]);
  }
  if (test_all) {
    listed_cases.clear();
    for (int i = 0; i < config["Cases"].size(); i++) {
      listed_cases.push_back(DeEscape(config["Cases"][i]["tid"]));
    }
  } else if (test_sub_tree) {
    listed_cases.clear();
    for (int i = 0; i < config["Cases"].size(); i++) {
      if (DeEscape(config["Cases"][i]["tid"]).find(sub_tree) == 0 &&
          (DeEscape(config["Cases"][i]["tid"]).length() == sub_tree.length() ||
           DeEscape(config["Cases"][i]["tid"])[sub_tree.length()] == '/')) {
        listed_cases.push_back(DeEscape(config["Cases"][i]["tid"]));
      }
    }
  }
  for (int i = 0; i < listed_cases.size(); i++) {
    std::cerr << "Testing " << listed_cases[i] << std::endl;
    std::cerr << "Command = " << index[listed_cases[i]] << std::endl;
    int status = system(index[listed_cases[i]].c_str()) / 256;
    if (status == 0) {
      std::cerr << "Test " << listed_cases[i] << " passed" << std::endl;
    } else {
      std::cerr << "Test " << listed_cases[i] << " failed" << std::endl;
      std::cerr << "status code = " << status << std::endl;
      std::cerr
          << "Brief info: "
          << (config["StatusInterpreter"].contains(std::to_string(status))
                  ? DeEscape(
                        config["StatusInterpreter"][std::to_string(status)])
                  : std::string("Unknown Error"))
          << std::endl;
      if (!continuous) {
        return 1;
      }
    }
    std::cerr << '\n' << std::endl;
  }
  return 0;
}
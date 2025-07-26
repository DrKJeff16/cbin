#include <string>
#include <vector>
#include <iostream>
#include <docopt/docopt.h>

using std::cout, std::endl;
using std::map;
using std::string;
using std::vector;

static const char USAGE[] =
  R"(Naval Fate.

    Usage:
    naval_fate ship new <name>...
    naval_fate ship <name> move <x> <y> [--speed=<kn>]
    naval_fate ship shoot <x> <y>
    naval_fate mine (set|remove) <x> <y> [--moored | --drifting]
    naval_fate (-h | --help)
    naval_fate --version

    Options:
    -h --help     Show this screen.
    --version     Show version.
    --speed=<kn>  Speed in knots [default: 10].
    --moored      Moored (anchored) mine.
    --drifting    Drifting mine.
)";

int main(int argc, const char **argv) {
  vector<string> vec = { argv + 1, argv + argc };

  map<string, docopt::value> args = docopt::docopt(USAGE, vec, true, "Naval Fate 2.0");

  for (auto const &arg: args) {
    cout << arg.first << arg.second << endl;
  }

  return 0;
}

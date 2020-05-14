#include <memory>
#include <string>
#include <istream>
#include <iostream>

#include <cstdlib>

#include "command.hh"
#include "job.hh"

int
main(int argc, char* argv[])
{
  std::istream& in = std::cin;
  while (in) {
    std::unique_ptr<Command> commandP = Command::read(in);
    if (commandP) std::cout << *commandP << std::endl;
  }
}

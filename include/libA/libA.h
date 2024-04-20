#pragma once

#include <string>
#include <memory>
#include <list>
#include <vector>

namespace Foo {

struct Entry {
  std::string name= "";
  int count = 0;
  int strength = 0;
};

struct Group {
  int count = 0;
  int strength = 0;
  std::list<std::shared_ptr<Entry>> entries;
};

struct Result {
  bool found = false;
  Group group[2] = {};
};

/**
 * @brief Module identifying similar groups.
 *
 * @param entries Vector containing the entries
 * @param target_value Value to group the entries by.
 * @return Result Pair of groups that have similar strength.
 */
Result find_similar_groups(const std::vector<std::shared_ptr<Entry>>& entries, int target_value);

}

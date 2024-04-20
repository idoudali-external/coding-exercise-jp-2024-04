#include "libA/libA.h"

#include <tuple>
#include <cstdlib>

using namespace Foo;


/**
 * @brief Helper function that creates all possible combinations of entries that generate a count
 * sum equal to target_value
 *
 * @param entries Input vector of entries
 * @param start Search start index
 * @param target_value Target value
 * @param path List of entries currently selected
 * @param result_paths List of group currently found
 * @return std::tuple<bool, std::vector<int>> Result of the search
 */
std::tuple<bool, std::vector<int>> back_track(//
    const std::vector<std::shared_ptr<Entry>>& entries, //
    int start,//
    const int target_value,//
    std::vector<int>& path,//
    std::vector<std::vector<int>>& result_paths) {
    /* Generate all possible combinations of entries that generate a count sum equal to target_value
    */
    auto sum_value = 0;

    for (auto i : path) {
        sum_value += entries[i]->count;
    }

    if ( sum_value == target_value) {
        return {true, path};
    }

    if (sum_value > target_value) {
        return {false, {}};
    }

    for (int i = start; i < entries.size(); i++) {
        path.push_back(i);
        auto [found, result] = back_track(entries, i + 1, target_value, path, result_paths);
        if (found) {
             result_paths.push_back(path);
        }
        path.pop_back();
    }

    return {false, {}};
}

/**
 * @brief Find all possible groups of entries that generate a count sum equal to target_value
 *
 * @param entries Input vector of entries
 * @param target_value Target value
 * @return std::vector<Group> Resulting groups identified.
 */
std::vector<Group> find_groups(const std::vector<std::shared_ptr<Entry>>& entries, const int target_value) {
  std::vector<std::vector<int>> groups_indexes;
  std::vector<int> path;
  // find all possible groups of entries that generate a count sum equal to target_value
  back_track(entries, 0, target_value, path, groups_indexes);

  std::vector<Group> groups;
  // Compute the strength of each group
  for(auto& group_indexes : groups_indexes) {
    Group group;
    for(auto i : group_indexes) {
      group.count += entries[i]->count;
      group.strength += entries[i]->count * entries[i]->strength;
      group.entries.push_back(entries[i]);
    }
    group.strength /= group.count;
    groups.push_back(group);
  }

  // Return the vector of found groups.
  return groups;
}

Result Foo::find_similar_groups(const std::vector<std::shared_ptr<Entry>>& entries, int target_value) {
    Result res = {};

    // Given that there is threshold to determine similar find the
    // groups with the minimum difference in strength absolute value.
    int min_difference = - 1;
    // I think the const is O(N^2) where N is the number of entries
    auto groups = find_groups(entries, target_value);

    // The cost of the bellow is O(N^2)
    for (int i =0; i < groups.size(); i++) {
        for (int j = i + 1; j < groups.size(); j++) {
            auto difference = std::abs(groups[i].strength - groups[j].strength);
            if (min_difference == -1 || difference < min_difference) {
                res.found = true;
                min_difference = difference;
                res.group[0] = groups[i];
                res.group[1] = groups[j];
            }
        }
    }

    return res;
}

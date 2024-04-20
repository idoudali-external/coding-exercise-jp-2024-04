#include <gtest/gtest.h>
#include <list>
#include <vector>
#include <memory>

#include "libA/libA.h"

using namespace Foo;


extern std::vector<Foo::Group> find_groups(const std::vector<std::shared_ptr<Foo::Entry>>& entries, const int target_value);



// Demonstrate some basic assertions.
TEST(FindGroupCompinations, EmptyList) {
  const std::vector<std::shared_ptr<Foo::Entry>> empty = {};
  auto res = find_groups(empty, 5);

  ASSERT_EQ(res.size(), 0);

}

static const std::vector<std::shared_ptr<Foo::Entry>> example_entries = {
    std::make_shared<Foo::Entry>(Foo::Entry{"A", 1, 600}),
    std::make_shared<Foo::Entry>(Foo::Entry{"B", 2, 310}),
    std::make_shared<Foo::Entry>(Foo::Entry{"C", 2, 200}),
    std::make_shared<Foo::Entry>(Foo::Entry{"D", 2, 300}),
    std::make_shared<Foo::Entry>(Foo::Entry{"E", 4, 450}),
    std::make_shared<Foo::Entry>(Foo::Entry{"F", 1, 220}),
    std::make_shared<Foo::Entry>(Foo::Entry{"G", 3, 195}),
};

// Demonstrate some basic assertions.
TEST(FindGroupCompinations, ZeroTargetValue) {
  auto res = find_groups(example_entries, 0);

  ASSERT_EQ(res.size(), 0);

}


// Demonstrate some basic assertions.
TEST(FindGroupCompinations, OneTargetValue) {
  auto res = find_groups(example_entries, 1);

  ASSERT_EQ(res.size(), 2);

  for (auto& group : res) {
    std::cout << "Group: " << group.count << " " << group.strength << std::endl;
    for (auto& entry : group.entries) {
      std::cout << "Entry: " << entry->name << " " << entry->count << " " << entry->strength << std::endl;
    }
  }
}

TEST(FindGroupCompinations, RequestedTargetValue) {
  auto res = find_groups(example_entries, 5);

  for (auto& group : res) {
    std::cout << "Group: " << group.count << " " << group.strength << std::endl;
    for (auto& entry : group.entries) {
      std::cout << "Entry: " << entry->name << " " << entry->count << " " << entry->strength << std::endl;
    }
  }
}

TEST(FindClosesGroups, ZeroValue) {
  Result res = find_similar_groups(example_entries, 0);

  ASSERT_EQ(res.found, false);

}

TEST(FindClosesGroups, NoPairValue) {

  static const std::vector<std::shared_ptr<Foo::Entry>> example_entries = {
    std::make_shared<Foo::Entry>(Foo::Entry{"A", 1, 600}),
    std::make_shared<Foo::Entry>(Foo::Entry{"B", 2, 310}),
  };

  Result res = find_similar_groups(example_entries, 3);

  ASSERT_EQ(res.found, false);

}


TEST(FindClosesGroups, ReferenceValue) {
  Result res = find_similar_groups(example_entries, 5);

  ASSERT_EQ(res.found, true);

  for (auto& group : res.group) {
    std::cout << "Group: " << group.count << " " << group.strength << std::endl;
    for (auto& entry : group.entries) {
      std::cout << "Entry: " << entry->name << " " << entry->count << " " << entry->strength << std::endl;
    }
  }
}

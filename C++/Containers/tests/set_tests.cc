#include <gtest/gtest.h>

#include <set>

#include "../rbtree/node.h"
#include "../rbtree/rbtree.h"
#include "../set/s21_set.h"

template <typename Key>
bool EqSets(s21::set<Key>& first, std::set<Key>& second) {
  if (first.size() != second.size()) {
    return false;
  }
  auto it1 = first.begin();
  auto it2 = second.begin();
  for (; it1 != first.end() && it2 != second.end(); ++it1, ++it2) {
    if ((*it1).first != (*it2)) {
      return false;
    }
  }
  return true;
}

TEST(Set, CompareSets) {
  std::set<int> std_s = {0, 1, 2};
  s21::set<int> s21_s = {0, 1, 2};
  bool result = EqSets<int>(s21_s, std_s);
  ASSERT_EQ(result, true);
}

TEST(Set, DefaultInt) {
  std::set<int> std_s;
  s21::set<int> s21_s;
  ASSERT_EQ(std_s.size(), s21_s.size());
}

TEST(Set, ValueCtorInt) {
  std::set<int> std_s = {25, 30, 40, 50, 45, 55, 35};
  s21::set<int> s21_s = {25, 30, 40, 50, 45, 55, 35};
  bool result = EqSets<int>(s21_s, std_s);
  ASSERT_EQ(result, true);
}

TEST(Set, ValueCtorString) {
  std::set<std::string> std_s = {"zero", "one", "alpha"};
  s21::set<std::string> s21_s = {"zero", "one", "alpha"};
  bool result = EqSets<std::string>(s21_s, std_s);
  ASSERT_EQ(result, true);
}

TEST(Set, CopyCtor) {
  std::set<std::string> std_s = {"zero", "one"};
  s21::set<std::string> s21_s = {"zero", "one"};

  std::set<std::string> std_s_copy(std_s);
  s21::set<std::string> s21_s_copy(s21_s);

  bool result = EqSets<std::string>(s21_s_copy, std_s_copy);
  ASSERT_EQ(result, true);
}

TEST(Set, CopyCtor_2) {
  std::set<int> std_s = {1, 100, 1000};
  s21::set<int> s21_s = {1, 100, 1000};

  std::set<int> std_s_copy(std_s);
  s21::set<int> s21_s_copy(s21_s);

  bool result = EqSets<int>(s21_s_copy, std_s_copy);
  ASSERT_EQ(result, true);
}

TEST(Set, CopyOper) {
  std::set<std::string> std_s = {"zero", "one"};
  s21::set<std::string> s21_s = {"zero", "one"};

  std::set<std::string> std_s_copy = std_s;
  s21::set<std::string> s21_s_copy = s21_s;

  bool result = EqSets<std::string>(s21_s_copy, std_s_copy);
  ASSERT_EQ(result, true);
}

TEST(Set, MoveCtor) {
  std::set<std::string> std_s = {"zero", "one"};
  s21::set<std::string> s21_s = {"zero", "one"};
  std::set<std::string> std_s_copy(std::move(std_s));
  s21::set<std::string> s21_s_copy(std::move(s21_s));
  ASSERT_EQ(std_s_copy.size(), s21_s_copy.size());
  bool result = EqSets<std::string>(s21_s_copy, std_s_copy);
  ASSERT_EQ(result, true);
}

TEST(Set, MoveOper) {
  std::set<std::string> std_s = {"zero", "one"};
  s21::set<std::string> s21_s = {"zero", "one"};

  std::set<std::string> std_s_copy = std::move(std_s);
  s21::set<std::string> s21_s_copy = std::move(s21_s);
  ASSERT_EQ(std_s_copy.size(), s21_s_copy.size());
  bool result = EqSets<std::string>(s21_s_copy, std_s_copy);
  ASSERT_EQ(result, true);
}

TEST(Set, Begin) {
  std::set<std::string> std_s = {"zero", "one", "two"};
  s21::set<std::string> s21_s = {"zero", "one", "two"};
  auto it_std = std_s.begin();
  auto it_s21 = s21_s.begin();
  ASSERT_EQ((*it_std), (*it_s21).first);
  bool result = EqSets<std::string>(s21_s, std_s);
  ASSERT_EQ(result, true);
}

TEST(Set, Empty) {
  std::set<std::string> std_s = {"zero", "one", "two"};
  s21::set<std::string> s21_s = {"zero", "one", "two"};
  ASSERT_EQ(std_s.empty(), s21_s.empty());
}

TEST(Set, Empty_2) {
  std::set<std::string> std_s = {"zero"};
  s21::set<std::string> s21_s = {"zero"};
  ASSERT_EQ(std_s.empty(), s21_s.empty());
}

TEST(Set, Empty_3) {
  std::set<std::string> std_s;
  s21::set<std::string> s21_s;
  ASSERT_EQ(std_s.empty(), s21_s.empty());
}

TEST(Set, Size) {
  std::set<std::string> std_s;
  s21::set<std::string> s21_s;
  size_t s21_res = std_s.size();
  size_t std_res = s21_s.size();
  ASSERT_EQ(s21_res, std_res);
}

TEST(Set, Size_2) {
  std::set<std::string> std_s = {"zero"};
  s21::set<std::string> s21_s = {"zero"};
  size_t s21_res = std_s.size();
  size_t std_res = s21_s.size();
  ASSERT_EQ(s21_res, std_res);
  bool result = EqSets<std::string>(s21_s, std_s);
  ASSERT_EQ(result, true);
}

TEST(Set, Size_3) {
  std::set<std::string> std_s = {"zero", "one", "two"};
  s21::set<std::string> s21_s = {"zero", "one", "two"};
  size_t s21_res = std_s.size();
  size_t std_res = s21_s.size();
  ASSERT_EQ(s21_res, std_res);
  bool result = EqSets<std::string>(s21_s, std_s);
  ASSERT_EQ(result, true);
}

TEST(Set, Clear) {
  std::set<std::string> std_s = {"zero", "one", "two"};
  s21::set<std::string> s21_s = {"zero", "one", "two"};
  std_s.clear();
  s21_s.clear();
  ASSERT_EQ(std_s.size(), s21_s.size());
  ASSERT_EQ(std_s.empty(), s21_s.empty());
}

TEST(Set, Insert_1) {
  std::set<std::string> std_s = {"zero", "one", "two"};
  s21::set<std::string> s21_s = {"zero", "one", "two"};
  std_s.insert("three");
  s21_s.insert("three");
  bool result = EqSets<std::string>(s21_s, std_s);
  ASSERT_EQ(result, true);
}

TEST(Set, Erase) {
  std::set<std::string> std_s = {"zero", "one", "two"};
  s21::set<std::string> s21_s = {"zero", "one", "two"};
  std_s.erase(std_s.begin());
  s21_s.erase(s21_s.begin());
  ASSERT_EQ(std_s.size(), s21_s.size());
  // bool result = EqSets<std::string>(s21_s, std_s);
  // ASSERT_EQ(result, true);
}

TEST(Set, Erase_2) {
  std::set<std::string> std_s = {"zero"};
  s21::set<std::string> s21_s = {"zero"};
  std_s.erase(std_s.begin());
  s21_s.erase(s21_s.begin());
  ASSERT_EQ(std_s.size(), s21_s.size());
  ASSERT_EQ(std_s.empty(), s21_s.empty());
}

TEST(Set, Erase_3) {
  std::set<std::string> std_s = {"zero", "one", "two"};
  s21::set<std::string> s21_s = {"zero", "one", "two"};
  std_s.erase(++(std_s.begin()));
  s21_s.erase(++(s21_s.begin()));
  ASSERT_EQ(std_s.size(), s21_s.size());
  ASSERT_EQ(std_s.empty(), s21_s.empty());
}

TEST(Set, Erase_4) {
  std::set<int> std_s = {1, 5, 3, 4, 6, 7, 10, 11};
  s21::set<int> s21_s = {1, 5, 3, 4, 6, 7, 10, 11};
  auto it_std = std_s.begin();
  auto it_s21 = s21_s.begin();
  ++it_std;
  ++it_s21;
  ++it_std;
  ++it_s21;
  std_s.erase(it_std);
  s21_s.erase(it_s21);

  ASSERT_EQ(std_s.size(), s21_s.size());
  ASSERT_EQ(std_s.empty(), s21_s.empty());
}

TEST(Set, Erase_5) {
  std::set<int> std_s = {20, 10, 25, 4,  16, 23, 30, 2,
                         5,  3,  11, 12, 14, 15, 17, 19};
  s21::set<int> s21_s = {20, 10, 25, 4,  16, 23, 30, 2,
                         5,  3,  11, 12, 14, 15, 17, 19};
  auto it_std = std_s.begin();
  auto it_s21 = s21_s.begin();
  ++it_std;
  ++it_s21;

  ++it_std;
  ++it_s21;

  ++it_std;
  ++it_s21;

  ++it_std;
  ++it_s21;

  std_s.erase(it_std);
  s21_s.erase(it_s21);

  ASSERT_EQ(std_s.size(), s21_s.size());
  ASSERT_EQ(std_s.empty(), s21_s.empty());
}

TEST(Set, Erase_6) {
  std::set<int> std_s = {20, 10, 25, 4,  16, 23, 30, 2,
                         5,  3,  11, 12, 14, 15, 17, 19};
  s21::set<int> s21_s = {20, 10, 25, 4,  16, 23, 30, 2,
                         5,  3,  11, 12, 14, 15, 17, 19};
  auto it_std = std_s.begin();
  auto it_s21 = s21_s.begin();
  std_s.erase(it_std);
  s21_s.erase(it_s21);

  ASSERT_EQ(std_s.size(), s21_s.size());
  ASSERT_EQ(std_s.empty(), s21_s.empty());
}

TEST(Set, Erase_7) {
  std::set<int> std_s = {20, 10, 25, 4,  16, 23, 30, 2,
                         5,  3,  11, 12, 14, 15, 17, 19};
  s21::set<int> s21_s = {20, 10, 25, 4,  16, 23, 30, 2,
                         5,  3,  11, 12, 14, 15, 17, 19};
  auto it_std = std_s.begin();
  auto it_s21 = s21_s.begin();
  for (int i = 0; i < 2; i++) {
    ++it_s21;
    ++it_std;
  }

  std_s.erase(it_std);
  s21_s.erase(it_s21);

  ASSERT_EQ(std_s.size(), s21_s.size());
  ASSERT_EQ(std_s.empty(), s21_s.empty());
}

TEST(Set, Erase_8) {
  std::set<int> std_s = {20, 10, 25, 4,  16, 23, 30, 2,
                         5,  3,  11, 12, 14, 15, 17, 19};
  s21::set<int> s21_s = {20, 10, 25, 4,  16, 23, 30, 2,
                         5,  3,  11, 12, 14, 15, 17, 19};
  auto it_std = std_s.begin();
  auto it_s21 = s21_s.begin();
  for (int i = 0; i < 7; i++) {
    ++it_s21;
    ++it_std;
  }

  std_s.erase(it_std);
  s21_s.erase(it_s21);

  ASSERT_EQ(std_s.size(), s21_s.size());
  ASSERT_EQ(std_s.empty(), s21_s.empty());
}

TEST(Set, Erase_9) {
  std::set<int> std_s = {20, 10, 25, 4,  16, 23, 30, 2,
                         5,  3,  11, 12, 14, 15, 17, 19};
  s21::set<int> s21_s = {20, 10, 25, 4,  16, 23, 30, 2,
                         5,  3,  11, 12, 14, 15, 17, 19};
  auto it_std = std_s.begin();
  auto it_s21 = s21_s.begin();
  for (int i = 0; i < 5; i++) {
    ++it_s21;
    ++it_std;
  }

  std_s.erase(it_std);
  s21_s.erase(it_s21);

  ASSERT_EQ(std_s.size(), s21_s.size());
  ASSERT_EQ(std_s.empty(), s21_s.empty());
}

TEST(Set, Erase_10) {
  std::set<int> std_s = {0, 2, 56, 34, 11, 23, 1, 7, 5, 9, 10};
  s21::set<int> s21_s = {0, 2, 56, 34, 11, 23, 1, 7, 5, 9, 10};
  auto it_std = std_s.begin();
  auto it_s21 = s21_s.begin();

  ++it_s21;
  ++it_std;

  std_s.erase(it_std);
  s21_s.erase(it_s21);

  ASSERT_EQ(std_s.size(), s21_s.size());
  ASSERT_EQ(std_s.empty(), s21_s.empty());
}

TEST(Set, Erase_11) {
  std::set<int> std_s = {1, 5, 13, 4, 0};
  s21::set<int> s21_s = {1, 5, 13, 4, 0};
  auto it_std = std_s.begin();
  auto it_s21 = s21_s.begin();

  ++it_s21;
  ++it_std;

  std_s.erase(it_std);
  s21_s.erase(it_s21);

  ASSERT_EQ(std_s.size(), s21_s.size());
  ASSERT_EQ(std_s.empty(), s21_s.empty());
}

TEST(Set, Erase_12) {
  std::set<int> std_s = {40, 30, 50, 20, 35, 45, 60, 15, 25, 33, 43, 47, 65};
  s21::set<int> s21_s = {40, 30, 50, 20, 35, 45, 60, 15, 25, 33, 43, 47, 65};
  auto it_std = std_s.begin();
  auto it_s21 = s21_s.begin();

  ++it_s21;
  ++it_std;

  ++it_s21;
  ++it_std;

  ++it_s21;
  ++it_std;

  --it_s21;
  --it_std;

  std_s.erase(it_std);
  s21_s.erase(it_s21);

  ASSERT_EQ(std_s.size(), s21_s.size());
  ASSERT_EQ(std_s.empty(), s21_s.empty());
}

TEST(Set, Erase_13) {
  std::set<int> std_s = {40, 30, 50, 20, 35, 45, 60, 15, 25, 33, 43, 47, 65};
  s21::set<int> s21_s = {40, 30, 50, 20, 35, 45, 60, 15, 25, 33, 43, 47, 65};
  auto it_std = std_s.begin();
  auto it_s21 = s21_s.begin();

  ++it_s21;
  ++it_std;

  ++it_s21;
  ++it_std;

  ++it_s21;
  ++it_std;

  ++it_s21;
  ++it_std;

  ++it_s21;
  ++it_std;

  ++it_s21;
  ++it_std;

  ++it_s21;
  ++it_std;

  --it_s21;
  --it_std;

  std_s.erase(it_std);
  s21_s.erase(it_s21);

  ASSERT_EQ(std_s.size(), s21_s.size());
  ASSERT_EQ(std_s.empty(), s21_s.empty());
}

TEST(Set, Erase_14) {
  std::set<int> std_s = {20, 10, 25, 4, 16, 23, 30, 2,
                         5,  14, 17, 3, 12, 15, 11, 19};
  s21::set<int> s21_s = {20, 10, 25, 4, 16, 23, 30, 2,
                         5,  14, 17, 3, 12, 15, 11, 19};
  auto it_std = std_s.begin();
  auto it_s21 = s21_s.begin();

  ++it_s21;
  ++it_std;

  ++it_s21;
  ++it_std;

  ++it_s21;
  ++it_std;

  ++it_s21;
  ++it_std;

  ++it_s21;
  ++it_std;

  ++it_s21;
  ++it_std;

  ++it_s21;
  ++it_std;

  ++it_s21;
  ++it_std;

  std::cout << " == " << (*it_s21).first << std::endl;

  std_s.erase(it_std);
  s21_s.erase(it_s21);

  ASSERT_EQ(std_s.size(), s21_s.size());
  ASSERT_EQ(std_s.empty(), s21_s.empty());
}

TEST(Set, Swap) {
  std::set<std::string> std_s = {"zero", "one", "two"};
  s21::set<std::string> s21_s = {"zero", "one", "two"};

  std::set<std::string> std_s_swap = {"null", "first", "second"};
  s21::set<std::string> s21_s_swap = {"null", "first", "second"};

  std_s.swap(std_s_swap);
  s21_s.swap(s21_s_swap);

  ASSERT_EQ(std_s.size(), s21_s.size());
  bool result = EqSets<std::string>(s21_s_swap, std_s_swap);
  ASSERT_EQ(result, true);
  bool result2 = EqSets<std::string>(s21_s, std_s);
  ASSERT_EQ(result2, true);
}

TEST(Set, Merge) {
  std::set<std::string> std_s = {"zero", "one", "two"};
  s21::set<std::string> s21_s = {"zero", "one", "two"};

  std::set<std::string> std_s_merge = {"null", "first", "second"};
  s21::set<std::string> s21_s_merge = {"null", "first", "second"};

  std_s.merge(std_s_merge);
  s21_s.merge(s21_s_merge);

  ASSERT_EQ(std_s.size(), s21_s.size());
  bool result = EqSets<std::string>(s21_s, std_s);
  ASSERT_EQ(result, true);
}

TEST(Set, Find) {
  s21::set<std::string> s21_s = {"zero", "one", "two"};
  auto it = s21_s.find("zero");
  ASSERT_EQ("zero", (*it).first);
}

TEST(Set, Contains) {
  s21::set<std::string> s21_s = {"zero", "one", "two"};
  ASSERT_EQ(s21_s.contains("zero"), true);
  ASSERT_EQ(s21_s.contains("five"), false);
}

TEST(Set, Contains_2) {
  s21::set<std::string> s21_s;
  ASSERT_EQ(s21_s.contains("zero"), false);
}

TEST(Set, InsertMany) {
  std::set<std::string> std_s = {"zero", "one", "two"};
  s21::set<std::string> s21_s;
  s21_s.insert_many("zero", "one", "two");
  ASSERT_EQ(std_s.size(), s21_s.size());
  bool result = EqSets<std::string>(s21_s, std_s);
  ASSERT_EQ(result, true);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
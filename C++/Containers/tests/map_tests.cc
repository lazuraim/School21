#include <gtest/gtest.h>

#include <map>

#include "../map/s21_map.h"
#include "../rbtree/node.h"
#include "../rbtree/rbtree.h"

template <typename Key, typename T>
bool EqMaps(s21::map<Key, T>& first, std::map<Key, T>& second) {
  if (first.size() != second.size()) {
    return false;
  }
  // auto it1 = first.begin();
  // auto it2 = second.begin();
  for (auto it1 = first.begin(), it2 = second.begin();
       it1 != first.end() && it2 != second.end(); ++it1, ++it2) {
    if ((*it1).first != (*it2).first || (*it1).second != (*it2).second) {
      return false;
    }
  }
  return true;
}

TEST(Map, CompareMaps) {
  std::map<int, std::string> std_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  s21::map<int, std::string> s21_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  bool result = EqMaps<int, std::string>(s21_m, std_m);
  ASSERT_EQ(result, true);
}

TEST(Map, DefaultInt) {
  std::map<int, int> std_m;
  s21::map<int, int> s21_m;
  ASSERT_EQ(std_m.size(), s21_m.size());
}

TEST(Map, DefaultNoKey) {
  std::map<int, int> std_m;
  std_m[0] = 100;
  s21::map<int, int> s21_m;
  s21_m[0] = 100;
  ASSERT_EQ(std_m[1], s21_m[1]);
  ASSERT_EQ(0, s21_m[1]);
}

TEST(Map, ValueCtorInt) {
  std::map<int, int> std_m = {{0, 100}};
  s21::map<int, int> s21_m = {{0, 100}};
  ASSERT_EQ(std_m[0], s21_m[0]);
  ASSERT_EQ(100, s21_m[0]);
  bool result = EqMaps<int, int>(s21_m, std_m);
  ASSERT_EQ(result, true);
}

TEST(Map, ValueCtorInt_2) {
  std::map<int, int> std_m = {{0, 100}, {-1, 10}, {-2, 1}};
  s21::map<int, int> s21_m = {{0, 100}, {-1, 10}, {-2, 1}};
  ASSERT_EQ(std_m[0], s21_m[0]);
  ASSERT_EQ(100, s21_m[0]);
  bool result = EqMaps<int, int>(s21_m, std_m);
  ASSERT_EQ(result, true);
}

TEST(Map, ValueCtorString) {
  std::map<int, std::string> std_m = {{0, "zero"}};
  s21::map<int, std::string> s21_m = {{0, "zero"}};
  ASSERT_EQ(std_m[0], s21_m[0]);
  bool result = EqMaps<int, std::string>(s21_m, std_m);
  ASSERT_EQ(result, true);
}

TEST(Map, CopyCtor) {
  std::map<int, std::string> std_m = {{0, "zero"}};
  std::map<int, std::string> std_m_copy(std_m);
  s21::map<int, std::string> s21_m = {{0, "zero"}};
  s21::map<int, std::string> s21_m_copy(s21_m);
  ASSERT_EQ(std_m[0], s21_m[0]);
  bool result2 = EqMaps<int, std::string>(s21_m_copy, std_m_copy);
  ASSERT_EQ(result2, true);
}

TEST(Map, CopyCtor2) {
  std::map<int, int> std_m = {{0, 5}};
  std::map<int, int> std_m_copy(std_m);
  s21::map<int, int> s21_m = {{0, 5}};
  s21::map<int, int> s21_m_copy(s21_m);
  bool result = EqMaps<int, int>(s21_m_copy, std_m_copy);
  ASSERT_EQ(result, true);
}

TEST(Map, CopyCtor3) {
  std::map<int, int> std_m = {{0, 5}, {1, 10}, {2, 20}};
  std::map<int, int> std_m_copy(std_m);
  s21::map<int, int> s21_m = {{0, 5}, {1, 10}, {2, 20}};
  s21::map<int, int> s21_m_copy(s21_m);
  bool result = EqMaps<int, int>(s21_m_copy, std_m_copy);
  ASSERT_EQ(result, true);
}

TEST(Map, CopyCtor4) {
  std::map<int, int> std_m = {{0, 5},  {1, 10}, {2, 20},
                              {3, 30}, {4, 40}, {5, 50}};
  std::map<int, int> std_m_copy(std_m);
  s21::map<int, int> s21_m = {{0, 5},  {1, 10}, {2, 20},
                              {3, 30}, {4, 40}, {5, 50}};
  s21::map<int, int> s21_m_copy(s21_m);
  bool result = EqMaps<int, int>(s21_m_copy, std_m_copy);
  ASSERT_EQ(result, true);
}

TEST(Map, CopyOper) {
  std::map<int, std::string> std_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  std::map<int, std::string> std_m_copy = std_m;
  s21::map<int, std::string> s21_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  s21::map<int, std::string> s21_m_copy = s21_m;
  ASSERT_EQ(std_m[0], s21_m[0]);
  ASSERT_EQ(std_m_copy[0], s21_m_copy[0]);
  bool result = EqMaps<int, std::string>(s21_m_copy, std_m_copy);
  ASSERT_EQ(result, true);
}

TEST(Map, MoveCtor) {
  std::map<int, int> std_m = {{0, 5}};
  s21::map<int, int> s21_m = {{0, 5}};
  ASSERT_EQ(std_m.size(), s21_m.size());
  std_m = std::move(std_m);
  s21_m = std::move(s21_m);
  ASSERT_EQ(std_m.size(), s21_m.size());
  bool result = EqMaps<int, int>(s21_m, std_m);
  ASSERT_EQ(result, true);
}

TEST(Map, MoveCtor_2) {
  std::map<int, int> std_m = {{0, 5}};
  std::map<int, int> std_m_copy(std::move(std_m));
  s21::map<int, int> s21_m = {{0, 5}};
  s21::map<int, int> s21_m_copy(std::move(s21_m));
  ASSERT_EQ(std_m_copy[0], s21_m_copy[0]);
  ASSERT_EQ(std_m_copy.size(), s21_m_copy.size());
}

TEST(Map, MoveOper) {
  std::map<int, std::string> std_m = {{0, "zero"}};
  std::map<int, std::string> std_m_copy = std::move(std_m);
  s21::map<int, std::string> s21_m = {{0, "zero"}};
  s21::map<int, std::string> s21_m_copy = std::move(s21_m);
  ASSERT_EQ(std_m_copy[0], s21_m_copy[0]);
  ASSERT_EQ(std_m_copy.size(), s21_m_copy.size());
}

TEST(Map, OperatorBrackets) {
  std::map<int, std::string> std_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  s21::map<int, std::string> s21_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  ASSERT_EQ(std_m[0], s21_m[0]);
  ASSERT_EQ(std_m[1], s21_m[1]);
  ASSERT_EQ(std_m[2], s21_m[2]);
  bool result = EqMaps<int, std::string>(s21_m, std_m);
  ASSERT_EQ(result, true);
}

TEST(Map, At) {
  std::map<int, std::string> std_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  s21::map<int, std::string> s21_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  ASSERT_EQ(std_m.at(0), s21_m.at(0));
  ASSERT_EQ(std_m.at(1), s21_m.at(1));
  ASSERT_EQ(std_m.at(2), s21_m.at(2));
  EXPECT_ANY_THROW(std_m.at(3););
  EXPECT_ANY_THROW(s21_m.at(3););
  bool result = EqMaps<int, std::string>(s21_m, std_m);
  ASSERT_EQ(result, true);
}

TEST(Map, Operators) {
  std::map<int, std::string> std_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  s21::map<int, std::string> s21_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  auto it_s21 = s21_m.begin();
  auto it_std = std_m.begin();
  ++it_std;
  ++it_s21;
  --it_std;
  --it_s21;
  ASSERT_EQ((*it_s21).first, (*it_std).first);
}

TEST(Map, Operators_2) {
  std::map<int, std::string> std_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  s21::map<int, std::string> s21_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  auto it_s21 = s21_m.begin();
  auto it_std = std_m.begin();
  ++it_std;
  ++it_s21;
  ++it_std;
  ++it_s21;
  --it_std;
  --it_s21;
  ASSERT_EQ((*it_s21).first, (*it_std).first);
}

TEST(Map, Operators_3) {
  std::map<int, std::string> std_m = {{0, "zero"},
                                      {1, "one"},
                                      {2, "two"},
                                      {-1, "minus_one"},
                                      {-3, "minus_three"}};
  s21::map<int, std::string> s21_m = {{0, "zero"},
                                      {1, "one"},
                                      {2, "two"},
                                      {-1, "minus_one"},
                                      {-3, "minus_three"}};
  auto it_s21 = s21_m.begin();
  auto it_std = std_m.begin();
  ++it_std;
  ++it_s21;
  ++it_std;
  ++it_s21;
  --it_std;
  --it_s21;
  ASSERT_EQ((*it_s21).first, (*it_std).first);
}

TEST(Map, Begin) {
  std::map<int, std::string> std_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  s21::map<int, std::string> s21_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  auto it_std = std_m.begin();
  auto it_s21 = s21_m.begin();
  ASSERT_EQ((*it_std).first, (*it_s21).first);
  ASSERT_EQ((*it_std).second, (*it_s21).second);
  bool result = EqMaps<int, std::string>(s21_m, std_m);
  ASSERT_EQ(result, true);
}

TEST(Map, Empty) {
  std::map<int, std::string> std_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  s21::map<int, std::string> s21_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  bool s21_res = std_m.empty();
  bool std_res = s21_m.empty();
  ASSERT_EQ(s21_res, std_res);
  bool result = EqMaps<int, std::string>(s21_m, std_m);
  ASSERT_EQ(result, true);
}

TEST(Map, Empty_2) {
  std::map<int, std::string> std_m = {{0, "zero"}};
  s21::map<int, std::string> s21_m = {{0, "zero"}};
  bool s21_res = std_m.empty();
  bool std_res = s21_m.empty();
  ASSERT_EQ(s21_res, std_res);
  bool result = EqMaps<int, std::string>(s21_m, std_m);
  ASSERT_EQ(result, true);
}

TEST(Map, Empty_3) {
  std::map<int, std::string> std_m;
  s21::map<int, std::string> s21_m;
  ASSERT_EQ(std_m.empty(), s21_m.empty());
}

TEST(Map, Size) {
  std::map<int, std::string> std_m;
  s21::map<int, std::string> s21_m;
  ASSERT_EQ(std_m.size(), s21_m.size());
}

TEST(Map, Size_2) {
  std::map<int, std::string> std_m = {{0, "zero"}};
  s21::map<int, std::string> s21_m = {{0, "zero"}};
  size_t s21_res = std_m.size();
  size_t std_res = s21_m.size();
  ASSERT_EQ(s21_res, std_res);
  bool result = EqMaps<int, std::string>(s21_m, std_m);
  ASSERT_EQ(result, true);
}

TEST(Map, Size_3) {
  std::map<int, std::string> std_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  s21::map<int, std::string> s21_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  size_t s21_res = std_m.size();
  size_t std_res = s21_m.size();
  ASSERT_EQ(s21_res, std_res);
  bool result = EqMaps<int, std::string>(s21_m, std_m);
  ASSERT_EQ(result, true);
}

TEST(Map, Clear) {
  std::map<int, std::string> std_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  s21::map<int, std::string> s21_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  std_m.clear();
  s21_m.clear();
  ASSERT_EQ(std_m.size(), s21_m.size());
  ASSERT_EQ(std_m.empty(), s21_m.empty());
}

TEST(Map, Insert_1) {
  std::map<int, std::string> std_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  s21::map<int, std::string> s21_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  std_m.insert({3, "three"});
  s21_m.insert({3, "three"});
  ASSERT_EQ(std_m[3], s21_m[3]);
  bool result = EqMaps<int, std::string>(s21_m, std_m);
  ASSERT_EQ(result, true);
}

TEST(Map, Insert_2) {
  std::map<int, std::string> std_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  s21::map<int, std::string> s21_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  std_m.insert({3, "three"});
  s21_m.insert(3, "three");
  ASSERT_EQ(std_m[3], s21_m[3]);
  bool result = EqMaps<int, std::string>(s21_m, std_m);
  ASSERT_EQ(result, true);
}

TEST(Map, Insert_3) {
  std::map<int, std::string> std_m = {
      {-2, "minus_two"}, {-4, "minus_four"}, {-7, "minus_seven"}};
  s21::map<int, std::string> s21_m = {
      {-2, "minus_two"}, {-4, "minus_four"}, {-7, "minus_seven"}};
  std_m.insert({3, "three"});
  s21_m.insert(3, "three");
  ASSERT_EQ(std_m[3], s21_m[3]);
  bool result = EqMaps<int, std::string>(s21_m, std_m);
  ASSERT_EQ(result, true);
}

TEST(Map, InsertOrAssign) {
  std::map<int, std::string> std_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  s21::map<int, std::string> s21_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  std_m.insert_or_assign(3, "three");
  s21_m.insert_or_assign(3, "three");
  ASSERT_EQ(std_m[3], s21_m[3]);
  bool result = EqMaps<int, std::string>(s21_m, std_m);
  ASSERT_EQ(result, true);
}

TEST(Map, InsertOrAssign_2) {
  std::map<int, std::string> std_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  s21::map<int, std::string> s21_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  std_m.insert_or_assign(2, "second");
  s21_m.insert_or_assign(2, "second");
  ASSERT_EQ(std_m[2], s21_m[2]);
  bool result = EqMaps<int, std::string>(s21_m, std_m);
  ASSERT_EQ(result, true);
}

TEST(Map, InsertOrAssign_3) {
  s21::map<int, std::string> s21_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  s21_m.insert_or_assign(0, "null");
  ASSERT_EQ(s21_m[0], "null");
  ASSERT_EQ(s21_m[2], "two");
  ASSERT_EQ(s21_m[1], "one");
}

TEST(Map, Erase) {
  std::map<int, std::string> std_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  s21::map<int, std::string> s21_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  ASSERT_EQ(std_m.size(), s21_m.size());
  std_m.erase(std_m.begin());
  s21_m.erase(s21_m.begin());
  ASSERT_EQ(std_m.size(), s21_m.size());
  bool result = EqMaps<int, std::string>(s21_m, std_m);
  ASSERT_EQ(result, true);
}

TEST(Map, Erase_1) {
  std::map<int, std::string> std_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  s21::map<int, std::string> s21_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  auto it_std = std_m.begin();
  auto it_s21 = s21_m.begin();
  ++it_std;
  ++it_s21;
  std_m.erase(it_std);
  s21_m.erase(it_s21);
  EXPECT_EQ(s21_m.size(), s21_m.size());
}

TEST(Map, Erase_2) {
  std::map<int, std::string> std_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  s21::map<int, std::string> s21_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  auto it_std = std_m.begin();
  auto it_s21 = s21_m.begin();
  ++it_std;
  ++it_s21;
  std_m.erase(it_std);
  s21_m.erase(it_s21);
  EXPECT_EQ(s21_m.size(), s21_m.size());
}

TEST(Map, Swap) {
  std::map<int, std::string> std_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  s21::map<int, std::string> s21_m = {{0, "zero"}, {1, "one"}, {2, "two"}};

  std::map<int, std::string> std_m_swap = {{1, "first"}, {2, "second"}};
  s21::map<int, std::string> s21_m_swap = {{1, "first"}, {2, "second"}};

  std_m.swap(std_m_swap);
  s21_m.swap(s21_m_swap);

  ASSERT_EQ(std_m.size(), s21_m.size());
  bool result = EqMaps<int, std::string>(s21_m, std_m);
  ASSERT_EQ(result, true);
}

TEST(Map, Merge) {
  std::map<int, std::string> std_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  s21::map<int, std::string> s21_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  std::map<int, std::string> std_m_swap = {{1, "first"}, {3, "three"}};
  s21::map<int, std::string> s21_m_swap = {{1, "first"}, {3, "three"}};

  std_m.merge(std_m_swap);
  s21_m.merge(s21_m_swap);

  ASSERT_EQ(std_m.size(), s21_m.size());
  bool result = EqMaps<int, std::string>(s21_m, std_m);
  ASSERT_EQ(result, true);
}

TEST(Map, Contains) {
  s21::map<int, std::string> s21_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  ASSERT_EQ(s21_m.contains(1), true);
  ASSERT_EQ(s21_m.contains(5), false);
}

TEST(Map, Contains_2) {
  s21::map<int, std::string> s21_m;
  ASSERT_EQ(s21_m.contains(5), false);
}

TEST(Map, InsertMany) {
  std::map<int, std::string> std_m = {{0, "zero"}, {1, "one"}, {2, "two"}};
  s21::map<int, std::string> s21_m;
  s21_m.insert_many(std::make_pair(0, "zero"), std::make_pair(1, "one"),
                    std::make_pair(2, "two"));

  ASSERT_EQ(std_m.size(), s21_m.size());
  bool result = EqMaps<int, std::string>(s21_m, std_m);
  ASSERT_EQ(result, true);
}

// int main(int argc, char** argv) {
//   ::testing::InitGoogleTest(&argc, argv);

//   return RUN_ALL_TESTS();
// }

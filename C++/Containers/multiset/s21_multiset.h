#ifndef CPP2_S21_CONTAINERS_SRC_MULTISET_S21_MULTISET_H_
#define CPP2_S21_CONTAINERS_SRC_MULTISET_S21_MULTISET_H_

#include <iostream>
#include <limits>
#include <vector>

#include "../rbtree/node.h"
#include "../rbtree/rbtree.h"

namespace s21 {

template <typename Key>
class multiset : public rbtree<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using tree_type = rbtree<Key, Key>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = Iterator<key_type, key_type>;
  using const_iterator = ConstIterator<key_type, key_type>;
  using size_type = size_t;

  multiset() { tree_type(); }
  multiset(std::initializer_list<value_type> const& items) {
    for (const_reference item : items) {
      tree_type::insert({item, item}, true);
    }
  }
  multiset(const multiset& ms) : tree_type(ms) {}
  multiset(multiset&& ms) noexcept : tree_type(std::move(ms)) {}
  ~multiset() noexcept {}

  multiset operator=(multiset& ms) {
    tree_type::copy_tree(ms);
    return *this;
  }

  multiset operator=(multiset&& ms) {
    tree_type::move_tree(std::move(ms));
    return *this;
  }

  iterator begin() { return tree_type::begin(); }
  iterator end() { return tree_type::end(); }

  bool empty() const noexcept { return tree_type::empty(); }
  size_type size() const noexcept { return tree_type::size(); }
  size_type max_size() const noexcept { return tree_type::max_size(); }

  void clear() { tree_type::clear(); }

  iterator insert(const value_type& value) {
    return (tree_type::insert_general({value, value}, true)).first;
  }

  void erase(iterator pos) { tree_type::erase(pos); }
  void swap(multiset& other) { tree_type::swap(other); }
  void merge(multiset& other) { tree_type::merge(other, true); }

  size_type count(const Key& key) {
    size_type count = 0;
    for (iterator it = begin(); it != end(); ++it) {
      if ((*it).first = key) {
        ++count;
      }
    }
    return count;
  }

  iterator find(const Key& key) { return (tree_type::find_key(key)).first; }
  bool contains(const Key& key) { return (tree_type::find_key(key)).second; }

  std::pair<iterator, iterator> equal_range(const Key& key) {
    return {lower_bound(key), upper_bound(key)};
  }

  iterator lower_bound(const Key& key) {
    for (iterator it = begin(); it != end(); ++it) {
      if ((*it).first >= key) {
        return it;
      }
    }
    return end();
  }

  iterator upper_bound(const Key& key) {
    for (iterator it = begin(); it != end(); ++it) {
      if ((*it).first > key) {
        return it;
      }
    }
    return end();
  }

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    return tree_type::insert_many(true, args...);
  }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_MULTISET_S21_MULTISET_H_
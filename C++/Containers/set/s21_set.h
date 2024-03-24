#ifndef CPP2_S21_CONTAINERS_SRC_SET_S21_SET_H_
#define CPP2_S21_CONTAINERS_SRC_SET_S21_SET_H_

#include <iostream>
#include <limits>
#include <vector>

#include "../rbtree/node.h"
#include "../rbtree/rbtree.h"

namespace s21 {

template <typename Key>
class set : public rbtree<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using tree_type = rbtree<key_type, value_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = Iterator<key_type, key_type>;
  using const_iterator = ConstIterator<key_type, key_type>;
  using size_type = size_t;

  set() : tree_type() {}
  set(std::initializer_list<value_type> const &items) {
    for (const_reference item : items) {
      if (!contains(item)) {
        tree_type::insert({item, item}, false);
      }
    }
  }
  set(const set &s) : tree_type(s) {}
  set(set &&s) noexcept : tree_type(std::move(s)) {}
  ~set() noexcept {}

  set operator=(set &s) {
    tree_type::copy_tree(s);
    return *this;
  }

  set operator=(set &&s) {
    tree_type::move_tree(std::move(s));
    return *this;
  }

  iterator begin() { return tree_type::begin(); }
  iterator end() { return tree_type::end(); }

  bool empty() const noexcept { return tree_type::empty(); }
  size_type size() const noexcept { return tree_type::size(); }
  size_type max_size() const noexcept { return tree_type::max_size(); }

  void clear() { tree_type::clear(); }

  std::pair<iterator, bool> insert(const value_type &value) {
    return tree_type::insert_general({value, value}, false);
  }

  void erase(iterator pos) { tree_type::erase(pos); }
  void swap(set &other) { tree_type::swap(other); }
  void merge(set &other) { tree_type::merge(other, false); }

  iterator find(const Key &key) { return (tree_type::find_key(key)).first; }
  bool contains(const Key &key) { return (tree_type::find_key(key)).second; }

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    return tree_type::insert_many(false, args...);
  }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_SET_S21_SET_H_
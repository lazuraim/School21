#ifndef CPP2_S21_CONTAINERS_SRC_MAP_S21_MAP_H_
#define CPP2_S21_CONTAINERS_SRC_MAP_S21_MAP_H_

#include <iostream>
#include <limits>
#include <vector>

#include "../rbtree/node.h"
#include "../rbtree/rbtree.h"

namespace s21 {

template <typename Key, typename T>
class map : public rbtree<Key, T> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using tree_type = rbtree<key_type, mapped_type>;
  using node_type = node<key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = Iterator<key_type, mapped_type>;
  using const_iterator = ConstIterator<key_type, mapped_type>;
  using size_type = size_t;

  map() : tree_type() {}
  map(std::initializer_list<value_type> const& items) {
    for (const_reference item : items) {
      if (!contains(item.first)) {
        tree_type::insert(item, false);
      }
    }
  }
  map(const map& m) : tree_type(m) {}
  map(map&& m) noexcept : tree_type(std::move(m)) {}
  ~map() noexcept {}

  map operator=(map& m) {
    tree_type::copy_tree(m);
    return *this;
  }

  map operator=(map&& m) {
    tree_type::move_tree(std::move(m));
    return *this;
  }

  T& at(const Key& key) {
    if (!contains(key)) {
      throw std::out_of_range("map::at");
    }
    return tree_type::find_node(key)->value;
  }

  T& operator[](const Key& key) {
    if (!contains(key)) {
      insert(key, mapped_type());
    }
    return tree_type::find_node(key)->value;
  }

  iterator begin() { return tree_type::begin(); }
  iterator end() { return tree_type::end(); }

  const_iterator begin() const { return tree_type::begin(); }
  const_iterator end() const { return tree_type::end(); }

  bool empty() const noexcept { return tree_type::empty(); }
  size_type size() const noexcept { return tree_type::size(); }
  size_type max_size() const noexcept { return tree_type::max_size(); }

  void clear() { tree_type::clear(); }

  std::pair<iterator, bool> insert(const value_type& value) {
    return tree_type::insert_general(value, false);
  }

  std::pair<iterator, bool> insert(const Key& key, const T& obj) {
    return insert(std::make_pair(key, obj));
  }

  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
    std::pair<iterator, bool> node_info = tree_type::find_key(key);
    node_type* node_ptr = tree_type::find_node(key);
    iterator res = iterator(node_ptr);
    if (node_info.second) {
      node_ptr->value = obj;
      node_ptr->key_val.second = obj;
    } else {
      res = insert(key, obj).first;
    }
    return std::make_pair(res, true);
  }

  void erase(iterator pos) { tree_type::erase(pos); }
  void swap(map& other) { tree_type::swap(other); }
  void merge(map& other) { tree_type::merge(other, false); }

  bool contains(const Key& key) { return (tree_type::find_key(key)).second; }

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    return tree_type::insert_many_map(args...);
  }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_MAP_S21_MAP_H_
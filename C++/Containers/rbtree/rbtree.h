#ifndef CPP2_S21_CONTAINERS_SRC_RBTREE_RBTREE_H_
#define CPP2_S21_CONTAINERS_SRC_RBTREE_RBTREE_H_

#include <iostream>
#include <limits>
#include <vector>

#include "node.h"

namespace s21 {

template <typename Key, typename T>
class ConstIterator;

template <typename Key, typename T>
class Iterator;

template <typename Key, typename T>
class rbtree {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  using tree_type = rbtree<key_type, mapped_type>;
  using node_type = node<key_type, mapped_type>;
  using iterator = Iterator<key_type, mapped_type>;
  using const_iterator = ConstIterator<key_type, mapped_type>;
  using size_type = size_t;

  rbtree() = default;
  rbtree(const rbtree &other) { copy_tree(other); };
  rbtree(rbtree &&other) noexcept { move_tree(std::move(other)); }
  ~rbtree() noexcept { clear_tree(root_); }

  void copy_tree(const rbtree &other);
  void move_tree(rbtree &&other);

  std::pair<iterator, bool> insert_general(const value_type &value, bool multi);
  void insert(value_type val, bool multi);
  void erase(iterator iter);
  void clear();
  std::pair<iterator, bool> find_key(key_type key);
  node_type *find_node(key_type key);
  void swap(tree_type &other);
  void merge(tree_type &other, bool multi);

  bool empty() const noexcept { return !size_; }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_t>::max() / (sizeof(node_type));
  }

  const_iterator begin() const { return iterator(find_min(root_)); }

  const_iterator end() const { return iterator(find_max(root_)->right); }

  iterator begin() { return iterator(find_min(root_)); }

  iterator end() { return iterator(find_max(root_)->right); }

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many_map(Args &&...args);

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(bool multi,
                                                     Args &&...args);

 private:
  node_type *root_{};
  size_type size_{};

  void clear_tree(node_type *current_node);
  node_type *copy_nodes(node_type *current_node);
  node_type *find_min(node_type *node);
  node_type *find_max(node_type *node);

  void balance_after_insert(node_type *node);
  void swap_color(node_type *node);
  void left_rotate(node_type *node);
  void right_rotate(node_type *node);
  node_type *grandfather(node_type *node) { return node->parent->parent; }

  node_type *delete_node(node_type *node);
  void balance_after_delete(node_type *node);
  node_type *if_node_is_left_child(node_type *node);
  node_type *if_node_is_right_child(node_type *node);
};

template <typename Key, typename T>
void rbtree<Key, T>::copy_tree(const rbtree &other) {
  if (root_ != other.root_) {
    clear_tree(root_);
    if (other.root_ != nullptr) {
      node_type *node_ptr = copy_nodes(other.root_);
      while (node_ptr->parent != nullptr) {
        node_ptr = node_ptr->parent;
      }
      root_ = node_ptr;
    }
    size_ = other.size_;
  }
};

template <typename Key, typename T>
typename rbtree<Key, T>::node_type *rbtree<Key, T>::copy_nodes(
    node_type *current_node) {
  if (!current_node) {
    return nullptr;
  }
  node_type *new_node = new node_type(current_node->key, current_node->value);
  new_node->left = copy_nodes(current_node->left);
  new_node->right = copy_nodes(current_node->right);
  new_node->parent = current_node->parent;
  new_node->color = current_node->color;
  return new_node;
};

template <typename Key, typename T>
void rbtree<Key, T>::move_tree(rbtree &&other) {
  if (root_ == other.root_) {
    size_ = 0;
    return;
  }
  clear_tree(root_);
  std::swap(root_, other.root_);
  std::swap(size_, other.size_);
  other.root_ = nullptr;
}

template <typename Key, typename T>
void rbtree<Key, T>::clear_tree(node_type *current_node) {
  if (!current_node) {
    return;
  }
  clear_tree(current_node->right);
  clear_tree(current_node->left);
  delete current_node;
  root_ = nullptr;
}

template <typename Key, typename T>
void rbtree<Key, T>::clear() {
  if (root_) {
    clear_tree(root_);
    size_ = 0;
  }
};

template <typename Key, typename T>
void rbtree<Key, T>::insert(value_type val, bool multi) {
  node_type *new_node = new node_type(val.first, val.second);
  node_type *parent = nullptr;
  node_type *current_node = root_;
  if (!root_) {
    root_ = new_node;
  } else {
    while (current_node) {
      parent = current_node;
      if (val.first < current_node->key)
        current_node = current_node->left;
      else
        current_node = current_node->right;
    }
    new_node->parent = parent;
    if (val.first < parent->key)
      parent->left = new_node;
    else if (val.first > parent->key)
      parent->right = new_node;
    else if (val.first == parent->key && multi)
      parent->right = new_node;
  }
  balance_after_insert(new_node);
  ++size_;
};

template <typename Key, typename T>
void rbtree<Key, T>::balance_after_insert(node_type *node) {
  while (node != root_ && node->parent->color == kRED) {
    if (node->parent == grandfather(node)->left) {
      if (!grandfather(node)->right ||
          grandfather(node)->right->color == kBLACK) {
        if (node == node->parent->right) {
          node = node->parent;
          left_rotate(node);
        }
        node->parent->color = kBLACK;
        grandfather(node)->color = kRED;
        right_rotate(grandfather(node));
      } else if (grandfather(node)->right->color == kRED) {
        swap_color(grandfather(node));
        node = grandfather(node);
      }
    } else {
      if (!grandfather(node)->left ||
          grandfather(node)->left->color == kBLACK) {
        if (node == node->parent->left) {
          node = node->parent;
          right_rotate(node);
        }
        node->parent->color = kBLACK;
        grandfather(node)->color = kRED;
        left_rotate(grandfather(node));
      } else if (grandfather(node)->left->color == kRED) {
        swap_color(grandfather(node));
        node = grandfather(node);
      }
    }
  }
  root_->color = kBLACK;
};

template <typename Key, typename T>
std::pair<typename rbtree<Key, T>::iterator, bool>
rbtree<Key, T>::insert_general(const value_type &value, bool multi) {
  std::pair<iterator, bool> node_info = find_key(value.first);
  iterator it = node_info.first;
  bool inserted = false;
  if (multi) {
    inserted = true;
  } else {
    if (!node_info.second) {
      inserted = true;
    }
  }
  insert(value, multi);
  return std::make_pair(it, inserted);
};

template <typename Key, typename T>
void rbtree<Key, T>::erase(iterator iter) {
  if (iter.node_ptr) {
    iter.node_ptr = delete_node(iter.node_ptr);
    delete iter.node_ptr;
    --size_;
  }
};

template <typename Key, typename T>
typename rbtree<Key, T>::node_type *rbtree<Key, T>::delete_node(
    node_type *node) {
  node_type *y = nullptr, *x = nullptr;
  bool nil = 0;
  if (node->left == nullptr || node->right == nullptr) {
    y = node;
  } else {
    y = node->left;
    while (y->right) {
      y = y->right;
    }
  }
  if (y->left) {
    x = y->left;
  } else if (y->right) {
    x = y->right;
  } else {
    x = new node_type();
    y->right = x;
    nil = 1;
  }
  x->parent = y->parent;
  if (!y->parent)
    root_ = x;
  else if (y == y->parent->left)
    y->parent->left = x;
  else
    y->parent->right = x;

  if (y != node) {
    node->key = y->key;
    node->value = y->value;
  }
  if (y->color == kBLACK) balance_after_delete(x);
  if (nil) {
    y->right = nullptr;
    if (root_ == x) {
      root_ = nullptr;
    } else if (y->parent->left == x) {
      y->parent->left = nullptr;
    } else if (y->parent->right == x) {
      y->parent->right = nullptr;
    }
    delete x;
  }
  return y;
};

template <typename Key, typename T>
void rbtree<Key, T>::balance_after_delete(node_type *node) {
  while (node != root_ && node->color == kBLACK) {
    if (node == node->parent->left) {
      node = if_node_is_left_child(node);
    } else {
      node = if_node_is_right_child(node);
    }
  }
  if (node) {
    node->color = kBLACK;
  }
};

template <typename Key, typename T>
typename rbtree<Key, T>::node_type *rbtree<Key, T>::if_node_is_left_child(
    node_type *node) {
  node_type *w = node->parent->right;
  if (w->color == kRED) {
    w->color = kBLACK;
    node->parent->color = kRED;
    left_rotate(node->parent);
    w = node->parent->right;
  }
  if ((w->left == nullptr && w->right == nullptr) ||
      (w->left->color == kBLACK && w->right->color == kBLACK)) {
    w->color = kRED;
    node = node->parent;
  } else {
    if (w->right == nullptr || w->right->color == kBLACK) {
      if (w->left) {
        w->left->color = kBLACK;
      }
      w->color = kRED;
      right_rotate(w);
      w = node->parent->right;
    }
    w->color = node->parent->color;
    node->parent->color = kBLACK;
    if (w->right) {
      w->right->color = kBLACK;
    }
    left_rotate(node->parent);
    node = root_;
  }
  return node;
}

template <typename Key, typename T>
typename rbtree<Key, T>::node_type *rbtree<Key, T>::if_node_is_right_child(
    node_type *node) {
  node_type *w = node->parent->left;
  if (w->color == kRED) {
    w->color = kBLACK;
    node->parent->color = kRED;
    right_rotate(node->parent);
    w = node->parent->left;
  }
  if ((!w->right && !w->left) || (w->right && w->right->color == kBLACK &&
                                  w->left && w->left->color == kBLACK)) {
    w->color = kRED;
    node = node->parent;
  } else {
    if (!w->left || w->left->color == kBLACK) {
      if (w->right) w->right->color = kBLACK;
      w->color = kRED;
      left_rotate(w);
      w = node->parent->left;
    }
    w->color = node->parent->color;
    node->parent->color = kBLACK;
    if (w->left) w->left->color = kBLACK;
    right_rotate(node->parent);
    node = root_;
  }
  return node;
}

template <typename Key, typename T>
void rbtree<Key, T>::swap_color(node_type *node) {
  node->color = kRED;
  node->left->color = kBLACK;
  node->right->color = kBLACK;
};

template <typename Key, typename T>
void rbtree<Key, T>::left_rotate(node_type *node) {
  node_type *y = node->right;
  node->right = y->left;
  if (y->left != nullptr) y->left->parent = node;
  if (y != nullptr) y->parent = node->parent;

  if (node->parent == nullptr)
    root_ = y;
  else if (node == node->parent->left)
    node->parent->left = y;
  else
    node->parent->right = y;
  y->left = node;

  if (node != nullptr) node->parent = y;
};

template <typename Key, typename T>
void rbtree<Key, T>::right_rotate(node_type *node) {
  node_type *y = node->left;
  node->left = y->right;
  if (y->right != nullptr) y->right->parent = node;
  if (y != nullptr) y->parent = node->parent;

  if (node->parent == nullptr)
    root_ = y;
  else if (node == node->parent->right)
    node->parent->right = y;
  else if (node == node->parent->left)
    node->parent->left = y;

  y->right = node;
  if (node != nullptr) node->parent = y;
};

template <typename Key, typename T>
std::pair<typename rbtree<Key, T>::iterator, bool> rbtree<Key, T>::find_key(
    key_type key) {
  node_type *current_node = root_;
  while (current_node) {
    if (current_node->key == key)
      return std::make_pair(iterator(current_node), true);

    if (key < current_node->key)
      current_node = current_node->left;
    else
      current_node = current_node->right;
  }
  return std::make_pair(iterator(nullptr), false);
};

template <typename Key, typename T>
typename rbtree<Key, T>::node_type *rbtree<Key, T>::find_node(key_type key) {
  node_type *current_node = root_;
  while (current_node) {
    if (current_node->key == key) return current_node;

    if (key < current_node->key)
      current_node = current_node->left;
    else
      current_node = current_node->right;
  }
  return nullptr;
};

template <typename Key, typename T>
typename rbtree<Key, T>::node_type *rbtree<Key, T>::find_min(node_type *node) {
  if (!node) return nullptr;
  while (node->left != nullptr) {
    node = node->left;
  }
  return node;
};

template <typename Key, typename T>
typename rbtree<Key, T>::node_type *rbtree<Key, T>::find_max(node_type *node) {
  node_type *tmp = node;
  while (node->right != nullptr) {
    node = node->right;
    tmp = node;
  }
  return tmp;
};

template <typename Key, typename T>
void rbtree<Key, T>::swap(tree_type &other) {
  std::swap(root_, other.root_);
  std::swap(size_, other.size_);
};

template <typename Key, typename T>
void rbtree<Key, T>::merge(tree_type &other, bool multi) {
  for (iterator it = other.begin(); it != other.end(); ++it) {
    if (multi) {
      insert({(*it).first, (*it).second}, 1);
    } else {
      if (!(find_key((*it).first)).second) {
        insert({(*it).first, (*it).second}, 0);
      }
    }
  }
};

template <typename Key, typename T>
template <class... Args>
std::vector<std::pair<typename rbtree<Key, T>::iterator, bool>>
rbtree<Key, T>::insert_many_map(Args &&...args) {
  std::vector<std::pair<iterator, bool>> result{};
  for (auto &arg : {args...}) {
    result.push_back(tree_type::insert_general(arg, false));
  }
  return result;
};

template <typename Key, typename T>
template <class... Args>
std::vector<std::pair<typename rbtree<Key, T>::iterator, bool>>
rbtree<Key, T>::insert_many(bool multi, Args &&...args) {
  std::vector<std::pair<iterator, bool>> result{};
  for (auto &arg : {args...}) {
    result.push_back(tree_type::insert_general({arg, arg}, multi));
  }
  return result;
};

template <typename Key, typename T>
class ConstIterator {
 public:
  using node_type = node<Key, T>;
  using value_type = std::pair<Key, T>;

  template <typename K, typename Tt>
  friend class rbtree;

  ConstIterator() = default;
  ConstIterator(node_type *node) : node_ptr(node) {}
  ConstIterator(const Iterator<Key, T> &other) : node_ptr(other.node_ptr) {}

  const value_type &operator*() const { return node_ptr->key_val; }

  ConstIterator &operator++();
  ConstIterator &operator--();

  bool operator==(ConstIterator<Key, T> &other) const {
    return node_ptr == other.node_ptr;
  }

  bool operator!=(ConstIterator<Key, T> &other) const {
    return !(node_ptr == other.node_ptr);
  }

 private:
  node_type *node_ptr{};
};

template <typename Key, typename T>
ConstIterator<Key, T> &ConstIterator<Key, T>::operator++() {
  if (node_ptr) {
    if (node_ptr->right->right) {
      node_ptr = node_ptr->right;
      while (node_ptr->left->left) {
        node_ptr = node_ptr->left;
      }
    } else {
      node_type *ex = node_ptr;
      node_ptr = node_ptr->parent;
      while (node_ptr->right == ex && ex) {
        ex = node_ptr;
        node_ptr = node_ptr->parent;
      }
    }
  }
  return *this;
};

template <typename Key, typename T>
ConstIterator<Key, T> &ConstIterator<Key, T>::operator--() {
  if (node_ptr) {
    if (node_ptr->left->left) {
      node_ptr = node_ptr->left;
      while (node_ptr->right->right) {
        node_ptr = node_ptr->right;
      }
    } else {
      node_type *ex = node_ptr;
      node_ptr = node_ptr->parent;
      while (node_ptr && node_ptr->left == ex) {
        ex = node_ptr;
        node_ptr = node_ptr->parent;
      }
    }
  }
  return *this;
}

template <typename Key, typename T>
class Iterator : ConstIterator<Key, T> {
 public:
  using node_type = node<Key, T>;
  using value_type = std::pair<Key, T>;
  using tree_type = rbtree<Key, T>;

  template <typename K, typename Tt>
  friend class rbtree;

  Iterator() = default;
  Iterator(node_type *node) : node_ptr(node){};

  value_type &operator*() const { return node_ptr->key_val; }

  Iterator &operator++();
  Iterator &operator--();
  Iterator &operator++(int);
  Iterator &operator--(int);

  bool operator==(Iterator<Key, T> &other) const {
    return node_ptr == other.node_ptr;
  }

  bool operator!=(Iterator<Key, T> other) const {
    return !(node_ptr == other.node_ptr);
  }

 private:
  node_type *node_ptr{};
};

template <typename Key, typename T>
Iterator<Key, T> &Iterator<Key, T>::operator++() {
  if (node_ptr) {
    if (node_ptr->right) {
      node_ptr = node_ptr->right;
      while (node_ptr->left) {
        node_ptr = node_ptr->left;
      }
    } else {
      node_type *ex = node_ptr;
      node_ptr = node_ptr->parent;
      while (node_ptr && node_ptr->right == ex) {
        ex = node_ptr;
        node_ptr = node_ptr->parent;
      }
    }
  }
  return *this;
};

template <typename Key, typename T>
Iterator<Key, T> &Iterator<Key, T>::operator--() {
  if (node_ptr) {
    if (node_ptr->left) {
      node_ptr = node_ptr->left;
      while (node_ptr->right) {
        node_ptr = node_ptr->right;
      }
    } else {
      node_type *ex = node_ptr;
      node_ptr = node_ptr->parent;
      while (node_ptr && node_ptr->left == ex) {
        ex = node_ptr;
        node_ptr = node_ptr->parent;
      }
    }
  }
  return *this;
};

template <typename Key, typename T>
Iterator<Key, T> &Iterator<Key, T>::operator++(int) {
  Iterator tmp = *this;
  ++(*this);
  return tmp;
}

template <typename Key, typename T>
Iterator<Key, T> &Iterator<Key, T>::operator--(int) {
  Iterator tmp = *this;
  --(*this);
  return tmp;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_RBTREE_RBTREE_H_

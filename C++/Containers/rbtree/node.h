#ifndef CPP2_S21_CONTAINERS_SRC_RBTREE_NODE_H_
#define CPP2_S21_CONTAINERS_SRC_RBTREE_NODE_H_

namespace s21 {

enum node_color { kRED, kBLACK };

template <typename Key, typename T>
class node {
 public:
  using key_type = Key;
  using mapped_type = T;

  node() noexcept = default;
  node(key_type new_key, mapped_type new_value) {
    color = kRED;
    key = new_key;
    value = new_value;
    key_val = {key, value};
  };

  bool color = kBLACK;
  key_type key{};
  mapped_type value{};
  std::pair<key_type, mapped_type> key_val{key, value};
  node<key_type, mapped_type> *parent{}, *left{}, *right{};
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_RBTREE_NODE_H_

///////////////////////////////////////////////////////////////////////////////
//                              Private functions                            //
///////////////////////////////////////////////////////////////////////////////

#include "tree.h"
#include <iostream>

template <typename T>
void tree<T>::destroy(node &n){
  if (!n.is_null()){
    destroy(n.left_child());
    destroy(n.right_sibling());
    n.remove();
  }
}

template <typename T>
unsigned int tree<T>::count(const node &n) const {
  if (n.is_null()){
    return 0;
  } else {
    return 1 + count(n.left_child()) + count(n.right_sibling());
  }
}

template<typename T>
bool tree<T>::equals(node &lhs, node &rhs) const {
  bool equality = true;
  if (lhs.is_null() && rhs.is_null()){
    equality = true;
  } else if (lhs.is_null() && rhs.is_null()) {
    equality = false;
  } else if (*lhs != *rhs){
    equality = false;
  } else if (!equal(lhs.left_child(), rhs.left_child())){
    equality = false;
  } else if (!equal(lhs.right_sibling(), rhs.right_sibling())){
    equality = false;
  }
  return equality;
}

template <typename T>
void tree<T>::copy(const node &src, node &dest) {
  if (!dest.is_null()) {
    this->destroy(dest);
  }
  dest = node(*src);
  if (!src.left_child().is_null()){
    copy(src.left_child(), dest.left_child());
    if (!dest.left_child().is_null()){
      dest.left_child().set_parent(dest);
    }
  }
  if (!src.right_sibling().is_null()){
    copy(src.right_sibling(), dest.right_sibling());
    if (!dest.right_sibling().is_null()){
      dest.right_sibling().set_parent(dest.parent());
    }
  }
}

template <typename T>
void tree<T>::print(std::ostream &out, const std::string &prefix, const node &curr_node) const {
  if (!curr_node.is_null()) {
    out << prefix;
    bool is_last = curr_node.right_sibling().is_null();
    out << (is_last ? "└──" : "├──");
    out << *curr_node << std::endl;
    print(out, prefix + (is_last ? "   " : "│  " ), curr_node.left_child());
    print(out, prefix , curr_node.right_sibling());
  }
}

///////////////////////////////////////////////////////////////////////////////
//                              Public functions                             //
///////////////////////////////////////////////////////////////////////////////

template <typename T>
tree<T>::tree() {}

template <typename T>
inline tree<T>::tree(const T &label) : root(label){}

template<typename T>
tree<T>::tree(const tree<T> &other) {
  this->copy(other.root, this->root);
}

template<typename T>
typename tree<T>::node
tree<T>::insert_left_child(tree::node &n, tree<T> &child) {
  node new_node(*(child.root));
  new_node.set_left_child(child.root.left_child());
  node * aux = &child.root.left_child();

  while (!aux->is_null()){
    aux->set_parent(new_node);
    aux = &aux->right_sibling();
  }
  child.root.remove();

  new_node.set_right_sibling(n.left_child());
  new_node.set_parent(n);
  n.set_left_child(new_node);

  return new_node;
}

template<typename T>
typename tree<T>::node
tree<T>::insert_left_child(tree::node &n, const T &label) {
  node new_node(label);

  new_node.set_right_sibling(n.left_child());
  new_node.set_parent(n);
  n.set_left_child(new_node);

  return new_node;
}

template<typename T>
typename tree<T>::node
tree<T>::insert_right_sibling(tree::node &n, tree<T> &sibling) {
  node new_node(*(sibling.root));
  new_node.set_left_child(sibling.root.left_child());
  node * aux = &sibling.root.left_child();

  while (!aux->is_null()){
    aux->set_parent(new_node);
    aux = &aux->right_sibling();
  }

  sibling.root.remove();
  new_node.set_right_sibling(n.right_sibling());
  new_node.set_parent(n.parent());
  n.set_right_sibling(new_node);

  return new_node;
}

template<typename T>
typename tree<T>::node
tree<T>::insert_right_sibling(tree::node &n, const T &label) {
  node new_node(label);

  new_node.set_right_sibling(n.right_sibling());
  new_node.set_parent(n.parent());
  n.set_right_sibling(new_node);

  return new_node;
}

template<typename T>
tree<T>::~tree() {
  this->destroy(this->root);
}

template<typename T>
void tree<T>::set_root(const T &label) {
  if (!this->root.is_null()){
    this->root.wrap->label = label;
  } else this->root = node(label);
}

template<typename T>
tree<T> &tree<T>::operator=(const tree<T> &other) {
  if (this != &other){
    this->copy(other.root, this->root);
  }
  return *this;
}

template<typename T>
typename tree<T>::node tree<T>::get_root() const {
  return this->root;
}

template<typename T>
void tree<T>::prune_left_child(tree::node &n, tree<T> &dest) {
  if (!n.left_child().is_null()){
    destroy(dest.root);
    dest.root = n.left_child();
    n.left_child() = n.left_child().right_sibling();
    dest.root.set_parent(node());
    dest.root.set_right_sibling(node());
  }
}

template<typename T>
void tree<T>::prune_right_sibling(tree::node &n, tree<T> &dest) {
  if (!n.right_sibling().is_null()){
    destroy(dest.root);
    dest.root = n.right_sibling();
    n.set_right_sibling(dest.right_sibling().right_sibling());
    dest.root.set_parent(node());
    dest.root.set_right_sibling(node());
  }
}

template<typename T>
void tree<T>::clear() {
  this->destroy(this->root);
  this->root = node();
}

template<typename T>
unsigned int tree<T>::size() const {
  return this->count(this->root);
}

template<typename T>
bool tree<T>::empty() const {
  return this->root == node();
}

template<typename T>
bool tree<T>::operator==(const tree<T> &other) const {
  return this->equals(this->root, other.root);
}

template<typename T>
bool tree<T>::operator!=(const tree<T> &other) const {
  return !(*this == other);
}

template<typename U>
std::ostream &operator<<(std::ostream &out, const tree<U> &rhs) {
  rhs.print(out);
  return out;
}

///////////////////////////////////////////////////////////////////////////////
//                                  ITERATOR                                 //
///////////////////////////////////////////////////////////////////////////////

template<typename T>
tree<T>::preorder_iterator::preorder_iterator() {
}

template<typename T>
tree<T>::preorder_iterator::preorder_iterator(const tree::node &n) {
}

template<typename T>
bool tree<T>::preorder_iterator::operator!=(const tree::preorder_iterator &i) const {
}

template<typename T>
bool tree<T>::preorder_iterator::operator==(const tree::preorder_iterator &i) const {
}

template<typename T>
T &tree<T>::preorder_iterator::operator*() {
}

template<typename T>
typename tree<T>::preorder_iterator &
tree<T>::preorder_iterator::operator++() {
}

template<typename T>
typename tree<T>::preorder_iterator
tree<T>::begin_preorder() {
}

template<typename T>
typename tree<T>::preorder_iterator tree<T>::end_preorder() {
}

template<typename T>
tree<T>::const_preorder_iterator::const_preorder_iterator() {
}

template<typename T>
tree<T>::const_preorder_iterator::const_preorder_iterator(const tree::node &n) {
}

template<typename T>
bool tree<T>::const_preorder_iterator::operator!=(const tree::const_preorder_iterator &i) const {
}

template<typename T>
bool tree<T>::const_preorder_iterator::operator==(const tree::const_preorder_iterator &i) const {
}

template<typename T>
const T &tree<T>::const_preorder_iterator::operator*() const {
}

template<typename T>
typename tree<T>::const_preorder_iterator &
tree<T>::const_preorder_iterator::operator++() {
}

template<typename T>
typename tree<T>::const_preorder_iterator
tree<T>::cbegin_preorder() const {
}

template<typename T>
typename tree<T>::const_preorder_iterator
tree<T>::cend_preorder() const {
}
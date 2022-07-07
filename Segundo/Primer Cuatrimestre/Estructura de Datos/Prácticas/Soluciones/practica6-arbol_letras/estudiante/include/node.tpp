///////////////////////////////////////////////////////////////////////////////
//                              Public functions                             //
///////////////////////////////////////////////////////////////////////////////


#include <cassert>
#include "tree.h"

template <typename T>
tree<T>::node::node() {
    this->wrap = nullptr;
}

template <typename T>
typename tree<T>::node
&tree<T>::node::parent() const { return this->wrap->father; }

template <typename T>
typename tree<T>::node
&tree<T>::node::left_child() const { return this->wrap->l_child; }

template <typename T>
typename tree<T>::node
&tree<T>::node::right_sibling() const { return this->wrap->r_sibling; }

template <typename T>
T &tree<T>::node::operator*() { return this->wrap->label; }

template <typename T>
const T &tree<T>::node::operator*() const { return this->wrap->label; }

template <typename T>
bool tree<T>::node::operator==(const node &n) const {
    return (this->wrap == n.wrap);
}

template <typename T>
bool tree<T>::node::operator!=(const node &n) const {
    return !this->operator==(n);
}

///////////////////////////////////////////////////////////////////////////////
//                             Private functions                             //
///////////////////////////////////////////////////////////////////////////////

template <typename T>
tree<T>::node::node(const T &label) {
    this->wrap = new nodewrapper(label);
}

template <typename T>
bool tree<T>::node::is_null() const{
    return this->wrap == nullptr;
}

template <typename T>
void tree<T>::node::remove() {
    if (this->wrap != nullptr){
        delete this->wrap;
        this->wrap = nullptr;
    }
}

template <typename T>
void tree<T>::node::set_parent(node n) { this->wrap->father = n; }

template <typename T>
void tree<T>::node::set_left_child(node n) { this->wrap->l_child = n; }

template <typename T>
void tree<T>::node::set_right_sibling(node n) { this->wrap->r_sibling = n; }
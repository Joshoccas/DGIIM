#ifndef __TREE__
#define __TREE__

#include <queue>
#include <string>

/**
 * Class representing a tree with nodes labeled with data of type T.
 * The nodes of the tree lie in dynamic memory
 *
 * @tparam T is the type of the labels in each node. This type has to
 * implement the following operations:
 *
 * - T &operator=(const T & other);
 * - bool &operator==(const T & other);
 * - bool &operator!=(const T & other);
 */
template <typename T>
class tree {
public:
    /**
     * @brief Class representing a node of the tree
     *
     * This class represents a node of the tree. A node is determined
     * by its label and the nodes it is connected to (its parent, its
     * leftmost child, and its righthand sibling)
     *
     */
    class node;

private:

    // Internal representation of the tree
    node root;

    /**
     * @brief Destroy subtree hanging from n
     *
     * @param n Node whose subtree is being destroyed
     */
    void destroy(node &n);

    /**
     * @brief Count the number of nodes given a start node
     *
     * @param node Node to start the count
     * @return number of nodes in subtree
     */
    unsigned int count(const node &n) const;

    /**
     * @brief Equality comparison
     *
     * @param lhs Lefthand node in the comparison
     * @param rhs Righthand node in the comparison
     * @Return True If Subtrees Hanging From both nodes are equal,
     * false otherwise
     */
    bool equals(node &lhs, node &rhs) const;

    /**
     * @brief Copy tree structure from src to dest
     *
     * This method copies the tree structure hanging from a source
     * node into a destiny node
     *
     * @param src
     * @param dest
     */
    void copy(const node &src, node &dest);

    /**
     * @brief Recursive pretty print tree to standard output
     *
     * @param prefix Prefix to print previous to the node label. It is used
     * to properly format the depth of the tree
     * @param curr_node Current node to be printed
     */
    void print(std::ostream &out, const std::string &prefix, const node &curr_node) const;

public:
    /**
     * @brief Default constructor
     *
     * Creates an empty tree
     */
    tree();

    /**
     * @brief Default constructor given root label
     *
     * Creates a tree with root a node labeled with label
     *
     * @param label Value of label for root node
     */
    tree(const T &label);

    /**
     * @brief Copy constructor
     *
     * Creates an exact copy of the other tree
     *
     * @param other tree to be copied
     */
    tree(const tree<T> &other);

    /**
     * @brief Insert a subtree as child of specified node
     *
     * Given a node n and a tree child, inserts child as left child of
     * n. If a previous subtree exists as a child, it becomes the
     * righthand sibling of the new child
     *
     * @param child subtree to be inserted as a child. It is modified
     * @param n Node that inherits the subtree as a child.
     */
    node insert_left_child(node &n, tree<T> &child);

    /**
     * @brief Inserts a node as child using the provided label
     *
     * Given a node n and a label, inserts a child with the label as
     * left child of n. If a previous subtree exists as a child, it
     * becomes the righthand sibling of the new child
     *
     * @param n Node that inherits the subtree as a child.
     * @param label Label for the new node inserted as a child
     */
    node insert_left_child(node &n, const T &label);

    /**
     * @brief Insert a subtree as sibling of the specified node
     *
     * Given a node n and a tree sibling, inserts sibling as right
     * sibling of n. If a previous subtree exists as a sibling, it
     * becomes the righthand sibling of the inserted one
     *
     * @param n Node that receives the subtree as a sibling.
     * @param sibling subtree to be inserted as a sibling.
     */
    node insert_right_sibling(node &n, tree<T> &sibling);

    /**
     * @brief Insert a node as right sibling using the provided label
     *
     * Given a node n and a label, inserts a right sibling with the
     * label for n. If a previous subtree exists as a sibling, it
     * becomes the righthand sibling of the new one
     *
     * @param n Node that inherits the subtree as a sibling
     * @param label Label for the new node inserted as a sibling
     */
    node insert_right_sibling(node &n, const T &label);

    /**
     * @brief Tree destructor
     *
     * Destroys the tree content and frees the allocated memory
     */
    ~tree();

    /**
     * @brief Set the root for an empty tree
     *
     * @param label Value to be assigned to root label
     */
    void set_root(const T & label);

    /**
     * @brief Assignment operator
     *
     * It copies the content of other tree into current tree,
     * destroying the previous content if needed
     *
     * @param other Tree to be copied
     * @return Reference to this in order to chain the operator
     */
    tree<T> & operator=(const tree<T> & other);

    /**
     * @brief Tree root getter
     *
     * Returns the root of the current tree
     *
     * @return Pointer to tree root
     */
    node get_root() const;

    /**
     * @brief Prune the leftmost child of the specified node
     *
     * Removes the leftmost child of the specified node n. If there
     * are remaining children (as left siblings of the pruned node),
     * first sibling is set as current left children. The pruned tree
     * is returned using dest
     *
     * @param n Node to be pruned
     * @param dest Tree to return the pruned subtree. It is modified
     */
    void prune_left_child(node &n, tree<T> & dest);

    /**
     * @brief Prune the righthand sibling of the specified node
     *
     * Removes the righthand sibling of the specified node n. If there
     * are remaining siblings (as left siblings of the pruned node),
     * first sibling is set as current right sibling. The pruned tree
     * is returned using dest
     *
     * @param n Node to be pruned
     * @param dest Tree to return the pruned subtree. It is modified
     */
    void prune_right_sibling(node &n, tree<T> & dest);

    /**
     * @brief Empty the current tree
     *
     * Given a complete tree, it empties its content and frees the
     * memory
     */
    void clear();

    /**
     * @brief Get the number of nodes in a tree
     *
     * @return Number of nodes in the tree
     */
    unsigned int size() const;

    /**
     * @brief Checks if a tree is empty
     *
     * @return true if the tree is empty, false otherwise
     */
    bool empty() const;

    /**
     * @brief Checks if a node is the root of the tree
     *
     * @param v Node to be checked
     * @return true if v is the root of the tree, false otherwise
     */
    bool is_root(const node &v) const { return v == this->get_root(); };

    /**
     * @brief Checks if a node is a leaf of the tree
     *
     * Checks if a certain node is a leaf of the tree. A node is
     * considered a leaf if it has no children
     *
     * @param v node to be checked
     * @return true if the node is a leaf, false otherwise
     */
    bool is_leaf(const node *v) const {return v->left_child()->is_null();};

    /**
     * @brief Equality operator
     *
     * Equality operator overload. Two trees are considered to be
     * equal if they have the same structure, and the labels of the
     * corresponding nodes in each tree are the same.
     *
     * @param other tree to be compared with current
     * @return true if both trees are equal, false otherwise
     */
    bool operator==(const tree<T> & other) const;

    /**
     * @brief Inequality operator
     *
     * Inequality operator overload. Two trees are considered to be
     * equal if they have the same structure, and the labels of the
     * corresponding nodes in each tree are the same.
     *
     * @param other tree to be compared with current
     * @return true if trees are not equal, false otherwise
     */
    bool operator!=(const tree<T> &other) const;

    /**
     * @brief Pretty print tree hanging from n to standard output
     *
     * @param n Node used as starting point for printing
     */
    inline void print(std::ostream &out, const node &n) const { this->print(out, std::string(), n); };

    /**
     * @brief Preety print tree to ostream, starting at root node
     */
    inline void print(std::ostream &out) const { this->print(out, this->root); };

    template <class U>
    friend std::ostream &operator<< (std::ostream &out, const tree<U> &rhs);

    ////////////////////////////////////////////////////////////////////////////
    //                                ITERATOR                                //
    ////////////////////////////////////////////////////////////////////////////

    /**
     * @brief Preorder iterator. Allows to iterate over the tree using preorder
     */
    class preorder_iterator {
    public:
        preorder_iterator();
        preorder_iterator(const node &n);
        bool operator!=(const preorder_iterator & i) const;
        bool operator==(const preorder_iterator & i) const;
        inline int get_level() { return this->level; }
        T & operator*();
        preorder_iterator & operator++();
    private:
        node current;
        int level;
    };

    preorder_iterator begin_preorder();
    preorder_iterator end_preorder();

    /**
     * @brief Constant preorder iterator. Allows to iterate over the tree using preorder
     */
    class const_preorder_iterator {
    public:
        const_preorder_iterator();
        const_preorder_iterator(const node &n);
        bool operator!=(const const_preorder_iterator & i) const;
        bool operator==(const const_preorder_iterator & i) const;
        inline int get_level() { return this->level; }
        const T & operator*() const;
        const_preorder_iterator & operator++();
    private:
        node current;
        int level;
    };

    const_preorder_iterator cbegin_preorder() const;
    const_preorder_iterator cend_preorder() const;


    ////////////////////////////////////////////////////////////////////////////
    //                          Node class declaration                        //
    ////////////////////////////////////////////////////////////////////////////
    class node {
    private:
        /**
         * Node content encapsulation. A node is fully determined by its label, a
         * pointer to its parent node, a pointer to its leftmost child, and a pointer
         * to its righthand sibling. This structure lies in dynamic memory
         */
        struct nodewrapper{
            T label;
            node father;
            node l_child;
            node r_sibling;
            nodewrapper()
                : father(0), l_child(0), r_sibling(0) {}
            nodewrapper(const T &label) { this->label = label; }
        };
        nodewrapper * wrap;
    public:

        /**
         * @brief Default constructor
         */
        inline node();

        /**
         * @brief Return the parent of the current node
         *
         * @return Reference to parent node
         * @pre Current node cannot be null
        */
        inline node & parent() const;

        /**
         * @brief Return the leftmost child of the current node
         *
         * @return Reference to left child node
         * @pre Current node cannot be null
        */
        inline node & left_child() const;

        /**
         * @brief Return the righthand children of the current node
         *
         * @return Reference to right sibling node
         * @pre Current node cannot be null
        */
        inline node & right_sibling() const;

        /**
         * @brief Return the label of the current node
         *
         * @return Label of the current node
         * @pre Current node cannot be null
        */
        inline T &operator*();

        /**
         * @brief Return the label of the current node
         *
         * @return Label of the current node. Cannot be modified
         * @pre Current node cannot be null
        */
        inline const T &operator*() const;

        /**
         * @brief Equalily operator overload
         *
         * @param n Node to be compared with the current one
         * @return true if nodes are equal, false otherwise
        */
        inline bool operator==(const node &n) const;

        /**
         * @brief Inequality operator overload
         *
         * @param n Node to be compared with the current one
         * @return true if nodes are different, false otherwise
        */
        inline bool operator!=(const node &n) const;

        /**
         * @brief Check if the current node is null
         *
         * Checks if the current node is null, i.e., if the internal nodewrapper
         * does not have allocated memory
         *
         * @return True if there is not allocated memory, false otherwise
         */
        bool is_null() const;
    private:
        // Private functions, to be used from tree class

        /**
         * @brief Primitive constructor, given the node label
         *
         * @param e Node label to be assigned
        */
        inline node(const T &e);

        /**
         * @brief Sets the parent node to current node
         *
         * @param n Node to be assigned as parent. Cannot be null
        */
        inline void set_parent(node n);

        /**
         * @brief Sets the leftmost child to a node
         *
         * @param n Node to be assigned as leftmost child. Cannot be null
        */
        inline void set_left_child(node n);

        /**
         * @brief Sets the lefthand sibling to a node
         *
         * @param n Node to be assigned as leftmost child. Cannot be null
        */
        inline void set_right_sibling(node n);

        /**
         * @brief Node deletion
         *
         * Deletes the current node
         */
        void remove();

        friend class tree<T>;
    };
};

#include "tree.tpp"
#include "node.tpp"
#endif

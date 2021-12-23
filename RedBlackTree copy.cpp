#include <iostream>
#include "Utils.hpp"

// namespace ft {
	template < typename T >
	struct Node {
		typedef T			value_type;
		typedef Node<T>*	node_ptr;
		value_type			data;
		node_ptr			parent;
		node_ptr			left;
		node_ptr			right;
		int					color;
	};

	template < typename T, class Compare = ft::less<T>, class Allocator = std::allocator< T > >
	class RedBlackTree {
		public:
			typedef T								value_type;
			typedef Compare							key_compare;
			typedef Node<T>							node_type;
			typedef typename node_type::node_ptr	node_ptr;
			typedef Allocator						allocator_type;
			typedef size_t							size_type;
			typedef typename allocator_type::template rebind<node_type>::other	allocator_node;


		private:
			node_ptr		root;
			node_ptr		TNULL;
			allocator_node	_alloc;
			size_type		_size;
			key_compare		_comp;



			// Preorder
			void preOrderHelper(node_ptr node) {
				if (node != TNULL) {
					std::cout << node->data << " ";
					preOrderHelper(node->left);
					preOrderHelper(node->right);
				}
			}

			// Inorder
			void inOrderHelper(node_ptr node) {
				if (node != TNULL) {
					inOrderHelper(node->left);
					std::cout << node->data << " ";
					inOrderHelper(node->right);
				}
			}

			// Post order
			void postOrderHelper(node_ptr node) {
				if (node != TNULL) {
					postOrderHelper(node->left);
					postOrderHelper(node->right);
					std::cout << node->data << " ";
				}
			}

			node_ptr searchTreeHelper(node_ptr node, value_type key) {
				if (node == TNULL || key == node->data) {
					return node;
				}

				if (key < node->data) {
					return searchTreeHelper(node->left, key);
				}
				return searchTreeHelper(node->right, key);
			}

			// For balancing the tree after deletion
			void deleteFix(node_ptr x) {
				node_ptr s;
				while (x != root && x->color == 0) {
					if (x == x->parent->left) {
						s = x->parent->right;
						if (s->color == 1) {
							s->color = 0;
							x->parent->color = 1;
							leftRotate(x->parent);
							s = x->parent->right;
						}

						if (s->left->color == 0 && s->right->color == 0) {
							s->color = 1;
							x = x->parent;
						} else {
							if (s->right->color == 0) {
								s->left->color = 0;
								s->color = 1;
								rightRotate(s);
								s = x->parent->right;
							}

							s->color = x->parent->color;
							x->parent->color = 0;
							s->right->color = 0;
							leftRotate(x->parent);
							x = root;
						}
					} else {
						s = x->parent->left;
						if (s->color == 1) {
							s->color = 0;
							x->parent->color = 1;
							rightRotate(x->parent);
							s = x->parent->left;
						}

						if (s->right->color == 0 && s->right->color == 0) {
							s->color = 1;
							x = x->parent;
						} else {
							if (s->left->color == 0) {
								s->right->color = 0;
								s->color = 1;
								leftRotate(s);
								s = x->parent->left;
							}

							s->color = x->parent->color;
							x->parent->color = 0;
							s->left->color = 0;
							rightRotate(x->parent);
							x = root;
						}
					}
				}
				x->color = 0;
			}

			void rbTransplant(node_ptr u, node_ptr v) {
				if (u->parent == NULL) {
					root = v;
				} else if (u == u->parent->left) {
					u->parent->left = v;
				} else {
					u->parent->right = v;
				}
				v->parent = u->parent;
			}

			void deleteNodeHelper(node_ptr node, value_type key) {
				node_ptr z = TNULL;
				node_ptr x, y;
				while (node != TNULL) {
					if (node->data == key) {
						z = node;
					}

					if (node->data <= key) {
						node = node->right;
					} else {
						node = node->left;
					}
				}

				if (z == TNULL) {
					std::cout << "Key not found in the tree" << std::endl;
					return;
				}
				if (z->left == TNULL && z->right == TNULL && z == root) {
					_alloc.destroy(z);
					_alloc.deallocate(z, 1);
					root = TNULL;
					return;
				}
				y = z;
				int y_original_color = y->color;
				if (z->left == TNULL) {
					x = z->right;
					rbTransplant(z, z->right);
				} else if (z->right == TNULL) {
					x = z->left;
					rbTransplant(z, z->left);
				} else {
					y = minimum(z->right);
					y_original_color = y->color;
					x = y->right;
					if (y->parent == z) {
						x->parent = y;
					} else {
						rbTransplant(y, y->right);
						y->right = z->right;
						y->right->parent = y;
					}

					rbTransplant(z, y);
					y->left = z->left;
					y->left->parent = y;
					y->color = z->color;
				}
				_alloc.destroy(z);
				_alloc.deallocate(z, 1);
				// delete z;
				if (y_original_color == 0) {
					deleteFix(x);
				}
			}

			// For balancing the tree after insertion
			void insertFix(node_ptr k) {
				node_ptr u;
				while (k->parent->color == 1) {
					if (k->parent == k->parent->parent->right) {
						u = k->parent->parent->left;
						if (u->color == 1) {
							u->color = 0;
							k->parent->color = 0;
							k->parent->parent->color = 1;
							k = k->parent->parent;
						} else {
							if (k == k->parent->left) {
								k = k->parent;
								rightRotate(k);
							}
							k->parent->color = 0;
							k->parent->parent->color = 1;
							leftRotate(k->parent->parent);
						}
					} else {
						u = k->parent->parent->right;

						if (u->color == 1) {
							u->color = 0;
							k->parent->color = 0;
							k->parent->parent->color = 1;
							k = k->parent->parent;
						} else {
							if (k == k->parent->right) {
								k = k->parent;
								leftRotate(k);
							}
							k->parent->color = 0;
							k->parent->parent->color = 1;
							rightRotate(k->parent->parent);
						}
					}
					if (k == root) {
						break;
					}
				}
				root->color = 0;
			}

			void printHelper(node_ptr root, std::string indent, bool last) {
				if (root != TNULL) {
					std::cout << indent;
					if (last) {
						std::cout << "R----";
						indent += "   ";
					} else {
						std::cout << "L----";
						indent += "|  ";
					}

					std::string sColor = root->color ? "RED" : "BLACK";
					std::cout << root->data << "(" << sColor << ")" << std::endl;
					printHelper(root->left, indent, false);
					printHelper(root->right, indent, true);
				}
			}

		public:
			RedBlackTree(const key_compare &comp = key_compare()) : _comp(comp), _alloc(allocator_node())
			{
				TNULL = _alloc.allocate(1);
				TNULL->color = 0;
				TNULL->left = NULL;
				TNULL->right = NULL;
				root = TNULL;
			}
			~RedBlackTree()
			{
				if (root)
					destroy(root);
				_alloc.deallocate(TNULL, 1);
			}
			void destroy(node_ptr x)
			{
				if (x->left != TNULL)
				{
					destroy(x->left);
				}
				if (x->right != TNULL)
				{
					destroy(x->right);
				}
				_alloc.deallocate(x, 1);
			}

			void preorder() {
				preOrderHelper(this->root);
			}

			void inorder() {
				inOrderHelper(this->root);
			}

			void postorder() {
				postOrderHelper(this->root);
			}

			node_ptr searchTree(value_type k) {
				return searchTreeHelper(this->root, k);
			}

			node_ptr minimum(node_ptr node) {
				while (node->left != TNULL) {
					node = node->left;
				}
				return node;
			}

			node_ptr maximum(node_ptr node) {
				while (node->right != TNULL) {
					node = node->right;
				}
				return node;
			}

			node_ptr successor(node_ptr x) {
				if (x->right != TNULL) {
					return minimum(x->right);
				}

				node_ptr y = x->parent;
				while (y && x && y != TNULL && x == y->right) {
					x = y;
					y = y->parent;
				}
				return y;
			}

			node_ptr predecessor(node_ptr x) {
				if (x->left != TNULL) {
					return maximum(x->left);
				}

				node_ptr y = x->parent;
				while (y != TNULL && x == y->left) {
					x = y;
					if (y->parent == NULL)
						return NULL;
					y = y->parent;
				}

				return y;
			}

			void leftRotate(node_ptr x) {
				node_ptr y = x->right;
				x->right = y->left;
				if (y->left != TNULL) {
					y->left->parent = x;
				}
				y->parent = x->parent;
				if (x->parent == NULL) {
					this->root = y;
				} else if (x == x->parent->left) {
					x->parent->left = y;
				} else {
					x->parent->right = y;
				}
				y->left = x;
				x->parent = y;
			}

			void rightRotate(node_ptr x) {
				node_ptr y = x->left;
				x->left = y->right;
				if (y->right != TNULL) {
					y->right->parent = x;
				}
				y->parent = x->parent;
				if (x->parent == NULL) {
					this->root = y;
				} else if (x == x->parent->right) {
					x->parent->right = y;
				} else {
					x->parent->left = y;
				}
				y->right = x;
				x->parent = y;
			}

			// Inserting a node
			void insert(value_type key) {
				node_ptr node = _alloc.allocate(1);

				node->parent = NULL;
				node->data = key;
				node->left = TNULL;
				node->right = TNULL;
				node->color = 1;
				// _alloc.construct(&node, tmp);
				if (!root)
				{
					TNULL = _alloc.allocate(1);
					TNULL->color = 0;
					TNULL->left = NULL;
					TNULL->right = NULL;
					root = TNULL;
					return;
				}

				node_ptr y = NULL;
				node_ptr x = this->root;

				while (x != TNULL) {

					y = x;
					if (node->data < x->data) {
						x = x->left;
					} else {
						x = x->right;
					}
				}

				node->parent = y;
				if (y == NULL) {
					root = node;
				} else if (node->data < y->data) {
					y->left = node;
				} else {
					y->right = node;
				}

				if (node->parent == NULL) {
					node->color = 0;
					return;
				}

				if (node->parent->parent == NULL) {
					return;
				}

				insertFix(node);
			}

			node_ptr getRoot() {
				return this->root;
			}

			void deleteNode(value_type data) {
				deleteNodeHelper(this->root, data);
			}

			void printTree() {
				if (root) {
					printHelper(this->root, "", true);
				}
			}
	};
// }

int main()
{
    RedBlackTree<int> bst;
    bst.insert(4);
    bst.insert(5);
    bst.insert(1);
    bst.insert(42);



    bst.printTree();

    RedBlackTree<int>::node_ptr min = bst.minimum(bst.getRoot());
    while (min != NULL)
    {
        std::cout << min->data << std::endl;
        min = bst.successor(min);
    }

    RedBlackTree<int>::node_ptr max = bst.maximum(bst.getRoot());
    while (max != NULL)
    {
        std::cout << max->data << std::endl;
        max = bst.predecessor(max);
    }

    return 0;
}




#ifndef _STK_RBTREE_IMPLEMENTATION_CXX_H
#define _STK_RBTREE_IMPLEMENTATION_CXX_H


#include <Color.h>

namespace stk {

		template<typename T>
		struct RBNode
		{
			T data_;
			Color color_;
			RBNode* left_;
			RBNode* right_;
			RBNode* parent_;

			RBNode(const T& data) :
				data_(data),
				color_(Color::RED),
				left_(nullptr),
				right_(nullptr),
				parent_(nullptr) {}
		};

		template<typename T>
		class RBTree
		{
		public:
			RBTree();
			~RBTree();

			void insert(const T& value);
			void remove(const T& value);
			bool find(const T& value) const;
			bool isEmpty() const;
			void inorderPrint() const;

		private:
			void leftRotate(RBNode<T>* x);
			void rightRotate(RBNode<T>* y);
			void fixInsert(RBNode<T>* z);
			void fixDelete(RBNode<T>* x);
			void transplant(RBNode<T>* u, RBNode<T>* v);
			RBNode<T>* minimum(RBNode<T>* x) const;
			RBNode<T>* maximum(RBNode<T>* x) const;
			RBNode<T>* searchNode(const T& value) const;
			void clearHelper(RBNode<T>* node);
			void inorderHelper(RBNode<T>* node) const;

		private:
			RBNode<T>* root_;
			RBNode<T>* nil_;

		};

} 

#include "rbtree.tcc"

#endif 

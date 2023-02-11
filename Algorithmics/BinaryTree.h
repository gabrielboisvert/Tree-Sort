#pragma once
#include <cassert>

#include "SpyAllocator.h"

#include <stdexcept>

#include <iostream>

namespace BST
{
	template <typename T>
	using actual_type = std::remove_cv_t<std::remove_reference_t<T>>;

	template <typename T, typename U>
	using is_same_type = std::is_same<actual_type<T>, actual_type<U>>;

	template <typename K, typename V>
	struct TreeNode
	{
		TreeNode() = default;

		template <typename VFR>
		TreeNode(TreeNode* /*parent*/, const K& key, VFR&& val)
			: Key(key),
			Value(std::forward<VFR&&>(val))
		{
			static_assert(BST::is_same_type<VFR, V>());
		}

		TreeNode& operator=(const TreeNode& rhs)
		{
			if (this == &rhs)
				return *this;

			Key = rhs.Key;
			Value = rhs.Value;
			Left = rhs.Left;
			Right = rhs.Right;

			return *this;
		}

		TreeNode& operator=(TreeNode&& rhs)
		{
			if (this == &rhs)
				return *this;

			Key = std::move(rhs.Key);
			Value = std::move(rhs.Value);
			Left = rhs.Left;
			Right = rhs.Right;

			return *this;
		}


		virtual ~TreeNode()
		{}

		K	Key;
		V	Value;

		TreeNode* Left = nullptr;
		TreeNode* Right = nullptr;
	};



template <typename K, typename V, typename Node = TreeNode<K, V>, typename Allocator = SpyAllocator<Node>>
class BinaryTree
{
public:

	using NodeType = Node;

	virtual ~BinaryTree()
	{
		this->Clear_r(this->Root);
	}


	auto Size() const
	{
		return mSize;
	}


	Node* AddNode(const K& key, V const& value)
	{
		this->Root = this->InsertNode_r(this->Root, key, value);
		return this->Root;
	}

	Node* Search(const K& key)
	{
		return this->Search_r(this->Root, key);
	}

	Node* RemoveNode(const K& key)
	{
		this->Root = this->Remove_r(this->Root, key);
		return this->Root;
	}

	V&	operator [](const K& key)
	{
		Node* node = this->Search(key);
		if (node == nullptr)
		{
			this->AddNode(key, V());
			return this->Search(key)->Value;
		}
		return node->Value;
	}

	void Display()
	{
		this->Display_r(this->Root);
	}

	template <typename VFR>
	Node* SetValue(const K& key, VFR&& val)
	{
		Node* n = this->Search(key);
		if (n == nullptr)
			throw std::logic_error("This key is not in the tree");
		n->Value = val;
		return n;
	}

	Node* SetValue(const K& key, V&& val)
	{
		Node* n = this->Search(key);
		if (n == nullptr)
			throw std::logic_error("This key is not in the tree");
		n->Value = std::move(val);
		return n;
	}

	Node const*	GetRoot() const
	{
		return Root;
	}




protected:
	void Clear_r(Node* root)
	{
		if (root == nullptr)
			return;

		if (root->Left != nullptr)
			this->Clear_r(root->Left);

		if (root->Right != nullptr)
			this->Clear_r(root->Right);

		DeleteNode(root);
	}

	Node* FindPredecessor(Node* root)
	{
		if (root == nullptr)
			return nullptr;

		Node* it = this->Root;
		while (it->Left != root || it->Right != root)
		{
			if (it->Left == root || it->Right == root)
				break;

			if (it->Key > root->Key)
				it = it->Left;
			else
				it = it->Right;
		}
		return it;
	}

	Node* FindSuccessor(Node* root)
	{
		Node* current = root;
		while (current && current->Right != nullptr)
			current = current->Right;
		return current;
	}

	virtual Node* InsertRoot(K const& key, V const& val)
	{
		this->mSize++;
		return this->NewNode(nullptr, key, val);
	}

	virtual Node* InsertNode_r(Node* parent, const K& key, V const& val)
	{
		if (parent == nullptr)
		{
			this->mSize++;
			return this->NewNode(parent, key, val);
		}

		if (key < parent->Key)
			parent->Left = this->InsertNode_r(parent->Left, key, val);
		else if (key > parent->Key)
			parent->Right = this->InsertNode_r(parent->Right, key, val);
		else
			throw std::logic_error("This key is already in the tree");

		return parent;
	}

	virtual Node* RebalancePostInsertion(Node* parent, const K& insertedKey)
	{
		// TODO
		return nullptr;
	}

	virtual Node* RebalancePostDeletion(Node* parent)
	{
		// TODO
		return nullptr;
	}

	virtual Node* Remove_r(Node* root, const K& key)
	{
		if (root == nullptr)
			throw std::logic_error("This key is not in the tree");

		if (key < root->Key)
			root->Left = this->Remove_r(root->Left, key);
		else if (key > root->Key)
			root->Right = this->Remove_r(root->Right, key);
		else
		{
			// Case 1, has no child
			if (root->Left == nullptr && root->Right == nullptr)
			{
				this->mSize--;
				this->DeleteNode(root);
				return nullptr;
			}
			// case 2 with only one child
			else if (root->Left == nullptr)
			{
				this->mSize--;
				Node* right = root->Right;
				root->Right = nullptr;
				this->DeleteNode(root);
				return right;
			}
			// case 2 with only one child
			else if (root->Right == nullptr)
			{
				this->mSize--;
				Node* left = root->Left;
				root->Left = nullptr;
				this->DeleteNode(root);
				return left;
			}

			Node* successor = this->FindSuccessor(root->Left);
			root->Key = std::move(successor->Key);
			root->Value = std::move(successor->Value);
			root->Left = this->Remove_r(root->Left, successor->Key);
		}
		
		return root;
	}


	Node* Search_r(Node* root, const K& key)
	{
		if (root == nullptr)
			return nullptr;

		if (root->Key == key)
			return root;

		return key < root->Key ? this->Search_r(root->Left, key) : this->Search_r(root->Right, key);
	}

	//Utility
	#define DEFAULT_SPACE 5
	virtual void Display_r(Node* current, size_t space = 0)
	{
		if (current == nullptr)
			return;

		// Increase distance between levels
		space += DEFAULT_SPACE;

		// Print right
		Display_r(current->Right, space);

		// Print data
		for (size_t i = DEFAULT_SPACE; i < space; i++)
			std::cout << " ";
		std::cout << current->Key << "\n";

		// Print left
		Display_r(current->Left, space);
	}

	/*
	CreateNewNode allocates a new Node and passes key and val to the Node constructor using placement new.
	Throws std::bad_alloc if the allocation failed.
	*/
	Node* NewNode(Node* parent, const K& key, V const& val)
	{
		Node* newNode = Allocator().allocate(1);
		if (newNode == nullptr)
		{
			throw std::bad_alloc();
		}

		new (newNode) Node(parent, key, val);

		return newNode;
	}

	void DeleteNode(Node* deletedNode)
	{
		assert(deletedNode != nullptr);

		deletedNode->~Node();
		Allocator().deallocate(deletedNode, 1);
		deletedNode = nullptr;
	}

	Node*			Root = nullptr;
	size_t			mSize = 0;
};



}

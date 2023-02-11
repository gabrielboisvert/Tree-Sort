#pragma once
#include "BinaryTree.h"

#define REDBLACK_IMPLEMENTED 1

namespace BST
{
	enum class NodeColor : char
	{
		BLACK = 0,
		RED
	};

	template <typename K, typename V>
	struct RBTreeNode
	{
		template <typename VFR>
		RBTreeNode(RBTreeNode* parent, const K& key, VFR&& val) :
			Key(key),
			Value(std::forward<VFR&&>(val)),
			Parent(parent)
		{
		}


		void FlipColors()
		{
			this->Color = this->Color == NodeColor::BLACK ? NodeColor::RED : NodeColor::BLACK;
		}


		void FlipColorsForDeletion()
		{
			this->Color = this->Color == NodeColor::BLACK;
		}


		RBTreeNode* Parent = nullptr;
		NodeColor	Color{ NodeColor::RED };

		K	Key;
		V	Value;
		RBTreeNode* Left = nullptr;
		RBTreeNode* Right = nullptr;
	};

	template <typename K, typename V>
	class RedBlackTree :
		public BinaryTree<K, V, RBTreeNode<K, V>>
	{
	public:
		using Node = RBTreeNode<K, V>;


	protected:

		static bool	IsRed(Node* node)
		{
			return (node != nullptr && node->Color == NodeColor::RED);
		}

		Node* InsertRoot(K const& key, V const& val) override
		{
			this->mSize++;
			return this->NewNode(nullptr, key, val);
		}

		void Transplant(Node* deletedNode, Node* transplanted)
		{
			if (deletedNode->Parent == nullptr)
				this->Root = transplanted;
			else if (deletedNode == deletedNode->Parent->Left)
				deletedNode->Parent->Left = transplanted;
			else
				deletedNode->Parent->Right = transplanted;
			transplanted->Parent = deletedNode->Parent;
		}

		Node* GetGrandFather(Node* child)
		{
			if (child == nullptr)
				return child;
			
			if (child->Parent == nullptr)
				return child->Parent;
			
			return child->Parent->Parent;
		}

		Node* GetUncle(Node* child)
		{
			Node* grandFather = this->GetGrandFather(child);
			if (grandFather == nullptr)
				return grandFather;
			return grandFather->Left == child->Parent? grandFather->Right: grandFather->Left;
		}

		Node* GetSibling(Node* child)
		{
			if (child->Parent == nullptr)
				return child->Parent;
			return child->Parent->Left == child ? child->Parent->Right : child->Parent->Left;
		}

		Node* MoveRedLeft(Node* root)
		{
			// TODO

			return root;
		}

		Node* MoveRedRight(Node* root)
		{
			// TODO

			return root;
		}

		Node* Balance(Node* root)
		{
			// Its root
			if (root->Parent == nullptr)
				root->Color = NodeColor::BLACK;
			// Parent is black
			else if (root->Parent != nullptr && root->Parent->Color == NodeColor::BLACK)
				return root;
			// Uncle is red
			else if (this->GetUncle(root) != nullptr && this->GetUncle(root)->Color == NodeColor::RED)
			{
				root->Parent->Color = NodeColor::BLACK;
				this->GetUncle(root)->Color = NodeColor::BLACK;

				Node* grand_pere = this->GetGrandFather(root);
				grand_pere->Color = NodeColor::RED;
				Balance(grand_pere);
			}
			// Uncle is black
			else
				InsertCase4(root);

			return root;
		}

		//Node* RemoveMin(Node* root)
		//{
		//	// TODO
		//	return Balance(root);
		//}

		Node* RebalancePostDeletion(Node* rebalanced) override
		{


			return rebalanced;
		}

		Node* Remove_r(Node* root, const K& key)
		{
			if (root == nullptr)
				throw std::logic_error("This key is not in the tree");

			if (key < root->Key)
				root->Left = this->Remove_r(root->Left, key);
			else if (key > root->Key)
				root->Right = this->Remove_r(root->Right, key);
			else
			{
				// Case 1, has no child and is red
				if (root->Left == nullptr && root->Right == nullptr)
				{
					return removeCase1(root);
				}
				// case 2 with only one child
				else if (root->Left == nullptr)
				{
					return removeCase2Right(root);
				}
				// case 2 with only one child
				else if (root->Right == nullptr)
				{
					return removeCase2Left(root);
				}

				Node* successor = this->FindSuccessor(root->Left);
				root->Key = std::move(successor->Key);
				root->Value = std::move(successor->Value);
				root->Left = this->Remove_r(root->Left, successor->Key);
			}

			return root;
		}

		Node* removeCase1(Node*& root)
		{
			this->mSize--;
			this->DeleteNode(root);
			return nullptr;
		}

		Node* removeCase2Left(Node*& root)
		{
			this->mSize--;
			Node* left = root->Left;
			root->Left = nullptr;
			this->DeleteNode(root);
			return left;
		}

		Node* removeCase2Right(Node*& root)
		{
			this->mSize--;
			Node* right = root->Right;
			root->Right = nullptr;
			this->DeleteNode(root);
			return right;
		}

		Node* RebalancePostInsertion(Node* root, const K& insertedKey) override
		{
			return root;
		}

		void InsertCase4(Node* node)
		{
			Node* pere = node->Parent;
			Node* grand_pere = this->GetGrandFather(node);

			if (grand_pere->Left != nullptr && node == grand_pere->Left->Right)
			{
				LeftRotate(pere);
				node = node->Left;
			}

			else if (grand_pere->Right != nullptr && node == grand_pere->Right->Left)
			{
				RightRotate(pere);
				node = node->Right;
			}

			InsertCase5(node);
		}

		void InsertCase5(Node* node)
		{
			Node* pere = node->Parent;
			Node* grand_pere = this->GetGrandFather(node);

			if (node == pere->Left)
				RightRotate(grand_pere);
			else
				LeftRotate(grand_pere);

			pere->Color = NodeColor::BLACK;
			grand_pere->Color = NodeColor::RED;
		}

		void LeftRotate(Node* node)
		{
			Node* right = node->Right;

			node->Right = right->Left;
			if (right->Left != nullptr)
				right->Left->Parent = node;

			right->Parent = node->Parent;

			if (node->Parent == nullptr)
				this->Root = right;
			else if (node == node->Parent->Left)
				node->Parent->Left = right;
			else
				node->Parent->Right = right;

			right->Left = node;
			node->Parent = right;
		}

		void RightRotate(Node* node)
		{
			Node* left = node->Left;

			node->Left = left->Right;
			if (left->Right != nullptr)
				left->Right->Parent = node;

			left->Parent = node->Parent;

			if (node->Parent == nullptr)
				this->Root = left;
			else if (node == node->Parent->Right)
				node->Parent->Right = left;
			else
				node->Parent->Left = left;

			left->Right = node;
			node->Parent = left;
		}

		Node* InsertNode_r(Node* parent, const K& key, V const& val) override
		{
			Node* node = InsertNode(parent, key, val);

			Balance(node);

			parent = node;

			while (parent->Parent != nullptr)
				parent = parent->Parent;

			return parent;
		}

		Node* InsertNode(Node* parent, const K& key, V const& val)
		{
			if (parent == nullptr)
			{
				this->mSize++;
				return this->NewNode(parent, key, val);
			}

			if (key < parent->Key)
			{
				if (parent->Left == nullptr)
				{
					this->mSize++;
					return parent->Left = this->NewNode(parent, key, val);
				}
				else
					return InsertNode(parent->Left, key, val);
			}
			else if (key > parent->Key)
			{
				if (parent->Right == nullptr)
				{
					this->mSize++;
					return parent->Right = this->NewNode(parent, key, val);
				}
				else
					return InsertNode(parent->Right, key, val);
			}
			else
				throw std::logic_error("This key is already in the tree");

			return parent;
		}

		//Utility
		#define DEFAULT_SPACE 5
		void Display_r(Node* current, size_t space = 0) override
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

			if (current->Color == NodeColor::RED)
				std::cout << "\033[1;31m" + std::to_string(current->Key) + "\033[0m" << "\n";
			else
				std::cout << current->Key << "\n";

			// Print left
			Display_r(current->Left, space);
		}

	private:




	};



}

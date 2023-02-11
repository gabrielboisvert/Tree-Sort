#pragma once
#include "BinaryTree.h"
#include <cstdlib>

#define AVL_IMPLEMENTED 1

namespace BST
{
	template <typename K, typename V>
	struct AVLTreeNode
	{
		template <typename VFR>
		AVLTreeNode(AVLTreeNode* parent, const K& key, VFR&& val) :
			Key(key), Value(std::forward<VFR&&>(val))
		{}

		K	Key;
		V	Value;

		AVLTreeNode*	Left = nullptr;
		AVLTreeNode*	Right = nullptr;
		unsigned int	Height{ 1 };
	};


	template <typename T, typename U>
	T*	As(U* Node)
	{
		return static_cast<T*>(Node);
	}

	template <typename K, typename V>
	class AVLTree : public BinaryTree<K, V, AVLTreeNode<K,V>>
	{
	public:

		using Node = AVLTreeNode<K, V>;

		uint32_t GetHeight() const
		{
			return this->GetHeight(this->Root);
		}

		uint32_t GetHeight(Node* root) const
		{
			if (root == nullptr)
				return 0;
			
			int lDepth = this->GetHeight(root->Left);
			int rDepth = this->GetHeight(root->Right);

			if (lDepth > rDepth)
				return(lDepth + GetNodeHeight(root));
			else
				return(rDepth + GetNodeHeight(root));
		}


	protected:
		Node* RebalancePostDeletion(Node* root) override
		{
			// Left Left Case
			if (this->GetBalanceFactor(root) > 1 && this->GetBalanceFactor(root->Left) >= 0)
				return this->RightRotate(root);

			// Left Right Case
			if (this->GetBalanceFactor(root) > 1 && this->GetBalanceFactor(root->Left) < 0)
			{
				root->Left = this->LeftRotate(root->Left);
				return this->RightRotate(root);
			}

			// Right Right Case
			if (this->GetBalanceFactor(root) < -1 && this->GetBalanceFactor(root->Right) <= 0)
				return this->LeftRotate(root);

			// Right Left Case
			if (this->GetBalanceFactor(root) < -1 && this->GetBalanceFactor(root->Right) > 0)
			{
				root->Right = this->RightRotate(root->Right);
				return this->LeftRotate(root);
			}

			return root;
		}

		Node* RebalancePostInsertion(Node* root, const K& insertedKey) override
		{
			// Left Left Case
			if (this->GetBalanceFactor(root) > 1 && insertedKey < root->Left->Key)
				return this->RightRotate(root);

			// Right Right Case
			if (this->GetBalanceFactor(root) < -1 && insertedKey > root->Right->Key)
				return this->LeftRotate(root);

			// Left Right Case
			if (this->GetBalanceFactor(root) > 1 && insertedKey > root->Left->Key)
			{
				root->Left = this->LeftRotate(root->Left);
				return this->RightRotate(root);
			}

			// Right Left Case
			if (this->GetBalanceFactor(root) < -1 && insertedKey < root->Right->Key)
			{
				root->Right = RightRotate(root->Right);
				return LeftRotate(root);
			}

			return root;
		}

		Node* RightRotate(Node* root)
		{
			Node* left = root->Left;
			Node* right = left->Right;

			left->Right = root;
			root->Left = right;

			return left;
		}

		Node* LeftRotate(Node* root)
		{
			Node* right = root->Right;
			Node* left = right->Left;

			right->Left = root;
			root->Right = left;

			return right;
		}

		Node* InsertNode_r(Node* parent, const K& key, V const& val) override
		{
			if (parent == nullptr)
			{
				this->mSize++;
				return this->NewNode(parent, key, val);
			}

			if (key < parent->Key)
				parent->Left = InsertNode_r(parent->Left, key, val);
			else if (key > parent->Key)
				parent->Right = InsertNode_r(parent->Right, key, val);
			else
				throw std::logic_error("This key is already in the tree");

			parent = this->RebalancePostInsertion(parent, key);

			return parent;
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

			root = this->RebalancePostDeletion(root);

			return root;
		}

	private:
		static int GetNodeHeight(Node* node)
		{
			if (node == nullptr)
				return 0;

			return (node)->Height;
		}

		int GetBalanceFactor(Node* root)
		{
			if (root == nullptr)
				return 0;

			return this->GetHeight(root->Left) - this->GetHeight(root->Right);
		}
	};
}


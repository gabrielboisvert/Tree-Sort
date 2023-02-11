
#include "pch.h"
#include <iostream>
#include <string>

#include "catch.hpp"

#include "SpyAllocator.h"

#include "Foo.h"
#include "BinaryTree.h"
#include "AVLTree.h"
#include "RedBlackTree.h"

#define DO(inst) std::printf("\n" #inst "\n"); inst

using Catch::Matchers::Exception::ExceptionMessageMatcher;



TEST_CASE("Test Unbalanced Binary Tree", "[Algorithmics]")
{

#define UNBALANCED_ADD_IMPLEMENTED 1

#if UNBALANCED_ADD_IMPLEMENTED
	{
		std::printf("===========Test Unbalanced Binary Tree Insertion============\n");

		using UnbalancedTree = BST::BinaryTree<int, Foo>;

		UnbalancedTree myTree;
		REQUIRE(myTree.Size() == 0);

		DO(UnbalancedTree::NodeType * Node = myTree.AddNode(36, Foo()));
		REQUIRE(myTree.Size() == 1);
		REQUIRE(myTree.GetRoot() == Node);
		REQUIRE(myTree.GetRoot()->Left == nullptr);
		REQUIRE(myTree.GetRoot()->Right == nullptr);

		Foo johnCarmaFoo(55);
		REQUIRE(johnCarmaFoo.MyCount() == 55);
		DO(Node = myTree.AddNode(55, johnCarmaFoo));
		REQUIRE(myTree.Size() == 2);
		REQUIRE(Node->Right->Value.MyCount() == 56);

		const Foo adaLovelaFoo(28);
		REQUIRE(adaLovelaFoo.MyCount() == 28);
		DO(Node = myTree.AddNode(28, adaLovelaFoo));
		REQUIRE(Node->Left->Value.MyCount() == 29);
		REQUIRE(myTree.Size() == 3);

		Foo margaretHamilFoo(32);
		DO(myTree.AddNode(32, std::move(margaretHamilFoo)));
		REQUIRE(myTree.Size() == 4);
		REQUIRE(Node->Left->Right->Value.MyCount() == 33);
		REQUIRE(margaretHamilFoo.MyCount() == 32);

		Foo bjarneStrousFoo(66);
		Foo&& movedBjarne = std::move(bjarneStrousFoo);
		DO(Node = myTree.AddNode(66, movedBjarne));
		REQUIRE(myTree.Size() == 5);
		REQUIRE(Node->Right->Right->Value.MyCount() == 67);
		REQUIRE(bjarneStrousFoo.MyCount() == 66);

		// try to add Bjarne again, should throw an exception.
		std::printf("\nNode = myTree.Add(66, bjarneStrousFoo))\n");

		REQUIRE_THROWS_MATCHES(
			myTree.AddNode(66, bjarneStrousFoo),
			std::logic_error,
			ExceptionMessageMatcher("This key is already in the tree")
		);

		REQUIRE(myTree.Size() == 5);
		REQUIRE(bjarneStrousFoo.MyCount() == 66);

#else

	FAIL("Unbalanced Binary Tree Add (STEP 1.1) Unimplemented !");

#endif

#define UNBALANCED_SEARCH_IMPLEMENTED 1

#if UNBALANCED_SEARCH_IMPLEMENTED
	
	// operator[]
	myTree[70] = Foo(); // creates a new node

	Node = myTree.Search(70);
	REQUIRE(Node != nullptr);
	REQUIRE(Node->Left == nullptr);
	REQUIRE(Node->Right == nullptr);
	REQUIRE((Node->Key == 70 && Node->Value.MyCount() == 1));
	REQUIRE(myTree.GetRoot()->Right->Right->Right == Node);

	Foo& myFoo = myTree[70]; // accesses the existing node
	myFoo = Foo(700);
	REQUIRE((Node->Key == 70 && Node->Value.MyCount() == 700));

	const Foo donaldKnuFoo(1337);
	myFoo = donaldKnuFoo;
	REQUIRE(Node->Value.MyCount() == 1337);

	// Search for a key that does not exist
	DO(Node = myTree.Search(0xBAADF00D));
	REQUIRE(Node == nullptr);



	// Test SetValue
	Foo brianKerniFoo(42);
	Node = myTree.SetValue(70, brianKerniFoo);
	REQUIRE(Node != nullptr);
	REQUIRE(Node->Value == brianKerniFoo);
	Node = myTree.SetValue(70, Foo(64));
	REQUIRE(Node != nullptr);
	REQUIRE(Node->Value == Foo(64));

	REQUIRE_THROWS_MATCHES(
		myTree.SetValue(0xDEADBEEF, Foo(64)),
		std::logic_error,
		ExceptionMessageMatcher("This key is not in the tree")
	);

	// Verifying the tree is unbalanced
	DO(Node = myTree.AddNode(71, Foo()));
	REQUIRE(Node != nullptr);
	// get the root
	DO(Node = myTree.Search(36));
	REQUIRE(Node != nullptr);
	// Verifying the tree structure
	REQUIRE(Node->Left->Key == 28);
	REQUIRE(Node->Left->Left == nullptr);

	REQUIRE(Node->Left->Right->Key == 32);
	REQUIRE(Node->Left->Right->Left == nullptr);
	REQUIRE(Node->Left->Right->Right == nullptr);

	REQUIRE(Node->Right->Key == 55);
	REQUIRE(Node->Right->Left == nullptr);

	REQUIRE(Node->Right->Right->Key == 66);
	REQUIRE(Node->Right->Right->Left == nullptr);
	REQUIRE(Node->Right->Right->Right->Key == 70);

	REQUIRE(Node->Right->Right->Right->Right->Key == 71);
	REQUIRE(Node->Right->Right->Right->Right->Left == nullptr);
	REQUIRE(Node->Right->Right->Right->Right->Right == nullptr);
	}
CHECK(g_memorySpy.CheckLeaks());
#else

	FAIL("Unbalanced Binary Tree Search  (STEP 1.2) Unimplemented !");

#endif

}


TEST_CASE("Test Unbalanced Binary Tree Remove", "[Algorithmics]")
{
#define UNBALANCED_REMOVE_IMPLEMENTED 1
#if UNBALANCED_REMOVE_IMPLEMENTED
	{
		std::printf("===========Test Unbalanced Binary Tree Remove============\n");

		// Removing
		using UnbalancedTree = BST::BinaryTree<int, int>;

		UnbalancedTree tree;
		tree.AddNode(10, 1);
		tree.AddNode(9, 1);
		tree.AddNode(3, 1);
		tree.AddNode(2, 1);
		tree.AddNode(14, 1);
		tree.AddNode(16, 1);
		REQUIRE(tree.Size() == 6);

		bool removed = false;

		// Testing remove of a leaf node to the left
		DO(removed = tree.RemoveNode(2));
		REQUIRE(tree.Search(2) == nullptr);
		REQUIRE(tree.Size() == 5);

		// Testing remove of a leaf node to the right
		DO(removed = tree.RemoveNode(16));
		REQUIRE(tree.Search(16) == nullptr);
		REQUIRE(tree.Size() == 4);


		// testing a remove of unexisting key to the left
		REQUIRE_THROWS_MATCHES(
			tree.RemoveNode((int)0xBAAAAAAD),
			std::logic_error,
			ExceptionMessageMatcher("This key is not in the tree")
		);
		REQUIRE(tree.Size() == 4);

		// testing a remove of unexisting key to the right
		REQUIRE_THROWS_MATCHES(
			tree.RemoveNode((int)0xBADBAD),
			std::logic_error,
			ExceptionMessageMatcher("This key is not in the tree")
		);
		REQUIRE(tree.Size() == 4);

		tree.AddNode(1, int());
		tree.AddNode(7, int());
		tree.AddNode(8, int());
		tree.AddNode(0, int());
		tree.AddNode(20, int());
		tree.AddNode(32, int());
		tree.AddNode(21, int());
		tree.AddNode(18, int());
		tree.AddNode(15, int());
		tree.AddNode(16, int());
		tree.AddNode(17, int());
		REQUIRE(tree.Size() == 15);

		// testing a remove of node with only a left child
		auto* nodeToRemove = tree.Search(1);
		REQUIRE(nodeToRemove != nullptr);
		REQUIRE(nodeToRemove->Left != nullptr);
		REQUIRE(nodeToRemove->Left->Key == 0);
		REQUIRE(nodeToRemove->Right == nullptr);

		DO(removed = tree.RemoveNode(nodeToRemove->Key));
		REQUIRE(tree.Search(1) == nullptr);

		auto* nodeThree = tree.Search(3);
		REQUIRE(nodeThree != nullptr);
		REQUIRE(nodeThree->Left != nullptr);
		REQUIRE(nodeThree->Left->Key == 0);

		// testing a remove of node with only a right child
		nodeToRemove = tree.Search(7);
		REQUIRE(nodeToRemove != nullptr);
		REQUIRE(nodeToRemove->Left == nullptr);
		REQUIRE(nodeToRemove->Right != nullptr);
		REQUIRE(nodeToRemove->Right->Key == 8);

		DO(removed = tree.RemoveNode(nodeToRemove->Key));
		REQUIRE(tree.Search(7) == nullptr);

		REQUIRE(nodeThree->Right != nullptr);
		REQUIRE(nodeThree->Right->Key == 8);

		// testing a remove of node with both children
		auto* node = tree.AddNode(19, int());
		node = tree.Search(19);
		REQUIRE(node != nullptr);
		REQUIRE(node->Left == nullptr);
		REQUIRE(node->Right == nullptr);

		nodeToRemove = tree.Search(18);
		REQUIRE(nodeToRemove->Right == node);
		DO(removed = tree.RemoveNode(nodeToRemove->Key));
		REQUIRE(tree.Search(18) == nullptr);
		node = tree.Search(19);
		REQUIRE((node->Left == nullptr && node->Right == nullptr));
		node = tree.Search(17);
		REQUIRE((node->Left->Key == 15 && node->Right->Key == 19));
		node = tree.Search(16);
		REQUIRE((node->Left == nullptr && node->Right == nullptr));

		REQUIRE(tree.Size() == 13);

		// testing removing the root
		DO(removed = tree.RemoveNode(10));
		REQUIRE(tree.Search(10) == nullptr);
		REQUIRE(tree.Size() == 12);

		// testing removing with only a root
		UnbalancedTree treeSingleNode;
		treeSingleNode.AddNode(42, int());
		REQUIRE(treeSingleNode.Size() == 1);
		DO(treeSingleNode.RemoveNode(42));
		REQUIRE(treeSingleNode.Search(42) == nullptr);
		REQUIRE(treeSingleNode.Size() == 0);

		// testing removing on empty tree
		REQUIRE_THROWS_MATCHES(
			tree.RemoveNode(42),
			std::logic_error,
			ExceptionMessageMatcher("This key is not in the tree")
		);

		REQUIRE(treeSingleNode.Size() == 0);

	}

	g_memorySpy.CheckLeaks();
#else

	FAIL("Unbalanced Binary Tree Remove (STEP 1.3) Unimplemented !");

#endif
}


// My own test

//TEST_CASE("custom Test Unbalanced Binary Tree Remove", "[Algorithmics]")
//{
//	std::printf("===========Test Unbalanced Binary Tree Remove root============\n");
//	
//	{
//		// Removing with both side
//		using UnbalancedTree = BST::BinaryTree<int, int>;
//
//		UnbalancedTree tree;
//		DO(tree.AddNode(15, 1));
//		DO(tree.AddNode(13, 1));
//		DO(tree.AddNode(12, 1));
//		DO(tree.AddNode(14, 1));
//
//		DO(tree.RemoveNode(13));
//
//		REQUIRE(tree.GetRoot()->Key == 15);
//		REQUIRE(tree.GetRoot()->Left->Key == 12);
//
//		REQUIRE(tree.GetRoot()->Left->Left == nullptr);
//		REQUIRE(tree.GetRoot()->Left->Right->Key == 14);
//	}
//
//	{
//		// Removing with both side
//		using UnbalancedTree = BST::BinaryTree<int, int>;
//
//		UnbalancedTree tree;
//		DO(tree.AddNode(15, 1));
//		DO(tree.AddNode(13, 1));
//		DO(tree.AddNode(14, 1));
//		DO(tree.AddNode(10, 1));
//		DO(tree.AddNode(12, 1));
//
//		DO(tree.RemoveNode(13));
//
//		REQUIRE(tree.GetRoot()->Key == 15);
//		REQUIRE(tree.GetRoot()->Left->Key == 12);
//
//		REQUIRE(tree.GetRoot()->Left->Left->Key == 10);
//		REQUIRE(tree.GetRoot()->Left->Right->Key == 14);
//	}
//
//	{
//		// Removing only left
//		using UnbalancedTree = BST::BinaryTree<int, int>;
//
//		UnbalancedTree tree;
//		DO(tree.AddNode(10, 1));
//		DO(tree.AddNode(9, 1));
//		DO(tree.AddNode(3, 1));
//		DO(tree.AddNode(1, 1));
//		DO(tree.AddNode(2, 1));
//		DO(tree.AddNode(4, 1));
//
//		DO(tree.RemoveNode(10));
//		REQUIRE(tree.GetRoot()->Key == 9);
//		REQUIRE(tree.GetRoot()->Left->Key == 3);
//		REQUIRE(tree.GetRoot()->Right == nullptr);
//
//		REQUIRE(tree.GetRoot()->Left->Right->Key == 4);
//		REQUIRE(tree.GetRoot()->Left->Left->Key == 1);
//
//		REQUIRE(tree.GetRoot()->Left->Left->Right->Key == 2);
//	}
//
//	{
//		// Removing only right
//		using UnbalancedTree = BST::BinaryTree<int, int>;
//
//		UnbalancedTree tree;
//		DO(tree.AddNode(10, 1));
//		DO(tree.AddNode(12, 1));
//		DO(tree.AddNode(14, 1));
//		DO(tree.AddNode(16, 1));
//		DO(tree.AddNode(13, 1));
//
//		DO(tree.RemoveNode(10));
//		REQUIRE(tree.GetRoot()->Key == 12);
//		REQUIRE(tree.GetRoot()->Right->Key == 14);
//		REQUIRE(tree.GetRoot()->Left == nullptr);
//
//		REQUIRE(tree.GetRoot()->Right->Left->Key == 13);
//		REQUIRE(tree.GetRoot()->Right->Right->Key == 16);
//	}
//
//	{
//		// Removing with both side
//		using UnbalancedTree = BST::BinaryTree<int, int>;
//
//		UnbalancedTree tree;
//		DO(tree.AddNode(10, 1));
//		DO(tree.AddNode(7, 1));
//		DO(tree.AddNode(8, 1));
//		DO(tree.AddNode(3, 1));
//		DO(tree.AddNode(4, 1));
//		DO(tree.AddNode(1, 1));
//
//		//DO(tree.AddNode(15, 1));
//
//		DO(tree.RemoveNode(10));
//
//		REQUIRE(tree.GetRoot()->Key == 7);
//		REQUIRE(tree.GetRoot()->Left->Key == 3);
//		REQUIRE(tree.GetRoot()->Right->Key == 8);
//
//		REQUIRE(tree.GetRoot()->Left->Left->Key == 1);
//		REQUIRE(tree.GetRoot()->Left->Right->Key == 4);
//	}
//
//	{
//		// Removing with both side
//		using UnbalancedTree = BST::BinaryTree<int, int>;
//
//		UnbalancedTree tree;
//		DO(tree.AddNode(10, 1));
//		DO(tree.AddNode(7, 1));
//		DO(tree.AddNode(8, 1));
//		DO(tree.AddNode(3, 1));
//		DO(tree.AddNode(4, 1));
//		DO(tree.AddNode(1, 1));
//		//---------------------
//		DO(tree.AddNode(15, 1));
//
//		DO(tree.RemoveNode(10));
//
//		REQUIRE(tree.GetRoot()->Key == 8);
//		REQUIRE(tree.GetRoot()->Left->Key == 7);
//		REQUIRE(tree.GetRoot()->Right->Key == 15);
//
//		REQUIRE(tree.GetRoot()->Left->Left->Key == 3);
//		REQUIRE(tree.GetRoot()->Left->Right == nullptr);
//
//		REQUIRE(tree.GetRoot()->Left->Left->Key == 3);
//		REQUIRE(tree.GetRoot()->Left->Left->Left->Key == 1);
//		REQUIRE(tree.GetRoot()->Left->Left->Right->Key == 4);
//	}
//
//	{
//		// Removing with both side
//		using UnbalancedTree = BST::BinaryTree<int, int>;
//
//		UnbalancedTree tree;
//		DO(tree.AddNode(10, 1));
//		DO(tree.AddNode(7, 1));
//		DO(tree.AddNode(3, 1));
//		DO(tree.AddNode(4, 1));
//		DO(tree.AddNode(1, 1));
//		//---------------------
//		DO(tree.AddNode(15, 1));
//
//		DO(tree.RemoveNode(10));
//
//		REQUIRE(tree.GetRoot()->Key == 7);
//		REQUIRE(tree.GetRoot()->Left->Key == 3);
//		REQUIRE(tree.GetRoot()->Right->Key == 15);
//
//		REQUIRE(tree.GetRoot()->Left->Left->Key == 1);
//		REQUIRE(tree.GetRoot()->Left->Right->Key == 4);
//	}
//
//	{
//		// Removing with both side
//		using UnbalancedTree = BST::BinaryTree<int, int>;
//
//		UnbalancedTree tree;
//		DO(tree.AddNode(10, 1));
//		DO(tree.AddNode(15, 1));
//		DO(tree.AddNode(13, 1));
//		DO(tree.AddNode(12, 1));
//		DO(tree.AddNode(14, 1));
//		DO(tree.AddNode(17, 1));
//		DO(tree.AddNode(16, 1));
//
//		DO(tree.RemoveNode(10));
//
//		REQUIRE(tree.GetRoot()->Key == 15);
//		REQUIRE(tree.GetRoot()->Left->Key == 13);
//		REQUIRE(tree.GetRoot()->Left->Left->Key == 12);
//		REQUIRE(tree.GetRoot()->Left->Right->Key == 14);
//
//		REQUIRE(tree.GetRoot()->Right->Key == 17);
//		REQUIRE(tree.GetRoot()->Right->Left->Key == 16);
//	}
//
//}


TEST_CASE("Test AVL Tree", "[Algorithmics]")
{
#if AVL_IMPLEMENTED
	{
		std::printf("===========Test AVL Tree============\n");

		Foo::ResetCount();

		using AVLTree = BST::AVLTree< int, Foo >;

		AVLTree myTree;
		REQUIRE(myTree.Size() == 0);
		REQUIRE(myTree.GetHeight() == 0);

		AVLTree::NodeType* Node = nullptr;

		Foo kenThompFoo;
		DO(Node = myTree.AddNode(9, kenThompFoo));
		REQUIRE(myTree.Size() == 1);
		REQUIRE(myTree.GetHeight() == 1);

		Foo dennisRitchFoo;
		DO(Node = myTree.AddNode(6, dennisRitchFoo));
		REQUIRE(myTree.Size() == 2);
		REQUIRE(myTree.GetHeight() == 2);

		// Test Right-Right rotation
		Foo barbaraLiskFoo;
		DO(Node = myTree.AddNode(4, barbaraLiskFoo));
		REQUIRE(myTree.Size() == 3);
		REQUIRE(myTree.GetHeight() == 2);

		// Test Left-Left rotations
		myTree.AddNode(10, Foo());

		Foo alanKayFoo;
		DO(Node = myTree.AddNode(12, alanKayFoo));
		REQUIRE(myTree.Size() == 5);
		REQUIRE(myTree.GetHeight() == 3);

		Foo graceHopFoo;
		DO(Node = myTree.AddNode(30, graceHopFoo));
		REQUIRE(myTree.GetRoot()->Key == 10);
		REQUIRE(myTree.Size() == 6);
		REQUIRE(myTree.GetHeight() == 3);



		// Test Right-Left rotations
		Foo edsgerDijkstrFoo;
		DO(Node = myTree.AddNode(22, edsgerDijkstrFoo));
		REQUIRE(myTree.Size() == 7);
		REQUIRE(myTree.GetHeight() == 3);


		// Test left-right rotations
		DO(Node = myTree.AddNode(28, Foo()));

		Foo alanTurFoo;
		DO(Node = myTree.AddNode(29, alanTurFoo));
		REQUIRE(myTree.Size() == 9);
		REQUIRE(myTree.GetHeight() == 4);


		// Test remove with no rotation
		bool removed = false;

		DO(removed = myTree.RemoveNode(29));
		REQUIRE(myTree.Size() == 8);
		REQUIRE(myTree.GetHeight() == 4);
		REQUIRE(removed);


		DO(removed = myTree.RemoveNode(22)); // right-right rotation
		REQUIRE(removed);
		REQUIRE(myTree.Size() == 7);
		REQUIRE(myTree.GetHeight() == 3);


		// Testing remove with left-left rotation
		DO(removed = myTree.RemoveNode(9)); // no rotation
		REQUIRE(removed);

		DO(Node = myTree.AddNode(1, Foo()));
		DO(Node = myTree.AddNode(2, Foo()));
		DO(Node = myTree.AddNode(3, Foo()));
		DO(Node = myTree.AddNode(5, Foo()));
		DO(Node = myTree.AddNode(7, Foo()));
		DO(Node = myTree.AddNode(8, Foo()));

		DO(removed = myTree.RemoveNode(4)); // no rotation
		REQUIRE(removed);

		DO(removed = myTree.RemoveNode(3)); // no rotation
		REQUIRE(removed);

		DO(Node = myTree.AddNode(3, Foo()));

		DO(removed = myTree.RemoveNode(2)); // left-right rotation
		REQUIRE(removed);
		REQUIRE(myTree.Size() == 10);
		REQUIRE(myTree.GetHeight() == 4);

		// Veryfing the tree structure
		Node = myTree.Search(6); // the root
		REQUIRE(Node->Left->Key == 3);
		REQUIRE(Node->Left->Left->Key == 1);
		REQUIRE(Node->Left->Right->Key == 5);

		REQUIRE(Node->Right->Key == 10);
		REQUIRE(Node->Right->Left->Key == 7);
		REQUIRE(Node->Right->Left->Right->Key == 8);

		REQUIRE(Node->Right->Right->Key == 28);
		REQUIRE(Node->Right->Right->Left->Key == 12);
		REQUIRE(Node->Right->Right->Right->Key == 30);
	}

	g_memorySpy.CheckLeaks();


#else

	FAIL("Test AVL Tree (STEP 2) Unimplemented !");

#endif
}


TEST_CASE("Test Red/Black Tree", "[Algorithmics]")
{

	std::printf("===========Test Red/Black Tree============\n");

#if REDBLACK_IMPLEMENTED
	{

		using RedBlackTree = BST::RedBlackTree<int, Foo>;

		Foo::ResetCount();

		{
			RedBlackTree rbTree;

			// Test increasing keys only
			int i = 0;
			while (i < 12)
				rbTree.AddNode(1 << i++, Foo());

			// Testing the structure of the tree
			// YOUR STRUCTURE MAY DIFFER from this one based on how you programmed the tree.
			// IF YOU THINK YOU ARE CORRECT, ASK THE TEACHER.
			// DRAW YOUR TREE ON PAPER AND VERIFY IT RESPECTS THE 5 RULES OF RED BLACK TREE.
			REQUIRE(rbTree.Size() == 12);
			/*REQUIRE(rbTree.GetRoot()->Key == 128);
			REQUIRE(rbTree.GetRoot()->Color == BST::NodeColor::BLACK);

			REQUIRE(rbTree.GetRoot()->Left->Key == 8);
			REQUIRE(rbTree.GetRoot()->Left->Color == BST::NodeColor::RED);

			REQUIRE(rbTree.GetRoot()->Left->Left->Key == 2);
			REQUIRE(rbTree.GetRoot()->Left->Left->Color == BST::NodeColor::BLACK);

			REQUIRE(rbTree.GetRoot()->Left->Left->Left->Key == 1);
			REQUIRE(rbTree.GetRoot()->Left->Left->Color == BST::NodeColor::BLACK);

			REQUIRE(rbTree.GetRoot()->Left->Left->Right->Key == 4);
			REQUIRE(rbTree.GetRoot()->Left->Left->Color == BST::NodeColor::BLACK);

			REQUIRE(rbTree.GetRoot()->Left->Right->Key == 32);
			REQUIRE(rbTree.GetRoot()->Left->Right->Color == BST::NodeColor::BLACK);

			REQUIRE(rbTree.GetRoot()->Left->Right->Left->Key == 16);
			REQUIRE(rbTree.GetRoot()->Left->Right->Left->Color == BST::NodeColor::BLACK);

			REQUIRE(rbTree.GetRoot()->Left->Right->Right->Key == 64);
			REQUIRE(rbTree.GetRoot()->Left->Right->Right->Color == BST::NodeColor::BLACK);

			REQUIRE(rbTree.GetRoot()->Right->Key == 512);
			REQUIRE(rbTree.GetRoot()->Right->Color == BST::NodeColor::BLACK);

			REQUIRE(rbTree.GetRoot()->Right->Left->Key == 256);
			REQUIRE(rbTree.GetRoot()->Right->Left->Color == BST::NodeColor::BLACK);

			REQUIRE(rbTree.GetRoot()->Right->Right->Key == 2048);
			REQUIRE(rbTree.GetRoot()->Right->Right->Color == BST::NodeColor::BLACK);

			REQUIRE(rbTree.GetRoot()->Right->Right->Left->Key == 1024);
			REQUIRE(rbTree.GetRoot()->Right->Right->Left->Color == BST::NodeColor::RED);*/
		}

		{
			// Test decreasing keys only
			RedBlackTree rbTree;
			int i = 12;
			while (i > 2)
				rbTree.AddNode(1 << i--, Foo());


			// Testing the structure of the tree
			REQUIRE(rbTree.Size() == 10);
			REQUIRE(rbTree.GetRoot()->Key == 512);
			REQUIRE(rbTree.GetRoot()->Color == BST::NodeColor::BLACK);

			REQUIRE(rbTree.GetRoot()->Left->Key == 128);
			REQUIRE(rbTree.GetRoot()->Left->Color == BST::NodeColor::BLACK);

			REQUIRE(rbTree.GetRoot()->Left->Left->Key == 32);
			REQUIRE(rbTree.GetRoot()->Left->Left->Color == BST::NodeColor::RED);

			REQUIRE(rbTree.GetRoot()->Left->Left->Left->Key == 16);
			REQUIRE(rbTree.GetRoot()->Left->Left->Left->Color == BST::NodeColor::BLACK);

			REQUIRE(rbTree.GetRoot()->Left->Left->Left->Left->Key == 8);
			REQUIRE(rbTree.GetRoot()->Left->Left->Left->Left->Color == BST::NodeColor::RED);

			REQUIRE(rbTree.GetRoot()->Left->Left->Right->Key == 64);
			REQUIRE(rbTree.GetRoot()->Left->Left->Right->Color == BST::NodeColor::BLACK);

			REQUIRE(rbTree.GetRoot()->Left->Right->Key == 256);
			REQUIRE(rbTree.GetRoot()->Left->Right->Color == BST::NodeColor::BLACK);

			REQUIRE(rbTree.GetRoot()->Right->Key == 2048);
			REQUIRE(rbTree.GetRoot()->Right->Color == BST::NodeColor::BLACK);

			REQUIRE(rbTree.GetRoot()->Right->Left->Key == 1024);
			REQUIRE(rbTree.GetRoot()->Right->Left->Color == BST::NodeColor::BLACK);

			REQUIRE(rbTree.GetRoot()->Right->Right->Key == 4096);
			REQUIRE(rbTree.GetRoot()->Right->Right->Color == BST::NodeColor::BLACK);

		}

		{
			// Testing random keys
			RedBlackTree rbTree;
			rbTree.AddNode(42, Foo());
			rbTree.AddNode(76, Foo());
			rbTree.AddNode(77, Foo());
			rbTree.AddNode(92, Foo());
			rbTree.AddNode(46, Foo());
			rbTree.AddNode(11, Foo());
			rbTree.AddNode(12, Foo());
			rbTree.AddNode(14, Foo());
			rbTree.AddNode(19, Foo());
			rbTree.AddNode(36, Foo());
			rbTree.AddNode(29, Foo());
			rbTree.AddNode(84, Foo());
			rbTree.AddNode(5, Foo());
			rbTree.AddNode(2, Foo());

			// Testing the structure of the tree
			REQUIRE(rbTree.Size() == 14);
			REQUIRE(rbTree.GetRoot()->Key == 42);
			REQUIRE(rbTree.GetRoot()->Color == BST::NodeColor::BLACK);

			REQUIRE(rbTree.GetRoot()->Left->Key == 12);
			REQUIRE(rbTree.GetRoot()->Left->Color == BST::NodeColor::BLACK);

			REQUIRE(rbTree.GetRoot()->Left->Left->Key == 5);
			REQUIRE(rbTree.GetRoot()->Left->Left->Color == BST::NodeColor::BLACK);

			REQUIRE(rbTree.GetRoot()->Left->Left->Left->Key == 2);
			REQUIRE(rbTree.GetRoot()->Left->Left->Left->Color == BST::NodeColor::RED);

			REQUIRE(rbTree.GetRoot()->Left->Left->Right->Key == 11);
			REQUIRE(rbTree.GetRoot()->Left->Left->Right->Color == BST::NodeColor::RED);

			REQUIRE(rbTree.GetRoot()->Left->Right->Key == 19);
			REQUIRE(rbTree.GetRoot()->Left->Right->Color == BST::NodeColor::RED);

			REQUIRE(rbTree.GetRoot()->Left->Right->Right->Key == 36);
			REQUIRE(rbTree.GetRoot()->Left->Right->Right->Color == BST::NodeColor::BLACK);

			REQUIRE(rbTree.GetRoot()->Left->Right->Right->Left->Key == 29);
			REQUIRE(rbTree.GetRoot()->Left->Right->Right->Left->Color == BST::NodeColor::RED);


			REQUIRE(rbTree.GetRoot()->Left->Right->Left->Key == 14);
			REQUIRE(rbTree.GetRoot()->Left->Right->Left->Color == BST::NodeColor::BLACK);


			REQUIRE(rbTree.GetRoot()->Left->Right->Left->Key == 14);
			REQUIRE(rbTree.GetRoot()->Left->Right->Left->Color == BST::NodeColor::BLACK);


			REQUIRE(rbTree.GetRoot()->Right->Key == 76);
			REQUIRE(rbTree.GetRoot()->Right->Color == BST::NodeColor::BLACK);


			REQUIRE(rbTree.GetRoot()->Right->Right->Key == 84);
			REQUIRE(rbTree.GetRoot()->Right->Right->Color == BST::NodeColor::BLACK);


			REQUIRE(rbTree.GetRoot()->Right->Right->Right->Key == 92);
			REQUIRE(rbTree.GetRoot()->Right->Right->Right->Color == BST::NodeColor::RED);


			REQUIRE(rbTree.GetRoot()->Right->Right->Left->Key == 77);
			REQUIRE(rbTree.GetRoot()->Right->Right->Left->Color == BST::NodeColor::RED);


			REQUIRE(rbTree.GetRoot()->Right->Left->Key == 46);
			REQUIRE(rbTree.GetRoot()->Right->Left->Color == BST::NodeColor::BLACK);
			

			// Now removing random keys
			rbTree.RemoveNode(19);
			rbTree.RemoveNode(46);
			rbTree.RemoveNode(77);
			rbTree.RemoveNode(29);
			rbTree.RemoveNode(36);
			rbTree.RemoveNode(42);

			// Testing the structure of the tree



		}
	}

	g_memorySpy.CheckLeaks();


#else

	FAIL("Test Red/Black Tree Unimplemented !");

#endif
}





//TEST_CASE("Test Huffman encoding", "[Algorithmics]")
//{
//#if HUFFMAN_IMPLEMENTED
//	{
//
//	}
//
//	g_memorySpy.CheckLeaks();
//
//
//#else
//
//	FAIL("Test Huffman encoding Unimplemented !");
//
//#endif
//}

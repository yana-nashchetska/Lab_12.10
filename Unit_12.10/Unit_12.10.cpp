#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_12.10/Lab_12.10.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Unit1210
{
	TEST_CLASS(Unit1210)
	{
	public:
		TEST_METHOD(TestInfixTraversal)
		{
			Node* root = createNode(4);
			root->left = createNode(2);
			root->right = createNode(6);
			root->left->left = createNode(1);
			root->left->right = createNode(3);
			root->right->left = createNode(5);
			root->right->right = createNode(7);

			// Act
			Node* minValueNode = findMinValueNode(root);

			// Assert
			Assert::AreEqual(1, minValueNode->data);
		}
	};
}

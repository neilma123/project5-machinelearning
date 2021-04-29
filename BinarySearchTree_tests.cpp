// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"
using namespace std;

TEST(midterm_p_2) {
    BinarySearchTree<int> tree;
    tree.insert(9);
    tree.insert(6);
    tree.insert(13);
    tree.insert(4);
    tree.insert(7);
    tree.insert(5);
    tree.insert(20);
    tree.print();
}
TEST(test_bst_nodezero) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.size() == 0);
    ASSERT_TRUE(tree.height() == 0);
    ASSERT_TRUE(tree.empty());
    ASSERT_TRUE(tree.begin() == tree.end());
}

TEST(test_bst_node_one) {
    BinarySearchTree<int> tree;
    tree.insert(6);
    ASSERT_TRUE(tree.size() == 1);
    ASSERT_TRUE(tree.height() == 1);
    ASSERT_FALSE(tree.empty());
    ASSERT_TRUE(tree.check_sorting_invariant());
    ASSERT_EQUAL(*tree.max_element(), 6);
    ASSERT_EQUAL(*tree.min_element(), 6);
}
TEST(test_min_g1) {
    BinarySearchTree<int> test;
    ASSERT_EQUAL(test.min_greater_than(1), test.end());
}
TEST(test_min_g2) {
    BinarySearchTree<int> test;
    test.insert(2);
    ASSERT_EQUAL(*test.min_greater_than(1), 2);
}
TEST(test_min_g3) {
    BinarySearchTree<int> test;
    test.insert(1);
    test.insert(2);
    test.insert(3);
    ASSERT_EQUAL(*test.min_greater_than(1), 2);
    ASSERT_EQUAL(*test.min_greater_than(2), 3);
    ASSERT_EQUAL(test.min_greater_than(3), test.end());
}
TEST(test_min_g4) {
    BinarySearchTree<int> test;
    test.insert(1);
    test.insert(2);
    ASSERT_EQUAL(*test.min_greater_than(1), 2);
    ASSERT_EQUAL(test.min_greater_than(2), test.end());
}
TEST(test_invar) {
    BinarySearchTree<int> test;
    ASSERT_TRUE(test.check_sorting_invariant());
}
TEST(test_invar1) {
    BinarySearchTree<int> test;
    test.insert(2);
    ASSERT_TRUE(test.check_sorting_invariant());
}
TEST(test_invar2) {
    BinarySearchTree<int> test;
    test.insert(1);
    ASSERT_TRUE(test.check_sorting_invariant());
    test.insert(2);
    ASSERT_TRUE(test.check_sorting_invariant());
    test.insert(3);
    ASSERT_TRUE(test.check_sorting_invariant());
}
TEST(test_copy_ctor) {
    BinarySearchTree<int> test;
    test.insert(1);
    test.insert(2);
    test.insert(3);
    BinarySearchTree<int> test1(test);
    ASSERT_EQUAL(*test1.min_greater_than(1), 2);
    ASSERT_EQUAL(*test1.min_greater_than(2), 3);
    ASSERT_EQUAL(test1.min_greater_than(3), test.end());
}

TEST(test_tree_suite) {
    BinarySearchTree<int> test;
    test.insert(30);
    test.insert(29);
    test.insert(25);
    test.insert(45);
    test.insert(41);
    test.insert(48);
    test.insert(46);
    ASSERT_EQUAL(*test.find(46), 46);
    ASSERT_EQUAL(*test.min_element(), 25);
    ASSERT_EQUAL(*test.max_element(), 48);
    ASSERT_EQUAL(test.height(), 3);
}
TEST(test_tree_of_two) {
    BinarySearchTree<int> test;
    test.insert(30);
    test.insert(29);
    ASSERT_EQUAL(*test.find(30), 30);
    ASSERT_EQUAL(*test.min_element(), 29);
    ASSERT_EQUAL(*test.max_element(), 30);
    ASSERT_EQUAL(test.height(), 2);
}
TEST(test_tree_of_three) {
    BinarySearchTree<int> test;
    test.insert(30);
    test.insert(29);
    test.insert(31);
    ASSERT_EQUAL(*test.find(30), 30);
    ASSERT_EQUAL(*test.min_element(), 29);
    ASSERT_EQUAL(*test.max_element(), 31);
    ASSERT_EQUAL(test.height(), 2);
}
TEST(test_tree_order) {
    BinarySearchTree<int> test;
    test.insert(30);
    test.insert(29);
    test.insert(25);
    test.insert(45);
    test.insert(41);
    test.insert(48);
    ASSERT_EQUAL(*test.min_element(), 25);
    ASSERT_EQUAL(*test.max_element(), 48);
    ASSERT_EQUAL(test.height(), 3);
   
    ostringstream oss_preorder;
    test.traverse_preorder(oss_preorder);
    cout << "preorder" << endl;
    cout << oss_preorder.str() << endl << endl;
    ASSERT_TRUE(oss_preorder.str() == "30 29 25 45 41 48 ");
    
    ostringstream oss_inorder;
    test.traverse_inorder(oss_inorder);
    cout << "inorder" << endl;
    cout << oss_inorder.str() << endl << endl;
    ASSERT_TRUE(oss_inorder.str() == "25 29 30 41 45 48 ");
}
TEST(test_inv2) {
    BinarySearchTree<int> test;
    test.insert(30);
    test.insert(29);
    test.insert(25);
    test.insert(45);
    test.insert(41);
    test.insert(48);
    test.insert(46);
    test.insert(19);
    test.insert(50);
    ASSERT_TRUE(test.check_sorting_invariant());
}
TEST_MAIN()

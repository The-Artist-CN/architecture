#include <RBTree.h>
#include <gtest/gtest.h>

using namespace Stk;

// 测试夹具类 - 改名避免与 RBTree 类冲突
class RBTreeTest : public ::testing::Test
{
protected:
	void SetUp() override {
		// 插入一些初始数据
		rbtree.insert(10.0f);
		rbtree.insert(20.0f);
		rbtree.insert(5.0f);
	}

	RBTree<float> rbtree;  // 改名，不加数字后缀
};

// 测试：查找存在的元素
TEST_F(RBTreeTest, FindExisting) {
	EXPECT_TRUE(rbtree.find(10.0f));
	EXPECT_TRUE(rbtree.find(20.0f));
	EXPECT_TRUE(rbtree.find(5.0f));
}

// 测试：查找不存在的元素
TEST_F(RBTreeTest, FindNonExisting) {
	EXPECT_FALSE(rbtree.find(1.0f));
	EXPECT_FALSE(rbtree.find(99.0f));
	EXPECT_FALSE(rbtree.find(-10.0f));
}

// 测试：插入新元素
TEST_F(RBTreeTest, InsertAndFind) {
	rbtree.insert(30.0f);
	EXPECT_TRUE(rbtree.find(30.0f));
	EXPECT_FALSE(rbtree.find(40.0f));
}

// 测试：删除元素
TEST_F(RBTreeTest, RemoveAndFind) {
	rbtree.remove(20.0f);
	EXPECT_FALSE(rbtree.find(20.0f));
	EXPECT_TRUE(rbtree.find(10.0f));   // 其他元素还在
	EXPECT_TRUE(rbtree.find(5.0f));
}

// 测试：空树
TEST(RBTreeStandalone, EmptyTree) {
	RBTree<int> emptyTree;
	EXPECT_TRUE(emptyTree.isEmpty());
	EXPECT_FALSE(emptyTree.find(42));

	emptyTree.insert(42);
	EXPECT_FALSE(emptyTree.isEmpty());
	EXPECT_TRUE(emptyTree.find(42));
}

// 测试：中序遍历（如果实现了）
TEST_F(RBTreeTest, PrintInorder) {
	// 只是测试不崩溃
	testing::internal::CaptureStdout();
	rbtree.inorderPrint();
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_FALSE(output.empty());  // 应该有输出
}
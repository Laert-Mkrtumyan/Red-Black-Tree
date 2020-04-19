#ifndef RED_BLACKTREENODE_H
#define RED_BLACKTREENODE_H
class RB_TreeNode
{
public:
	friend class RB_Tree;
	RB_TreeNode(int val = 0)
	{
		left = right = parent = nullptr;
		value = val;
		color = false;
	}
private:
	RB_TreeNode* left, *right, *parent;
	int value;
	bool color; //1 red, 0 black
};
#endif
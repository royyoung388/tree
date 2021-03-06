#include <stdio.h>

typedef struct TreeNode
{
	int value, level, postion, size;
	struct TreeNode *next[16], *pre;
} TreeNode;

TreeNode * createTree(char * str) {
	//头结点
	TreeNode header = {
		.value = 0,
		.level = 0,
		.postion = 0,
		.size = 0,
		.next = {NULL},
		.pre = NULL,
	};
	//根结点
	TreeNode root = {
		.value = 0,
		.level = 1,
		.postion = 0,
		.size = 0,
		.next = { NULL },
		.pre = NULL,
	};
	header.next[0] = &root;
	TreeNode * curr = &root;

	int index = 0;

	while (str[index]) {
		switch (str[index])
		{
			//创建子树
		case '(':
			//添加一条空语句
			;
			TreeNode *node1 = (TreeNode *)malloc(sizeof(TreeNode));
			memset(node1, 0, sizeof(TreeNode));
			node1->level = curr->level + 1;
			node1->pre = curr;

			curr->next[0] = node1;
			curr->size++;
			curr = curr->next[0];
			break;
			//回到父节点
		case ')':
			curr = curr->pre;
			break;
			//创建兄弟节点
		case ',':
			;
			//先找到当前结点位置
			int i = 0;
			while (curr->pre->next[i] != NULL) {
				i++;
			}
			//创建兄弟节点
			TreeNode *node2 = (TreeNode *)malloc(sizeof(TreeNode));
			memset(node2, 0, sizeof(TreeNode));
			node2->pre = curr->pre;

			curr->pre->next[i] = node2;
			curr->pre->size++;
			curr = curr->pre->next[i];
			break;
			//设置节点值
		default:
			curr->value = str[index] - '0';
			break;
		}
		index++;
	}

	return &header;
}

void printTree(TreeNode* header) {
	TreeNode * curr = header;
	header->next[0]->postion = 50;

	TreeNode * brother[125];
	//记录brother的长度
	int length = 0;

	do {
		//记录brother的长度
		length = 0;

		TreeNode * old[125];
		memcpy(old, brother, sizeof(brother));
		//brother的长度
		int sp = 0;

		//对old中的每一个元素处理
		for (int i = 0; i < length; i++) {
			//更新子节点position,同时入栈
			for (int j = 0; j < old[i]->size; j++) {
				old[i]->next[j]->postion = ((j / 2) - old[i]->size) * 70 / old[i]->level;
				brother[sp] = old[i]->next[j];
				sp++;
			}

			//输出
			if (i == 0) {
				printf("%*s{%d", old[i]->postion - 2, "", old[i]->value);
			}
			else {
				printf("%*s%d", old[i]->postion - 1, "", old[i]->value);

				if (i == length - 1) {
					putchar('}');
				}

			}
		}

		length = sp;
		memcpy(brother, old, sizeof(old));
	} while (length > 0);
}

int main()
{
	//char str[512];
	//scanf_s("enter the tree:%s", str);

	char * str = "9(2(1,1(1)),4(1,3(2(2(1,1)),1)),3(1,1,1(1)))";

	TreeNode* header = createTree(str);

	printTree(header);

	return 0;
}

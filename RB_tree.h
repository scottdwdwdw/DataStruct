#ifndef RB_TREE_H
#define RB_TREE_H

namespace DATE_BASE
{
	enum { RED = 0,BLACK = 1};
	template<typename T>    //红黑树节点的定义
	struct rb_node
	{
		using _Node= rb_node < T >;
		using _NodePtr= rb_node<T>*;
		using value_type= T;
		rb_node():left(NULL), right(NULL), parent(NULL), value(T()), COLOR(RED) {}
		_NodePtr left;
		_NodePtr right;
		_NodePtr parent;
		T value;
		int COLOR;

	};

	template<typename T>
	class RB_Tree
	{
	public:
		using value_type = T;
		using reference = T&;
		using _Node = rb_node<T>;
		using _NodePtr = rb_node<T>*;
	private:
		_NodePtr root;
		_NodePtr nil;    //哨兵节点
	public:
		//
		RB_Tree()
		{
			nil=make_node(T());
			nil->COLOR=BLACK;
			root=nil;
			root->parent = nil;
		}
		void insert(_NodePtr&root,const T& key);   //插入函数
		_NodePtr& getRoot()
		{
			return root;
		}
	private:
		//私有成员函数
		//旋转
		void left_rotate(_NodePtr&position);   //左旋转
		void right_rotate(_NodePtr&position);  //右旋转
		_NodePtr make_node(const T&key);     //构造节点
		void destory_node(_NodePtr position);  //删除节点
		void RB_insert_fixup(_NodePtr& position); //维护红黑树的性质


	}; //end of class

	template<typename T>
	typename RB_Tree<T>::_NodePtr RB_Tree<T>::make_node(const T&key)
	{
		_NodePtr temp=new _Node;
		temp->left=temp->right=temp->parent=NULL;
		temp->COLOR=RED;
		temp->value=key;

		return temp;
	}

    //左旋转
	template<typename T>
	void RB_Tree<T>::left_rotate(_NodePtr&position)   //参照图来理解
	{
		_NodePtr rotate_temp=position->right;   //其中position->right是一定存在的，否则也就没必要旋转了

		position->right = rotate_temp->left; 
		if(rotate_temp->left!=nil)rotate_temp->left->parent=position;   //将y的左子树接到position上

		rotate_temp->parent=position->parent;
		if(position->parent==nil)root=rotate_temp;  //设置根节点
		else if(position==position->parent->left)position->parent->left=rotate_temp;
		else if(position==position->parent->right)position->parent->right=rotate_temp;
		

		rotate_temp->left=position;
		position->parent=rotate_temp;


	}

	//右旋转
	template<typename T>
	void RB_Tree<T>::right_rotate(_NodePtr&position)
	{
		_NodePtr rotate_temp=position->left;

		position->left=rotate_temp->right;
		if(rotate_temp->right!=nil)rotate_temp->right->parent=position;

		rotate_temp->parent=position->parent;
		if(position->parent==nil)root=rotate_temp;
		else if(position==position->parent->left)position->parent->left=rotate_temp;
		else if(position==position->parent->right)position->parent->right=rotate_temp;

		rotate_temp->right=position;
		position->parent=rotate_temp;
	}

	template<typename T>
	void RB_Tree<T>::insert(_NodePtr&root,const T& key)  //插入元素
	{
		_NodePtr pre=root;
		_NodePtr cur=root;  
		_NodePtr insert_node=make_node(key);
		while(cur!=nil)
		{
			pre=cur;
			if(key<cur->value)cur=cur->left;
			else
				cur=cur->right;
		}
		insert_node->parent=pre;
		if(pre==nil)root=insert_node;
		else if(key<pre->value)pre->left=insert_node;
		else 
		{
			pre->right=insert_node;
		}
		insert_node->left=nil;
		insert_node->right=nil;
		insert_node->COLOR=RED;
		//插入完成，下面维护红黑树的性质
		RB_insert_fixup(insert_node);

	}

	template<typename T>   //维护树的性质
	void RB_Tree<T>::RB_insert_fixup(_NodePtr& position)
	{
		while(position->parent->COLOR==RED)  //这里能够保证根节点的颜色是黑色的
		{
			if(position->parent==position->parent->parent->left)
			{
				if(position->parent->parent->right->COLOR==RED)  //case1,叔节点也是红色
				{
					position->parent->parent->right->COLOR=BLACK;
					position->parent->COLOR=BLACK;
					position->parent->parent->COLOR=RED;
					position=position->parent->parent;  
				}
				else if(position==position->parent->right)      //case 2 要将其转换为case3
				{
					position=position->parent;
					left_rotate(position);  //左旋转转换为了case3
				}
				else if(position==position->parent->left)//叔节点肯定是黑色的
				{
					position->parent->COLOR=BLACK;
					position->parent->parent->COLOR=RED;
					position=position->parent->parent;
					right_rotate(position);    //右旋转
				}
			}
			else if(position->parent=position->parent->parent->right)
			{
				if(position->parent->parent->left->COLOR==RED) //叔节点
				{
					 position->parent->parent->left->COLOR=BLACK;
					 position->parent->parent->COLOR=RED;
					 position->parent->COLOR=BLACK;
					 position=position->parent->parent;
				}
				else if(position==position->parent->left)   //case 2
				{
					position=position->parent;
					right_rotate(position);    //右旋转  ,转换为case3
				}
				else if(position==position->parent->right)
				{
					position->parent->COLOR=BLACK;
					position->parent->parent->COLOR=RED;
					position=position->parent->parent;
					left_rotate(position);   //左旋
				}
			}
		}

		root->COLOR=BLACK;  
	}



} //end of namespace





#endif

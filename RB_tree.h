#ifndef RB_TREE_H
#define RB_TREE_H

namespace DATE_BASE
{
	enum { RED = 0,BLACK = 1};
	template<typename T>    //������ڵ�Ķ���
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
		_NodePtr nil;    //�ڱ��ڵ�
	public:
		//
		RB_Tree()
		{
			nil=make_node(T());
			nil->COLOR=BLACK;
			root=nil;
			root->parent = nil;
		}
		void insert(_NodePtr&root,const T& key);   //���뺯��
		_NodePtr& getRoot()
		{
			return root;
		}
	private:
		//˽�г�Ա����
		//��ת
		void left_rotate(_NodePtr&position);   //����ת
		void right_rotate(_NodePtr&position);  //����ת
		_NodePtr make_node(const T&key);     //����ڵ�
		void destory_node(_NodePtr position);  //ɾ���ڵ�
		void RB_insert_fixup(_NodePtr& position); //ά�������������


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

    //����ת
	template<typename T>
	void RB_Tree<T>::left_rotate(_NodePtr&position)   //����ͼ�����
	{
		_NodePtr rotate_temp=position->right;   //����position->right��һ�����ڵģ�����Ҳ��û��Ҫ��ת��

		position->right = rotate_temp->left; 
		if(rotate_temp->left!=nil)rotate_temp->left->parent=position;   //��y���������ӵ�position��

		rotate_temp->parent=position->parent;
		if(position->parent==nil)root=rotate_temp;  //���ø��ڵ�
		else if(position==position->parent->left)position->parent->left=rotate_temp;
		else if(position==position->parent->right)position->parent->right=rotate_temp;
		

		rotate_temp->left=position;
		position->parent=rotate_temp;


	}

	//����ת
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
	void RB_Tree<T>::insert(_NodePtr&root,const T& key)  //����Ԫ��
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
		//������ɣ�����ά�������������
		RB_insert_fixup(insert_node);

	}

	template<typename T>   //ά����������
	void RB_Tree<T>::RB_insert_fixup(_NodePtr& position)
	{
		while(position->parent->COLOR==RED)  //�����ܹ���֤���ڵ����ɫ�Ǻ�ɫ��
		{
			if(position->parent==position->parent->parent->left)
			{
				if(position->parent->parent->right->COLOR==RED)  //case1,��ڵ�Ҳ�Ǻ�ɫ
				{
					position->parent->parent->right->COLOR=BLACK;
					position->parent->COLOR=BLACK;
					position->parent->parent->COLOR=RED;
					position=position->parent->parent;  
				}
				else if(position==position->parent->right)      //case 2 Ҫ����ת��Ϊcase3
				{
					position=position->parent;
					left_rotate(position);  //����תת��Ϊ��case3
				}
				else if(position==position->parent->left)//��ڵ�϶��Ǻ�ɫ��
				{
					position->parent->COLOR=BLACK;
					position->parent->parent->COLOR=RED;
					position=position->parent->parent;
					right_rotate(position);    //����ת
				}
			}
			else if(position->parent=position->parent->parent->right)
			{
				if(position->parent->parent->left->COLOR==RED) //��ڵ�
				{
					 position->parent->parent->left->COLOR=BLACK;
					 position->parent->parent->COLOR=RED;
					 position->parent->COLOR=BLACK;
					 position=position->parent->parent;
				}
				else if(position==position->parent->left)   //case 2
				{
					position=position->parent;
					right_rotate(position);    //����ת  ,ת��Ϊcase3
				}
				else if(position==position->parent->right)
				{
					position->parent->COLOR=BLACK;
					position->parent->parent->COLOR=RED;
					position=position->parent->parent;
					left_rotate(position);   //����
				}
			}
		}

		root->COLOR=BLACK;  
	}



} //end of namespace





#endif

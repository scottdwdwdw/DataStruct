#ifndef TREE_H
#define TREE_H

#include<stack>

namespace DATE_BASE
{
	template<typename T>
	struct node
	{
		typedef T value_type;
		typedef node<T>*  pointer;
		pointer parent;
		pointer left;
		pointer right;
		value_type value;
		node():value(T()),parent(NULL),left(NULL),right(NULL){} ;
	};

	template<typename T>
	class BinarySearchTree{
 	public:
 		typedef node<T>  Node;
 		typedef node<T>* NodePtr;
 		typedef T 		 value_type;
 	public:
		BinarySearchTree():root(NULL){}
 		//member-function
 		void insert(NodePtr& root,const T& value);
 		void inorder_tree_walk(NodePtr position);   //中序遍历
 		void preorder_tree_walk(NodePtr position);  //先序遍历
 		void postorder_tree_walk(NodePtr position);  //后续遍历
 		void inorder_tree_walk_with_stack(NodePtr position);  //中序遍历，使用栈作为辅助,而不使用递归
 		void inorder_tree_walk_without_stack(NodePtr position); //中序遍历，使用普通方法,非递归，迭代
		NodePtr& GetRoot() { return root; };
 	private:
 		NodePtr MakeNode(const T&value);
 		NodePtr root;  

 	};  //end of BinarySearchTree

 	template<typename T>
 	inline typename BinarySearchTree<T>::NodePtr BinarySearchTree<T>::MakeNode(const T&lvalue)
 	{
 		NodePtr temp=new Node;
 		temp->value= lvalue;
 		temp->parent=temp->left=temp->right=NULL;
 		return temp;
 	}

 	template<typename T>
 	void BinarySearchTree<T>::insert(NodePtr& root,const T& lvalue)  //注意，这个是个copy,和原来的root没有关系
 	{
 		NodePtr temp=MakeNode(lvalue);
 		NodePtr pTree=root;
 		NodePtr temp_ptr=NULL;  //为了保存pTree的旧值
 		while(pTree!=NULL)
 		{
 			temp_ptr=pTree;
 			if(temp->value<pTree->value)pTree=pTree->left;
 			else pTree=pTree->right;
 		}
 		temp->parent=temp_ptr;
 		if(temp_ptr==NULL)root=temp;   //说明是空的树
 		else if(temp->value<temp_ptr->value)temp_ptr->left=temp;
 		else 
 			temp_ptr->right=temp;
 	} 

 	template<typename T>      //中序遍历
 	void BinarySearchTree<T>::inorder_tree_walk(NodePtr position)
 	{
 		if(position!=NULL)
 		{
 			inorder_tree_walk(position->left);
 			std::cout<<position->value<<" ";
 			inorder_tree_walk(position->right);
 		}
 	}

 	template<typename T>
 	void BinarySearchTree<T>::preorder_tree_walk(NodePtr position)
 	{
 		if(position !=NULL)
 		{
 			std::cout<<position->value<<" ";
 			preorder_tree_walk(position->left);
 			preorder_tree_walk(position->right);
 		}

 	}

 	template<typename T>
 	void BinarySearchTree<T>::postorder_tree_walk(NodePtr position)
 	{
 		if(position!=NULL)
 		{
 			postorder_tree_walk(position->left);
 			postorder_tree_walk(position->right);
 			std::cout<<position->value<<" ";
 		}
 	}

 	template<typename T>
    void BinarySearchTree<T>::inorder_tree_walk_with_stack(NodePtr position)
    {
    	std::stack<NodePtr>node_temp;
        while(position!=NULL||!node_temp.empty())
    	{

    	   while(position!=NULL)
    	   {
    		  node_temp.push(position);
    		  position=position->left;
    	   }
    	   position= node_temp.top();
    	   std::cout<<position->value<<" ";
    	   node_temp.pop();
    	   position=position->right;
    	}
    }

    template<typename T>
    void BinarySearchTree<T>::inorder_tree_walk_without_stack(NodePtr position)
    {
    	while(position!=NULL)
    	{
    	 	 while(position->left!=NULL)  //移动到节点的最左节点
    	 	 {
    			position=position->left;
    	 	 } 
    	
    	 	std::cout<<position->value<<" ";   //输出最左的值
    	  	if(position->right==NULL) //没有右孩子，要回溯到父节点
    	  	{
    			 NodePtr temp=position;
    			 position=position->parent;
    			 for(;position!=NULL&&position->right==temp;)
    			 {
					 temp = position;
					 position=position->parent;   //移动到父节点	
    			 }
    			if(position==NULL)break;  //结束
    			std::cout<<position->value<<" ";  //输出父节点的值；
    			
    	 	}
    	 	
    	 	position=position->right;   //遍历右枝
    	}
    }



} //end of DATA_BASE

#endif

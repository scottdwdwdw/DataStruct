#ifndef TREE_H
#define TREE_H


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

} //end of DATA_BASE

#endif

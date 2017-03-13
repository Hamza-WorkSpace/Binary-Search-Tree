#include<iostream>
#include<conio.h>
using namespace std;

int dpth=0;
class node
{
public:
	int data;
	
	node*left;
	node*right;
	node();
};

node ::node()
{
	data=0;
	left=NULL;
	right=NULL;
	
}

class BinaryTree
{
public:
	node*root;
	//function to insert node in binary tree
	void insert(void);

	//function to delete node 

	void Delete();
	void delete_leaf_node(node*);
	void delete_node_having_1_left_child(node*,int);
	void delete_node_having_1_right_child(node*,int);
	void delete_node_having_both_left_and_right_child(node*,node*);
	//void delete_root(node*root);

	//function to search the node

	void search_node();

	//modify

	void modify();

	//functions to traverse the binary tree
	void pre_order(node*);
	void in_order(node*);//also used for sorting
	void post_order(node*);

	//constructor

	BinaryTree();
};

 
BinaryTree::BinaryTree()
{
	root=NULL;
}


void BinaryTree::insert(void)
{

	int val;
	cout<<"enter value\n\n";
	cin>>val;

	if(root==NULL)
	{
		root= new node;
		root->data=val;
		root->left=NULL;
		root->right=NULL;
		val=0;
	}

	else
	{
		node *newnode=new node;
		newnode->data=val;
	

		node *p;
		node *q;

		p=root;
		q=root;

			while(p->data!=val && q!=NULL)
			{
				p=q;

				if(val   <p->data)
				{
					q=p->left;
				}
				else
				{
					q=p->right;
				}
			}

			if(val<p->data)
			{
				p->left=newnode;
			}

			else
			{
				p->right=newnode;
			}
		}//end of else
}



//delete node functions-----------------------------------------------------------------------------------------------------------------

void BinaryTree::Delete(void)
{
	system("cls");
// first searching the element to be deleated
	int val;
	bool found = false;
	node*temp=root;
	node*temp1=root;


	if(root==NULL )
	{
		cerr<<"can not delete from empty tree";
	}
	else
	{

		cout<<"enter the value you want to delete : ";
		cin>>val;


		while(temp1->data!=val )// temp1=q
		{
				temp=temp1;//temp=p
			
				if(val<temp->data)
				{
					temp1=temp->left;
				}
				else
				{
					temp1=temp->right;
				}

				if( temp1==NULL)
				{
					break;
				}


		}//end of while..

//-----------------searching node is  done---------	

		if(temp1==NULL )//if value is not found then loop will not  Break and end with temp==NULL
		{
			cout<<"\n\nvalue to be deleted not found in TREE ";
		}
		else
		{

			if(temp1->left==NULL && temp1->right!=NULL)// left child null but having right child
			{
				delete_node_having_1_right_child(temp,val);//p

			}

			else if(temp1->left != NULL  &&  temp1->right == NULL) // right child null but having left child
			{
				delete_node_having_1_left_child(temp,val);//p
			}
			else if(temp1->left != NULL  &&  temp1->right != NULL) // if temp is having both left and right child
			{
					delete_node_having_both_left_and_right_child(temp1,temp1->left);//q,q->left
			}
			if(temp1->left == NULL  &&  temp1->right == NULL)// if temp is a leaf node
			{
				 delete_leaf_node(temp);//p
			}
			

		}//end of else;
	} 

	
}


//to delete a node with two childrens	FIRST
//find the smallest value in the right subtree of the given node OR 
//FIND the largest value in the left subtree  of the given node.
//then copy the largst value of left subtree or smallest value of right subtree
//to the node to be deleted then delete the node having largest value in left subtree
//or smallest value in right subtree

void BinaryTree::delete_node_having_both_left_and_right_child(node*temp,node*tmp)//tmp= q->left .......temp =q
{
	
	if(tmp->right != NULL && tmp->left != NULL)
	{
		node*t1 = tmp->right;
		int save=0;

		//finding predecessor in t1

		while(t1->right!=NULL)
		{
			t1=t1->right;
			save = t1->data;
			tmp=tmp->right;
		}
		temp->data = save;//temp=q

		if(t1->left!=NULL && t1->right==NULL)
		{
			node*n= t1->left;
			tmp->right=NULL;
			t1->left=NULL;
			delete t1;

			if(tmp->data > n->data)
			{
				tmp->left=n;
			}
			else   //(t->data > nod->data)
			{
				tmp->right=n;
			}
		
		}
		else//if(t1->left==NULL && t1->right==NULL)
		{
				tmp->right = NULL;
				delete t1;
		}
	}

//if(tmp->right == NULL && tmp->left == NULL)
//
//	{
//		temp->data = tmp->data;
//		temp->left=NULL;
//
//		delete tmp;
//	}
	//if(tmp->right == NULL && tmp->left != NULL)
	//{
	//	node*t=tmp->left ;
	//	temp->data = tmp->data;
	//	temp->left = NULL;

	//	tmp->left = NULL;

	//	delete tmp;
	//	temp->left=t;
	//}
   
}


void BinaryTree::delete_leaf_node(node*nod)//nod==p
{
	node* tmp;

	if(nod->left!= NULL)
	{
		tmp=nod->left;
		nod->left=NULL;
	
	}
	else if(nod->right!=NULL)
	{
		tmp=nod->right;
		nod->right=NULL;
	}
	
	delete tmp;
}
void BinaryTree::delete_node_having_1_left_child(node*nod, int val)// nod is p here
{

	node*t;
	node*t1;

	if(nod->data > val)
	{
		t = nod->left;
		nod->left = NULL;
	}
	else  //(nod->data < val)
	{
		t = nod->right; 
		nod->right = NULL;
	}

	t1= t->left;
	t->left=NULL;

	delete t;

	if(nod->data > t1->data)
	{
		nod->left = t1;
	}
	else  //(nod->data < t1->data)
	{
		nod->right = t1;
	}

}
void BinaryTree::delete_node_having_1_right_child(node*nod,int val)
{
	node*t;
	node*t1;
	 
	if(nod->data > val)
	{
		t = nod->left;
		nod->left = NULL;
	}
	else  //(nod->data < val)
	{
		t = nod->right; 
		nod->right = NULL;
	}

	t1= t->right;
	t->right=NULL;

	delete t;

	if(nod->data > t1->data)
	{
		nod->left = t1;
	}
	else  //(nod->data < t1->data)
	{
		nod->right = t1;
	}
}


//function to search value in binary tree---------------------------------------------------------------------------------------------
void BinaryTree::search_node(void)
{
	system("cls");

	int val;
	bool found = false;
	node*temp=root;

	cout<<"enter the value you want to search";
	cin>>val;
	
	if(root==NULL )
	{
		cerr<<"can not search empty tree";
	}
	else
	{
		while(temp!=NULL && found!=true)
		{
			if(temp->data==val)
			{
				found=true;
			}
			else
			{
			
				if(temp->data > val)
				{
					temp=temp->left;
				}

				else //if(temp->data < val)
				{
					temp=temp->right;
				}
			}//end of else...
		}//end of while..
	

		if(found!=true)//if value is not found then loop will not reak and end with temp==NULL
		{
			cout<<"\n\nvalue not found in TREE";
		}
		else
		{
			cout<<"value found : "<<temp->data;
		}
	} //end of else;
}

//printing functions in pre,in and post order
//function for pre order traversal
void BinaryTree:: pre_order(node*temp)
{

	if(temp!=NULL)
	{
		cout<<temp->data<<"\t";
		
		pre_order(temp->left);
		pre_order(temp->right);
	}

}//end of pre order function

//function for in order traversal
void BinaryTree::in_order(node*temp)//also used for sorting
{

	if(temp!=NULL)
	{
		in_order(temp->left);
		cout<<temp->data<<"\t";
		in_order(temp->right);
	}

}//end of in order function

//function for post order traversal
void BinaryTree::post_order(node*temp)
{
	if(temp!=NULL)
	{
		post_order(temp->left);
		post_order(temp->right);
		cout<<temp->data<<"\t";
	}
}//end of post order function

void main()
{
	BinaryTree obj;
	node *t;
	char ch;

main_menu:
			system("cls");

			cout<<"press a to insert\n\n";
			cout<<"press b to traverse pre-order\n\n";
			cout<<"press c to traverse in-order\n\n";
			cout<<"press d to traverse post-order\n\n";
			cout<<"press f to search a value\n\n";
			cout<<"press g to delete a value\n\n";
			cout<<"press e to exit\n\n";

			ch=getch();


				if(ch=='a')
				{
					char c;
					int m;
						again:
								
								system("cls");	

								obj.insert();//calling insert function

								cout<<"press a to insert again\n\n";
								
								c=getch();

								if(c=='a')
								{
										goto again;
								}
								else
								{
										goto main_menu;
								}
				}



				if(ch=='b')
				{
						  system("cls");
							t=obj.root;
						cout<<"pre-order : \n\n";
					    obj.pre_order(t);

						getch();

						goto main_menu;


				}

				if(ch=='c')
				{
						  // system("cls");
						   t=obj.root;
						   cout<<"in-order : \n\n";
						  obj.in_order(t);

						getch();

						goto main_menu;
				}
				if(ch=='d')
				{
						  //system("cls");
						  t=obj.root;
						  cout<<"post-order : \n";
						  obj.post_order(t);

						getch();

						goto main_menu;

				}

				if(ch=='f')
				{
						  //system("cls");
						  obj.search_node();

						  getch();

						  goto main_menu;
				}
				if(ch=='g')
				{
					obj.Delete();
					 getch();
					 goto main_menu;
				}

				if(ch=='e')
				{
						exit(0);
				}

			
		getch();

}
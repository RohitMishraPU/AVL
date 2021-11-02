#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
#include<dos.h>

// An AVL tree node
struct node
{

    int key;
    struct node *left;
    struct node *right;
    int height;
}*root=NULL;
int maxx,midx,x,y,level=255,c=0;
char str[10];
int balance;

void display(struct node *p,int x,int y,int k)
{
  if (p!=NULL)
	{
	   level=level/2;
	   setcolor(BLACK);
	   settextstyle(4,0,4);
	   outtextxy(208,3,"AVL Tree Rotation");

	   setfillstyle(1,BLUE);
	   setcolor(BLACK);
	   if(p->left->key!=0)
		line(x,y,x-level-10,y+50);
	   if(p->right->key!=0)
		line(x,y,x+level-10,y+50);
	   fillellipse(x,y,20,20);
	   sprintf(str,"%d",p->key,x,y);
	   settextstyle(2,0,4);
	   setcolor(YELLOW);
	   outtextxy(x-7,y-7,str);
	   display(p->left,x-(level),y+50,c);
	   display(p->right,x+(level),y+50,c);
	   level=level*2;
	   settextstyle(6,0,1);
	   setcolor(RED);
	    if(k==1)
	    outtextxy(40,50,"Left Left Rotation");
	   if(k==2)
	    outtextxy(40,50,"Right Right Rotation");
	   if(k==3)
	     outtextxy(40,50,"Left Right Rotation");
	   if(k==4)
	     outtextxy(40,50,"Right Left Rotation");
	   //c=0;
	}
}


// A utility function to get maximum of two integers
int maximum(int a, int b)
{
	return ((a > b)? a : b);
}


// A utility function to get height of the tree
int height(struct node *N)
{
    if (N == NULL)
	return 0;
    return N->height;
}
struct node* newNode(int key)
{
    struct node* node = (struct node*)
			malloc(sizeof(struct node));
    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;
	//draw(key);
  /*;*/
	// new node is initially added at leaf
    return(node);
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct node *rightRotate(struct node *y)
{
    struct node *x = y->left;
    struct node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = maximum(height(y->left), height(y->right))+1;
    x->height = maximum(height(x->left), height(x->right))+1;

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct node *leftRotate(struct node *x)
{
    struct node *y = x->right;
    struct node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = maximum(height(x->left), height(x->right))+1;
    y->height = maximum(height(y->left), height(y->right))+1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(struct node *N)
{
    if (N == NULL)
	return 0;
    return height(N->left) - height(N->right);
}

struct node* insert(struct node* node, int key)
{
    //int balance;
    /* 1.  Perform the normal BST rotation */
    if (node == NULL)
    {
	//draw(key);
	return(newNode(key));
	}


    if (key < node->key)
    {
	//l=1;
	node->left  = insert(node->left, key);

	//draw(key);
	}

    else
    {
	node->right = insert(node->right, key);
	}
    node->height = maximum(height(node->left), height(node->right)) + 1;

    balance = getBalance(node);
    //getch();
    if(balance > 1 || balance < -1)
    {
       //outtextxy(100,20,"Before rotation ");
			maxx=getmaxx();
			midx=maxx/2;
			x=midx+20/2;
			y=65;
			clrscr();
			display(root,x,y,c);
			settextstyle(8,0,1);
			outtextxy(220,getmaxy()-150,"The tree before rotation");
			outtextxy(208,getmaxy()-135,"Now it's going to be ROTATE");
			getch();
			cleardevice();
    if (balance > 1 && key < node->left->key)
    {   c=2;
	return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && key > node->right->key)
    {   c=1;
	return leftRotate(node);
    }
    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {   c=3;
	node->left =  leftRotate(node->left);
	return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {   c=4;
	node->right = rightRotate(node->right);
	return leftRotate(node);
    }
		       /*	delay(1000);
			maxx=getmaxx();
			midx=maxx/2;
			x=midx+20/2;
			y=65;
			clrscr();
			display(root,x,y,c);
			//settextstyle(3,0,4);
			//outtextxy(220,getmaxy()-150,"Rotatin");
			getch();
			cleardevice();
			//printf("hey");*/
    }
    /* return the (unchanged) node pointer */
	//printf("hey");
    return node;
}
/*struct node* rotate(struct node *node)
{      balance = getBalance(node);
    if (balance > 1 && node->key < (node->left)->key)
    {   c=2;
      //	printf("hii");
	return rightRotate(node);
    }
    if (balance < -1 && node->key > (node->right)->key)
    {   c=1;
    //printf("hii");
	return leftRotate(node);
    }
    // Left Right Case
    if (balance > 1 && node->key > (node->left)->key)
    {   c=3;
   // printf("hii");
	node->left =  leftRotate(node->left);
	return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && node->key < node->right->key)
    {   c=4;
    //printf("hii");
	node->right = rightRotate(node->right);
	return leftRotate(node);
    }
  return node;
}*/
void preOrder(struct node *root)
{
    if(root != NULL)
    {
	printf("%d ", root->key);
	preOrder(root->left);
	preOrder(root->right);
    }
}

void main()
{
  //struct node *root = NULL;
  int answer,data;
  int gd=DETECT,gm;
  initgraph(&gd,&gm,"C:\\Turboc3\\BGI");
  while(1)
  {		clrscr();
		gotoxy(27,23);
		printf("Created By ROHIT");
		gotoxy(25,2);
		printf("*** Assignment First Semester ***\n");
		gotoxy(25,4);
		printf("     ***** AVL Rotation *****     \n");
		gotoxy(3,7);
		printf("Press 1 to insert                      \n");
		gotoxy(3,8);
		printf("Press 2 for pre-order traversal        \n");
		gotoxy(3,9);
		printf("Press 3 to display  tree after ROTATION\n");
		//printf("Press 4 rotate \n");
		gotoxy(3,10);
		printf("Press 4 to exit  	                 \n");
		gotoxy(3,12);
		printf("Enter your choice - ");
		scanf("%d",&answer);


		//getch();
		switch(answer)
		{
			case 1:         gotoxy(3,12);
					printf("Enter data to be inserted = ");
					scanf("%d",&data);
					root = insert(root,data);
					break;
			case 2:
					gotoxy(3,12);
					printf("Pre order traversal of the constructed AVL tree is \n");
					preOrder(root);
					getch();
					break;
			case 3: maxx=getmaxx();
				midx=maxx/2;
				x=midx+20/2;
				y=65;
				clrscr();
				display(root,x,y,c);
				getch();
				cleardevice();
				c=0;
				break;
			/*case 4:root=rotate(root);
				getch();
			       break;
			*/case 4:closegraph();
				 exit(0);
			default:
				gotoxy(3,12);
				printf("Invalid choice.........");
				getch();
		}
	}

}
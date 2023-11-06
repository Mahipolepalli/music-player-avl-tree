#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100
#define NUMBER_OF_SONGS 26
#define NUMBER_OF_ATTRIBUTES 2
typedef struct song_details_Tag
{
   char name[SIZE];
   char singer[SIZE];
   char lyricist[SIZE];
   char composer[SIZE];
   char album[SIZE];
   char genre[SIZE];
   char duration[SIZE];
}song_details;

typedef struct TreeNode_Tag
{
   song_details song;
   struct TreeNode_Tag *left;
   struct TreeNode_Tag *right;
   int left_height;
   int right_height;
}TreeNode;

TreeNode* createTreeNode(song_details s)
{
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
      fflush(stdin);
      strcpy(newNode->song.name,s.name);
      fflush(stdin);
      strcpy(newNode->song.singer,s.singer);
      fflush(stdin);
      strcpy(newNode->song.lyricist,s.lyricist);
      fflush(stdin);
      strcpy(newNode->song.album,s.album);
      fflush(stdin);
      strcpy(newNode->song.composer,s.composer);
      fflush(stdin);
      strcpy(newNode->song.genre,s.genre);
      fflush(stdin);
      strcpy(newNode->song.duration,s.duration);
      fflush(stdin);
      newNode->left = newNode->right = NULL;
      newNode->left_height = 0;
      newNode->right_height = 0;
      return newNode;
}

void visit(TreeNode *node)
{
   if(node != NULL)
   {
     printf("LH:%d,RH:%d,%s",node->left_height,node->right_height,node->song.name);
     printf("%s",node->song.singer);
     printf("\n");
   }
}

// void visit(TreeNode *node)
// {
//    if(node != NULL)
//    {
//      printf("LH:%d,RH:%d,%s",node->left_height,node->right_height,node->song.name);
//      printf("%s",node->song.singer);
//      printf("%s",node->song.lyricist);
//      printf("%s",node->song.album);
//      printf("%s",node->song.composer);
//      printf("%s",node->song.genre);
//      printf("%s",node->song.duration);
//      printf("\n");
//    }
// }
void printChild(TreeNode *node)
{
   if(node != NULL)
   {
     printf("%s",node->song.name);
   }  
}
typedef struct Node_tag
{
    TreeNode *data;
    struct Node_tag *next;
}Node;

typedef struct queue_tag
{
  Node *head;
  Node *tail; 
}queue;

void initialize(queue *q)
{
  q->head = q->tail = NULL;
}

Node* createNode(TreeNode *node)
{
    Node *newNode =(Node*) malloc(sizeof(Node));
    newNode->data = node;
    newNode->next = NULL;
    return newNode;
}
void push(queue *q,TreeNode *node)
{
  Node *newNode = createNode(node);
  if(q->head == NULL)
  {
   q->head = q->tail = newNode;
  }
  else
  {
    q->tail = q->tail->next  = newNode;
  }
}


void pop(queue *q)
{
    if(q->head != NULL)
    {
       if(q->head->next == NULL)
       {
           free(q->head);
           q->head = q->tail = NULL;
       }
       else
       {
          Node* temp = q->head;
          q->head = q->head->next;
          temp->next = NULL;
          free(temp);
       }
    }
}
int empty(queue *q)
{
    int isEmpty;
    if(q->head == NULL)
    {
        isEmpty = 1;
    }
    else
    {
        isEmpty = 0;
    }
    return isEmpty;
}
TreeNode* front(queue *q)
{
    TreeNode* f = NULL;
    if(q->head != NULL)
    {
        f = q->head->data;
    }
    return f;
}

typedef struct stack_tag
{
  Node *head;
}stack;

void initialize_stack(stack *s)
{
  s->head = NULL;
}

void push_stack(stack *s,TreeNode *node)
{
 Node* newNode = createNode(node);
 newNode->next = s->head;
 s->head = newNode;
}

void pop_stack(stack *s)
{
    if(s->head != NULL)
    {
     Node* temp = s->head;
     s->head = s->head->next;
     free(temp); 
    }
}

int empty_stack(stack *s)
{
    int isEmpty;
    if(s->head == NULL)
    {
        isEmpty = 1;
    }
    else
    {
        isEmpty = 0;
    }
    return isEmpty;
}

TreeNode* top_stack(stack *s)
{
    TreeNode* t = NULL;
    if(s->head != NULL)
    {
        t = s->head->data;
    }
    return t;
}

void  PrintLevelWise(TreeNode* root)
{
    queue parent;
    int level = 1;
  // int serial_number = 1;
    initialize(&parent);

    if(root != NULL)
    {
        push(&parent,root);
    }

    while(empty(&parent) == 0)
    {
        queue child;
        initialize(&child);
        printf("Level : %d\n",level);
        while(empty(&parent) == 0)
        {
            TreeNode* temp = front(&parent);
            visit(temp);
            pop(&parent);
            push(&child,temp);
            if(temp->left != NULL)
            {
              printf("LC:");
              printChild(temp->left);
            }
            else
            {
              printf("LC:\n");
            }
            if(temp->right != NULL)
            {
              printf("RC:");
              printChild(temp->right);
            }
            else
            {
              printf("RC:\n");
            }
        }
        level++;
        printf("\n");
        while(empty(&child) == 0)
        {
            TreeNode *temp = front(&child);
            
            if(temp->left != NULL)
            {
                push(&parent,temp->left);
            }
            if(temp->right != NULL)
            {
                push(&parent,temp->right);
            }
            pop(&child);
        }
    }
    printf("\n");
}

void  Display(TreeNode* root)
{
    queue parent;
    int serial_number = 1;
    initialize(&parent);

    if(root != NULL)
    {
        push(&parent,root);
    }

    while(empty(&parent) == 0)
    {
      printf("%d\n",serial_number);
      TreeNode* temp = front(&parent);
      visit(temp);
      if(temp->left != NULL)
      {
        push(&parent,temp->left);
      }   
      if(temp->right != NULL)
      {
        push(&parent,temp->right);
      }    
      serial_number++; 
      pop(&parent);   
    }
}

/* 
		 r                              x
		/ \      rotate right         /   \
	       x   T3   -------------->      T1    r
	      / \	<--------------           / \
	     T1 T2       rotate left             T2  T3
*/

TreeNode* RightRotate(TreeNode* root)
{
 if(root != NULL)
 {
   TreeNode* r = root;
   if(r->left != NULL)
   {
      TreeNode* x = r->left;
      r->left = x->right;
      x->right = r;
      int t2 = x->right_height;
      int t3=r->right_height;
      if(t2>t3)
      {
          x->right_height=t2+1;
      }
      else
      {
	  x->right_height=t3+1;
      }
      root = x;
   }
 }
 return root;
}

TreeNode* LeftRotate(TreeNode* root)
{
   if(root != NULL)
   {
     TreeNode* x = root;
     if(x->right != NULL)
     {
       TreeNode* r= x->right;
       x->right = r->left;
       r->left = x;
       int t1 = x->left_height;
       int t3=r->right_height;
       if(t1>t3)
      {
          x->left_height=t1+1;
      }
      else
      {
	  x->left_height=t3+1;
      }
       root = r;
     }
   }
   return root;
}

// char **attribute;
// attrribute = (char**)malloc(sizeof(char*)*NUMBER_OF_ATTRIBUTES);
// for(int i=0; i<NUMBER_OF_ATTRIBUTES; i++)
// {
//   attribute[i]=(char*)malloc(sizeof(char)*NUMBER_OF_ATTRIBUTES);
// }
// //
// attribute[0] = "name";
// attribute[1] = "singer";
typedef struct Triplet_tag
{
   TreeNode *node;
   int isRotated;
   int heightDifference;
}Triplet;

Triplet insert_name(TreeNode* root,song_details song)
{ 
   Triplet ret_val;
   if(root == NULL)
   {
      ret_val.node = createTreeNode(song);
      ret_val.isRotated = 0;
      ret_val.heightDifference=0;
   }
   else
   {
      if(strcmp(song.name,root->song.name) < 0)
      {
          TreeNode* temp = root->left;
          ret_val = insert_name(root->left,song);
          root->left = ret_val.node;

          if((temp == NULL)||(!ret_val.isRotated && ret_val.heightDifference != 0))
          {
            root->left_height++;
            ret_val.heightDifference = root->left_height-root->right_height;           
          }
          ret_val.node = root;
      }
      else
      {
          TreeNode* temp = root->right;
          ret_val = insert_name(root->right,song);
          root->right = ret_val.node;

          if((temp == NULL)||(!ret_val.isRotated && ret_val.heightDifference != 0))
          {
            root->right_height++;
            ret_val.heightDifference = root->right_height-root->left_height;           
          }

          ret_val.node = root;
      }
   int balance_factor = root->left_height - root->right_height;

   if(balance_factor == 2)
   {
      
      if(strcmp(song.name,root->left->song.name) < 0)
      {
         //LL case
         //printf("LL\n");
        root = RightRotate(root);
      }
      else
      {
         //LR case
         //printf("LR\n");
         root->left = LeftRotate(root->left);
         root = RightRotate(root);
      }
       ret_val.isRotated = 1;
       ret_val.node = root;
   }
   else if(balance_factor == -2)
   {     
      if(strcmp(song.name,root->right->song.name) >= 0)
      {
        //RR case
        //printf("RR\n");
        root = LeftRotate(root);
      }
      else
      {
         //RL case
         //printf("RL\n");
         root->right = RightRotate(root->right);
         root = LeftRotate(root);
      }
       ret_val.isRotated = 1;
       ret_val.node = root;
   }
   }  
  return ret_val;
}

TreeNode* TakeInput()
{
  TreeNode* root = NULL;
  FILE* fptr;
  Triplet val;
  fptr = fopen("DSPD2_InputFile.txt","r");
  if(fptr == NULL)
  {
   printf("Cannot open file\n");
  }
  else
  {
  song_details s;
  for(int i=1; i<=NUMBER_OF_SONGS; i++)
  {
   fgets(s.name,SIZE,fptr);
   fflush(stdin);
   fgets(s.singer,SIZE,fptr);
   fflush(stdin);
   fgets(s.lyricist,SIZE,fptr);
   fflush(stdin);
   fgets(s.album,SIZE,fptr);
   fflush(stdin);
   fgets(s.composer,SIZE,fptr);
   fflush(stdin);
   fgets(s.genre,SIZE,fptr);
   fflush(stdin);
   fgets(s.duration,SIZE,fptr);  
   fflush(stdin);

   Triplet ret_val = insert_name(root,s);
   root = ret_val.node;
  }
  }
  fclose(fptr);
  return root;
}

Triplet insert_singer_based(TreeNode* root,song_details song)
{ 
   Triplet ret_val;
   if(root == NULL)
   {
      ret_val.node = createTreeNode(song);
      ret_val.isRotated = 0;
      ret_val.heightDifference=0;
   }
   else
   {
      if(strcmp(song.singer,root->song.singer) < 0)
      {
          TreeNode* temp = root->left;
          ret_val = insert_singer_based(root->left,song);
          root->left = ret_val.node;

          if((temp == NULL)||(!ret_val.isRotated && ret_val.heightDifference != 0))
          {
            root->left_height++;
            ret_val.heightDifference = root->left_height-root->right_height;           
          }
          ret_val.node = root;
      }
      else
      {
          TreeNode* temp = root->right;
          ret_val = insert_singer_based(root->right,song);
          root->right = ret_val.node;

          if((temp == NULL)||(!ret_val.isRotated && ret_val.heightDifference != 0))
          {
            root->right_height++;
            ret_val.heightDifference = root->right_height-root->left_height;           
          }

          ret_val.node = root;
      }
   int balance_factor = root->left_height - root->right_height;

   if(balance_factor == 2)
   {
      
      if(strcmp(song.singer,root->left->song.singer) < 0)
      {
         //LL case
         //printf("LL\n");
        root = RightRotate(root);
      }
      else
      {
         //LR case
         //printf("LR\n");
         root->left = LeftRotate(root->left);
         root = RightRotate(root);
      }
       ret_val.isRotated = 1;
       ret_val.node = root;
   }
   else if(balance_factor == -2)
   {     
      if(strcmp(song.singer,root->right->song.singer) >= 0)
      {
        //RR case
        //printf("RR\n");
        root = LeftRotate(root);
      }
      else
      {
         //RL case
         //printf("RL\n");
         root->right = RightRotate(root->right);
         root = LeftRotate(root);
      }
       ret_val.isRotated = 1;
       ret_val.node = root;
   }
   }  
  return ret_val;
}

TreeNode* Insertion_Singer_Based(TreeNode* root,song_details song)
{
  return insert_singer_based(root,song).node;
}


TreeNode* TakeInput_Based_On_Singer()
{
  TreeNode* root = NULL;
  FILE* fptr;
  Triplet val;
  fptr = fopen("DSPD2_InputFile.txt","r");
  if(fptr == NULL)
  {
   printf("Cannot open file\n");
  }
  else
  {
  song_details s;
  for(int i=1; i<=NUMBER_OF_SONGS; i++)
  {
   fgets(s.name,SIZE,fptr);
   fflush(stdin);
   fgets(s.singer,SIZE,fptr);
   fflush(stdin);
   fgets(s.lyricist,SIZE,fptr);
   fflush(stdin);
   fgets(s.album,SIZE,fptr);
   fflush(stdin);
   fgets(s.composer,SIZE,fptr);
   fflush(stdin);
   fgets(s.genre,SIZE,fptr);
   fflush(stdin);
   fgets(s.duration,SIZE,fptr);  
   fflush(stdin);

   Triplet ret_val = insert_singer_based(root,s);
   root = ret_val.node;
  }
  }
  fclose(fptr);
  return root;
}

/*************************************************/
//DELETION

typedef struct Pair_Tag
{
 TreeNode* node;
 int isRotated;
 int decreaseHeight;
}Pair;

void replace_song_details(TreeNode* root,TreeNode* maxNode)
{
  fflush(stdin);
   strcpy(root->song.name,maxNode->song.name);
  fflush(stdin);
   strcpy(root->song.singer,maxNode->song.singer);
  fflush(stdin);
   strcpy(root->song.lyricist,maxNode->song.lyricist);
  fflush(stdin);
   strcpy(root->song.composer,maxNode->song.composer);
  fflush(stdin);
   strcpy(root->song.album,maxNode->song.album);
  fflush(stdin);
   strcpy(root->song.genre,maxNode->song.genre);
  fflush(stdin);
   strcpy(root->song.duration,maxNode->song.duration);
  // printf("Copied succesfully\n");
}
Pair delete_song(TreeNode* root,char* song_name);

Pair delete_song(TreeNode* root,char* song_name)
{
   Pair ret_val;
  if(root == NULL)
  {
    //("SONG not found\n");
    ret_val.node = NULL;
    ret_val.decreaseHeight = 0;
    ret_val.isRotated = 0;
  }
  else
  {
    if(strcmp(root->song.name,song_name) > 0)
    {
      //printf("Entered left\n");
      int sameHeight = 0;
        if(root->left_height == root->right_height)
        {
          sameHeight = 1;
        }
       ret_val = delete_song(root->left,song_name);
      // printf("returned into left\n");
       root->left = ret_val.node;
       ret_val.node = root;
       if((ret_val.decreaseHeight) || ret_val.isRotated)
       {
        root->left_height--;
       }
       if(sameHeight)
       {
        ret_val.decreaseHeight = 0;
       }
       
    }
    else if(strcmp(root->song.name,song_name) < 0)
    {
      //printf("Entered right\n");
      int sameHeight = 0;

        if(root->left_height == root->right_height)
        {
          sameHeight = 1;
        }
       ret_val = delete_song(root->right,song_name);
        //printf("returned into right\n");
       root->right = ret_val.node;
       ret_val.node = root;     

       if((ret_val.decreaseHeight) || ret_val.isRotated)
       {
        root->right_height--;
       }
       if(sameHeight)
       {
        ret_val.decreaseHeight = 0;
       }     
    }
    else
    {
       ret_val.decreaseHeight = 1;
       ret_val.isRotated = 0;
       if(root->left == NULL && root->right == NULL)
       {
         //printf("Both Child NULL case\n");
         free(root);
         ret_val.node = NULL;
       }
       else if(root->left == NULL)
       {
         //printf("Left Child NULL case\n");
         ret_val.node = root->right;
         root->right = NULL;
         free(root);
       }
       else if(root->right == NULL)
       {
         //printf("Right Child NULL case\n");
         ret_val.node = root->left;
         root->left = NULL;
         free(root);      
       }
       else
       {
         //printf("Both child not NULL ");
         TreeNode* max_node = root->left;
         while(max_node->right != NULL)
         {
          max_node = max_node->right;
         }
        replace_song_details(root,max_node);
         int sameHeight = 0;
         if(root->left_height == root->right_height)
         {
           sameHeight = 1;
         }
          ret_val  = delete_song(root->left,max_node->song.name);
          root->left = ret_val.node;
          ret_val.node = root;
       if((ret_val.decreaseHeight) || ret_val.isRotated)
       {
        root->left_height--;
       }
       if(sameHeight)
       {
        ret_val.decreaseHeight = 0;
       }
       }
    }

  int balance_factor = root->left_height - root->right_height;

   if(balance_factor == 2)
   {
      int small_balance_factor = root->left->left_height-root->left->right_height;      
      if(small_balance_factor == 1)
      {
         //LL case
         //printf("LL\n");
        root = RightRotate(root);
      }
      else if(small_balance_factor == -1)
      {
         //LR case
         //printf("LR\n");
         root->left = LeftRotate(root->left);
         root = RightRotate(root);
      }
       ret_val.isRotated = 1;
       ret_val.node = root;
   }
   else if(balance_factor == -2)
   {   
    int small_balance_factor = root->right->left_height-root->right->right_height;
      if(small_balance_factor == -1)
      {
        //RR case
        //printf("RR\n");
        root = LeftRotate(root);
      }
      else if(small_balance_factor == 1)
      {
         //RL case
         //printf("RL\n");
         root->right = RightRotate(root->right);
         root = LeftRotate(root);
      }
       ret_val.isRotated = 1;
       ret_val.node = root;
   }
  }
  return ret_val;
}

TreeNode* Deletion(TreeNode* root,char* song_name)
{
   Pair ret_val;
   ret_val = delete_song(root,song_name);
   return ret_val.node;
}

//Q1
TreeNode* Insertion(TreeNode* root,song_details song)
{
   return insert_name(root,song).node;
}

int hasDuplicate(TreeNode *root,char *song_name)
{
  int ret_val;
  if(root == NULL)
  {
    ret_val = 0;
  }
  else
  {
    if(strcmp(root->song.name,song_name) == 0)
    {
      ret_val = 1;
    }
    else if(strcmp(root->song.name,song_name) > 0)
    {
      ret_val = hasDuplicate(root->left,song_name);
    }
    else
    {
       ret_val = hasDuplicate(root->right,song_name);
    }
  }
  return ret_val;
}

//Q2
TreeNode* RemoveDuplicates(TreeNode* root)
{
queue q;
initialize(&q);
if(root != NULL)
{
 while(root!=NULL && (hasDuplicate(root->right,root->song.name)||hasDuplicate(root->right,root->song.name)))
 {
  printf("W.Duplicate:%s",root->song.name);
   root = Deletion(root,root->song.name);
 }
}
if(root != NULL)
{
  push(&q,root);
}
 while(!empty(&q))
 {
  TreeNode* temp = front(&q);
  int ret_val = 0;
  if(temp->left != NULL)
  {
    while(hasDuplicate(temp->left->left,temp->left->song.name) || hasDuplicate(temp->left->right,temp->left->song.name))
    {
     root = Deletion(root,temp->left->song.name);
    }
  }

  if(temp->right != NULL)
  {
     while(hasDuplicate(temp->right->left,temp->right->song.name) || hasDuplicate(temp->right->right,temp->right->song.name))
     {
      root = Deletion(root,temp->right->song.name);
     }
  }

  if(temp->left != NULL)
  {
    push(&q,temp->left);
  }
  if(temp->right != NULL)
  {
    push(&q,temp->right);
  }
  pop(&q);
 }
 return root;
}
//Q3
void PrintPlaylistAscending(TreeNode* root)
{
  if(root != NULL)
  {
   PrintPlaylistAscending(root->left);
   visit(root);
   PrintPlaylistAscending(root->right);
  }
}

void PrintPlaylistDescending(TreeNode* root)
{
  if(root != NULL)
  {
   PrintPlaylistDescending(root->right);
   visit(root);
   PrintPlaylistDescending(root->left);
  }
}

//Q4
TreeNode* DeleteWithAritistAttribute(TreeNode* root,char *attribute_value)
{
  queue q;
  initialize(&q);
  if(root != NULL)
  {
  while(root != NULL && strcmp(root->song.singer,attribute_value) == 0)
  {
    printf("%s",root->song.name);
    root = Deletion(root,root->song.name);
  }
  if(root != NULL)
  {
    push(&q,root);
  }
  }


  while(!empty(&q))
  {
    TreeNode *temp = front(&q);
    if(temp->left != NULL)
    {
      while(temp->left != NULL && strcmp(temp->left->song.singer,attribute_value) == 0)
      {
        printf("%s",root->song.name);
        root = Deletion(root,temp->left->song.name);
      }
    }
    if(temp->right != NULL)
    {
      while(temp->right != NULL && strcmp(temp->right->song.singer,attribute_value) == 0)
      {
        root = Deletion(root,temp->right->song.name);
      }
    }
    if(temp->left != NULL)
    {
      push(&q,temp->left);
    }
    if(temp->right != NULL)
    {
      push(&q,temp->right);
    }
    pop(&q);
  }
  return root;
}

//5 helper
TreeNode* Q5_helper(TreeNode* root,TreeNode* MyPlaylist,char **attribute,char **attribute_value,int number_of_attributes)
{
 if(root == NULL)
 {
    printf("Empty Playlist !!!");
    MyPlaylist = NULL;
 }
 else
 {
  int attribute_count = 0;
  for(int i=0; i<number_of_attributes; i++)
  {
    if(strcmp(attribute[i],"singer\n") == 0 && strcmp(root->song.singer,attribute_value[i])==0)
    {
     attribute_count++;
    }
    else if(strcmp(attribute[i],"lyricist\n") == 0 && strcmp(root->song.lyricist,attribute_value[i])==0)
    {
     attribute_count++;
    }
    else if(strcmp(attribute[i],"album\n") == 0 && strcmp(root->song.album,attribute_value[i])==0)
    {
     attribute_count++;
    }
    else if(strcmp(attribute[i],"composer\n") == 0 && strcmp(root->song.composer,attribute_value[i])==0)
    {
     attribute_count++;
    }
    else if(strcmp(attribute[i],"genre\n") == 0 && strcmp(root->song.genre,attribute_value[i])==0)
    {
     attribute_count++;
    }
  }
  if(attribute_count == number_of_attributes)
  {
    MyPlaylist = Insertion(MyPlaylist,root->song);
  }
  if(root->left != NULL)
  {
    MyPlaylist = Q5_helper(root->left,MyPlaylist,attribute,attribute_value,number_of_attributes);
  }
  if(root->right != NULL)
  {
    MyPlaylist = Q5_helper(root->right,MyPlaylist,attribute,attribute_value,number_of_attributes);
  }
 }
 return MyPlaylist;
}
//5
TreeNode* createPlaylist_Based_On_Multiple_Attributes(TreeNode* root)
{
  TreeNode* MyPlaylist = NULL;
  int number_of_attributes;
  printf("Enter number of attributes : ");
  scanf("%d",&number_of_attributes);
 char **attribute,**attribute_value;
 attribute = (char**)malloc(sizeof(char*)*number_of_attributes);
 attribute_value = (char**)malloc(sizeof(char*)*number_of_attributes);
for(int i=0; i<number_of_attributes; i++)
{
  attribute[i]=(char*)malloc(sizeof(char)*SIZE);
  attribute_value[i]=(char*)malloc(sizeof(char)*SIZE);
}

for(int i=0; i<number_of_attributes; i++)
{
  printf("Enter attribute :\n");
  fflush(stdin);
  fgets(attribute[i],SIZE,stdin);
  printf("Enter attribute value :\n");
  fflush(stdin);
  fgets(attribute_value[i],SIZE,stdin);
}
 
MyPlaylist =  Q5_helper(root,MyPlaylist,attribute,attribute_value,number_of_attributes);
return MyPlaylist;

}

//Q6
void  DisplayASongAndItsNextPrev(TreeNode* root,int k)
{
     queue q;
     initialize(&q);
     stack s;
     initialize_stack(&s);
     char option[SIZE];
     int serial_number = 0,song_found = 0;
     if(root != NULL)
     {
      push(&q,root);
     }
     while(empty(&q) == 0 && song_found == 0)
     {
        TreeNode* temp = front(&q);
        serial_number++;
        if(k==serial_number)
        {
          visit(temp);
          song_found = 1;
        }
        else
        {
           push_stack(&s,temp);
        }
          if(temp->left != NULL)
          {
            push(&q,temp->left);
          }
          if(temp->right != NULL)
          {
            push(&q,temp->right);
          }
          pop(&q);
     }

     if(song_found)
     {
      TreeNode* song = front(&q);
      //visit(song);
      printf("Enter next or prev : ");
      scanf("%s",option);
      if(strcmp(option,"next") == 0)
      {
        if(empty(&q) == 1)
        {
          printf("No next song\n");
        }
        else
        {
          visit(front(&q));
        }
      }
      else if(strcmp(option,"prev") == 0)
      {
         if(empty_stack(&s) == 1)
         {
          printf("No previous song\n");
         }
         else
         {
          visit(top_stack(&s));
         }
      }
     }
     else
     {
      printf("Song not found\n");
     }
}

//Q7
void Kth_NextSongOrPreviousSong(TreeNode* root,int serial_number,int offset)
{
     queue q;
     initialize(&q);
     stack prev_song;
     initialize_stack(&prev_song);
     queue next_song;
     initialize(&next_song);
     char option[SIZE];
     int k = 0,song_found = 0;
     TreeNode *song = NULL;
     if(root != NULL)
     {
      push(&q,root);
     } 
     while(empty(&q) == 0)
     {
      TreeNode* temp = front(&q);
       k++;
       if(k<serial_number)
       {
       // visit(temp);
        push_stack(&prev_song,temp);
        //printf("%d\n",empty_stack(&prev_song));
       // printf("Size : %d\n",sizeOfStack(&prev_song));
       }
       else if(k == serial_number)
       {
          song_found = 1;
          song = temp;
       }
       else
       {
          push(&next_song,temp);
       }
       if(temp->left != NULL)
       {
        push(&q,temp->left);
       }
       if(temp->right != NULL)
       {
        push(&q,temp->right);
       }
       pop(&q);
     }    

    if(song_found)
    {
      printf("Your desired song \n");
     visit(song);
     printf("Enter direction up or down : ");
     scanf("%s",option);

     if(strcmp(option,"up") == 0)
     {
      //printf("Size : %d",sizeOfStack(&prev_song));
      //printf("after entered offset loop\n");
      while(offset != 1)
      {
        offset--;
        // visit(top_stack(&prev_song));
        //visit(top_stack(&prev_song));
        pop_stack(&prev_song);
      }
    
      if(empty_stack(&prev_song) == 1)
      {
       printf("Invalid offset\n");
      }
      else
      {
        visit(top_stack(&prev_song));
      }
     } 
     else if(strcmp(option,"down") == 0)
     {
      while(offset != 1)
      {
        offset--;
       // visit(front(&next_song));
        pop(&next_song);
      }
      if(empty(&next_song) == 1)
      {
        printf("Invalid offset\n");       
      }
      else
      {
        visit(front(&next_song));
      }
     }
    }
    else
    {
      printf("Invalid serial number\n");
    }
}

//Q8
TreeNode* PlayList_Based_On_Given_Serial_Number_Of_song(TreeNode* root,int serial_number)
 {
  TreeNode* Myplaylist = NULL;
  int k = 1;
  queue q;
  initialize(&q);
  if(root != NULL)
  {
    push(&q,root);
  }

 TreeNode* song_node = NULL;
  while(empty(&q) == 0 && song_node==NULL)
  {
    TreeNode* temp = front(&q);
    if(k == serial_number)
    {
      song_node = temp;
    }
    else
    {
      if(temp->left != NULL)
      {
        push(&q,temp->left);
      }
      if(temp->right != NULL)
      {
        push(&q,temp->right);
      }
    }
    pop(&q);
    k++;
  }

  if(song_node != NULL)
  {
    visit(song_node);
    int number_of_attributes;
    printf("Enter number of attributes : ");
    scanf("%d",&number_of_attributes);
    char **attribute,**attribute_value;
    attribute = (char**)malloc(sizeof(char*)*number_of_attributes);
    attribute_value = (char**)malloc(sizeof(char*)*number_of_attributes);
    for(int i=0; i<number_of_attributes; i++)
    {
     attribute[i]=(char*)malloc(sizeof(char)*SIZE);
     attribute_value[i]=(char*)malloc(sizeof(char)*SIZE);
    }

     for(int i=0; i<number_of_attributes; i++)
     {
      printf("Enter attribute :\n");
      fflush(stdin);
      fgets(attribute[i],SIZE,stdin);
      if((strcmp(attribute[i],"singer\n")==0) )
      {
        fflush(stdin);
         strcpy(attribute_value[i],song_node->song.singer);
      }
      else if((strcmp(attribute[i],"album\n")==0))
      {
        fflush(stdin);
        strcpy(attribute_value[i],song_node->song.album);
      }
      else if((strcmp(attribute[i],"lyricist\n")==0))
      {
        fflush(stdin);
        strcpy(attribute_value[i],song_node->song.lyricist);
      }
      else if((strcmp(attribute[i],"genre\n")==0))
      {
        fflush(stdin);
        strcpy(attribute_value[i],song_node->song.genre);
      }
      else if((strcmp(attribute[i],"composer\n")==0))
      {
        fflush(stdin);
       strcpy(attribute_value[i],song_node->song.composer); 
      }
     }    
    Myplaylist = Q5_helper(root,Myplaylist,attribute,attribute_value,number_of_attributes);
  }
  else
  {
    printf("Invalid serial number\n");
  }
  return Myplaylist;
 }

//Q9
TreeNode* Filter_Playlist(TreeNode* root)
{
    TreeNode* atrributeBased_MyPlaylist = NULL;
    char **attribute,**attribute_value;
    attribute = (char**)malloc(sizeof(char*)*1);
    attribute_value = (char**)malloc(sizeof(char*)*1);
    attribute[0]=(char*)malloc(sizeof(char)*SIZE);
    attribute_value[0]=(char*)malloc(sizeof(char)*SIZE);
    printf("Enter attribute : ");
    fflush(stdin);
    fgets(attribute[0],SIZE,stdin);
    fflush(stdin);
    printf("Enter attribute value : ");
    fgets(attribute_value[0],SIZE,stdin);
    atrributeBased_MyPlaylist = Q5_helper(root,atrributeBased_MyPlaylist,attribute,attribute_value,1);
    fflush(stdin);
    printf("Enter attribute : ");
    fgets(attribute[0],SIZE,stdin);
    fflush(stdin);
    printf("Enter attribute value : ");
    fgets(attribute_value[0],SIZE,stdin);
    TreeNode *MyPlaylist = NULL;
    MyPlaylist = Q5_helper(atrributeBased_MyPlaylist,MyPlaylist,attribute,attribute_value,1);
    return MyPlaylist;
}

//Q10

TreeNode* Shuffle(TreeNode* root)
{
  printf("Enter number of attributes\n");
  int num_of_attributes;
  scanf("%d",&num_of_attributes);
  char **attribute,**attribute_value;
  attribute =(char**)malloc(sizeof(char*)*num_of_attributes);
  attribute_value =(char**)malloc(sizeof(char*)*num_of_attributes);
  for(int i=0; i<num_of_attributes; i++)
  {
    attribute[i] = (char*)malloc(sizeof(char)*SIZE);
    attribute_value[i] =(char*)malloc(sizeof(char)*SIZE);
  }
  for(int i=0; i<num_of_attributes; i++)
  {
    fflush(stdin);
    printf("Enter attribute : ");
    fgets(attribute[i],SIZE,stdin);
    fflush(stdin);
    printf("Enter attribute name : ");
    fgets(attribute_value[i],SIZE,stdin);
  }
  int upper = NUMBER_OF_SONGS-1,lower=1;
  TreeNode* randomPlaylist = NULL;
  randomPlaylist = Q5_helper(root,randomPlaylist,attribute,attribute_value,num_of_attributes);
  if(randomPlaylist != NULL)
  {
    root = Deletion(root,randomPlaylist->song.name);
  }
  else
  {
    upper++;
  }
 srand(time(0));

 for(int i=0;i<NUMBER_OF_SONGS; i++)
 {
  int num = rand();
  int random_num = (num%(upper-lower+1))+1;
  queue q;
  initialize(&q);
  int k = 1;
  if(root != NULL)
  {
    push(&q,root);
  }
  while(!empty(&q) && k < random_num)
  {
    TreeNode* temp = front(&q);
    if(temp->left != NULL)
    {
      push(&q,temp->left);
    }
    if(temp->right != NULL)
    {
      push(&q,temp->right);
    }
      pop(&q);
      k++;
  }
  if(!empty(&q))
  {
      TreeNode* front_node = front(&q);
      randomPlaylist = Insertion(randomPlaylist,front_node->song);
      root = Deletion(root,front_node->song.name);
  }
  upper--;
 }
   return randomPlaylist;
}

//Q11:
void RangeSearch(TreeNode* root,char *singer1,char *singer2)
{
  if(root != NULL)
  {
    if(strcmp(root->song.singer,singer1) >= 0 && strcmp(root->song.singer,singer2) <= 0)
    {
     RangeSearch(root->left,singer1,singer2);
     visit(root);
     RangeSearch(root->right,singer1,singer2);
    }
    else if(strcmp(root->song.singer,singer1) < 0)
    {
      RangeSearch(root->right,singer1,singer2);
    }
    else if(strcmp(root->song.singer,singer2) > 0)
    {
      RangeSearch(root->left,singer1,singer2);
    }
  }
}


void menu()
{
 printf("1.To insert a song into tree\n");
 printf("2.To remove duplicate entries from records\n");
 printf("3.To print records in ascending and descending order\n");
 printf("4.To delete particular song details as per song name and artist name provided by user\n");
 printf("5.To create a playlist based on multiple attributes and print in lexicographic order\n");
 printf("6.To display a song based on serial number and provide an option to user to choose next or previous song\n");
 printf("7.To display kth song from given serial number song in up or down direction\n");
 printf("8.To create a playlist based on the multiple attributes of given serial number song\n");
 printf("9.To create a playlist based on the given attribute and create another playlist from recently created playlist\n");
 printf("10.To print songs in random order \n");
 printf("11.Range-search Search songs belonging to singers whose names are in-between singer- name-1 and singer-name-2, in lexicographic sorting sense\n");
}
int main()
{
   TreeNode* root = NULL;
    root = TakeInput();
   int choice;
   do
   {
     menu();
     printf("Enter choice : ");
     scanf("%d",&choice);
     switch (choice)
     {
     case 1:
     {
       song_details song;
       fflush(stdin);
       printf("Enter song name : ");
       fgets(song.name,SIZE,stdin);
       fflush(stdin);
       printf("Enter singer name : ");
       fgets(song.singer,SIZE,stdin);
       fflush(stdin);
       printf("Enter lyricist name : ");
       fgets(song.lyricist,SIZE,stdin);
       fflush(stdin);
       printf("Enter album : ");
       fgets(song.album,SIZE,stdin);
       fflush(stdin);
       printf("Enter composer name : ");
       fgets(song.composer,SIZE,stdin);
       fflush(stdin);
       printf("Enter genre : ");
       fgets(song.genre,SIZE,stdin );
       fflush(stdin);
       printf("Enter duration : ");
       fgets(song.duration,SIZE,stdin);  
       fflush(stdin);
       root = Insertion(root,song);
       break;
     } 
     case 2:
     {
      root = RemoveDuplicates(root);
      PrintLevelWise(root);
      printf("Ascending : \n");
      //PrintPlaylistAscending(root);
      Display(root);
      break;
     }
     case 3:
     {
      PrintPlaylistAscending(root);
      PrintPlaylistDescending(root);
      break;
     }
     case 4:
     {
      char song_name[SIZE];
      printf("Enter name of the song : \n");
      fflush(stdin);
      fgets(song_name,SIZE,stdin);
      TreeNode* newNode =  Deletion(root,song_name);
      if(newNode == NULL)
      {
        printf("song not found\n");
      }
      else
      {
        root = newNode;
      }
      PrintLevelWise(root);
      char artist_name[SIZE];
      printf("Enter artist name : ");
      fgets(artist_name,SIZE,stdin);
      root = DeleteWithAritistAttribute(root,artist_name);
      PrintLevelWise(root);
      printf("Display\n");
      Display(root);
      // printf("Copy : \n");
      // TreeNode* newNode =(TreeNode*)malloc(sizeof(TreeNode));
      // printf("Enter name of the song : \n");
      // fflush(stdin);
      // fgets(song_name,SIZE,stdin);
      // strcpy(newNode->song.name,song_name);
      // strcpy(newNode->song.singer,"A\n");
      // replace_song_details(root,newNode);
      // visit(root);
      break;
     } 
     case 5:
     {
      TreeNode* MyPlaylist = createPlaylist_Based_On_Multiple_Attributes(root);
      PrintPlaylistAscending(MyPlaylist);
      break;
     } 
     case 6:
     {
      //Display functions which prints song with serial numbers
       Display(root);
       int serial_number;
       printf("Enter serial number : ");
       scanf("%d",&serial_number);
       DisplayASongAndItsNextPrev(root,serial_number);
       break;
     } 
     case 7:
     {
       int serial_number;
       printf("Enter serial number : ");
       scanf("%d",&serial_number);
       int offset;
       printf("Enter offset : ");
       scanf("%d",&offset);
       Kth_NextSongOrPreviousSong(root,serial_number,offset);
       break;
     }
     case 8:
     {
      int serial_number;
      printf("Enter serial number of the song : ");
      scanf("%d",&serial_number);
      TreeNode* MyPlaylist =  PlayList_Based_On_Given_Serial_Number_Of_song(root,serial_number);
      PrintPlaylistAscending(MyPlaylist);
      break;
     }
     case 9:
     {
      TreeNode *MyPlaylist;
      MyPlaylist = Filter_Playlist(root);
      PrintPlaylistAscending(MyPlaylist);
      break;
     }
     case 10:
     {   
      TreeNode* RandomPlaylist = Shuffle(root);
      PrintLevelWise(RandomPlaylist);
      break;
     }
     case 11:
     {
      TreeNode* root_based_on_singer = NULL;
      root_based_on_singer = TakeInput_Based_On_Singer();
      char singer1[SIZE],singer2[SIZE];
      fflush(stdin);
      printf("Enter name of singer 1 : ");
      fgets(singer1,SIZE,stdin);
      fflush(stdin);
      printf("Enter name of singer 2 : ");
      fgets(singer2,SIZE,stdin);
      RangeSearch(root_based_on_singer,singer1,singer2);
      //PrintLevelWise(root_based_on_singer);
      break;
     }
     case 12:
     {
      PrintLevelWise(root);
      break;
     }
     default:
     {
       break;
     }
     }
   } while (choice != -1);

}

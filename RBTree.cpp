#ifndef RBTREE_CPP
#define RBTREE_CPP

#include <iostream>
#include "RBTreeNode.h"

#define RED 1
#define BLACK 0

class RB_Tree
{
public:
   RB_Tree()  
   {  
      TNILL = new RB_TreeNode();
      root = TNILL;
   }
  
    
   RB_TreeNode* Search(int key) { return SearchHelper(root, key); }
   
   void RB_Inorder_Traverse() {RB_Inorder_TraverseHelper(root);}

   void RB_Insert(int key)
   {
      RB_TreeNode* z = new RB_TreeNode(key), *y = TNILL, *x = root;
      z->left = TNILL;
      z->right = TNILL;
      while (x != TNILL)
      {
         y = x;
         if (x->value < key)
            x = x->right;
         else
            x = x->left;
      }
      z->parent = y;
      
      if (y == TNILL)
         root = z;
      else if (key < y->value)
         y->left = z;
      else
         y->right = z;
      z->color = RED;
      RB_Insert_Fixup(root, z);
   }
   


   void RB_Delete(const int key)
   {
      RB_TreeNode* z = Search(key), *y = z, *x;
      if (z == TNILL)
         return;
      bool y_initial_color = y->color;
      if (z->left == TNILL)
      {
         x = z->right;
         RB_Transplant(z, z->right);
      }

      else if (z->right == TNILL)
      {
         x = z->left;
         RB_Transplant(z, z->left);
      }

      else
      {
         y = MIN_Tree(z->right);
         y_initial_color = y->color;
         x = y->right;
         if (y->parent == z)
            x->parent = y;
         else
         {
            RB_Transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
         }

         RB_Transplant(z, y);
         y->left = z->left;
         y->left->parent = y;
         y->color = z->color;
      }

      if (y_initial_color == BLACK)
         RB_Delete_Fixup(root, x);
   }

private:
   RB_TreeNode* TNILL;
   RB_TreeNode* root;


   RB_TreeNode* SearchHelper(RB_TreeNode* root, int key)
   {
      RB_TreeNode* curr = root;
      while (curr != TNILL && curr->value != key)
      {
         if (curr->value < key)
            curr = curr->right;
         else
            curr = curr->left;
      }
      return curr;
   }


   void Left_Rotate(RB_TreeNode* x)
   {
      RB_TreeNode* y = x->right;
      x->right = y->left;
      
      if (y->left != TNILL)
         y->left->parent = x;
      y->parent = x->parent;
      if (x->parent == TNILL)
         root = y, root->color = BLACK;
      else if (x == x->parent->left)
         x->parent->left = y;
      else
         x->parent->right = y;
      
      y->left = x;
      x->parent = y;
   }
   
   void Right_Rotate(RB_TreeNode* x)
   {
      RB_TreeNode* y = x->left;
      x->left = y->right;
      
      if (y->right != TNILL)
         y->right->parent = x;
      y->parent = x->parent;
      if (x->parent == TNILL)
         root = y, root->color = BLACK;
      else if (x == x->parent->left)
         x->parent->left = y;
      else
         x->parent->right = y;
      y->right = x;
      x->parent = y;
   }
   
   void RB_Insert_Fixup(RB_TreeNode* root, RB_TreeNode* z)
   {
        while (z->parent->color == RED)
        {
           if (z->parent == z->parent->parent->left)
           {
               RB_TreeNode* y = z->parent->parent->right;
               if (y->color == RED)
               {
                  z->parent->color = BLACK;
                  y->color = BLACK;
                  z->parent->parent->color = RED;
                  z = z->parent->parent;
               }
               
               else
               { 
                  if (z == z->parent->right)
                  {
                     z = z->parent;
                     Left_Rotate(z);
                  }
                  z->parent->color = BLACK;
                  z->parent->parent->color = RED;
                  Right_Rotate(z->parent->parent);
               }
           }

           else
           {
               RB_TreeNode* y = z->parent->parent->left;
               if (y->color == RED)
               {
                  z->parent->color = BLACK;
                  y->color = BLACK;
                  z->parent->parent->color = RED;
                  z = z->parent->parent;
               }
               
               else
               {
                  if (z == z->parent->left)
                  {
                     z = z->parent;
                     Right_Rotate(z);
                  }
                  z->parent->color = BLACK;
                  z->parent->parent->color = RED;
                  Left_Rotate(z->parent->parent);
               }
           }
           
         }
      root->color = BLACK;
   }

   RB_TreeNode* MIN_Tree(RB_TreeNode* x)
   {
      while (x != TNILL && x->left != TNILL )
         x = x->left;
      return x;
   }

   RB_TreeNode* MAX_Tree(RB_TreeNode* x)
   {
      while (x != TNILL && x->right != TNILL)
         x = x->right;
      return x;
   }

   void RB_Transplant(RB_TreeNode* u, RB_TreeNode* v)
   {
      if (u->parent == TNILL)
         root = v;
      else if (u == u->parent->left)
         u->parent->left = v;
      else
         u->parent->right = v;
      
      v->parent = u->parent;
   }
   
   void RB_Delete_Fixup(RB_TreeNode* root, RB_TreeNode* x)
   {
      while (x != root && x->color == BLACK)
      {
         if (x == x->parent->left)
         {
            RB_TreeNode* w = x->parent->right;
            if (w->color == RED)
            {
               w->color = BLACK;
               x->parent->color = RED;
               Left_Rotate(x->parent);
               w = x->parent->right;
            }

            if (w->left->color == BLACK && w->right->color == BLACK)
            {
               w->color = RED;
               x = x->parent;
            }

            else
            {
               if (w->right->color == BLACK)
               {
                  w->left->color = BLACK;
                  w->color = RED;
                  Right_Rotate(w);
                  w = x->parent->right;
               }

               w->color = x->parent->color;
               x->parent->color = BLACK;
               w->right->color = BLACK;
               Left_Rotate(x->parent);
               x = root;
            }
         }
         else
         {
            RB_TreeNode* w = x->parent->left;
            if (w->color == RED)
            {
               w->color = BLACK;
               x->parent->color = RED;
               Right_Rotate(x->parent);
               w = x->parent->left;
            }

            if (w->right->color == BLACK && w->left->color == BLACK)
            {
               w->color = RED;
               x = x->parent;
            }

            else
            {
               if (w->left->color == BLACK)
               {
                  w->right->color = BLACK;
                  w->color = RED;
                  Left_Rotate(w);
                  w = x->parent->left;
               }

               w->color = x->parent->color;
               x->parent->color = BLACK;
               w->left->color = BLACK;
               Left_Rotate(x->parent);
               x = root;
            }
         }
         
      }
      x->color = BLACK;
   }

   void RB_Inorder_TraverseHelper(RB_TreeNode* root)
   {
      if (root != TNILL)
      {
         RB_Inorder_TraverseHelper(root->left);
         std::cout << root->value << '\n';
         RB_Inorder_TraverseHelper(root->right);
      }
   }     
};

#endif
/*
** simple_btree.c for Creer un arbre simple in /home/tholim_r//afs/rendu/cpp/d02a/ex_1
** 
** Made by romain tholimet
** Login   <tholim_r@epitech.net>
** 
** Started on  Wed Jan  5 18:54:47 2011 romain tholimet
** Last update Wed Jan  5 20:41:14 2011 romain tholimet
*/

#include		<stdio.h>
#include		<stdlib.h>
#include		"simple_btree.h"

t_bool			btree_is_empty(t_tree tree)
{
  t_bool		test = FALSE;

  if (!tree)
    return (test);
  else
    test = TRUE;
  return (test);
}

unsigned int		btree_get_size(t_tree tree)
{
  unsigned int		res = 0;

  if (!tree)
    return (res);
  res += 1 + btree_get_size(tree->left) + btree_get_size(tree->right);
  return (res);
}

unsigned int		btree_get_depth(t_tree tree)
{
  unsigned int		deep1 = 0;
  unsigned int		deep2 = 0;

  if (!tree)
    return ((deep1 > deep2) ? deep1 : deep2);
  deep1 += btree_get_size(tree->left);
  deep2 += btree_get_size(tree->right);
    return ((deep1 > deep2) ? deep1 : deep2);
}

t_bool			btree_create_node(t_tree *node_ptr, double value)
{
  t_tree		new_node;
  t_bool		test = FALSE;

  new_node = malloc(sizeof(*new_node));
  if (!new_node)
    return (test);
  test = TRUE;
  new_node->value = value;
  new_node->left = NULL;
  new_node->right = NULL;
  *node_ptr = new_node;
  return (test);
}

t_bool			btree_delete(t_tree *root_ptr)
{
  t_bool		test = FALSE;

  if (!(*root_ptr))
    return (test);
  test = TRUE;
  (*root_ptr)->left = NULL;
  (*root_ptr)->right = NULL;
  free((*root_ptr));
  (*root_ptr) = NULL;
  return (test);
}

double			btree_get_max_value(t_tree tree)
{
  double		max_l = 0.0;
  double		max_r = 0.0;
  double		max = 0.0;

  if (!tree)
    return (0);
  max = tree->value;
  if (tree->right)
    {
      max_r = btree_get_max_value(tree->right);
      if (max_r > max)
	max = max_r;
    }
  if (tree->left)
    {
      max_l = btree_get_max_value(tree->left);
      if (max_l > max)
	max = max_l;
    }
  return (max);
}

double			btree_get_min_value(t_tree tree)
{
  double		min_l = 0.0;
  double		min_r = 0.0;
  double		min = 0.0;

  if (!tree)
    return (0);
  min = tree->value;
  if (tree->right)
    {
      min_r = btree_get_min_value(tree->right);
      if (min_r < min)
	min = min_r;
    }
  if (tree->left)
    {
      min_l = btree_get_min_value(tree->left);
      if (min_l < min)
	min = min_l;
    }
  return (min);
}

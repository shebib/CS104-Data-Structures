#include "avlbst.h"
#include <iostream>

int main()
{
  AVLTree<int, int> tree;
    tree.insert(std::make_pair(4, -4));
    tree.insert(std::make_pair(2, -2));
    tree.print();
    tree.insert(std::make_pair(1, -1));
    tree.print();
    tree.insert(std::make_pair(3, -3));
    tree.print();
    tree.insert(std::make_pair(6, -6));
    tree.print();
    tree.insert(std::make_pair(7, -7));
    tree.print();
    tree.insert(std::make_pair(5, -5));

    tree.print();

  std::cout << "Inorder traversal with Iterator" << std::endl;
  for(AVLTree<int, int>::iterator it = tree.begin(); it != tree.end(); ++it)
  {
    std::cout << it->first << "|" << it->second << std::endl;
  }
  std::cout << tree.find(5)->second <<std::endl;
  std::cout << tree.find(7)->second<<std::endl;
  std::cout << tree.find(1)->second<<std::endl;

  tree.erase(1);
  tree.erase(2);
    tree.print();
  tree.erase(3);
    tree.print();
  tree.erase(4);
    tree.print();
  tree.insert(std::make_pair(4, -4));
  tree.insert(std::make_pair(1, -1));
  tree.insert(std::make_pair(2, -2));
  tree.insert(std::make_pair(3, -3));
    tree.print();
  tree.erase(5);
    tree.print();
}

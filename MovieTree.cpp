// ===========================================
// Created: October 12, 2016
// Sheila Doherty
// Homework Assignment #5: Binary Search Tree
// Included Files: MovieTree.cpp & DriverHW5.cpp
// Provided File: MovieTree.hpp
// Instructor: Elizabeth Boese
// Description: Builds a binary search tree
// searches, traverses & deletes tree
// ===========================================

#include "MovieTree.hpp"

#include <iostream>
#include <string>

using namespace std;

MovieTree::MovieTree()
{
    //ctor   
    root = NULL; //sets root to NULL
}

MovieTree::~MovieTree()
{
    //dtor
    DeleteAll(root);
}

/*
 * Function name: printMovieInventory
 * Purpose: Returns root
 * @return - pointer to the root of the tree
*/
void MovieTree::printMovieInventory()
{
	printMovieInventory(root);
}


/*
 * Function name: printMovieInventory
 * Purpose: to print the movie inventory & quantity in alphabetical order
 * @return - none
*/
void MovieTree::printMovieInventory(MovieNode * node)
{
	if (node->leftChild != NULL)
	{
		printMovieInventory(node->leftChild);
	}
	cout << "Movie: " << node->title << "  Quantity: " << node->quantity << endl;
	
	if (node->rightChild != NULL)
	{
		printMovieInventory(node->rightChild);
	}
}

/*
 * Function name: addMovieNode
 * Purpose: to add a node to the binary tree
 * @return - none
*/
void MovieTree::addMovieNode(int ranking, string title, int releaseYear, int quantity)
{
	MovieNode *s = new MovieNode; //creates a new MovieNode
	s->parent = NULL;
	s->ranking = ranking;
	s->title = title;
	s->year = releaseYear;
	s->quantity = quantity;
	
	if (root==NULL) //tree is empty
	{
		root = s;
		root->parent = NULL;
		root->leftChild = NULL;
		root->rightChild = NULL;
	}
	else //tree not empty
	{
		MovieNode *m = new MovieNode;
		m = root;

		while (s->parent != m)
		{
			if (s->title > m->title && m->rightChild == NULL) //adds leaf node as a right child
			{
				m->rightChild = s;
				s->parent = m;
				s->leftChild = NULL;
				s->rightChild = NULL;
			}
			else if (s->title < m->title && m->leftChild == NULL) //adds leaf node as a left child
			{
				m->leftChild = s;
				s->parent = m;
				s->leftChild = NULL;
				s->rightChild = NULL;
			}
			else if (s->title > m->title && m->rightChild != NULL) //incrementes through the right node if not the leaf
			{
				m = m->rightChild;
			}
			else if (s->title < m->title && m->leftChild != NULL) //incrementes through the left node if not the leaf
			{
				m = m->leftChild;
			}
		}
	}
}

/*
 * Function name: search
 * Purpose: Searches the tree
 * @return - pointer to the desired node in the tree
*/
MovieNode* MovieTree::search(string title)
{
	MovieNode *foundMovie = new MovieNode;
	foundMovie = root;
	
	while (foundMovie != NULL)
	{
		if (title == foundMovie->title) //returns the pointer to the desired node when title is found in it
		{
			return foundMovie;
		}
		else if (title < foundMovie->title) //searches the left child node
		{
			if (foundMovie->leftChild == NULL) 
			{
				foundMovie = NULL;
			}
			else
			{
				foundMovie = foundMovie->leftChild;
			}
		}	
		else if (title > foundMovie->title) //searches the right child node
		{
			if (foundMovie->rightChild == NULL)
			{
				foundMovie = NULL;
			}
			else
			{
				foundMovie = foundMovie->rightChild;
			}
		}
	}
	return foundMovie;
}

/*
 * Function name: findMovie
 * Purpose: prints whether a movie is found & its details
 * @return - none
*/
void MovieTree::findMovie(string title)
{
	MovieNode *foundMovie = new MovieNode;
	foundMovie = search(title);
	
	if (foundMovie == NULL)
	{
		cout << "     " << endl;
		cout << "Movie not found." << endl;
	}
	else
	{
		cout << "    " << endl;
		cout << "Movie Info:" << endl;
		cout << "===========" << endl;
		cout << "Ranking:" << foundMovie->ranking << endl;
		cout << "Title:" << foundMovie->title << endl;
		cout << "Year:" << foundMovie->year << endl;
		cout << "Quantity:" << foundMovie->quantity << endl;
	}
}

/*
 * Function name: rentMovie
 * Purpose: if movie found, takes 1 from quantity and prints movie info
 * @return - none
*/
void MovieTree::rentMovie (string title)
{
	MovieNode *foundMovie = new MovieNode;
	foundMovie = search(title);
	
	if (foundMovie == NULL)
	{
		cout << "   " << endl;
		cout << "Movie not found." << endl;
	}
	else if (foundMovie->quantity < 1)
	{
		cout << "    " << endl;
		cout << "Movie out of stock." << endl;
	}
	else
	{
		cout << "    " << endl;
		cout << "Movie has been rented."<< endl;
		foundMovie->quantity = foundMovie->quantity - 1;
		cout << "Movie Info:" << endl;
		cout << "===========" << endl;
		cout << "Ranking:" << foundMovie->ranking << endl;
		cout << "Title:" << foundMovie->title << endl;
		cout << "Year:" << foundMovie->year << endl;
		cout << "Quantity:" << foundMovie->quantity << endl;
	}
}

/*
 * Function name: DeleteAll
 * Purpose: delete the entire tree
 * @return - none
*/
void MovieTree::DeleteAll (MovieNode *node)
{
	if (node->leftChild != NULL)
	{
		DeleteAll(node->leftChild);
	}
	if (node->rightChild != NULL)
	{
		DeleteAll(node->rightChild);
	}
	//cout << "Deleting: " << node->title << endl;
	
	delete node;
}

/*
 * Function name: countMovieNodes
 * Purpose: Function that counts the number of nodes in the tree
 * @return - none
*/
void MovieTree::countMovieNodes(MovieNode *node, int *c)
{	
	(*c)++;
	if (node->leftChild)
	{
		countMovieNodes(node->leftChild, c);
	}
	if (node->rightChild)
	{
		countMovieNodes(node->rightChild, c);
	}

}

/*
 * Function name: countMovieNodes
 * Purpose: Calls function to count nodes
 * @return - int of number of movie nodes present
*/
int MovieTree::countMovieNodes()
{
	if (!root)
	{
		return 0;
	}
	else
	{
		int c = 0;
		countMovieNodes(root, &c);
		return c;
	}
}

/*
 * Function name: treeMinimum
 * Purpose: find the minimum value of a tree
 * @return - the pointer to the minimum value of the tree
*/
MovieNode* MovieTree::treeMinimum(MovieNode *node)
{
	if (node == NULL)
	{
		return NULL;
	}
	if (node->leftChild == NULL)
	{
		return node;
	}
	else
	{
		return treeMinimum(node->leftChild);
	}
}

/*
 * Function name: deleteMovieNode
 * Purpose: delete a node on the tree
 * @return - none
 * */
 void MovieTree::deleteMovieNode(string title)
{
 	MovieNode *rNode = search(title);
 	
 	if (rNode != NULL)
 	{
		if (rNode->rightChild == NULL && rNode->leftChild == NULL) //if node has no children
		{
			//cout << "No children" << endl;
			if (rNode->parent->leftChild == rNode) //if the node being deleted is a left child of it's parent
			{
				rNode->parent->leftChild = NULL;
			}
			else //if the node being deleted is right child of it's parent
			{
				rNode->parent->rightChild = NULL;
			}
			cout << "   " << endl;
			cout << rNode->title << " was removed." << endl;
			delete rNode;
		}
		else if (rNode->rightChild == NULL) // if the node has only a left child
		{
			//cout << "Left child only" << endl;
			if (rNode->parent->leftChild == rNode) //if the node is a left child
			{
				rNode->parent->leftChild = rNode->leftChild;
				rNode->leftChild->parent = rNode->parent;
			}
			else //if the node if a right child
			{
				rNode->parent->rightChild = rNode->leftChild;
				rNode->leftChild->parent = rNode->parent;
			}
			cout << "   " << endl;
			cout << rNode->title << " was removed." << endl;
			delete rNode;
		}
		else if (rNode->leftChild == NULL) //if the node has only right child
		{
			//cout << "right child only" << endl;
			if (rNode->parent->leftChild == rNode) //if the node is a left child
			{
				rNode->parent->leftChild = rNode->rightChild;
				rNode->rightChild->parent = rNode->parent;
			}
			else //if the node is a right child
			{
				rNode->parent->rightChild = rNode->rightChild;
				rNode->rightChild->parent = rNode->parent;
			}
			cout << "   " << endl;
			cout << rNode->title << " was removed." << endl;
			delete rNode;
		}
		else if (rNode->leftChild != NULL && rNode->rightChild != NULL) //node has 2 children
		{
			//cout << "2 children" << endl;
			MovieNode *min = treeMinimum(rNode->rightChild);
					
			//cout << "min is " << min->title << endl;
			cout << "   " << endl;
			cout << rNode->title << " was removed." << endl;

			rNode->title = min->title;
			rNode->ranking = min->ranking;
			rNode->year = min->year;
			rNode->quantity = min->quantity;
			
			if (min->rightChild != NULL) // if min has a right child, update pointers
			{
				min->rightChild->parent = min->parent;
			}
			if (min->parent->leftChild == min)
			{
				min->parent->leftChild = min->rightChild;
			}
			else
			{
				min->parent->rightChild = min->rightChild;
			}
			
			delete min;
		}
	}
	else
	{
		cout << "Requested movie not found." << endl;
	}
}


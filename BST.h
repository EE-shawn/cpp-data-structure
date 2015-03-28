#include "Bintree.h"

template <typename T>
class BST : public BinTree<T>
{
public:
	BST();
	virtual BinNodePosi(T) search(const T &);
	virtual BinNodePosi(T) insert(const T &);
	virtual bool remove(const T &);
protected:
	using BinTree<T>::_root;
	using BinTree<T>::_size;

	BinNodePosi(T) _hot;	//parent of (x returned by search)
	void transplant(BinNodePosi(T) p, BinNodePosi(T) c);	//move single node c to p

};

template <typename T>
BST<T>::BST()
{
	_hot = NULL;
}
template <typename T>
BinNodePosi(T) searchIn(BinNodePosi(T) root, const T & e, BinNodePosi(T) & hot)
{
	BinNodePosi(T) x = root;
	hot = root;
	while (x != NULL)
	{
		hot = x;
		if (e < x->data)
			x = x->lchild;
		else if (x->data < e)
			x = x->rchild;
		else
			return x;
	}
	return x;
}
template <typename T>
BinNodePosi(T) BST<T>::search(const T & e)
{
	return searchIn(_root, e, _hot);
}

template <typename T>
BinNodePosi(T) BST<T>::insert(const T & e)
{
	BinNodePosi(T) p = search(e);
	if (p != NULL && p->data == e)	//already exist
	{
		return p;
	}

	BinNodePosi(T) x = new BinNode<T>(e, _hot);
	if (_hot == NULL)	//empty tree
	{
		_root = x;
	}
	else	//insert as a leaf
	{
		if (e < _hot->data)
			_hot->lchild = x;
		else
			_hot->rchild = x;
	}
	++_size;
	this->updateHeightAbove(x);
	return x;
}


//the called function should modify the lchild and rchild of c
//meanwhile, children node of p not changed
template <typename T>
void BST<T>::transplant(BinNodePosi(T) p, BinNodePosi(T) c)
{
	if (p == _root)
		_root = c;

	if (p->parent->lchild == p)
		p->parent->lchild = c;
	else
		p->parent->rchild = c;

	if (c) c->parent = p->parent;
}
template <typename T>
bool BST<T>::remove(const T & e)
{
	BinNodePosi(T) x = search(e);
	if (!x) return false;

	if (!x->lchild)	//x has no lchild, just use rchild to replace x,including rchild==NULL
	{
		_hot = x->parent;
		transplant(x, x->rchild);
	}
	//has lchild
	else if (!x->rchild)	//no rchild ,move lchild to x
	{
		_hot = x->parent;
		transplant(x, x->lchild);
	}
	else	//two children
	{
		BinNodePosi(T) p = x->succ();
		


		//p has no lchild
		if (p->parent == x)
		{
			_hot = x;
			transplant(x, p);
		}
		else
		{
			if (!p->rchild)
				_hot = p->parent;
			else
				_hot = p->rchild;
			transplant(p, p->rchild);
			transplant(x, p);

			p->lchild = x->lchild;
			p->lchild->parent = p;
			p->rchild = x->rchild;
			p->rchild->parent = p;
		}
	}
	--_size;
	this->updateHeightAbove(_hot);

	return true;
}

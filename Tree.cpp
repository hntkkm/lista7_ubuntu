#include <iostream>
#include <string>
using namespace std;

class Tree{
	public:
		int key;
		Tree *left, *right;
	
	
		Tree();
		~Tree();
		bool search(struct binaryTree* wezel, int key);
		string draw(struct binaryTree* wezel);
		struct binaryTree* minWezel(struct binaryTree* wezel);
		struct binaryTree* deleteElement(struct binaryTree* wezelSprawdzany, int key);

};
Tree::Tree()
{
	int key;
	Tree *left, *right;
}

Tree::~Tree()
{
	delete left;
	delete right;
}

Tree* newTree(int key){
		Tree* tree = (Tree*)malloc(sizeof(Tree));
		tree->key = key;
		tree->left = tree->right = NULL;
		return tree;
	}

Tree* insert(Tree* wezel, int key)
{
	// Tree* wezel;
	// this.wezel = wezel;
	if (wezel == NULL)
		return newTree(key);

	if (key < wezel->key)
		wezel->left = insert(wezel->left, key);
	else
		wezel->right = insert(wezel->right, key);

	return wezel;
}

bool search(Tree* wezel, int key)
{
    // sprawdza puste drzewko i korzeń
    if (wezel == NULL)
        return false;
    if (wezel->key == key)
       return true;
    
    // Key jest wieksza od key'a wezla
    if (wezel->key < key)
       return search(wezel->right, key);
 
    // Key jest mniejsza od key'a wezla
    else return search(wezel->left, key);
}

string draw(Tree* wezel) {
	if( wezel != NULL ){
		// rysuje zaczynając od lewej strony każdego rodzica i jego synów
		return "(" + to_string(wezel->key) + ":" + draw(wezel->left) + ":" + draw(wezel->right) + ")";
	}
	return "()";
}

Tree* minWezel(Tree* wezel)
{
	// struct binaryTree* current = wezel;

	// petla ktora szuka najmniejszy element idac na maxa w lewo
	while (/*current &&*/ wezel->left != NULL)					//???????
		wezel = wezel->left;

	return wezel;
}


Tree* deleteElement(Tree* wezelSprawdzany, int key)
{
	//puste drzewo
	if (wezelSprawdzany == NULL)
		return wezelSprawdzany;
	//poszukiwanie elementu ktory bedziemy usuwac
	if (key < wezelSprawdzany->key)
		wezelSprawdzany->left = deleteElement(wezelSprawdzany->left, key);
	else if (key > wezelSprawdzany->key)
		wezelSprawdzany->right = deleteElement(wezelSprawdzany->right, key);

	//usuwanie:
	else {
		// wezel nie ma dzieci
		if (wezelSprawdzany->left==NULL and wezelSprawdzany->right==NULL){
			//free(root);									//?????
			return NULL; //usuwanie elementu
		}
		// wezel ma jedno dziecko
		else if (wezelSprawdzany->left == NULL) {
			Tree* wezel = wezelSprawdzany->right;
			free(wezelSprawdzany);
			return wezel;
		}
		else if (wezelSprawdzany->right == NULL) {
			Tree* wezel = wezelSprawdzany->left;
			free(wezelSprawdzany);
			return wezel;
		}

		Tree* wezel = minWezel(wezelSprawdzany->right);

		// na puste miejsce dodajemy drzewo o najmniejszym rodzicu
		wezelSprawdzany->key = wezel->key;

		// przeszukajemy prawą strony od nowego elementu oby byla dobra kolejnosc
		wezelSprawdzany->right = deleteElement(wezelSprawdzany->right, wezel->key);
	}
	return wezelSprawdzany;
}


int main()
{
	Tree* root = NULL;

	root = deleteElement(root, 5);
	cout << draw(root)<<endl;
	root = insert(root, 10);
	root = insert(root, 8);
	root = insert(root, 9);
	root = insert(root, 20);
	root = insert(root, 15);
	root = insert(root, 25);
	root = insert(root, 12);
    
	root = deleteElement(root, 20);;
	cout << draw(root)<<endl;
	

	root = deleteElement(root, 10);
	cout << draw(root)<<endl;
	cout<<" "<<endl;
	
	root = insert(root, 10);
	cout << draw(root)<<endl;
	cout<<" "<<endl;

	return 0;
}

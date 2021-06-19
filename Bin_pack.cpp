//Group 134167
/*
          1800001312 OSMAN CAN ÝSKÝT
		  1800003537 DURSUN ALPEREN ÇOBAN
*/

#include<iostream>
using namespace std;
int gbin = 1;


class Bin//Define Class
{
public:
	int binNo;// because we use avl tree we need to use binNo to track bins while they are changing
	int weight;
	Bin* left;
	Bin* right;
	int height;
};


int max(int a, int b);// function to get maximum of two integers 

int height(Bin* B)// function to get height of the tree
{
	if (B == NULL)
		return 0;
	return B->height;
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

Bin* newBin(int w)// function that allocates a new node with the given key and NULL left and right pointers.
{
	Bin* bin = new Bin();
	bin->binNo = gbin;
	bin->weight = w;
	bin->left = NULL;
	bin->right = NULL;
	bin->height = 1;// new node is added at leaf 
	gbin++;
	return(bin);
}


Bin* rightRotate(Bin* b)
{
	Bin* a = b->left;
	Bin* tleaf = a->right;

	// perform rotation 
	a->right = b;
	b->left = tleaf;

	// update heights 
	b->height = max(height(b->left),
		height(b->right)) + 1;
	a->height = max(height(a->left),
		height(a->right)) + 1;


	return a;
}

Bin* leftRotate(Bin* a)
{
	Bin* b = a->right;
	Bin* tleaf = b->left;

	// perform rotation
	b->left = a;
	a->right = tleaf;

	// update heights 
	a->height = max(height(a->left),
		height(a->right)) + 1;
	b->height = max(height(b->left),
		height(b->right)) + 1;


	return b;
}

// Get Balance factor of node N
int getBalance(Bin* B)
{
	if (B == NULL)
		return 0;
	return height(B->left) -//it checks differance between heights
		height(B->right);
}



void printBins(Bin* root)
{
	if (root != NULL)
	{
		cout << root->binNo << "bin in weight " << root->weight << " gr.\n";//avl tree changes places of leafs but so we  print our tree with bin numbers but un-ordered
		printBins(root->left);
		printBins(root->right);
	}
}
Bin* BalanceTree(Bin* bin, int w)//Get AVL tree Balanced
{

	int balance = getBalance(bin);//Retruns 0 if tree balanced



	// Case:Left Left 
	if (balance > 1 && w < bin->left->weight)
		return rightRotate(bin);

	// Case:Right Right 
	if (balance < -1 && w > bin->right->weight)
		return leftRotate(bin);

	// Case:Left Right  
	if (balance > 1 && w > bin->left->weight)
	{
		bin->left = leftRotate(bin->left);
		return rightRotate(bin);
	}

	//Case:Right Left 
	if (balance < -1 && w < bin->right->weight)
	{
		bin->right = rightRotate(bin->right);
		return leftRotate(bin);
	}


	return bin;
}
Bin* insert(Bin* bin, int w)//Insert new bin if bin tree null or unsatisfy conditions 
{

	if (bin == NULL)//if bin tree null then add new bin
		return(newBin(w));
	//get binary tree balanced weight hieracy is left less than root right is higher than root
	if (w < bin->weight)
		bin->left = insert(bin->left, w);
	else if (w > bin->weight)
		bin->right = insert(bin->right, w);
	//add height parameter for avl tree balance formula
	bin->height = 1 + max(height(bin->left), height(bin->right));


	return BalanceTree(bin, w);
}
Bin* find_BestFit(Bin* bin, int w) {
	Bin* temp = NULL;
	if (bin != NULL)
	{
		if (bin->weight + w == 1000)//if program find perfect fit sum equal 1000 then it will return the bin
			return bin;
		else if (bin->weight + w < 1000)//if sum is less than 100 then there are no better fits on the left side so function keep going with ride side
		{
			temp = bin;            // if sum is less than 1000 we can directly change the temp because the weight in that bin is greater than the weight in the temp 
			if (bin->right != NULL)// so it will be a better fit
			{
				//recursive algorithm for find best bin
				if (find_BestFit(bin->right, w) != NULL)
					find_BestFit(bin->right, w);
				else
					return temp;
			}
			else
				return bin;

		}
		else if (bin->weight + w > 1000)//if sum is greater than 100 then there is no fit on the ride side so program keep going with left side
		{
			if (bin->left != NULL)
				find_BestFit(bin->left, w);
			else
				return temp;
		}
	}
	else
		return temp;

}
Bin* find_FirstFit(Bin* bin, int w) {
	Bin* temp = NULL;
	Bin* right = NULL;
	Bin* left = NULL;
	if (bin != NULL)
	{

		if (bin->weight + w <= 1000)// if sum is less than or equal to 1000 than we still need to check every bin cause our first-bin is still in there hiding because
		{                           // of the working algorithm of the avl tree
			temp = bin;
			if (bin->right != NULL)
			{
				//recursive algorithm for find first bin
				left = find_FirstFit(bin->left, w);
				if (left != NULL && left->binNo < temp->binNo)
					temp = left;
				right = find_FirstFit(bin->right, w);
				if (right != NULL && right->binNo < temp->binNo)
					temp = right;
				return temp;
			}
			else
				return bin;

		}
		else if (bin->weight + w > 1000)// if sum is greater than 1000 then we can eliminate the right part of the tree because there are no leaf there that the weight fits
		{
			if (bin->left != NULL)
				find_FirstFit(bin->left, w);

			else
				return temp;
		}
	}
	else
		return temp;
}
Bin* FirstFit(Bin* bin, int w) {
	Bin* temp = NULL;
	if (bin == NULL)
	{
		return(newBin(w));
	}
	temp = find_FirstFit(bin, w);//Function call if FirstFit satisfied function turns bin node.
	if (temp != NULL) {
		temp->weight += w;
	}
	else {
		if (w < bin->weight)
			bin->left = insert(bin->left, w);
		else if (w > bin->weight)
			bin->right = insert(bin->right, w);

		else
			return bin;
	}
	return BalanceTree(bin, bin->weight);
}
Bin* BestFit(Bin* bin, int w)
{
	Bin* temp = NULL;
	if (bin == NULL)
	{
		return(newBin(w));
	}
	temp = find_BestFit(bin, w);//Function Call if BestFit satisfied function turns bin node.
	if (temp != NULL) {
		temp->weight += w;
	}
	else {
		if (w < bin->weight)
			bin->left = insert(bin->left, w);
		else if (w >= bin->weight)
			bin->right = insert(bin->right, w);

		else
			return bin;
	}
	return BalanceTree(bin, bin->weight);
}

void swap(int* aw, int* ab, int* bw, int* bb)// this function helps to correct the tree after adding extra value to a bin
{
	int tw = *aw;
	int tb = *ab;
	*aw = *bw;
	*ab = *bb;
	*bw = tw;
	*bb = tb;
}

void correctAVLUtil(Bin* root, Bin** first, Bin** middle, Bin** last, Bin** prev) {// It checks weights after updateting a bin's weight and if weight hierachy is wrong 
	if (root)                                                                      // find and point the wrong nodes
	{
		correctAVLUtil(root->left, first, middle, last, prev);


		if (*prev && root->weight < (*prev)->weight)
		{
			if (!*first)
			{
				*first = *prev;
				*middle = root;
			}
			else
				*last = root;
		}
		*prev = root;

		correctAVLUtil(root->right, first, middle, last, prev);
	}

}

void correctAVL(Bin* root)//After updating a bin if weight values don't correct position right and left tree we swap the binNo and weights of pointed bins.
{
	Bin* first, * middle, * last, * prev;
	first = middle = last = prev = NULL;

	correctAVLUtil(root, &first, &middle, &last, &prev);

	if (first && last)
		swap(&(first->weight), &(first->binNo), &(last->weight), &(last->binNo));
	else if (first && middle)
		swap(&(first->weight), &(first->binNo), &(middle->weight), &(middle->binNo));
}

int main()
{
	Bin* root = NULL;//Initial Node
	int gr;//gram metric
	float kg;//kg metric
	int choice_fit;
	int choice_metric;
	cout << "Please choose fit type;\n1.)First-Fit Algorithm\n2.)Best-Fit Algorithm\n ";// we have both best-fit and first-fit algorithms in one code so we ask user which one to use
	cin >> choice_fit;
	cout << "Please choose metric;\n1.)Gram\n2.)Kilogram\n ";// our algorithms work for gram format but we ask user which metric format they will use and act according to the answer
	cin >> choice_metric;

	switch (choice_fit)// First switch case identify which fit-type we use 1 first-fit and 2 best-fit
	{
	case 1:

		cout << "\t\t\t First-Fit Selected\n";
		switch (choice_metric)// The second one identify the metric system we use 1 for gram and 2 for kilogram
		{

		case 1:
			cout << "Please enter the weight of your item(in gram format)[0-1000]exit:-1 : ";
			cin >> gr;// to assign the gr before the loop we didn't use do while to prevent adding -1 to tree
			while (gr != -1) {// when user enter -1 loop will and without adding -1 to tree

				root = FirstFit(root, gr);
				for (int i = 0; i < gbin; i++)//Correct tree values after done first fit algorithm
				{
					correctAVL(root);
				}
				cout << "Please enter the weight of your item(in gram format)[0-1000]exit:-1 : ";
				cin >> gr;
			};
			break;
		case 2:
			cout << "Please enter the weight of your item(in Kilogram format)[0.00-1.00]exit:-1 : ";
			cin >> kg;
			while (kg != -1) {


				kg *= 1000.00;// we need to change kilogram format to gram format because our algorithms use gram format
				root = FirstFit(root, kg);
				for (int i = 0; i < gbin; i++)//Correct tree values after done first fit algorithm
				{
					correctAVL(root);
				}
				cout << "Please enter the weight of your item(in Kilogram format)[0.00-1.00]exit:-1 : ";
				cin >> kg;
			};
			break;
		}
		break;


	case 2:
		cout << "\t\t\t Best-Fit Selected\n";
		switch (choice_metric)
		{

		case 1:
			cout << "Please enter the weight of your item(in gram format)[0-1000]exit:-1 : ";
			cin >> gr;
			while (gr != -1) {

				root = BestFit(root, gr);
				for (int i = 0; i < gbin; i++)//Correct tree values after done first fit algorithm
				{
					correctAVL(root);
				}
				cout << "Please enter the weight of your item(in gram format)[0-1000]exit:-1 : ";
				cin >> gr;
			};
			break;
		case 2:
			cout << "Please enter the weight of your item(in Kilogram format)[0.00-1.00]exit:-1 : ";
			cin >> kg;
			while (kg != -1) {


				kg *= 1000.00;
				root = BestFit(root, kg);
				for (int i = 0; i < gbin; i++)//Correct tree values after done first fit algorithm
				{
					correctAVL(root);
				}
				cout << "Please enter the weight of your item(in Kilogram format)[0.00-1.00]exit:-1 : ";
				cin >> kg;
			};
			break;
		}

		break;

	}
	cout << "The Bin tree is:\n";
	printBins(root);



	return 0;
}

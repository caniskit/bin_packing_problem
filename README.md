# Bin Packing Problem 

### 1.Initializing & Declaring
Declare used Library and global variables
Gbin used for assign bin no to bin node.

![image](https://user-images.githubusercontent.com/58433345/122649023-8a13f380-d134-11eb-8bdf-2da6554dad12.png)

Declare class details

![image](https://user-images.githubusercontent.com/58433345/122649052-ab74df80-d134-11eb-8bf7-1b955d281517.png)

### 2.Main Function

![image](https://user-images.githubusercontent.com/58433345/122649111-01498780-d135-11eb-82c6-35aabc3f3e18.png)

![image](https://user-images.githubusercontent.com/58433345/122649113-04447800-d135-11eb-94c1-30336b1a6b77.png)

Main function shows up the user interaction menu then ask for user options which are fit
algorithm and metric selection such as kg(kilogram) or gr(gram). After the user response main function calls
for best fit or first fit functions depend on given entry If user choose metric kg, then main
function converts the entry to integer number of gram value Selected Algorithm continues
until user enter -1 for the purpose of terminating loop. End of the main function calls
print Bins functio n to print all bins after the fitting algorithms.

### 3. Functions
#### BalanceTree
![image](https://user-images.githubusercontent.com/58433345/122649195-74eb9480-d135-11eb-8efd-5ebb92938c84.png)

Balance tree function makes AVL tree bal anced with compare inserted weight.
In the first step, getBalance function is called for the locally defined balance value. The getBalance
function checks the deepest points of both sides of the tree and returns an integer value. The situation
where the balance value is 0 is ideal and the function ends.
In cases where the balance value is 1 and -1, rotation processes will be applied. On Right Rotation the Unbalanced knot turns right
and becomes the right child of the left child.
Also, the Left Rotation Unbalanced tree turns left and becomes the parent left child of right child

#### Find_FirstFit

![image](https://user-images.githubusercontent.com/58433345/122649263-b54b1280-d135-11eb-8935-970964bf5724.png)

The purpose of this function is searching algorithm for fitting bin with the smallest bin
number. It checks if the sum of root weight and the item weight less than 1000. If it is not,
then it eliminates all right side of the tree to prevent time loss. When it finds a fitting
place, it reminds the bin during that time function still searches for fitting bins with smaller
bin numbers. At the and if the reminding is empty function calls for insert function.

#### FirstFit

![image](https://user-images.githubusercontent.com/58433345/122649292-dc094900-d135-11eb-8a8e-144fa245fa5d.png)

First the function checks for if the bin is empty , if it is empty then calls new bin function to
insert new bin. If it is not empty function calls find FirstFit function to find the first
available bin. If found an available bin function update the weight of node If function
cannot find an available bin, then it calls insert function depending on comparison of weights.


#### Find_BestFit

![image](https://user-images.githubusercontent.com/58433345/122649339-11159b80-d136-11eb-9cbf-3cd90dfcb549.png)

This function calculates the sum of bin weight and item weight and compare it with 1000 If sum is less than or equal to 1000, function remind the bin and keep checking right leaves. If there is a fitting place it must be better fitting because of AVL tree mechanism. If root weight is greater than 1000 then function goes with left leaves without reminding. At the and if the reminding is empty function calls for insert function.

#### BestFit

![image](https://user-images.githubusercontent.com/58433345/122649397-4e7a2900-d136-11eb-9ae4-cce5e9b0cca3.png)

First the function checks for if the bin is empty, if it is empty then calls new bin function to insert new bin. If it is not empty function calls find_BestFit function to find the best fitted available bin. If found an available bin function update the weight of node. If function cannot find an available bin, then it calls insert function depending on comparison of weights.

#### CorrectAVLUtil

![image](https://user-images.githubusercontent.com/58433345/122649457-a1ec7700-d136-11eb-91a1-d3d5e9af3a75.png)

The function checks the weight of the incoming nodes and if the leaf is not suitable for the structure of the AVL tree, it works recursively until the correct location is found.

#### CorrectAVL

![image](https://user-images.githubusercontent.com/58433345/122649497-baf52800-d136-11eb-8a8f-b0e69ef1f742.png)

The function calls the swap function to rearrange the weight balance of the incoming node, bringing the tree weights to the correct position.

#### PrintBins

![image](https://user-images.githubusercontent.com/58433345/122649519-cf392500-d136-11eb-9c0f-1dad7f050c89.png)

It prints the tree members recursively on this method, but the locations of the members are irregular due to the AVL tree structure.

Reference :www.geeksforgeeks.org/avl-tree-set-1-insertion/

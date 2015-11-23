#include<stdio.h>
#include<stdlib.h>

#define FALSE_VALUE 0
#define TRUE_VALUE 1

struct treeNode
{
    int item;
    struct treeNode * left; //points to left child
    struct treeNode * right; //points to right child
};

struct treeNode * root;


void initializeTree()
{
    root = 0;
}


struct treeNode * searchItem(struct treeNode * node, int item)
{
    if(node==0) return 0;
    if(node->item==item) return node; //found, return node
    struct treeNode * t = 0;
    if(item < node->item)
        t = searchItem(node->left, item); //search in the left sub-tree
    else
        t = searchItem(node->right, item); //search in the right sub-tree
    return t;
};


struct treeNode * makeTreeNode(int item)
{
    struct treeNode * node ;
    node = (struct treeNode *)malloc(sizeof(struct treeNode));
    node->item = item;
    node->left = 0;
    node->right = 0;
    return node;
};

struct treeNode * insertItem(struct treeNode * node, int item)
{
    if(node==0) //insert as the root as the tree is empty
    {
        struct treeNode * newNode = makeTreeNode(item);
        root = newNode;
        return newNode;
    }

    if(node->item==item) return 0; //already an item exists, so return NULL

    if(item<node->item && node->left==0) //insert as the left child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->left = newNode;
        return newNode;
    }

    if(item>node->item && node->right==0) //insert as the right child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->right = newNode;
        return newNode;
    }

    if(item<node->item)
        return insertItem(node->left, item); //insert at left sub-tree
    else
        return insertItem(node->right, item); //insert at right sub-tree
}



int calcNodeHeight(struct treeNode * node) //return height of a node
{
    if(node==0) return -1;
    int l, r;
    l = calcNodeHeight(node->left);
    r = calcNodeHeight(node->right);
    if(l>r) return l+1;
    else return r+1;
}


int calcHeight(int item) //return height of an item in the tree
{
    struct treeNode * node = 0;
    node = searchItem(root, item);
    if(node==0) return -1; //not found
    else return calcNodeHeight(node);
}

int getSize(struct treeNode * node)
{

    int i;
    if (node==0) return 0;
    else i = (getSize(node->left) + 1 + getSize(node->right));
    return i;
}


int calcNodeDepth(struct treeNode * node) //return depth of a node
{
    struct treeNode *t = root;
    int i = 0;
    while(t!=0){
        if(t == node) return i;
        if(t->item > node->item){
            t = t-> left;
        }
        else{
            t = t -> right;
        }
        i++;
    }
    if(t == 0)return -1;
}


int calcDepth(int item)//return depth of an item in the tree
{
    struct treeNode *t = root;
    int i = 0;
    while(t!=0){
        if(t -> item == item) return i;
        if(t->item > item){
            t = t-> left;
        }
        else{
            t = t -> right;
        }
        i++;
    }
    if(t == 0)return -1;
}




int deleteItem(struct treeNode * node, int item)
{
    struct treeNode *current,*parent,*temp,*succ,*psucc;
    if(node==NULL) return FALSE_VALUE;
    else{
        current=node;
        parent=current;
        while(current->item!=item){
            parent=current;
            if(item<current->item) current=current->left;
            else current=current->right;
        }
        if(root->item == item){
            if(root->left == NULL && root->right == NULL){
                root = 0;
                return TRUE_VALUE;
            }
        }
        if(current->left!=NULL&&current->right!=NULL){
            succ=current->right;
            while(succ->left!= 0 ){
                psucc=succ;
                succ = succ->left;
        }
            if(parent->right==current){
                parent->right->item=succ->item;
                parent=parent->right;
                current=parent->right;
                if(current==succ){
                    parent->right=succ->right;
                    free(succ);
                    return TRUE_VALUE;
            }
                if(current!=succ){
                    psucc->left=0;
                    free(succ);
                    return TRUE_VALUE;
            }

        }
            if(parent->left == current){
                parent->left->item=succ->item;
                parent=parent->left;
                current=parent->right;
                if(current==succ){
                    parent->right=succ->right;
                    free(succ);
                    return TRUE_VALUE;
            }
                if(current!=succ){
                    psucc->left=0;
                    free(succ);
                    return TRUE_VALUE;
        }

    }

}


    if(current->left==NULL&&current->right==NULL){
        if(parent->right==current) parent->right=NULL;
        else parent->left=NULL;
        free(current);
        return TRUE_VALUE;
        }
    if(current->left==NULL&&current->right!=NULL){
        if(parent->left==current) parent->left=current->right;
            else parent->right=current->right;
            free(current);
            return TRUE_VALUE;
        }
    if(current->left!=NULL&&current->right==NULL){
        if(parent->left==current) parent->left=current->left;
        else parent->right=current->left;
        free(current);
        return TRUE_VALUE;
        }
    }
}








int getMinItem() //returns the minimum item in the tree
{
    struct treeNode *t = root;
    while(1){
        if(t->left == 0)return t->item;
        t = t->left;
    }
}

int getMaxItem() //returns the maximum item in the tree
{
    struct treeNode *t = root;
    while(1){
        if(t->right == 0)return t->item;
        t = t->right;
    }
}

int rangeSearch(struct treeNode * node, int leftBound, int rightBound) //returns number of items in the
{
    if (node == 0) return 0;
    if (node->item == rightBound && node->item == leftBound) return 1;

    if (node->item <= rightBound && node->item >= leftBound) return 1 + rangeSearch(node->left, leftBound, rightBound) + rangeSearch(node->right, leftBound, rightBound);
    else if (node->item < leftBound) return rangeSearch(node->right, leftBound, rightBound);
    else return rangeSearch(node->left, leftBound, rightBound);
}


void printInOrder(struct treeNode * node, int height)
{
    if(node==0) return ;

    //print left sub-tree
    printInOrder(node->left, height-1);

    //print item
    for(int i=0;i<height;i++)printf("   ");
    printf("%03d\n",node->item);

    //print right sub-tree
    printInOrder(node->right, height-1);
}



int main(void)
{
    initializeTree();
    while(1)
    {
        printf("1. Insert item. 2. Delete item. 3. Search item. \n");
        printf("4. Print height of tree. 5. Print height of an item. \n");
        printf("6. PrintInOrder. 7. exit.\n");
        printf("8.GetSize. 9.Calculate Depth Of an Item\n");
        printf("10.Calculate Depth of a Node. 11.MaxTerm. 12.MinTerm\n");
        printf("13.RangeSearch\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(root, item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            deleteItem(root,item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct treeNode * res = searchItem(root, item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            int height = calcNodeHeight(root);
            printf("Height of tree = %d\n", height);
        }
        else if(ch==5)
        {
            int item;
            scanf("%d", &item);
            int height = calcHeight(item);
            printf("Height of %d = %d\n", item, height);
        }
        else if(ch==6)
        {
            int h = calcNodeHeight(root);
            printf("\n--------------------------------\n");
            printInOrder(root, h);
            printf("--------------------------------\n");
        }
        else if(ch==7)
        {
            break;
        }
        else if(ch==8)
        {
            int i = getSize(root);
            printf("Size is %d\n",i);
        }
        else if(ch==9)
        {
            int item;
            scanf("%d",&item);
            int i = calcDepth(item);
            printf("Depth of the item %d\n",i);
        }
        else if(ch == 10)
        {
            int item;
            scanf("%d",&item);
            int i = calcNodeDepth(searchItem(root,item));
            printf("depth of the Node %d\n",i);
        }
        else if(ch==11)
        {
            int i = getMaxItem();
            printf("MaxItem is %d\n",i);
        }
        else if(ch==12)
        {
            int i = getMinItem();
            printf("MinItem is %d\n",i);
        }
        else if(ch == 13){
            int l,r,i;
            scanf("%d",&l);
            scanf("%d",&r);
            i = rangeSearch(root,l,r);
            printf("Number of Item %d\n",i);
        }

    }

}

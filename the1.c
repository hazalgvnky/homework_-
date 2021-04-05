#include <stdio.h>
#include <math.h>
#include "the1.h"

/*
 * This function gets a parameter that indicateswhether user will give initial values or not. If it evaluates false,
 * you will simply set all values of thearray -1. Otherwise, you will scan an integer from the user stating the number
 * of values that s/he willenter. User will enter that many integer index and value pairs. If the value for that index
 * is insertedbefore, or the index or the value is out of the range, you will simply ignore it.
*/
void initialize_the_tree(int binary_tree[MAX_LENGTH], int get_values_from_user){
    int m,i,n;
    if(get_values_from_user){
        int num_values;
        for(i=0; i < MAX_LENGTH; i++){         
            binary_tree[i] = -1;
        }
        scanf(" %d", &num_values);
        for(n=0;n < num_values;n++){
            int my_index, my_value;
            scanf(" %d %d", &my_index, &my_value);
            if(binary_tree[my_index] == -1){
                binary_tree[my_index] = my_value;
            }
        }
    }
    else{
        for(m=0; m < MAX_LENGTH; m+=1){         
            binary_tree[m] = -1;
        }
    }
}


/*
 * This function gets index of parent node, 'l'eft, 'r'ight or 'i'tself for where to insert and integer value.
 * If the value for the inserted node already exists, it ignores and does nothing.
 */
void insert_node(int binary_tree[MAX_LENGTH], int node, char where, int value){
    int place, path;
    if(where == 'l'){
        path = (2*node)+1;
        if(path < MAX_LENGTH){
            place = binary_tree[path];
            if(place == -1){
                binary_tree[path] = value;
            }
        }
    }
    if(where == 'r'){
        path = (2*node)+2;
        if(path < MAX_LENGTH){
            place = binary_tree[path];
            if(place == -1){
                binary_tree[path] = value;
            }
        }
    }
    if(where == 'i'){
        if(node < MAX_LENGTH){
            place = binary_tree[node];
            if(place == -1){
                binary_tree[node] = value;
            }
        }
    }
}


/*
 * This method  gets  the  index  of  the  node  to  be  deleted.   If  a  node  is  to  be deleted, all of its
 * descendants will be also purged.  Deleting means putting -1 value to the proper area in the array.
 */
void delete_node_rec(int binary_tree[MAX_LENGTH], int node){
    int left, right;
    if(node < (MAX_LENGTH-2)/2){
        left = binary_tree[(node*2)+1];
        right = binary_tree[(node*2)+2];
        if(binary_tree[node] != -1){
            binary_tree[node] = -1;
            if(left != -1){
                delete_node_rec(binary_tree, (node*2)+1);
            }
            if(right != -1){
                delete_node_rec(binary_tree, (node*2)+2);
            }
        }
    }
    else{
        if(2*node+1 < MAX_LENGTH){
           left = binary_tree[(node*2)+1];
           if(binary_tree[node] != -1){
                binary_tree[node] = -1;
                if(left != -1){
                    delete_node_rec(binary_tree, (node*2)+1);
                }
            }
        }
        else{
            if(binary_tree[node] != -1){
                binary_tree[node] = -1;
            }
        }
    }
}


/*
 * This is  a recursive function that prints the tree in in-order fashion. In other words, it will print the nodes 
 * starting from the left-most child and traverse the rest of the tree in that manner. Printing order will be 
 * <left-child, root, right-child>. It gets the index of the root and the depth value as control variable. Initial 
 * value of the depth will be the height of the tree. Be careful, any sub-tree can be given to the function.
 */
void helper_t(int depth, int count){
    char space='\t';
    if(count<= depth){
        printf("%c", space);
        helper_t(depth, count+1);
    }
} 
void draw_binary_tree_rec(int binary_tree[MAX_LENGTH], int root, int depth){
    int count=1, left, right;
    left = (root*2)+1;
    right = (root*2)+2;
    if(right <= MAX_LENGTH){
        if(binary_tree[root] != -1){
            draw_binary_tree_rec(binary_tree, left, depth-1);
            helper_t(depth, count);
            printf("%d\n", binary_tree[root]);
            draw_binary_tree_rec(binary_tree, right, depth-1);
        }
    }
    else{
        if(root < MAX_LENGTH){
            helper_t(depth, count);
            printf("%d\n", binary_tree[root]);
        }
    }
}
/*
 * This is a recursive function that returns the height of the tree.  If given root does not have any child, its height
 * is 0.  Be careful, any sub-tree can be given to the function
 */
int find_height_of_tree_rec(int binary_tree[MAX_LENGTH], int root){
    int height;
    int left, right, left_height, right_height;
    if((root*2)+2 < MAX_LENGTH){
        left = binary_tree[(root*2)+1];
        right = binary_tree[(root*2)+2];
        if(left == -1 && right == -1){
            return 0;
        }
        else{
            left_height = find_height_of_tree_rec(binary_tree, (root*2)+1);
            right_height = find_height_of_tree_rec(binary_tree, (root*2)+2); 
            if(left_height >= right_height){
                height = left_height;    
            }
            else{
                height = right_height;
            }
            return height+1;
        }
    }
    return 0;
}
/*
 * This is a recursive function that returns the minimum value given tree contains.
 * Be careful, any sub-tree can be given to the function.
 */
int find_min_of_tree_rec(int binary_tree[MAX_LENGTH], int root){
    int result;
    int left_min, right_min, node;
        node = binary_tree[root];
        result = node;
    if(root*2+2 < MAX_LENGTH){
        if(binary_tree[(root*2)+1] == -1 && binary_tree[(root*2)+2] == -1){
            return result;
        }
        else{
            if(binary_tree[(root*2)+1] != -1){
                left_min = find_min_of_tree_rec(binary_tree, (root*2)+1);
                if(left_min <= result){
                    result = left_min;
                }
            }
            if(binary_tree[(root*2)+2] != -1){
               right_min = find_min_of_tree_rec(binary_tree, (root*2)+2); 
                if(right_min <= result){
                    result = right_min;
                }
            }
            return result;
        }
    }
    return result;
}

/*
 * This is an iterative function that performs breadth-first search on the given tree.  If the value does not appear
 * in the given tree,  it returns -1.  Otherwise,  it returns the index of the first observation of the value.
 * It gets the index of the root and the integer value that is to be searched.  Be careful, any sub-tree can be given to
 * the function and you will apply level-wise search in the tree
 */
int breadth_first_search_itr(int binary_tree[MAX_LENGTH], int root, int value){
    int m,n,i,b,queue[MAX_LENGTH];
    for(b = 0; b< MAX_LENGTH; b+= 1){
        queue[b] = -1;
    }
    queue[0] = root;
    for(i = 0; i< MAX_LENGTH; i+= 1){
        if(queue[i] == -1){
            return -1;
        }
        else if(binary_tree[queue[i]] == value){
            return queue[i];
        }
        else{
            if(queue[i]*2+2 < MAX_LENGTH){
                if(binary_tree[queue[i]*2+1] != -1){
                    for(n=0;n< MAX_LENGTH; n+=1){
                        if(queue[n] == -1){
                            queue[n] = queue[i]*2+1;
                            break;
                        }
                    }
                }
                if(binary_tree[queue[i]*2+2] != -1){
                    for(m = 0;m< MAX_LENGTH; m+=1){
                        if(queue[m] == -1){
                            queue[m] = queue[i]*2+2;
                            break;
                        }
                    }
                }
            }
        }
    }
}

/*
 * This is  a  recursive  function  that  performs  depth-first search on the given tree.  If the value does not appear
 * in the given tree,  it returns -1.  Otherwise,  itreturns the index of the first observation of the value.  It gets
 * the index of the root and the integer valuethat is to be searched.
 * Be careful, any sub-tree can be given to the function.
*/
int depth_first_search_rec(int binary_tree[MAX_LENGTH], int root, int value){
    if(root*2+2 < MAX_LENGTH){
        if(binary_tree[root] == -1){
            return -1;
        }
        if(binary_tree[depth_first_search_rec(binary_tree,root*2+1,value)] == value){
              return depth_first_search_rec(binary_tree,root*2+1,value);
           }
        else if(binary_tree[root] == value){
            return root;
        }
        else if(binary_tree[depth_first_search_rec(binary_tree,root*2+2,value)] == value){
            return depth_first_search_rec(binary_tree,root*2+2,value);
        }
        else{
            return -1;
        }
    }
    else{
        if(binary_tree[root] == -1){
            return -1;
        }
        else if(binary_tree[root] == value){
            return root;
        }
        else{
            return -1;
        }
    }
}
 

/*
 * This is already given to you.
 */
void print_binary_tree_values(int binary_tree[MAX_LENGTH]){
    int i;
    for (i = 0; i < MAX_LENGTH; i++) {
        if (binary_tree[i] != -1) {
            printf("%d - %d\n", i, binary_tree[i]);
        }
    }

}



/**
 * @file BST_ADT.c
 *
 * @version <BST_ADT.0.0.1>
 * @author <Peter D Swisher> (pswisher@pdx.edu)
 * @date   <12/06/2024>
 *
 * @brief
 * Source code for Binary Search Tree ADT.
 *
 * @details
 * Revision History
 * ----------------
 *	1.0.0	(01-DEC-2024)	Initial version
 */


#include "BST_Helper.h"

//CREATE BST
listNodePTR_t create_tree(char * buffer, float temp, float hum) { //generate root node if it does not exist
    listNodePTR_t root = (listNodePTR_t)malloc(sizeof(listNode_t)); //alloc mem block of size listNode, cast to listNode ptr and assign to root
	if(!root){
		printf("Could not allocate memory... Terminating application...\n");
		return NULL;
	}
	
	//set root node values
    root->Ftime = buffer;
    root->temperature = temp;
    root->humidity = hum;
    root->left = NULL;
    root->right = NULL;
	
								printf("DEBUG(create_tree): Successfully created BST\n");
    return root;
}

//INSERT NODE
listNodePTR_t add_leaf(listNodePTR_t nodePTR, char * buffer, float temp, float hum) {
    
    if (!nodePTR) { 								// If the tree is empty, calls create tree function, creates and returns root node
        nodePTR = create_tree(buffer, temp, hum);
		printf("DEBUG(add_leaf): Generated new Binary Search Tree.\n");
		return nodePTR;
    }
	
		listNodePTR_t new_node = (listNodePTR_t)malloc(sizeof(listNode_t));
		new_node->Ftime = buffer;
		new_node->temperature = temp;
		new_node->humidity = hum;
		new_node->left = NULL;
		new_node->right = NULL;
	
	
    if ((new_node->Ftime) < (nodePTR->Ftime))  //insert left if timestamp is earlier than current node
        nodePTR->left = new_node;
	else if ((new_node->Ftime) > (nodePTR->Ftime))//insert right if greater
		nodePTR->right = add_leaf(new_node, buffer, temp, hum);
	
    return nodePTR;
}

//SEARCH BST
listNodePTR_t search_tree(listNodePTR_t nodePTR, char * buffer){

	if(!nodePTR){
		printf("The item you are looking for does not exist...\n");
		return NULL;
	}
	
    if ((nodePTR->Ftime) == buffer){
		printf("Match found! ...\n");
		return nodePTR; //returns pointer to node with matching timestamp info. TODO: handle data output in main
	}
	
	listNodePTR_t target = search_tree(nodePTR->left, buffer);
			
    if (target != NULL) {
        return target; // Return if match found in left subtree
    }
	
	 return search_tree(nodePTR->right, buffer); //search right subtree; 
		
}

//PRINT ALL NODES IN ORDER
/*void print_inOrder(listNodePTR_t nodePTR){

	if(!nodePTR){ 
		//printf("Nothing to print... returning...\n");
		return;
	}
	
	print_inOrder(nodePTR->left);
	
	char time_buffer[30];  // Array to hold formatted time value
    //struct tm *time = localtime(&nodePTR->timestamp);  // Convert time_t to struct tm using time.h lib function
    strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", time); //formats time into readable stringf
	
	
	printf("Temperature:\t %.2f °C\t Humidity:\t %.2f%%\t Timestamp: \t%s\t\n", nodePTR->temperature, nodePTR->humidity, time_buffer);
	print_inOrder(nodePTR->right);   
}*/

//Shuffles Array Values
void shuffle_array(ValsPTR_t arrptr, int arrsize){
	
	srand((uint32_t)time(NULL));//seed RNG
	
	Vals_t temp[arrsize];
	
	for (int i = arrsize - 1; i > 0; i--) {
        
        int j = rand() % (i + 1); // // Generates random index j such that 0 ≤ j ≤ i

        // Swap array[i] and array[j]
        temp[i] = arrptr[i];
        arrptr[i] = arrptr[j];
        arrptr[j] = temp[i];
    }
}
	
	
/*void getUI(listNodePTR_t nodePTR){
	
	//greet user
	//while user does not enter escape char, continue prompting after each entry
	//prompt user for a timestamp
	//search BST for node with matching timestamp
	//print all data for that node
	//reprompt user
	
}*/
	
	

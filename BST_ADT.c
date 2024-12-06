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
listNodePTR_t create_tree(char * buffer, time_t Rtm, float temp, float hum) { //generate root node if it does not exist

	//printf("DEBUG(create_tree): \t%s\t\n", *buffer);
    listNodePTR_t root = (listNodePTR_t)malloc(sizeof(listNode_t)); //alloc mem block of size listNode, cast to listNode ptr and assign to root
	if(!root){
		printf("Could not allocate memory... Terminating application...\n");
		exit(EXIT_FAILURE);
	}
	
	//set root node values
    root->Ftime = buffer;
	root->UFtime = Rtm;
    root->temperature = temp;
    root->humidity = hum;
    root->left = NULL;
    root->right = NULL;
	
								//printf("DEBUG(create_tree): Successfully created BST\n");
    return root;

	
}

//ISSUE OCCURS HERE/////////////////////////////////////////////////////// buffer not passed correctly

listNodePTR_t add_leaf(listNodePTR_t nodePTR, char * buffer, time_t Rtm, float temp, float hum) {
	
	
    
    if (!nodePTR) { 								// If the tree is empty, calls create tree function, creates and returns root node
        nodePTR = create_tree(buffer, Rtm, temp, hum);
		//add_leaf(nodePTR, buffer, Rtm, temp, hum);
		return nodePTR;
    }
	else{
		listNodePTR_t new_node = (listNodePTR_t)malloc(sizeof(listNode_t));
		if(!new_node){
			printf("Could not allocate memory... Terminating application...\n");
			exit(EXIT_FAILURE);
		}
	
		new_node->Ftime = buffer;
		new_node->UFtime = Rtm;
		new_node->temperature = temp;
		new_node->humidity = hum;
		new_node->left = NULL;
		new_node->right = NULL;
	}
	
	
	
	
	if (Rtm > nodePTR->UFtime) {  // Insert into the left subtree
        nodePTR->left = add_leaf(nodePTR->left, buffer, Rtm, temp, hum);
    } else if (Rtm < nodePTR->UFtime) {  // Insert into the right subtree
        nodePTR->right = add_leaf(nodePTR->right, buffer, Rtm, temp, hum);
    } else {
        printf("DEBUG(add_leaf): Duplicate timestamp encountered, ignoring: %s\n", buffer);
    }

	
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
	
	
void getUI(listNodePTR_t nodePTR){
	
	//greet user
	//while user does not enter escape char, continue prompting after each entry
	//prompt user for a timestamp
	//search BST for node with matching timestamp
	//print all data for that node
	//reprompt user
	
}

//DEBUG: PRINT ALL NODES IN ORDER
void print_inOrder(listNodePTR_t nodePTR){

	if(!nodePTR){ 
		return;
	}
	
	print_inOrder(nodePTR->left);
	
	printf("Temperature: %.2f °C\t Humidity: %.2f%%\t Timestamp: %s\n", nodePTR->temperature, nodePTR->humidity, nodePTR->Ftime);
	
	//printf("Temperature:\t %.2f °C\t Humidity:\t %.2f%%\t Timestamp: \t%s\t\n", nodePTR->temperature, nodePTR->humidity, time_buffer);
	print_inOrder(nodePTR->right);   
}
	

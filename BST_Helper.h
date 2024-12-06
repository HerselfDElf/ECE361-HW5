/**
 * @file BST_Helper.h
 *
 * @version 1.0.0
 * @author 	Peter Swisher (pswisher@pdx.edu)
 * @date 	06-Dec-2024
 *
 * @brief
 * This is the header file for a refactored implementation of Karumanchi's Binary Search Tree ADT.
 * Contains function prototypes, typedefs, and global vars for --ECE361 HW5 project--
 *
 * @details
 * Revision History
 * ----------------
 *	1.0.0	(06-Dec-2024)	Initial version
 */

#ifndef BST_Helper_H
#define BST_Helper_H

#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


//Typedefs and Structs//
typedef char arr_t[30][20];		//2D array to hold formatted timestamps

/**
 * @struct BST
 * @brief Node struct for the BST
 */
typedef struct listNode{
	float temperature;
	float humidity;
	char * Ftime;
	time_t UFtime;
	struct listNode* left;
	struct listNode* right;
}listNode_t, *listNodePTR_t;

/**
 * @struct Vals (Set to November 1st, 2024)
 * @brief Struct to temporarily hold value before randomizing
 */
typedef struct Vals{
	float temperature;
	float humidity;
	time_t rawtm;
	struct tm *ftimestamp;
}Vals_t, *ValsPTR_t;

/**
 * @struct Start Time (Set to November 1st, 2024)
 * @brief Standard Time Lib Struct to hold starting time info
 */
struct tm nov_time = {0};
 


// API FUNCTION PROTOTYPES
/**
 * @brief Allocates memory for root node of new BST
 * @param timestamp is the time_t value representing the date of data collection
 * @param temp is the temperature value to be placed in root node
 * @param hum is the humidity value to be placed in root node
 * @return Pointer to generated root node
 *
 * @details Generates new BST
 * 
 * 
 */
listNodePTR_t create_tree(char * buffer, time_t UFtime, float temp, float hum);


/**
 * @brief Allocates memory for new node of BST. Calls create_tree func if BST does not exist.
 * @param timestamp is the time_t value representing the date of data collection
 * @param temp is the temperature value to be placed in new node
 * @param hum is the humidity value to be placed in new node
 * @return void
 *
 * @details Inserts new node into BST. 
 * 
 * 
 */
listNodePTR_t add_leaf(listNodePTR_t nodePTR, char * buffer, time_t UFtime, float temperature, float humidity);


/**
 * @brief Searches BST based on user provided timestamp
 * @param nodePTR is a pointer to a BST
 * @param timestamp is the time_t value representing the date of data collection
 * @return Pointer to node with matching timestamp, or NULL if timestamp was not in tree
 *
 * @details Recursive DLR (pre-order) search. Checks root for match, then searches left subtree, then searches right subtree.
 * 			Returns pointer to node with matching timestamp if found, else returns NULL.
 * 
 * 
 */
listNodePTR_t search_tree(listNodePTR_t nodePTR, char * buffer);



/**
 * @brief Prints entire tree in order
 * @param nodePTR is a pointer to the root node of a BST
 * @return none
 *
 * @details Visits each node, prints the temp, humidity, and time data to stdout
 *			Time data is formated to be human readable via strftime function (provided in time.h standard library)
 */
//void print_inOrder(listNodePTR_t nodePTR);


/**
 * @brief Shuffles values in array using Fisher-Yates Algorithm
 * @param arrptr is the base address of an array
 * @param arrsize is the size of that array
 * @return none
 *
 * @details For more information on the Fisher-Yates Shuffle algorithm see: (https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle)
 *			Time Complexity: O(n)O(n) because each element is swapped once.
 *			Space Complexity: O(1)O(1) as it doesn't use additional memory.
 */
 
void shuffle_array(ValsPTR_t arrptr, int arrsize);



/**
 * @brief Handles user input
 * @param 
 * @return 
 *
 * @details
 */
//void getUI(listNodePTR_t nodePTR)


#endif
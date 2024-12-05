#include "BST_Helper.h" //should probably be .c
#include <time.h>


int main(){
	
	float ATemperature = 11; 
	float AHumidity = 11;
	time_t ATime = time(NULL);
	
	float AnotherTemperature = 22;
	float AnotherHumidity = 22;
	time_t AnotherTime = time(NULL) + 100;
	
	float AThirdTemperature = 33;
	float AThirdHumidity = 33;
	time_t AThirdTime = time(NULL) - 100;
	
//BASIC TESTS	
	listNodePTR_t NodePTR = NULL;
	listNodePTR_t root = NULL;
	
	root = create_tree(ATime, ATemperature, AHumidity);
	if(!root)
		printf("DEBUG(main): ALLOC FAILURE. ROOT RETURNED NULL\n");
	
	//print_inOrder(root); //EXPECTED: print root node data only (no leaves exists at this point)
	
	if(!add_leaf(root, AnotherTime, AnotherTemperature, AnotherHumidity))
		printf("DEBUG(main): ALLOC FAILURE. LEAF RETURNED NULL\n");
	else
		printf("DEBUG (add_leaf): succesfully added new leaf to BST\n");
	
	if(!add_leaf(root, AThirdTime, AThirdTemperature, AThirdHumidity));
		printf("DEBUG(main): ALLOC FAILURE. LEAF RETURNED NULL\n");
	else
		printf("DEBUG (add_leaf): succesfully added new leaf to BST\n");
	
	print_inOrder(root); //EXPECTED: prints data from all three nodes
	
	
//EDGE CASES
	
	//print_inOrder(NodePTR); //EXPECTED: prints empty list error case
	
	
	
	return 0;
}
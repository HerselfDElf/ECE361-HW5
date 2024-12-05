typedef struct listNode{
	float temp;
	float humidity;
	time_t timestamp;
	struct listNode* left;
	struct listNode* right;
}listNode_t, listNodePTR_t


void simulate_month_readings(ListNode** root) {
    time_t current_time;
    struct tm* time_info;
    
    // Set typical temperature and humidity range for Portland, OR in November
    float temp_low = 5.0, temp_hi = 15.0;  // Temperature between 5°C and 15°C
    float humid_low = 80.0, humid_hi = 90.0;  // Humidity between 80% and 90%

    // Simulate 30 days of readings
    for (int day = 1; day <= 30; ++day) {
        // Get current time and update for the specific day
        time(&current_time);
        time_info = localtime(&current_time);
        time_info->tm_mday = day;  // Set the day of the month
        current_time = mktime(time_info);  // Get the updated timestamp

        // Set random temperature and humidity for each day (simulating real-world variations)
        float temp = temp_low + (rand() % ((int)(temp_hi - temp_low) + 1));
        float humidity = humid_low + (rand() % ((int)(humid_hi - humid_low) + 1));

        // Insert the data into the BST
        *root = add_leaf(*root, current_time, temp, humidity);
    }
}



listNodePTR_t create_tree(time_t timestamp, float temp, float hum) { //generate root node if it does not exist
    listNodePTR_t root = (listNodePTR)malloc(sizeof(listNode));
	if(!root){
		printf("Could not allocate memory... Terminating application...\n");
		return -1;
	}
	
    root->timestamp = timestamp;
    root->temperature = temp;
    root->humidity = hum;
    root->left = NULL;
    root->right = NULL;
    return root;
}


listNodePTR_t add_leaf(listNodePTR_t root, time_t timestamp, float temperature, float humidity) {
    
    if (!root) { // If the tree is empty, calls create tree function
        root = create_tree(timestamp, temperature, humidity);
		printf("BST does not exist. Returned pointer to newly generated BST.\n");
		return root;
    }
    
    if (timestamp < (root->timestamp)) { // Insert node left if timestamp is less than root, right if greater
        root->left = add_leaf(root->left, timestamp, temperature, humidity);
    } else {
        root->right = add_leaf(root->right, timestamp, temperature, humidity);
    }

    return root;
}
// globals consts and structs
#define MAX_DATA_ITEMS	10
#define NUM_LEDS		16
#define NUM_SWITCHES	16
#define DAY_SECONDS		86400 //number of seconds in a day

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include "BST_ADT.c"
#include "iom361_r2.c"
#include "float_rndm.c"


	
int main() {
	
	int rtn_code;
	uint32_t *io_base;
	Vals_t store_entries[30];
	uint32_t temp_value;
	uint32_t humid_value;
	char time_buffer[30];
	
	
	nov_time.tm_year = 124;  		// Years since 1900
	nov_time.tm_mon  = 10;          // November - 11th month(0-indexed)
	nov_time.tm_mday = 1;           // 1st day of the month
	nov_time.tm_hour = 0;          
	nov_time.tm_min  = 0;          
	nov_time.tm_sec  = 0;
	
	
//GREETING PROTOCOL
//
    printf("Welcome. //CODE DESCRIPTION// .\n");
    errno = 0;
    char *buf = getcwd(NULL, 0);      
    if (buf == NULL) {
        perror("getcwd");
        printf("Could not display the path\n");
    }
    else {
        printf("Current working directory: %s\n", buf);
        free(buf);
    }
    printf("\n");
//
//END GREETING PROTOCOL
	
	 
//REGISTER INITIALIZATION PROTOCOL
//
	io_base = iom361_initialize(NUM_LEDS, NUM_SWITCHES, &rtn_code); //initialize 32 switches, 32 leds. 
	
	if (rtn_code != 0 || io_base == NULL) { // initialization fails if rtn_code return >0 or pointer returns null
		printf("FATAL(main): Could not initialize I/O module. Exiting...\n");
		return 1;
	}
	else printf("STATUS REPORT: Initialization Success!\n\n");
//
//END REGISTER INITIALIZATION PROTOCOL

	uint32_t temp_low = 41.0, temp_hi = 52.0;  // Typical temp values for Portland in November (https://www.currentresults.com/Weather/Oregon/Places/portland-weather-in-november.php)
    uint32_t humid_low = 75.0, humid_hi = 90.0;  // Typical humidity values for Portland in November (https://www.currentresults.com/Weather/Oregon/humidity-november.php)


	// Set random temperature and humidity for 30 days
	
	listNodePTR_t BST = NULL;
	time_t nov_rawtm = mktime(&nov_time); //converts data from nov_time struct into time_t value; strftime to reverse
	
    for (int day = 0; day <= 29; ++day) { 

		//SET SENSOR EACH LOOP PASSING RESTRICTED RANGE//
        _iom361_setSensor1_rndm(temp_low, temp_hi, humid_low, humid_hi);
		
		//READ BACK AHT20 VALUE FROM TEMP REGISTER
		temp_value = iom361_readReg(io_base, TEMP_REG, &rtn_code); 
			if (rtn_code != 0) {
				printf("Error reading I/O register\n");
				return -1;
			}
			
		//convert back to C
		temp_value = ((temp_value/(powf(2, 20))) * 200) - 50;
		
		//READ BACK AHT20 VALUE FROM HUM REGISTER
        humid_value = iom361_readReg(io_base, HUMID_REG, &rtn_code); 
			if (rtn_code != 0) {
				printf("Error reading I/O register\n");
				return -1;
			}
			
		//convert back to RH
		humid_value = ((humid_value/(powf(2, 20))) * 100);
			//printf("DEBUG(H): %u\n\n", humid_value);
	
			
		store_entries[day].temperature = temp_value;
		store_entries[day].humidity = humid_value;
		store_entries[day].rawtm = nov_rawtm + (day*DAY_SECONDS);
		store_entries[day].ftimestamp = localtime(&store_entries[day].rawtm); //increments time by 1 day for each reading and converts into struct tm*
		strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", store_entries[day].ftimestamp); //formats and returns string
	}
	
	
	

	
	
	//STATUS: store_entries arrays now has a struct holding raw time, temp, and humidity for each day (IN ORDER OF TIMESTAMP)
	/*	for(int day = 0; day<30; day++){
		printf("DEBUG(main1): %.2f, %.2f, %.2ld\n", store_entries[day].temperature, store_entries[day].humidity, store_entries[day].timestamp);
		}
		printf("\n");
	*/

	//randomize values in array
	shuffle_array(store_entries, 30);
	//STATUS: store_entries array now has a struct holding raw time, temp, and humidity for each day (IN RANDOM ORDER)
	/*	for(int day = 0; day<30; day++){
		printf("DEBUG(main2): %.2f, %.2f, %ld\n", store_entries[day].temperature, store_entries[day].humidity, store_entries[day].timestamp);
		}
	*/
		
	//insert into BST
	for(int i = 0; i<=30; ++i){
			
		if(!BST){
			BST = add_leaf(BST, time_buffer, store_entries[i].temperature, store_entries[i].humidity);
			printf("DEBUG(main): %.2f, %.2f, %s\n", BST->temperature, BST->humidity, BST->Ftime);
		}
		else{
			add_leaf(BST, time_buffer, store_entries[i].temperature, store_entries[i].humidity);
			printf("DEBUG(main): %.2f, %.2f, %s\n", BST->temperature, BST->humidity, BST->Ftime);
		}
	}

		

		//TODO: figure out how to convert and display rawtime to user as formatted timestamp
		//size_t strftime(char *s, size_t maxsize, const char *format, const struct tm *timeptr);
	
	
	//TODO: USER IO. PROMPT USER FOR SPECIFIC DATE IN SPECIFIC TIME FORMAT (match to fields of struct). 
	//printf data for that date if it exists, throw error else
		
		
return 0;
}
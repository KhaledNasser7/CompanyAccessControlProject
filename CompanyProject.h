/*
 * CompanyProject.h
 *
 * Created: 24/05/2018 06:38:20 م
 *  Author: Khaled Mohamed Nasser
 */ 


#ifndef COMPANYPROJECT_H_
#define COMPANYPROJECT_H_

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "VirtualTerminal.h"
#include "Keypad.h"
#include "EEPROMFunctions.h"
#include "RTCFunctions.h"

// super admin data
#define super_admin_name		"khaled"
#define super_admin_id			1465u
#define super_admin_password	1031u
#define super_admin_authority   ADMIN
#define unblock_code			5547u // must be 4 digit number
#define max_password_attempts	3
#define buzzer_pin	6
#define door_pin	7



// enum
typedef enum{
	USER,ADMIN
	}authority_t;

typedef enum{
	INVALID_ID,VALID_ID
	}id_status_t;
	
typedef enum{
	INVALID_PASSWORD,VALID_PASSWORD
}password_status_t;


// Structures
typedef struct{
	char name[8];
	uint16_t id;
	uint16_t password;
	authority_t type;
	boolean_t password_is_set;
}employee_t;


typedef struct point {
	employee_t employee;
	struct point *next;
}node;

#define node_malloc (node*) malloc(sizeof(node))

// Functions prototypes
id_status_t id_menu(node **company, uint16_t* id);
password_status_t password_menu(node **company, uint16_t id);
void admin_menu(node **company);
authority_t check_authority(node **company, uint16_t id);
void system_block();

void checkInput(uint8_t input,node **company);
void newEmployee(node **company);
void editEmployee(node **company);
void deleteEmployee(node **company);
void printEmployee(node **company);
void show_log_file(node **company);
void restore_factory_settings(node **company);
void exitProgram();
node* findemployee(node **company,uint8_t id);


void print_list(node **company);
void insert_employee(node ** head_ptr, node *new_employee);
void remove_employee(node ** head_ptr,node *employee);
void remove_employee_without_freeing(node ** head_ptr,node *employee);
void rearrangeList(node **head_ptr, node *employee);
void add_to_log_file(uint8_t id);

#define node_malloc (node*) malloc(sizeof(node))


#endif /* COMPANYPROJECT_H_ */
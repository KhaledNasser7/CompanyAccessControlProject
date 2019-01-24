/*
 * main.c
 *
 * Created: 24/05/2018 06:07:20 م
 *  Author: Khaled Mohamed Nasser
 *
 * Project : security access system of a company ... each employee has an ID & a password .. only eployees in the company database can enter
 * IDs range from 1->100 .. passwords are 4 character passwords .. there are three types of authority .. users, who can only go in and out ..
 * admins & admins, who can access the data base ... initially when there is no database yet, only super admins can access and add new employees
 *
 */ 


#include <avr/io.h>
#include "CompanyProject.h"


int main(void)
{
	SETBIT(DDRC,buzzer_pin);  //  buzzer or led pin	
	SETBIT(DDRC,door_pin); // door open/clos control pin
	node *company = NULL;
	virtual_terminal_init();
	keypad_init();
	i2c_init();
    while(1)
    {
        //TODO:: Please write your application code
		uint16_t id;
		while(id_menu(&company,&id) == INVALID_ID);
		uint8_t i = 0;
		password_status_t password_status=password_menu(&company,id);
		while(password_status == INVALID_PASSWORD && i <max_password_attempts-1){
			password_status=password_menu(&company,id);
			i++;
		}
		if(i == max_password_attempts-1 && password_status==INVALID_PASSWORD){
			system_block();
			CLRBIT(PORTC,buzzer_pin);  // stop buzzer
			continue;
		}
		if(check_authority(&company,id) == ADMIN ){
			admin_menu(&company);
			node* employee = findemployee(&company,id);
			i=0;
			SETBIT(PORTC,door_pin);  // open door
			virtual_terminal_clear();
			virtual_terminal_print_string("Hi ");
			if(employee!=NULL){
			while(employee->employee.name[i]!='\0'){virtual_terminal_print_character(employee->employee.name[i++]);}
			}else{
				virtual_terminal_print_string(super_admin_name);
			}
			virtual_terminal_newLine();virtual_terminal_print_string("You can enter now");
			if(employee != NULL){  // an admin
				add_to_log_file(id);
			}else{ // the super admin
				add_to_log_file(0);
			}
			_delay_ms(2000);
			CLRBIT(PORTC,door_pin); // close door
		}else{
			node* employee = findemployee(&company,id);
			i=0;
			virtual_terminal_clear();
			virtual_terminal_print_string("Hi ");
			while(employee->employee.name[i]!='\0'){virtual_terminal_print_character(employee->employee.name[i++]);}
			virtual_terminal_newLine();virtual_terminal_print_string("You can enter now");
			SETBIT(PORTC,door_pin);  // open door
			add_to_log_file(id);
			_delay_ms(2000);
			CLRBIT(PORTC,door_pin); // close door
		}
		
    }
}
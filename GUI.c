/*
 * GUI.c
 *
 * Created: 01/06/2018 09:46:12 م
 *  Author: Khaled Mohamed Nasser
 */ 

#include "CompanyProject.h"


static uint16_t scan_id(){
	uint8_t id[]={0,0,0,0};
	uint8_t i =0;
	id[i]=keypad_get_pressed_key();
	while(id[i] == 255 || (id[i] != '#' && i<4) ){
		id[i]=keypad_get_pressed_key();
		if(id[i] != '#' && id[i] != 255){
			virtual_terminal_print_character(id[i]);
			i++;
		}
	}
	_delay_ms(1000);
	uint16_t employee_id=0;
	switch(i){
		case 0: employee_id =0;break;
		case 1: employee_id = id[0]-48;break;
		case 2: employee_id = (id[0]-48)*10 +(id[1]-48);break;
		case 3: employee_id = (id[0]-48)*100+(id[1]-48)*10+(id[2]-48);break;
		case 4: employee_id = (id[0]-48)*1000+(id[1]-48)*100+(id[2]-48)*10+(id[3]-48);break;
		default: employee_id = 0;
	}
	return employee_id;
}


id_status_t id_menu(node **company, uint16_t* ret_id){
	id_status_t status = INVALID_ID;
	virtual_terminal_clear();
	virtual_terminal_print_string("Please Enter your ID then press '#' :");
	virtual_terminal_newLine();
	uint16_t employee_id=scan_id();
	if( (employee_id <=100 && employee_id >0 /*&& i<4*/) || employee_id == super_admin_id ){
		if( (findemployee(company,employee_id) != NULL) || employee_id == super_admin_id ){
			*ret_id = employee_id;
			status = VALID_ID;
			}else{
			virtual_terminal_clear();
			virtual_terminal_print_string("No ID match found!");
			_delay_ms(1000);
		}
		}else{
		virtual_terminal_clear();
		virtual_terminal_print_string("Invalid ID!");
		_delay_ms(1000);
	}
	return status;
}


password_status_t password_menu(node **company, uint16_t id){
	password_status_t status = INVALID_PASSWORD;
	if(findemployee(company,id)->employee.password_is_set == FALSE){
		virtual_terminal_clear();
		virtual_terminal_print_string("Please Enter your password :(you can reset your password only by contacting an admin)"); // 4 character password
		virtual_terminal_newLine();
		}else{
		virtual_terminal_clear();
		virtual_terminal_print_string("Please Enter your password :"); // 4 character password
		virtual_terminal_newLine();
	}
	uint8_t password[4];
	uint8_t i =0;
	password[i]=keypad_get_pressed_key();
	while(password[i] == 255 || i<4){
		password[i]=keypad_get_pressed_key();
		if( password[i] != 255){
			virtual_terminal_print_character(password[i]);
			_delay_ms(500);
			virtual_terminal_backspace();
			virtual_terminal_print_character('*');
			i++;
		}
	}
	_delay_ms(1000);
	uint16_t employee_password=0;
	switch(i){
		case 0: employee_password =0;break;
		case 1: employee_password = password[0]-48;break;
		case 2: employee_password = (password[0]-48)*10 +(password[1]-48);break;
		case 3: employee_password = (password[0]-48)*100+(password[1]-48)*10+(password[2]-48);break;
		case 4: employee_password = (password[0]-48)*1000+(password[1]-48)*100+(password[2]-48)*10+(password[3]-48);break;
		default: employee_password = 0;
	}
	if( (findemployee(company,id)->employee.password_is_set == FALSE)
	|| (findemployee(company,id)->employee.password == employee_password )
	|| ( id == super_admin_id && employee_password == super_admin_password) ){
		status = VALID_PASSWORD;
		if(findemployee(company,id)->employee.password_is_set == FALSE){
			findemployee(company,id)->employee.password_is_set=TRUE;
			findemployee(company,id)->employee.password=employee_password;
		}
		}else{
		virtual_terminal_clear();
		virtual_terminal_print_string("Wrong password!");
		_delay_ms(1000);
	}
	return status;
}


void system_block(){
	virtual_terminal_clear();
	virtual_terminal_print_string("SYSTEM BLOCK!!");
	SETBIT(PORTC,buzzer_pin);// turn led or buzzer on
	uint16_t employee_password=0;
	while(employee_password != unblock_code){
		uint8_t password[4];
		uint16_t unblock=unblock_code;
		password[0]=keypad_get_pressed_key();
		while(password[0] == 255){
			password[0]=keypad_get_pressed_key();
		}
		unblock=unblock_code/1000;
		if( (password[0]-48) == unblock ){
			//_delay_ms(100);
			unblock = (unblock_code-(unblock*1000))/100;
			password[1]=keypad_get_pressed_key();
			while(password[1] == 255){
				password[1]=keypad_get_pressed_key();
			}
			if( (password[1]-48) == unblock ){
				_delay_ms(100);
				unblock = (unblock_code-((unblock_code/100)*100))/10;
				password[2]=keypad_get_pressed_key();
				while(password[2] == 255){
					password[2]=keypad_get_pressed_key();
				}
				if( (password[2]-48) == unblock ){
					_delay_ms(100);
					unblock = (unblock_code-((unblock_code/10)*10));
					password[3]=keypad_get_pressed_key();
					while(password[3] == 255){
						password[3]=keypad_get_pressed_key();
					}
					if( (password[3]-48) == unblock ){
						return;
					}
				}
			}
		}
		//uint8_t i =0;
		//password[i]=keypad_get_pressed_key();
		//while(password[i] == 255 || i<4){
		//password[i]=keypad_get_pressed_key();
		//if(password[i] != 255){
		//i++;
		//}
		//}
		//switch(i){
		//case 0: employee_password =0;break;
		//case 1: employee_password = password[0]-48;break;
		//case 2: employee_password = (password[0]-48)*10 +(password[1]-48);break;
		//case 3: employee_password = (password[0]-48)*100+(password[1]-48)*10+(password[2]-48);break;
		//case 4: employee_password = (password[0]-48)*1000+(password[1]-48)*100+(password[2]-48)*10+(password[3]-48);break;
		//default: employee_password = 0;
		//}
		//employee_password = (password[0]-48)*1000+(password[1]-48)*100+(password[2]-48)*10+(password[3]-48);break;
		//TOGBIT(PORTC,buzzer_pin);
	}
}


void admin_menu(node **company){
	uint8_t input;
	virtual_terminal_clear();
	virtual_terminal_print_string("Please select an option ...");
	virtual_terminal_newLine();virtual_terminal_print_string("Menu :");
	virtual_terminal_newLine();virtual_terminal_print_string("1-New employee data");
	virtual_terminal_newLine();virtual_terminal_print_string("2-Edit employee data");
	virtual_terminal_newLine();virtual_terminal_print_string("3-Delete employee data");
	virtual_terminal_newLine();virtual_terminal_print_string("4-Print employee data");
	virtual_terminal_newLine();virtual_terminal_print_string("5-Print all employees data");
	virtual_terminal_newLine();virtual_terminal_print_string("6-Show log file");
	virtual_terminal_newLine();virtual_terminal_print_string("7-Restore factory settings");
	virtual_terminal_newLine();virtual_terminal_print_string("8-Exit");
	input = keypad_get_pressed_key();
	while(input == 255){
		input = keypad_get_pressed_key();
	}
	checkInput((input-48),company);
}
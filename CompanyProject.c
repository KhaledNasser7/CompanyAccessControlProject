/*
 * CompanyProject.c
 *
 * Created: 24/05/2018 06:55:53 م
 *  Author: Khaled Mohamed Nasser
 */ 

#include "CompanyProject.h"


static uint16_t eeprom_next_free_address=0x00;


static uint32_t bcd_to_decimal(uint8_t bcd){
	return (uint32_t)((bcd/16*10)+(bcd%16));
}


static void scan_name(uint8_t name[]){
	uint8_t i=0;
	name[0] = keypad_get_pressed_key();
	while(name[i] == 255 || (name[i] != '#' && i<7) ){
		name[i] = keypad_get_pressed_key();
		if(name[i] != 255 && name[i] != '#'){
			virtual_terminal_print_character(name[i]);
			i++;
		}
	}
	name[i]='\0';
}


static uint16_t scan_id(){
	uint16_t employee_id;
	uint8_t id[]={0,0,0,0};
	uint8_t i=0;
	id[i]=keypad_get_pressed_key();
	while(id[i] == 255 || (id[i] != '#' && i<4) ){
		id[i]=keypad_get_pressed_key();
		if(id[i] != '#' && id[i] != 255){
			virtual_terminal_print_character(id[i]);
			i++;
		}
	}
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


authority_t check_authority(node **company, uint16_t id){
	authority_t authority = USER;
	node* employee = findemployee(company,id);
	if (employee->employee.type == ADMIN || id==super_admin_id){
		authority = ADMIN;
	}
	return authority;
}


void checkInput(uint8_t input,node **company){
	switch(input){
		case 1: newEmployee(company);break;
		case 2: editEmployee(company);break;
		case 3: deleteEmployee(company);break;
		case 4: printEmployee(company);break;
		case 5: print_list(company);break;
		case 6: show_log_file(company);break;
		case 7: restore_factory_settings(company);break;
		case 8: exitProgram();break;
		default: virtual_terminal_print_string("Invalid option!");
				 _delay_ms(1000);
				 admin_menu(company);
	}
}


void newEmployee(node **company){
	virtual_terminal_clear();
	node *new_employee = node_malloc;
	if( new_employee == NULL ){       // malloc returns NULL means no space in memory
		virtual_terminal_print_string("Sorry There is no space for new employee data!");
		_delay_ms(1000);
	}
	else{
		char name[8];
		virtual_terminal_print_string("Please enter the name of the new employee followed by '#' : (Max. 7 characters)");
		virtual_terminal_newLine();
		scan_name(name);
		uint8_t j=0;
		while(name[j]!='\0'){
		new_employee->employee.name[j]=name[j];
		j++;
		}
		_delay_ms(500);
		
		id_status_t id_status = INVALID_ID;
		while(id_status == INVALID_ID){
		virtual_terminal_clear();
		virtual_terminal_print_string("Please enter the ID of the new employee followed by '#' :(IDs range from 1->100)");
		virtual_terminal_newLine();
		uint16_t employee_id=scan_id();
		if(employee_id>0 && employee_id<101){
			if(findemployee(company,employee_id) == NULL){
				id_status = VALID_ID;
				new_employee->employee.id=employee_id;
			}else{
				virtual_terminal_clear();
				virtual_terminal_print_string("This ID already exists for another employee!");
				_delay_ms(1000);
			}
		}else{
			virtual_terminal_clear();
			virtual_terminal_print_string("ID not within range!");
			_delay_ms(1000);
		}
		}
		new_employee->employee.password_is_set=FALSE;
		boolean_t authority_status= FALSE;
		uint8_t authority;
		while(authority_status == FALSE){
		virtual_terminal_clear();
		virtual_terminal_print_string("Please choose authority type :");
		virtual_terminal_newLine();virtual_terminal_print_string("1-Admin");
		virtual_terminal_newLine();virtual_terminal_print_string("2-User");
		authority = keypad_get_pressed_key();
		while(authority == 255){
			authority = keypad_get_pressed_key();
		}
		switch(authority){
			case 49: new_employee->employee.type=ADMIN;
					 authority_status=TRUE;break;
			case 50: new_employee->employee.type=USER;
					 authority_status=TRUE;break;
			default: virtual_terminal_clear();
					 virtual_terminal_print_string("Invalid option!");
					 _delay_ms(1000);
		}
		}
		virtual_terminal_clear();
		virtual_terminal_print_string("An employee is added successfully.");
		_delay_ms(1000);
		insert_employee(company,new_employee);
		admin_menu(company);
	}
	
}


void editEmployee(node **company){
	if(*company == NULL){
		virtual_terminal_clear();
		virtual_terminal_print_string("No employees data entered yet!");
		_delay_ms(1000);
		admin_menu(company);
	}else{
		node* current;
		uint16_t employee_id;
		id_status_t id_status=INVALID_ID;
		while(id_status==INVALID_ID){
		virtual_terminal_clear();
		virtual_terminal_print_string("Please enter the ID of the employee to be edited followed by '#' :");
		virtual_terminal_newLine();
		employee_id=scan_id();
			if(findemployee(company,employee_id) != NULL){
				id_status = VALID_ID;
				}else{
				virtual_terminal_clear();
				virtual_terminal_print_string("This ID does not exist!");
				_delay_ms(1000);
			}
		}
		uint8_t input;
		do {
		virtual_terminal_clear();
		virtual_terminal_print_string("Please select an option :");
		virtual_terminal_newLine();virtual_terminal_print_string("1-Edit name");
		virtual_terminal_newLine();virtual_terminal_print_string("2-Edit ID");
		virtual_terminal_newLine();virtual_terminal_print_string("3-Edit password");
		virtual_terminal_newLine();virtual_terminal_print_string("4-Edit type");
		
		do 
		{
			input = keypad_get_pressed_key();
		} while (input==255);
		
		input-=48;
		switch(input){
			case 1: virtual_terminal_clear();
					virtual_terminal_print_string("Please enter the new name followed by '#':");
					virtual_terminal_newLine();
					char name[]={0,0,0,0,0,0,0,0};
					scan_name(name);
					uint8_t j=0;
					node* employee=findemployee(company,employee_id);
					while(name[j]!='\0'){
						employee->employee.name[j]=name[j];
						j++;
					}
					_delay_ms(500);break;
			case 2: virtual_terminal_clear();
					id_status_t id_status = INVALID_ID;
					while(id_status==INVALID_ID){
						 virtual_terminal_clear();
						 virtual_terminal_print_string("Please enter the new ID followed by '#':");
						 virtual_terminal_newLine();
						uint16_t employee_new_id=scan_id();
						if(employee_new_id>0 && employee_new_id<101){
							if(findemployee(company,employee_new_id) == NULL){
								id_status = VALID_ID;
								findemployee(company,employee_id)->employee.id=employee_new_id;
								rearrangeList(company,findemployee(company,employee_new_id));
								}else{
								virtual_terminal_clear();
								virtual_terminal_print_string("This ID already exists for another employee!");
								_delay_ms(1000);
							}
							}else{
							virtual_terminal_clear();
							virtual_terminal_print_string("ID not within range!");
							_delay_ms(1000);
						}
					}break;
			case 3: findemployee(company,employee_id)->employee.password_is_set=FALSE;
					virtual_terminal_clear();
					virtual_terminal_print_string("Password now can be reset at next entry of the employee");
					_delay_ms(1000);break;
			case 4: virtual_terminal_clear();
					boolean_t authority_status= FALSE;
					uint8_t authority;
					while(authority_status == FALSE){
						virtual_terminal_clear();
						virtual_terminal_print_string("Please choose authority type :");
						virtual_terminal_newLine();virtual_terminal_print_string("1-Admin");
						virtual_terminal_newLine();virtual_terminal_print_string("2-User");
						authority = keypad_get_pressed_key();
						while(authority == 255){
							authority = keypad_get_pressed_key();
						}
						switch(authority){
							case 49: findemployee(company,employee_id)->employee.type=ADMIN;
							authority_status=TRUE;break;
							case 50: findemployee(company,employee_id)->employee.type=USER;
							authority_status=TRUE;break;
							default: virtual_terminal_clear();
							virtual_terminal_print_string("Invalid option!");
							_delay_ms(1000);
						}
					}break;
			default:virtual_terminal_clear();
			virtual_terminal_print_string("Invalid option!");
			_delay_ms(500);
		}
		} while ((input != 1) && (input != 2) &&( input != 3 ) && ( input != 4 ));
		virtual_terminal_clear();
		virtual_terminal_print_string("Edit done successfully");
		_delay_ms(1000);
		admin_menu(company);
	}
}


void deleteEmployee(node **company){
	if(*company == NULL){
		virtual_terminal_clear();
		virtual_terminal_print_string("No employees data entered yet!");
		_delay_ms(1000);
		}else{
			node* current;
			uint16_t employee_id;
			id_status_t id_status=INVALID_ID;
			while(id_status==INVALID_ID){
				virtual_terminal_clear();
				virtual_terminal_print_string("Please enter the ID of the employee to be deleted :");
				virtual_terminal_newLine();
				employee_id=scan_id();
				current=findemployee(company,employee_id);
				if(current!=NULL){
					id_status=VALID_ID;
					remove_employee(company,current);
					virtual_terminal_clear();
					virtual_terminal_print_string("Employee is deleted successfully");
					_delay_ms(1000);
				}else{
					virtual_terminal_clear();
					virtual_terminal_print_string("No data found for this ID!");
					_delay_ms(1000);
				}
		}
	}
	admin_menu(company);
}


void printEmployee(node **company){
	if(*company == NULL){
		virtual_terminal_clear();
		virtual_terminal_print_string("No employees data entered yet!");
		_delay_ms(1000);
		}else{
			uint16_t employee_id;
			id_status_t id_status=INVALID_ID;
			while(id_status==INVALID_ID){
				virtual_terminal_clear();
				virtual_terminal_print_string("Please enter the ID of the employee to be printed followed by '#' :");
				virtual_terminal_newLine();
				employee_id=scan_id();
				if(findemployee(company,employee_id) != NULL){
					id_status = VALID_ID;
					}else{
					virtual_terminal_clear();
					virtual_terminal_print_string("This ID does not exist!");
					_delay_ms(1000);
				}
			}
			node* employee = findemployee(company,employee_id);
			virtual_terminal_clear();
			virtual_terminal_print_string("Name : ");
			uint8_t i=0;
			while(employee->employee.name[i]!='\0'){virtual_terminal_print_character(employee->employee.name[i++]);}
			virtual_terminal_newLine();
			virtual_terminal_print_string("ID : ");virtual_terminal_print_number(employee->employee.id);
			virtual_terminal_newLine();
			virtual_terminal_print_string("Authority : ");
			if(employee->employee.type ==ADMIN){
				virtual_terminal_print_string("Admin");
				}else{
				virtual_terminal_print_string("User");
			}
			_delay_ms(5000);
		}
		admin_menu(company);
}


void show_log_file(node **company){
	uint8_t eeprom_data=0x00;
	eeprom_read(0x7FF,&eeprom_data);
	if(eeprom_data==0xFF){  // no log data entered yet
		virtual_terminal_clear();
		virtual_terminal_print_string("NO log data entered yet!");
		_delay_ms(1000);
	}else{
		eeprom_read(0x7FF,&eeprom_next_free_address);		// to load last value from eeprom at power off then power on
		uint16_t temp_address = 0x00;
		virtual_terminal_clear();
		virtual_terminal_print_string("Log Data :");
		virtual_terminal_newLine();
		while(temp_address<eeprom_next_free_address){
			// get id
			virtual_terminal_print_string("ID: ");
			eeprom_read(temp_address++,&eeprom_data);				// first read is id
			_delay_ms(50);
			if(eeprom_data == 0){  // super admin id will be shown as private
				virtual_terminal_print_string("private");
			}else{
			virtual_terminal_print_number(bcd_to_decimal(eeprom_data));
			}
			virtual_terminal_print_string(",	date: ");
			eeprom_read(temp_address++,&eeprom_data);				// second read is day
			_delay_ms(50);
			virtual_terminal_print_number(bcd_to_decimal(eeprom_data));
			virtual_terminal_print_character('-');
			eeprom_read(temp_address++,&eeprom_data);				// third read is month
			_delay_ms(50);
			virtual_terminal_print_number(bcd_to_decimal(eeprom_data));
			virtual_terminal_print_character('-');
			eeprom_read(temp_address++,&eeprom_data);				// fourth read is year
			_delay_ms(50);
			virtual_terminal_print_number(bcd_to_decimal(eeprom_data));
			virtual_terminal_print_string(",		time: ");
			eeprom_read(temp_address++,&eeprom_data);				// fifth read is hours
			_delay_ms(50);
			virtual_terminal_print_number(bcd_to_decimal(eeprom_data));
			virtual_terminal_print_character(':');
			eeprom_read(temp_address++,&eeprom_data);				// sixth read is minutes
			_delay_ms(50);
			virtual_terminal_print_number(bcd_to_decimal(eeprom_data));
			virtual_terminal_print_character(':');
			eeprom_read(temp_address++,&eeprom_data);				// seventh read is seconds
			_delay_ms(50);
			virtual_terminal_print_number(bcd_to_decimal(eeprom_data));
			virtual_terminal_newLine();
		}
		_delay_ms(5000);
	}
	admin_menu(company);
}


void restore_factory_settings(node **company){
	// clear log file by rewriting from the beginning
	eeprom_write(0x7FF,0xFF);
	_delay_ms(50);
	eeprom_next_free_address=0x00;
	// clear database by deleting all employees
	uint8_t i;
	node* employee=*company;
	while(employee != NULL){
		remove_employee(company,employee);
		employee=*company;
	}
	admin_menu(company);
}


void exitProgram(){
	
}


void print_list(node **company){
	node* head = *company;
	if( head == NULL ){
		virtual_terminal_clear();
		virtual_terminal_print_string("No employees data entered yet!");
		_delay_ms(1000);
		admin_menu(company);
	}
	else {
		uint8_t i;
		virtual_terminal_clear();
		while (head != NULL) {
			virtual_terminal_print_string("Name : ");
			i=0;
			while(head->employee.name[i]!='\0'){virtual_terminal_print_character(head->employee.name[i++]);}
			virtual_terminal_newLine();
			virtual_terminal_print_string("ID : ");virtual_terminal_print_number(head->employee.id);
			virtual_terminal_newLine();
			virtual_terminal_print_string("Authority : ");
			if(head->employee.type ==ADMIN){
				virtual_terminal_print_string("Admin");
			}else{
				virtual_terminal_print_string("User");
			}
			virtual_terminal_newLine();
			head = head->next;
		}
		_delay_ms(5000);
	}
	admin_menu(company);
}


node* findemployee(node **company,uint8_t id){
	node *current = *company;
	while( (current != NULL) && (current->employee.id != id) ){
		current = current->next;
	}
	return current;
}


void insert_employee(node ** head_ptr, node *new_employee){
	 if ( *head_ptr == NULL ) // if list is empty
	 {
		 *head_ptr = new_employee;
		 (*head_ptr)->next = NULL;
	 }
	 else
	 {
		 node * current = *head_ptr;
		 if( new_employee->employee.id < current->employee.id ){
			 // compare id with first student in list
			 new_employee->next = current;
			 *head_ptr = new_employee;
		 }
		 else {
			 while ( (current->next != NULL) &&
			 (current->next->employee.id < new_employee->employee.id) )
			 {
				 current = current->next;
			 }
			 new_employee->next = current->next ;
			 current->next = new_employee;
		 }
		 
	 }
}


void remove_employee(node ** head_ptr,node *employee){
	if(*head_ptr == employee){
		*head_ptr = (*head_ptr)->next;
		free(employee);
	}
	else {
		node *prev_employee = *head_ptr;
		while(prev_employee->next != employee){
			prev_employee = prev_employee->next;
		}
		prev_employee->next = employee->next;
		free(employee);
	}
}


void remove_employee_without_freeing(node ** head_ptr,node *employee){
	if(*head_ptr == employee){
		*head_ptr = (*head_ptr)->next;
	}
	else {
		node *prev_employee = *head_ptr;
		while(prev_employee->next != employee){
			prev_employee = prev_employee->next;
		}
		prev_employee->next = employee->next;
	}
}


void rearrangeList(node **head_ptr, node *employee){
	remove_employee_without_freeing(head_ptr, employee);
	node *current = *head_ptr;
	if(employee->employee.id < current->employee.id){ // insert first
		employee->next = *head_ptr;
		*head_ptr = employee;
	}
	else {
		while ( (current->next != NULL) &&
		(current->next->employee.id < employee->employee.id) )
		{
			current = current->next;
		}
		employee->next = current->next ;
		current->next = employee;
	}
}


void add_to_log_file(uint8_t id){
	uint8_t status=0;
	uint16_t saved_address=0x00;
	status=eeprom_read(0x7FF,&saved_address);
	_delay_ms(50);
	if(saved_address != 0xFF){  // if not defaul initial value
		eeprom_next_free_address=saved_address;
	}else{/*MISRA*/}
	if(eeprom_next_free_address>=2043){  // eeprom size is 2048 byte so we can save 2044 logs 0->2043 the rest4 byte will be reserved, last byte 0x7FF will contain the saved address
		eeprom_next_free_address=0x00;
	}else{/*MISRA*/}
	eeprom_write(eeprom_next_free_address++,id);
	_delay_ms(50);
	time_t time = ds1307_get_time();
	_delay_ms(50);
	date_t date = ds1307_get_date();
	_delay_ms(50);
	eeprom_write(eeprom_next_free_address++,date.day);
	_delay_ms(50);
	eeprom_write(eeprom_next_free_address++,date.month);
	_delay_ms(50);
	eeprom_write(eeprom_next_free_address++,date.year);
	_delay_ms(50);
	eeprom_write(eeprom_next_free_address++,time.hours);
	_delay_ms(50);
	eeprom_write(eeprom_next_free_address++,time.minutes);
	_delay_ms(50);
	eeprom_write(eeprom_next_free_address++,time.seconds);
	_delay_ms(50);
	eeprom_write(0x7FF,eeprom_next_free_address);	// save next free address at last location of eeprom 
	_delay_ms(50);
}
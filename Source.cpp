// Source: source.cpp
// Project: Wudo Employee Management System
// Created by: Sokpheng Kean
// Last update: 06/April/2020
// Version: 2.0

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>
#include <cctype>
#include <ctime>
using namespace std;

////////////////// struct //////////////////////
struct CurrentDate {
	int day {};
	int month {};
	int year {};
	int hour {};
	int minute {};
	int sec {};
};
struct Employee {
	int id {};
	string name;
	string sex;
	string position;
	float salary {};
	CurrentDate date;
	CurrentDate newDate;
};


////////////////// Function Declaration //////////////////////

// Function declaration
void welcome();													  // WELCOME PAGE		  
void login();									 				  // LOGIN
void back();													  // Back to privous page function
void swap( int i, int j, Employee employee[] ); 				  // Swap data ( bubble sort algorithm) 

///////////////////// Menu and Sub-Menu //////////////////
void mainMenu( int size, Employee employee[] );					  // Main Menu  
void displayAll( int size, Employee employee[] );				  // Display all employee lists
void sortDateMenu( int size, Employee employee[] );				  // Sort by date menu

///////////////////// Add Employee //////////////////
string validateSex( string &sex );								  // Validate Sex
string validateName( string &name );							  // Validate Name
void addEmployee( int size, Employee employee[] );				  // Add Employee		 

///////////////////// Modify Employee //////////////////
void modifyByID( int size, Employee employee[] );				  // Modify by select ID
void inModify( int size, Employee employee[] );					  // separate from modifyEmployee function
void modifyEmployee( int size, Employee employee[] );			  // Modify Employee record

///////////////////// Delete Employee //////////////////
void deleteByID( int size, Employee employee[] ); 				  // Delete Employee by ID
void deleteSuccess( int size, Employee employee[] );			  // Delete success
void deleteEmployee( int size, Employee employee[] );			  // delete employee
void confirmDelete( int size, Employee employee[] );			  // Ask to confirm delete employee
void deleteSuccess( int size, Employee employee[] );			  // After employee delete successfully
																  
///////////////////// Search //////////////////
void search( int size, Employee employee[] );					  // Search
void searchId( int size, Employee employee[] );					  // Search by ID
void searchName( int size, Employee employee[] );				  // Search by Name
void searchPosition( int size, Employee employee[] );			  // Search by Position

///////////////////// Output data //////////////////
void outputTitle();												  // output table titles
void printArray( int size, Employee employee[] );				  // Print data form array

//////////////////// Sort //////////////////
void sortId( int size, Employee employee[] );					  // Sort by ID ( smallest to biggest )
void sortName( int size, Employee employee[] ); 				  // Sort by Name ( A-Z )
void sortPosition( int size, Employee employee[] ); 			  // Sort by Position ( A-Z )
void sortSalary( int size, Employee employee[] );				  // Sort employe by salary ( highest - lowest )
void sortByHireDate( int size, Employee employee[] );			  // Sort employe by Hire date ( newest - oldest )						 /// error output sort btw SortID and SortDate
void sortByLastUpdate( int size, Employee employee[] );			  // Sort employe by Last update ( newest - oldest )
																  
//////////////////// Locatime Function //////////////////
void localtime();

////////////////// Main //////////////////////
int main() {
	// current time and date
	localtime();
	// Welcome page
	welcome();
	// Login
	login();

	// Initailize size of date in arr
	int total = 0;
	const int MAX_SIZE = 1000;
	Employee employee[ MAX_SIZE ];

	//Menu
	mainMenu( total, employee );



	return 0;
}

////////////////// Functions user defined //////////////////////

//////////////////// WELCOME //////////////////
// Current localtime 
void localtime() {
	//// current date/time based on current system
	time_t now = time( NULL );

	//cout << "Number of sec since January 1,1970:" << now << endl;

	tm* ltm = localtime( &now );

	// print various components of tm structure.
	cout << "Time: " << ltm->tm_hour << ":";
	cout << ltm->tm_min << ":";
	cout << ltm->tm_sec << endl;
	cout << "Day: " << ltm->tm_mday << endl;
	cout << "Month: " << 1 + ltm->tm_mon << endl;
	cout << "Year: " << 1900 + ltm->tm_year << endl;

}
// Welcome page
void welcome() {
	cout << "\n" << setw(70) << " Wudo Employee Management System" << endl;
	cout << setw(75) << "******************************************" << endl << endl;
	cout << setw(110) << "Application name: Wudo" << endl;
	cout << setw( 110 ) << "Version: 2.0" << endl;
	cout << setw( 110 ) << "Made by: Sokpheng Kean" << endl << endl;
	cout << setw( 100 ) << "*************************************************************************************" << endl << endl;
	cout << setw( 85 ) << "****** Welcome to Wudo Employee Management System ******" << endl << endl;
	cout << setw( 100 ) << "*************************************************************************************" << endl << endl;
}
// Login
void login() {
	string username, password;
	bool pass = true;
	int i = 1;
	do {
		cout << "\n\t\t\t\tEnter username: ";
		getline( cin, username );
		cout << "\n\t\t\t\tEnter password: ";
		getline( cin, password );
		if ( username == "admin" && password == "1234" ) {							  // username: admin | password: 1234
			pass = false;
			system( "cls" );																   // mainMenu function
		}
		else {
			if ( i == 3 ) {
				cout << "\n\t\tYou entered incorrect 3 time. The program will close automatically..." << endl;
				exit( 0 );
			}
			cout << "\n\t\t\t\tIncorrect!! Please try again..." << endl;
			i++;

		}
	} while ( pass );

}
// Swap ( bubble sort )
void swap( int i, int j, Employee employee[] ) {
	Employee swap = employee[ i ];
	employee[ i ] = employee[ j ];
	employee[ j ] = swap;
}
// Back function
void back() {
	cout << "\t\t\tPress enter to go back...";
	cin.ignore();
	cin.get();
}

//////////////////// Menu and Sub-Menu //////////////////
// Main Menu
void mainMenu( int size, Employee employee[] ) {
	do {
		system( "cls" );
		cout << "\n\t\tMAIN MENU: " << endl;
		cout << "\t\t\t1. Add New Employee" << endl;
		cout << "\t\t\t2. Modify Employee Record" << endl;
		cout << "\t\t\t3. Remove Employee" << endl;
		cout << "\t\t\t4. Search" << endl;
		cout << "\t\t\t0. Exit program" << endl;
		cout << "\t\t\tPlease select your option ( 1-4 ) or ( 0 ) to exit_ ";
		char choice;
		cin >> choice;																	  // input char
		switch ( choice ) {
		case '1':
			/*cout << "\n\t\t\t\t*** Add New Employee ***" << endl;*/
			addEmployee( size, employee );
			size++;															   // change bool value to false														   // back to mainMenu function
			break;
		case '2':
			//cout << "\n\t\t\t\t*** Modify Employee Record ***" << endl;
			modifyEmployee( size, employee );
			break;
		case '3':
			//cout << "\n\t\t\t\t*** Remove Employee ***" << endl;
			deleteEmployee( size, employee );
			size--;
			break;
		case '4':
			//cout << "\n\t\t\t\t*** Search ***" << endl;
			search( size, employee );
			break;
		case '0':
			system( "cls" );
			cout << "\n\t\t\t\t***** Goodbye! see you next time :) *****" << endl;
			exit( 0 );																	   // exit function
			break;
		default:
			cout << "\n\t\t\t\tYou entered invalid number...." << endl;
			back();
		}
	} while ( true );
	
}
// Search Menu
void search( int size, Employee employee[] ) {
	char choice;
	do {
		system( "cls" );
		cout << "\n\t\tSearch: " << endl;
		cout << "\t\t\t1. Display all" << endl;
		cout << "\t\t\t2. Search by Name" << endl;
		cout << "\t\t\t3. Search by ID" << endl;
		cout << "\t\t\t4. Search by Position" << endl;
		cout << "\t\t\t0. Back to main menu" << endl;
		cout << "\t\t\tPlease select your option ( 1-4 or 0 to go back ) ";
		cin >> choice;																	  // input char
		switch ( choice ) {
		case '1':
			//cout << "\n\t\t\t\t*** Display all ***" << endl;
			displayAll( size, employee );
			back();															   // back to mainMenu function
			break;
		case '2':
			//cout << "\n\t\t\t\t*** Search by Name ***" << endl;
			searchName( size, employee );
			back();
			break;
		case '3':
			//cout << "\n\t\t\t\t*** Search by ID ***" << endl;
			searchId( size, employee );
			back();
			break;
		case '4':
			//cout << "\n\t\t\t\t*** Search by Position ***" << endl;
			searchPosition( size, employee );
			back();
			break;
		case '0':
			mainMenu( size, employee );
			break;
		default:
			cout << "\n\t\t\t\tYou entered invalid number...." << endl;
			back();
		}
	} while ( true );

}
// Display All Employee Menu
void displayAll( int size, Employee employee[] ) {
	char choice;
	do {
		system( "cls" );
		cout << "\n\t\tDisplay All: " << endl;
		cout << "\t\t\t1. Sort by ID" << endl;
		cout << "\t\t\t2. Sort by Name" << endl;
		cout << "\t\t\t3. Sort by Position" << endl;
		cout << "\t\t\t4. Sort by Salary" << endl;
		cout << "\t\t\t5. Sort by Date" << endl;
		cout << "\t\t\t0. Back" << endl;
		cout << "\t\t\tPlease select your option ( 1-5 or 0 to go back ) ";
		cin >> choice;																	  // input char
		//system( "cls" );
		switch ( choice ) {
		case '1':
			// Sort by ID
			sortId( size, employee );
			back();
			break;
		case '2':
			//cout << "\n\t\t\t\t*** Sort by Name ***" << endl;
			sortName( size, employee );
			back();
			break;
		case '3':
			//cout << "\n\t\t\t\t*** Sort by Position ***" << endl;
			sortPosition( size, employee );
			back();
			break;
		case '4':
			//cout << "\n\t\t\t\t*** Sort by Salary ***" << endl;
			sortSalary( size, employee );
			back();
			break;
		case '5':
			//cout << "\n\t\t\t\t*** Sort by Date ***" << endl;
			sortDateMenu( size, employee );
			//back();
			break;
		case '0':
			//cout << "\n\t\t\t\t*** Back to search page ***" << endl;
			search( size, employee );
			break;
		default:
			cout << "\n\t\t\t\tYou entered invalid number...." << endl;
			back();
		}
	} while ( true );
}
// Sort by date menu
void sortDateMenu( int size, Employee employee[] ) {
	bool check = true;
	string option;
	do {
		system( "cls" );
		cout << "\n\t\tSort by Date: " << endl;
		cout << "\t\t\t1. Sort by hire date" << endl;
		cout << "\t\t\t2. Sort by last update" << endl;
		cout << "\t\t\t0. Back" << endl;
		cout << "\t\t\tOption (1-2) or (0) to go back ";
		cin >> option;
		if ( option == "1" ) {
			// sort by HIRE DATE
			sortByHireDate( size, employee );
			back();
		} 
		else if ( option == "2" ) {
			// Sort by LAST UPDATE
			sortByLastUpdate( size, employee );
			back();
		}
		else if ( option == "0" ) {
			check = false;
		}
		else {
			cout << "\t\t\tPlease enter the right option (1-2) or (0) to go back..." << endl << endl;
		}
	} while ( check );
}

/////////////////////////// Add Employee ///////////////////
// Check validate sex
string validateSex( string &sex ) {
	int i = 0;
	do {
		if ( i > 0 )
			cout << "\t\t\tEnter sex (M|F): ";
		i++;
		getline( cin, sex );
		if ( sex == "m" ) {
			sex = "M";
		}
		else if ( sex == "f" ) {
			sex = "F";
		}
	} while ( sex != "M" && sex != "F" && sex!="" );

	return sex;
}
// Check validate name
string validateName( string &name ) {
	bool check = false;
	int i = 0;
	cin.ignore();
	do {
		if ( i > 0 )
			cout << "\t\t\tEnter name : ";
		i++;
		getline( cin, name );
		//validation for name
		if ( name != "" ) {
			for ( char c : name ) {
				if ( !( isalpha( c ) || isspace( c ) ) ) {
					cout << "\t\t\tInvalid name...." << endl;
					check = true;
				}
				else
					check = false;
			}
		}
		else
			check = false;
	} while ( check );
	
	return name;
}
// Add Employee 
void addEmployee( int size, Employee employee[] ) {
	system( "cls" );

	// auto increase ID by the size value
	int id = size +1;

	string name;
	string sex;
	string position;
	float salary {};
	string date;
	bool check = true;
	do {
		cout << "\t\t\tEnter name : ";
		name = validateName( name );
		cout << "\t\t\tEnter sex (M|F): ";
		sex = validateSex( sex );
		cout << "\t\t\tEnter position: ";
		getline( cin, position );
		cout << "\t\t\tEnter salary: ";
		cin >> salary;


		time_t now = time( 0 );
		tm* ltm = localtime( &now );
		if ( name != "" && sex != "" && position != "" ) {
			check = false;
			employee[ size ].id = id;
			employee[ size ].name = name;
			employee[ size ].sex = sex;
			employee[ size ].position = position;
			employee[ size ].salary = salary;
			employee[ size ].date.day = ltm->tm_mday;
			employee[ size ].date.month = 1 + ltm->tm_mon;
			employee[ size ].date.year = 1900 + ltm->tm_year;
			employee[ size ].date.hour = ltm->tm_hour;
			employee[ size ].date.minute = ltm->tm_min;
			employee[ size ].date.sec = ltm->tm_sec;

			cout << "\n\t\t\t***** Employee added successfully. *****" << endl << endl;
			//system( "cls" );
			outputTitle();
			printArray( size, employee );
			cout << "\t ===========================================================================================================" << endl << endl;
			++size;
			// add more employee
			char add;
			cout << "\t\tDo you want to add more emplyee? (y/n) ";
			cin >> add;
			if ( add == 'y' ) {
				addEmployee( size, employee );
			}
			else {
				mainMenu( size, employee );
			}
		}
		else {
			string retry;
			cout << "\n\n\t\t\t=> Fail to create employee..." << endl;
			cout << "\t\t\t=> Name, Sex, Postion are require..." << endl << endl;
			cout << "\t\t\tDo you to try again? (y/n) ";
			cin >> retry;
			if ( retry == "y" )
				check = true;
			else
				break;
		}
	} while ( check );
	
}

/////////////////////////// Output data //////////////////
// output data titles
void outputTitle() {
	cout << "\t ===========================================================================================================" << endl;
	cout << "\t\t" << left << setw( 5 ) << "ID" << left << setw( 25 ) << "Employee Name" << left << setw( 10 ) << "Sex" << left << setw( 15 )
		<< "Position" << left << setw( 10 ) << "Salary" << left << setw( 15 ) << "Hire date" << left << setw( 15 ) << "Last update" << endl;
	cout << "\t ===========================================================================================================" << endl;
}
// Print data from array
void printArray( int size, Employee employee[] ) {
	if ( employee[ size ].id != 0 ) {
		cout << "\t\t" << left << setw( 5 ) << employee[ size ].id << left << setw( 25 ) << employee[ size ].name << left << setw( 10 ) << employee[ size ].sex << left << setw( 15 )
			<< employee[ size ].position << left << setw( 10 ) << employee[ size ].salary
			<< employee[ size ].date.day << '/' << employee[ size ].date.month << '/' << employee[ size ].date.year << "\t";
		
		// check if newDate == 0 do not display it
		if ( ( employee[ size ].newDate.day, employee[ size ].newDate.month, employee[ size ].newDate.year ) != 0 ) {
			cout << employee[ size ].newDate.day << '/' << employee[ size ].newDate.month << '/' << employee[ size ].newDate.year;
		}
		cout << endl;
	}
}

/////////////////////////// Search ////////////////////////
// Search by ID
void searchId( int size, Employee employee[] ) {
	cout << "\n\t\t\t***** Enter (0) to stop the search *****" << endl << endl;
	cout << "\t\t\tEnter employee ID: ";
	bool check = true;
	int id;
	cin >> id;
	if ( id != 0 ) {
		for ( int i = 0; i < size; i++ ) {
			if ( id == employee[ i ].id ) {
				outputTitle();
				printArray( i, employee );
				cout << "\t ===========================================================================================================" << endl << endl;
				check = false;
			}
		}
		if ( check ) {
			cout << "\n\t\t\tEmploye ID: " << id << " has not been found..." << endl;
		}
	}
}
// Search by Name
void searchName( int size, Employee employee[] ) {
	cout << "\n\t\t\tEnter name to search: ";
	size_t str;
	bool check = true;

	const int nameSize = 50;
	char name[ nameSize ];
	cin.ignore();
	cin.getline( name, nameSize );

	outputTitle();
	for ( int i = 0; i < size; i++ ) {
		str = ( employee[ i ].name ).find( name );
		if ( str != string::npos ) {
			// ( string::npos ) value for a len (or sublen) parameter in string's member functions, means "until the end of the string".
			// it is usually used to indicate no matches
			printArray( i, employee );
			check = false;
		}
	}
	cout << "\t ===========================================================================================================" << endl << endl;
	if ( check ) {
		cout << "\n\t\t\tEmployee name: " << name << " has not been found..." << endl;
	}
}
// Search By Position
void searchPosition( int size, Employee employee[] ) {
	cout << "\n\t\t\tEnter any position to search: ";
	size_t str;
	bool check = true;

	const int positionSize = 50;
	char position[ positionSize ];
	cin.ignore();
	cin.getline( position, positionSize );

	outputTitle();
	for ( int i = 0; i < size; i++ ) {
		str = ( employee[ i ].position ).find( position );
		if ( str != string::npos ) {
			// ( string::npos ) value for a len (or sublen) parameter in string's member functions, means "until the end of the string".
			// it is usually used to indicate no matches
			printArray( i, employee );
			check = false;
		}
	}
	cout << "\t ===========================================================================================================" << endl << endl;
	if ( check ) {
		cout << "\n\t\t\tThe position: "<< position <<" has not been found..." << endl;
	}
}

/////////////////////////// Sort //////////////////////////
// Sort by ID
void sortId( int size, Employee employee[] ) {
	// Sort Title
	for ( int i = 0; i < size - 1; i++ ) {
		for ( int j = i + 1; j < size; j++ ) {
			if ( employee[ i ].id > employee[ j ].id ) {
				// Swap bubble sort
				swap( i, j, employee );
			}
		}
	}
	outputTitle();
	for ( int i = 0; i < size; i++ ) {
		printArray( i, employee );
	}
	cout << "\t ===========================================================================================================" << endl << endl;
}
// Sort by name (a-z)
void sortName( int size, Employee employee[] ) {
	for ( int i = 0; i < size - 1; i++ ) {
		for ( int j = i + 1; j < size; j++ ) {
			if ( employee[ i ].name > employee[ j ].name ) {
				// Swap bubble sort
				swap( i, j, employee );
			}
		}
	}
	outputTitle();
	for ( int i = 0; i < size; i++ ) {
		printArray( i, employee );
	}
	cout << "\t ===========================================================================================================" << endl << endl;
}
// Sort by Postion (a-z)
void sortPosition( int size, Employee employee[] ) {
	for ( int i = 0; i < size - 1; i++ ) {
		for ( int j = i + 1; j < size; j++ ) {
			if ( employee[ i ].position > employee[ j ].position ) {
				// Swap bubble sort
				swap( i, j, employee );
			}
		}
	}
	outputTitle();
	for ( int i = 0; i < size; i++ ) {
		printArray( i, employee );
	}
	cout << "\t ===========================================================================================================" << endl << endl;
}
// Sort by Salary ( high - low )
void sortSalary( int size, Employee employee[] ) {
	outputTitle();
	for ( int i = 0; i < size; i++ ) {
		for ( int j = i + 1; j < size; j++ ) {
			if ( employee[ i ].salary < employee[ j ].salary ) {
				// Swap bubble sort
				swap( i, j, employee );
			}
		}
		printArray( i, employee );
	}
	cout << "\t ===========================================================================================================" << endl << endl;
}
// Sort by Hire date
void sortByHireDate( int size, Employee employee[] ) {
	bool check = false;
	for ( int i = 0; i < size - 1; i++ ) {
		for ( int j = i + 1; j < size; j++ ) {
			if ( employee[ i ].date.year < employee[ j ].date.year ) {
				swap( i, j, employee );
			}
			else if ( ( employee[ i ].date.year == employee[ j ].date.year ) && ( employee[ i ].date.month < employee[ j ].date.month ) ) {
				swap( i, j, employee );
			}
			else if ( ( employee[ i ].date.year == employee[ j ].date.year ) && ( employee[ i ].date.month == employee[ j ].date.month ) && ( employee[ i ].date.day < employee[ j ].date.day ) ) {
				swap( i, j, employee );
			}
			else if ( ( employee[ i ].date.year == employee[ j ].date.year ) && ( employee[ i ].date.month == employee[ j ].date.month ) && ( employee[ i ].date.day == employee[ j ].date.day )
				&& ( employee[i].date.hour < employee[j].date.hour ) ) {
				swap( i, j, employee );
			}
			else if ( ( employee[ i ].date.year == employee[ j ].date.year ) && ( employee[ i ].date.month == employee[ j ].date.month ) && ( employee[ i ].date.day == employee[ j ].date.day )
				&& ( employee[ i ].date.hour == employee[ j ].date.hour ) && ( employee[ i ].date.minute < employee[ j ].date.minute ) ) {
				swap( i, j, employee );
			}
			else if ( ( employee[ i ].date.year == employee[ j ].date.year ) && ( employee[ i ].date.month == employee[ j ].date.month ) && ( employee[ i ].date.day == employee[ j ].date.day )
				&& ( employee[ i ].date.hour == employee[ j ].date.hour ) && ( employee[ i ].date.minute == employee[ j ].date.minute ) && ( employee[ i ].date.sec < employee[ j ].date.sec ) ) {
				swap( i, j, employee );
			}
		}
	}
	outputTitle();
	for ( int i = 0; i < size; i++ ) {
		printArray( i, employee );
	}
	cout << "\t ===========================================================================================================" << endl << endl;
}
// Sort by last modify or LAST UPDATE
void sortByLastUpdate( int size, Employee employee[] ) {
	bool check = false;
	for ( int i = 0; i < size - 1; i++ ) {
		for ( int j = i + 1; j < size; j++ ) {
			if ( employee[ i ].newDate.year < employee[ j ].newDate.year ) {
				swap( i, j, employee );
			}
			else if ( ( employee[ i ].newDate.year == employee[ j ].newDate.year ) && ( employee[ i ].newDate.month < employee[ j ].newDate.month ) ) {
				swap( i, j, employee );
			}
			else if ( ( employee[ i ].newDate.year == employee[ j ].newDate.year ) && ( employee[ i ].newDate.month == employee[ j ].newDate.month ) && ( employee[ i ].newDate.day < employee[ j ].newDate.day ) ) {
				swap( i, j, employee );
			}
			else if ( ( employee[ i ].newDate.year == employee[ j ].newDate.year ) && ( employee[ i ].newDate.month == employee[ j ].newDate.month ) && ( employee[ i ].newDate.day == employee[ j ].newDate.day )
				&& ( employee[ i ].newDate.hour < employee[ j ].newDate.hour ) ) {
				swap( i, j, employee );
			}
			else if ( ( employee[ i ].newDate.year == employee[ j ].newDate.year ) && ( employee[ i ].newDate.month == employee[ j ].newDate.month ) && ( employee[ i ].newDate.day == employee[ j ].newDate.day )
				&& ( employee[ i ].newDate.hour == employee[ j ].newDate.hour ) && ( employee[ i ].newDate.minute < employee[ j ].newDate.minute ) ) {
				swap( i, j, employee );
			}
			else if ( ( employee[ i ].newDate.year == employee[ j ].newDate.year ) && ( employee[ i ].newDate.month == employee[ j ].newDate.month ) && ( employee[ i ].newDate.day == employee[ j ].newDate.day )
				&& ( employee[ i ].newDate.hour == employee[ j ].newDate.hour ) && ( employee[ i ].newDate.minute == employee[ j ].newDate.minute ) && ( employee[ i ].newDate.sec < employee[ j ].newDate.sec ) ) {
				swap( i, j, employee );
			}
		}
	}
	outputTitle();
	for ( int i = 0; i < size; i++ ) {
		printArray( i, employee );
	}
	cout << "\t ===========================================================================================================" << endl << endl;
}

//////////////////////// Modify Employee //////////////////
// separate from modifyEmployee function
void modifyByID( int size, Employee employee[] ) {
	bool isTrue = true;
	int searchId;
	cout << "\n\t\t\tEnter employee ID: ";
	cin >> searchId;
	// Modify data in arr search by ID
	for ( int i = 0; i < size; i++ ) {
		if ( employee[ i ].id == searchId ) {
			outputTitle();
			printArray( i, employee );
			cout << "\t ===========================================================================================================" << endl << endl;
			isTrue = false;
			inModify( i, employee );								  // From inModify function
		}
	}
	if ( isTrue ) {
		cout << "\n\t\t\tEmploye ID: " << searchId << " has not been found..." << endl;
		back();
	}
}
void inModify( int size, Employee employee[] ) {
	/*outputTitle();
	printArray( size, employee );
	cout << "\t ===========================================================================================================" << endl << endl;*/
	cout << "\t\t\tAre you sure to modify this employee? (y/n) ";
	char choice;
	cin >> choice;
	if ( choice == 'y' ) {
		cout << "\n\n\t\t\t***** Note: Press (Enter) to skip | (0) to skip on salary field *****" << endl << endl;
		string name;
		string sex;
		string position;
		float salary {};
		string date;

		// Name
		cout << "\t\tName: " << left << setw( 20 ) << employee[ size ].name;
		cout << "\t\t\tNew name: ";
		name = validateName( name );
		// Sex
		cout << "\t\tSex: " << left << setw( 21 ) << employee[ size ].sex;
		cout << "\t\t\tNew sex: ";
		sex = validateSex( sex );
		// Position
		cout << "\t\tPosition: " << left << setw( 17 ) << employee[ size ].position;
		cout << "\t\t\tNew position: ";
		getline( cin, position );
		// Salary
		cout << "\t\tSalary: " << left << setw( 20 ) << employee[ size ].salary;
		cout << "\t\t\tNew salary: ";
		cin >> salary;

		// current date and time
		time_t now = time( 0 );
		tm* ltm = localtime( &now );

		// import new data to arr
		if ( name != "" ) {
			employee[ size ].name = name;
		}
		if ( sex != "" ) {
			employee[ size ].sex = sex;
		}
		if ( position != "" ) {
			employee[ size ].position = position;
		}
		if ( salary != 0 ) {
			employee[ size ].salary = salary;
		}
		if ( name != "" || sex != "" || position != "" || salary != 0 ) {
			// last update date
			employee[ size ].newDate.day = ltm->tm_mday;
			employee[ size ].newDate.month = 1+ ltm->tm_mon;
			employee[ size ].newDate.year = 1900 + ltm->tm_year;
			employee[ size ].newDate.hour = ltm->tm_hour;
			employee[ size ].newDate.minute = ltm->tm_min;
			employee[ size ].newDate.sec = ltm->tm_sec;

			// output new modified
			outputTitle();
			printArray( size, employee );
			cout << "\t ===========================================================================================================" << endl << endl;
			// Feedback
			cout << "\t\t\t\t***** Employee modify successfully *****" << endl << endl;
			back();
		}
		else {
			cout << "\n\n\t\t\t***** Employee has not been update ******" << endl;
			back();
		}
	}
}
// Modify Employee
void modifyEmployee( int size, Employee employee[] ) {
	string option;
	int count = 0;
	string searchName;
	// check options
	bool isTrue;
	do {
		system( "cls" );
		isTrue = true;
		cout << "\t\tModify Employee Record" << endl;
		cout << "\t\t\t1. Search by ID" << endl;
		cout << "\t\t\t2. Search by Name" << endl;
		cout << "\t\t\t0. Back" << endl;
		cout << "\t\t\tOption (1-2) or (0) to go back: ";
		cin >> option;
		if ( option == "1" ) {
			modifyByID( size, employee );
			//isTrue = false;
		}
		else if ( option == "2" ) {
			cout << "\t\t\tEnter employee Name: ";
			int count = 0;
			int getI;
			size_t str;
			const int nameSize = 50;
			char name[ nameSize ];
			cin.ignore();
			cin.getline( name, nameSize );
			// output data
			outputTitle();
			for ( int i = 0; i < size; i++ ) {
				str = ( employee[ i ].name ).find( name );
				if ( str != string::npos ) {
					printArray( i, employee );
					getI = i;
					count++;
				}
			}
			cout << "\t ===========================================================================================================" << endl << endl;
			// check the condition
			if ( count == 1 ) {
				// From inModify function
				inModify( getI, employee );								  
				//isTrue = false;
			}
			// check if have doublicate name let user choose the ID to confirm
			else if( count > 1 ) {
				// From modifyByID function
				modifyByID( size, employee );
				//isTrue = false;
			}
			else {
				cout << "\n\t\t\tEmploye name: " << name << " has not been found..." << endl;
				back();
			}
		}
		else if ( option == "0" ) {
			isTrue = false;
		}
		else {
			cout << "\n\t\t\tInvalid. Please try again." << endl;
		}
	} while ( isTrue );

}

//////////////////////// Delete Employee //////////////////
// Delete employee success 
void deleteSuccess( int size, Employee employee[] ) {
	cout << "\n\n\t\t\t***** Employee remove successfully *****" << endl << endl;
	cout << "\t\t\tDo you want to remove more employee? (y/n) ";
	char choice;
	cin >> choice;
	if ( choice == 'y' )
		deleteEmployee( size, employee );
	else {
		mainMenu( size, employee );
	}
}
// Separate from delete employee function
void inDeleteEmployee( int size, Employee employee[] ) {													 //error wrong delete employee
	employee[ size ].position = "";
	employee[ size ].salary = 0;
	employee[ size ].date.day = 0;
	employee[ size ].date.month = 0;
	employee[ size ].date.year = 0;
	employee[ size ].newDate.day = 0;
	employee[ size ].newDate.month = 0;
	employee[ size ].newDate.year = 0;
	employee[ size ].date.hour = 0;
	employee[ size ].date.minute = 0;
	employee[ size ].date.sec = 0;	employee[ size ].id = 0;
	employee[ size ].name = "";
	employee[ size ].sex = "";

}
//confirm delete employee
void confirmDelete( int size, Employee employee[] ) {
	outputTitle();
	printArray( size, employee );
	cout << "\t ===========================================================================================================" << endl;
	cout << "\n\t\t\tEmployee ID: " << employee[ size ].id << ". Are you sure to remove this employee? (y/n) ";
}
// Delete By ID function
void deleteByID( int size, Employee employee[] ) {
	int searchId {};
	bool checkId = false;
	cout << "\n\t\t\tEnter employee ID: ";
	cin >> searchId;
	if ( searchId == 0 ) {
		cout << "\n\t\t\tEmploye ID: " << searchId << " has not been found..." << endl;

		back();
	}
	else {
		for ( int i = 0; i < size; i++ ) {
			if ( searchId == employee[ i ].id ) {
				//confirm delete
				confirmDelete( i, employee );
				char option;
				cin >> option;
				if ( option == 'y' ) {
					for ( int j = i; j < size; j++ ) {
						employee[ j ].id = employee[ j + 1 ].id;
						employee[ j ].name = employee[ j + 1 ].name;
						employee[ j ].sex = employee[ j + 1 ].sex;
						employee[ j ].position = employee[ j + 1 ].position;
						employee[ j ].salary = employee[ j + 1 ].salary;
						employee[ j ].date = employee[ j + 1 ].date;
						employee[ j ].newDate = employee[ j + 1 ].newDate;

					}
					inDeleteEmployee( size, employee );
					deleteSuccess( size, employee );
					checkId = true;
					break;
				}
				else {
					mainMenu( size, employee );
				}
			}
		}
		if ( checkId ) {
			cout << "\n\t\t\tEmploye ID: " << searchId << " has not been found..." << endl;
			back();
		}
	}
}
// Delete employee
void deleteEmployee( int size, Employee employee[] ) {
	string option;
	string searchName;
	// check options
	bool isTrue = true;
	do {
		system( "cls" );
		cout << "\t\tRemove Employee" << endl;
		cout << "\t\t\t1. Search by ID" << endl;
		cout << "\t\t\t2. Search by Name" << endl;
		cout << "\t\t\t0. Back" << endl;
		cout << "\t\t\tOption (1-2), Enter (0) to go back ";

		cin >> option;
		if ( option == "1" ) {
			// delete By ID function
			deleteByID( size, employee );
		}
		else if ( option == "2" ) {
			cout << "\n\t\t\tEnter employee Name: ";
			int count = 0;
			int getI;
			size_t str;
			const int nameSize = 50;
			char name[ nameSize ];
			cin.ignore();
			cin.getline( name, nameSize );
			// output data
			outputTitle();
			for ( int i = 0; i < size; i++ ) {
				str = ( employee[ i ].name ).find( name );
				if ( str != string::npos ) {
					printArray( i, employee );
					getI = i;
					count++;
				}
			}
			cout << "\t ===========================================================================================================" << endl << endl;
			if ( count == 1 ) {
				//confirm delete
				cout << "\n\t\t\tEmployee ID: " << employee[ getI ].id << ". Are you sure to remove this employee? (y/n) ";
				char option;
				cin >> option;
				if ( option == 'y' ) {
					for ( int j = getI; j < size; j++ ) {
						employee[ j ].id = employee[ j + 1 ].id;
						employee[ j ].name = employee[ j + 1 ].name;
						employee[ j ].sex = employee[ j + 1 ].sex;
						employee[ j ].position = employee[ j + 1 ].position;
						employee[ j ].salary = employee[ j + 1 ].salary;
						employee[ j ].date = employee[ j + 1 ].date;
						employee[ j ].newDate = employee[ j + 1 ].newDate;
					}
					size--;
					inDeleteEmployee( size, employee );
					deleteSuccess( size, employee );
					break;
				}
				else {
					mainMenu( size, employee );
				}			
			}
			else if ( count > 1 ) {
				// delete By ID function
				deleteByID( size, employee );
			}
			else {
				cout << "\n\t\t\tEmploye name: " << name << " has not been found..." << endl;
				back();
			}
		}
		else if ( option == "0" ) {
			isTrue = false;
		}
		else {
			cout << "\n\t\t\tInvalid. Please try again." << endl;
			back();
		}
	} while ( isTrue );
}										

//////////////////////// TEST FUNCTIONS /////////////////////
// Sort-bubble
void bubbleSort( int arr[], int size ) {
	for ( int i = 0; i < size; i++ ) {
		for ( int j = i + 1; j < size; j++ ) {
			if ( arr[ i ] > arr[ j ] ) {
				int swap = arr[ i ];
				arr[ i ] = arr[ j ];
				arr[ j ] = swap;
			}
		}
	}
}
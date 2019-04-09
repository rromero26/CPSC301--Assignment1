#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
using namespace std;


struct  PERSON {
    char  Name[20];
    float Balance;
};

//------------------------------------------------------------------------------
int countRecords(int numOfCustomers){
    string line;
    fstream myFile;                      //open file
    myFile.open("data.txt");
    if(!myFile){                          //check if file open properly
        cout<< "Unable to open file.";
        exit(1);
    }
    while(getline(myFile, line)){       //counts num of records
      numOfCustomers++;
    }

    return numOfCustomers;
    myFile.close();
  }
//------------------------------------------------------------------------------

PERSON * readData(int numOfCustomers){
  PERSON * tempArrayPtr;                 //create array that will be return
  tempArrayPtr = new PERSON[numOfCustomers];

  string firstName;
  string lastName;
  string fullName;
  char fullCharName [20];
  int counter = 0;

  fstream tempFile;                       //open txt file
  tempFile.open("data.txt");
  if(!tempFile){                          //check if file open properly
      exit(1);
  }

  while(counter < numOfCustomers){
    tempFile >> firstName;                   //gets first name
    tempFile >> lastName;                   //gets last name
    firstName = firstName.substr(0, 9);
    lastName = lastName.substr(0, 10);

    fullName = firstName + ' ' + lastName;     //save full name from file
    strcpy(tempArrayPtr[counter].Name, fullName.c_str());

    tempFile >> tempArrayPtr[counter].Balance;  //Blance is save into dynamic array
    counter ++;
  }

  tempFile.close();                        // close file
  return tempArrayPtr;                     // returns the pointer created
}
//------------------------------------------------------------------------------

void display(PERSON myArray[], int numOfCustomers){
  int counter2 = 0;
  cout << "Name                Balance" << endl;
  cout << "---------------------------------------------" << endl;
  while (counter2 < numOfCustomers){
    cout << myArray[counter2].Name << "   ";
    printf( "%.2f",myArray[counter2].Balance);
    cout << endl;
    counter2++;
  }
}
//------------------------------------------------------------------------------

void FindRichest(PERSON myArray[], int numOfCustomers){
  float highestBalance = 0;
  int temp = 0;

  for(int i = 0; i < numOfCustomers; i++){
    if (myArray[i].Balance > highestBalance){
      highestBalance = myArray[i].Balance;
      temp = i;
    }
  }
  cout << "The customer with the Highest balance is: " << myArray[temp].Name;
}

void Deposit(PERSON myArray[], int numOfCustomers, string userName, float userDeposit){
  int temp = 0;
  for(int x = 0; x < numOfCustomers; x++) {
      if(userName == myArray[x].Name){
        temp = x + 1;                    // Note: next comment will explain the +1
      }
  }
        //Name is not found in 'myArray', temp = 0. BUT Maria Brown index is 0
        //This causes an error so we add 1 whenever a name is found in myArray and later
        //subtract 1 after the 'myArray' check.

  if (temp == 0){
    cout << "ERROR: name not found in records." << endl;
    return;
  }

  temp = temp - 1;                       // here the -1 mention from previous comment
  myArray[temp].Balance = myArray[temp].Balance + userDeposit;
  cout << "Your new balance is: ";     //<< myArray[temp].Balance;
  printf( "%.2f",myArray[temp].Balance);
  cout << endl;
}

void newCopy(PERSON myArray[], int numOfCustomers){
  ofstream theFile;
  theFile.open("data.txt");

  for (int z = 0; z < numOfCustomers; z++){
    theFile << myArray[z].Name << " " << myArray[z].Balance << endl;
  }
  theFile.close();
}
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

int main(){
  int numOfCustomers = 0;
  numOfCustomers = countRecords(numOfCustomers);         //get num of customer in txt file
  cout << "Running Program: Welcome" << endl;

  PERSON *myArrayPtr;                                    //create dynamic array
  myArrayPtr = readData(numOfCustomers);                 //points to dynamic array

  if (myArrayPtr == nullptr)                             //check if dynamic array remain empty
    {cout << "Error: memory could not be allocated";}

//MENU HERE --------------------------------------------------------------------------

  int userInput = 0;
  cout << "File successfully read" << endl;    //did not exit during readData, so successful

  while (userInput != 4){
    cout << "----------------------------------------------------------" << endl;
    cout << "What would you like to do?" << endl;
    cout << "1) Display all account balances." << endl;
    cout << "2) Display information of account with highest balance." << endl;
    cout << "3) Deposit money to an account" << endl;
    cout << "4) Close program (will also update any changes to file)" << endl;
    cout << "----------------------------------------------------------" << endl << endl;
    cin >> userInput;
    cin.ignore();

    if(userInput == 1){
      cout << endl;
      display(myArrayPtr, numOfCustomers);
      cout << endl << endl;
    }

    if(userInput == 2){
      cout << endl;
      FindRichest(myArrayPtr, numOfCustomers);
      cout << endl << endl;
    }

    if(userInput == 3){
      string userName;
      string tempFname;
      string tempLname;
      cout << "Enter your full name to deposit: " << endl;
      cin >> tempFname;
      cin >> tempLname;
      userName = tempFname + " " + tempLname;
      cout << endl;


      float userDeposit = 0.0;
      cout << userName << ", how much would you like to deposit? ";
      cin >> userDeposit;
      Deposit(myArrayPtr, numOfCustomers, userName, userDeposit);
      cout << endl << endl;
    }

    if(userInput == 4){
      cout << endl;
      cout << "Updating text file..." << endl << endl;
      newCopy(myArrayPtr, numOfCustomers);

      cout << "Closing program: Thank You" << endl;
    }
  }

return 0;
}

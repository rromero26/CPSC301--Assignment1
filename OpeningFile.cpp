#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
using namespace std;


struct  PERSON {
    char  Name[20];
    float Balance;
};
//--------------------------------------------------------------------------------------------------

void countRecords(int numOfCustomers){
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
    myFile.close();
  }
//--------------------------------------------------------------------------------------------------

void readingData(PERSON myArray[], int numOfCustomers){
  char aNames[20];
  string myStr1;
  string myStr2;
  string fullName;
  int counter = 0;
  fstream myFile;
  myFile.open("data.txt");
  if(!myFile) {                          //check if file open properly
      exit(1);
  }

  while(counter < numOfCustomers) {
    myFile >> myStr1;
    myFile >> myStr2;
    fullName = myStr1 + " " + myStr2;
    strcpy(aNames, fullName.c_str());
    myArray[counter].Name = aNames;
    counter ++;
  }
  myFile.close();
}
//----------------------------------------------------------------------------------------------------

void display(PERSON myArray[], int numOfCustomers){
  int counter2 = 0;
  cout << "Name                Balance" << endl;
  cout << "---------------------------------------------" << endl;
  while (counter2 < numOfCustomers){
    cout << myArray[counter2].Name << "   " << myArray[counter2].Balance << endl;
    counter2++;
  }
  cout << endl;
}
//----------------------------------------------------------------------------------------------------

void FindRichest(PERSON myArray[], int numOfCustomers){
  float highestBalance = 0.0;
  int temp = 0;

  for(int i = 0; i < numOfCustomers; i++){
    if (myArray[i].Balance > highestBalance){
      highestBalance = myArray[i].Balance;
      temp = i;
    }
  }
  cout << "The customer with the Highest balance is: " << myArray[temp].Name;
}
//-----------------------------------------------------------------------------------------------------

void deposit(string userName,PERSON myArray[], int numOfCustomers){
  int temp = 0;
  for(int x = 0; x < numOfCustomers; x++) {
      if(myArray[x].Name == userName){
        temp = x;
      }
  }
  float userDeposit = 0.0;
  cout << userName << " , how much would you like to deposit? ";
  cin >> userDeposit;

  myArray[temp].Balance = myArray[temp].Balance + userDeposit;
  cout << "Your new balance is: " << myArray[temp].Balance;

}
//---------------------------------------------------------------------------------------------

void newCopy(PERSON myArray[], int numOfCustomers){
  fstream theFile;
  theFile.open("data.txt");

  for(int z = 0; z < numOfCustomers; z++){
    theFile << myArray[z].Name << " " << myArray[z].Balance << endl;
  }
  theFile.close();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------

int main() {
  int numOfCustomers = 0;

  countRecords(numOfCustomers);
  PERSON myArray[numOfCustomers];

  readingData(myArray, numOfCustomers);

  display(myArray, numOfCustomers);

  FindRichest(myArray, numOfCustomers);

  string userName;
  cout << "Enter your full name to deposit money: ";
  cin >> userName;
  deposit(userName, myArray, numOfCustomers);

  newCopy(myArray, numOfCustomers);
  return 0;
}

#include<iostream>
#include<cmath>
#include<fstream>
using namespace std;
void Input(int &terms, int deg[], int coef[]);
void FileInput(int& terms, int deg[], int coef[]);
int Solve(int terms, int deg[], int coef[], int variable);
void Add(int aterms, int adeg[], int acoef[],int bterms, int bdeg[], int bcoef[],int rterms, int rdeg[], int rcoef[]);
void Multiply(int aterms, int adeg[], int acoef[], int bterms, int bdeg[], int bcoef[], int rterms, int rdeg[], int rcoef[]);
void Subtract(int aterms, int adeg[], int acoef[], int bterms, int bdeg[], int bcoef[], int rterms, int rdeg[], int rcoef[]);
bool Equal(int aterms, int adeg[], int acoef[],int bterms, int bdeg[], int bcoef[]);
void Print(int terms, int deg[], int coef[]);
void Menu(int aterms, int adeg[], int acoef[], int bterms, int bdeg[], int bcoef[], int rterms, int rdeg[], int rcoef[]);
int main()
{
	int aterms=0;
	int bterms=0;
	int rterms=0;
	int adeg[16] = { 0 };   //since the maximum degree can be 15 the user can enter a polynomial of 16 terms if he enters consecitive degrees from 15 to 0
	int acoef[16] = { 0 };
	int bdeg[16] = { 0 };
	int bcoef[16] = { 0 };
	int rdeg[256] = { 0 };  //i have kept the size of resultant array 256 because if the user enters two polynomials of 16 terms and multiplies tehm we will need an 16x16=256 sized to array to store the data
	int rcoef[256] = { 0 };

    Menu(aterms, adeg, acoef, bterms, bdeg, bcoef, rterms, rdeg, rcoef);// menu is the function which will be responsible for showing the menu and intelligently utillzing all the other functions 
}
void Input(int &terms, int deg[], int coef[])
{
	cout << "enter the number of terms: ";
	cin >> terms;
	for (int i = 0; i < terms; i++)
	{
		cout << "enter the coefficient: ";
		cin >> coef[i];
		cout << "enter the degree: ";
		cin >> deg[i];		
		cout << endl;
	}
	
    // following code will sort the data in such a way that the degree is in descending order
    int i = 0,container_deg,container_coef;
	while (i < terms)
	{
		int max = i;
		int j = i + 1;
		for (; j < terms; j++)
		{
			if (deg[max] < deg[j])
				max = j;
		}
		
		container_deg = deg[i];
		container_coef = coef[i];
		deg[i] = deg[max];
		coef[i] = coef[max];
		deg[max] = container_deg;
		coef[max] = container_coef;
		i++;
		j++;
	}
	
	
	 //following code will check the polynomial for duplicate degrees and if duplicates are found it will merge them and set the duplicate terms to zero
	for (int i = 0; i < terms; i++)
	{
		int k = i+1;
		while (k < terms - 1)
		{
			if (deg[i] == deg[k])
			{
				coef[i] = coef[i] + coef[k];
				deg[k] = 0;
				coef[k] = 0;
			}
			k++;
		}
	}

}
int Solve(int terms, int deg[], int coef[], int variable)
{
	int sum = 0;
	for (int i = 0; i < terms; i++)
	{
		sum = sum + (coef[i] * (pow(variable, deg[i])));
	}
	return sum;
}
void Add(int aterms, int adeg[], int acoef[], int bterms, int bdeg[], int bcoef[], int rterms, int rdeg[], int rcoef[])
{
	
	rterms = aterms + bterms;
	int i = 0,ai=0,bi=0;
	while (i < rterms && ai<16 && bi<16)
	{
		if ( acoef[ai] == 0) // now as written in the input function if a duplicate is found it will merge them and set one of them to zero these two if conditions essentially checks that if the coef is zero skip to the next term
			ai++;
		if ( bcoef[bi] == 0)
			bi++;
	    if (adeg[ai] == bdeg[bi])
		{
			rdeg[i] = adeg[ai];
			rcoef[i] = acoef[ai] + bcoef[bi];
			ai++;
			bi++;
			i++;
		}
		else
		{
			if (adeg[ai] > bdeg[bi])
			{
				rdeg[i] = adeg[ai];
				rcoef[i] = acoef[ai];
				i++;
				ai++;
			}
			else
			{
				rdeg[i] = bdeg[bi];
				rcoef[i] = bcoef[bi];
				i++;
				bi++;
			}
		}
	}
		

	
	Print(rterms, rdeg, rcoef);
}
void Multiply(int aterms, int adeg[], int acoef[], int bterms, int bdeg[], int bcoef[], int rterms, int rdeg[], int rcoef[])
{
	rterms = aterms * bterms;

	int ai = 0,i=0;
	// folowing code will multiply each term of 1st polynomial with all terms of second polynomial
	while(i<rterms)
	{
		int bi = 0;
		if ( acoef[ai] == 0)
			ai++;
		if ( bcoef[bi] == 0)
			bi++;

		while (bi < bterms)
		{
			rdeg[i] = adeg[ai] + bdeg[bi];
			rcoef[i] = acoef[ai] * bcoef[bi];
			bi++;
			i++;
		}
		ai++;

	}
	//following code will sort all the terms
	int I = 0, container_deg, container_coef;
	while (I < rterms)
	{
		int max = I;
		int j = I + 1;
		for (; j < rterms; j++)
		{
			if (rdeg[max] < rdeg[j])
				max = j;
		}

		container_deg = rdeg[I];
		container_coef = rcoef[I];
		rdeg[I] = rdeg[max];
		rcoef[I] = rcoef[max];
		rdeg[max] = container_deg;
		rcoef[max] = container_coef;
		I++;
		j++;
	}
	//following code will handle the duplicates similar to the input function
	for (int i = 0; i < rterms; i++)
	{
		int k = i + 1;
		while (k < rterms - 1)
		{
			if (rdeg[i] == rdeg[k])
			{
				rcoef[i] = rcoef[i] + rcoef[k];
				rdeg[k] = 0;
				rcoef[k] = 0;
			}
			k++;
		}
	}
	cout << ai<<endl;
	Print(rterms, rdeg, rcoef);
	


}
void FileInput(int& terms, int deg[], int coef[])
{
	ifstream fin;
	fin.open("polynomial.txt");
	if (!fin)
		cout << "error: failed to open the file";
	else
	{
		fin >> terms;
		for (int i = 0; i < terms; i++)
			fin >> coef[i];
		for (int i = 0; i < terms; i++)
			fin >> deg[i];
		//following code will sort the terms
		int i = 0, container_deg, container_coef;
		while (i < terms)
		{
			int max = i;
			int j = i + 1;
			for (; j < terms; j++)
			{
				if (deg[max] < deg[j])
					max = j;
			}

			container_deg = deg[i];
			container_coef = coef[i];
			deg[i] = deg[max];
			coef[i] = coef[max];
			deg[max] = container_deg;
			coef[max] = container_coef;
			i++;
			j++;
		}


		//following code will handle duplicates
		for (int i = 0; i < terms; i++)
		{
			int k = i + 1;
			while (k < terms - 1)
			{
				if (deg[i] == deg[k])
				{
					coef[i] = coef[i] + coef[k];
					deg[k] = 0;
					coef[k] = 0;
				}
				k++;
			}
		}
	}
	

}
void Subtract(int aterms, int adeg[], int acoef[], int bterms, int bdeg[], int bcoef[], int rterms, int rdeg[], int rcoef[])
{
	
	rterms = aterms + bterms;
	int i = 0, ai = 0, bi = 0;
	while (i < rterms && ai < 16 && bi < 16)
	{
		if ( acoef[ai] == 0)
			ai++;
		if (bcoef[bi] == 0)
			bi++;
		if (adeg[ai] == bdeg[bi])
		{
			rdeg[i] = adeg[ai];
			rcoef[i] = acoef[ai] - bcoef[bi];
			ai++;
			bi++;
			i++;
		}
		else
		{
			if (adeg[ai] > bdeg[bi])
			{
				rdeg[i] = adeg[ai];
				rcoef[i] = acoef[ai];
				i++;
				ai++;
			}
			else
			{
				rdeg[i] = bdeg[bi];
				rcoef[i] = -1 * bcoef[bi];
				i++;
				bi++;
			}
		}
	}

	Print(rterms, rdeg, rcoef);
	if (rcoef[0] == 0)  //in case if both polynomials are equal the answer will be zero, we will only need to check the value of first index to determine that
		cout << 0 << endl;
}
bool Equal(int aterms, int adeg[], int acoef[], int bterms, int bdeg[], int bcoef[])
{
	
	for (int ai = 0,bi=0; ai < aterms; ai++)
	{
		if (acoef[ai] == 0)
			ai++;
		if (bcoef[bi] == 0)
			bi++;
		if (adeg[ai] != bdeg[bi] || acoef[ai] != bcoef[bi])
			return false;
		bi++;
	}
	return true;

}
void Print(int terms, int deg[], int coef[])
{  // if coef is zero the term will not be printed,if degree is one only 'x' is diplayed,if degree is zero only coef is diplayed 
	for (int i = 0; i < terms; i++)
	{
		
		if (coef[i] != 0)
		{

			if (deg[i] == 1 && i > 0)
				cout << showpos << coef[i] << "x" << noshowpos;
			else if (deg[i] == 1)
				cout << coef[i] << "x";
			else if (deg[i] == 0 && i > 0)
				cout << showpos << coef[i] << noshowpos;
			else if (deg[i] == 0)
				cout << coef[i];
			else if (i == 0)
				cout << coef[i] << "x^" << deg[i];
			else
				cout << showpos << coef[i] << "x^" << noshowpos << deg[i];
		}
		
			
	}
	cout << endl;
}
void Menu(int aterms,int adeg[] ,int acoef[],int bterms,int bdeg[],int bcoef[],int rterms,int rdeg[],int rcoef[] )
{
	int choice=10;
	//this function kind of replicates a drop down menu system if user have entered only a single polynomial then only limited options will be displayed 
	while (choice != 0)
	{
		if (aterms == 0 && bterms == 0)
		{
			cout << "0. Exit the program" << endl;
			cout << "1. Enter a single polynomial" << endl;
			cout << "2. Enter two polynomials" << endl;
			cin >> choice;
			if (choice == 1)
			{
				int input_choice;
				cout << "Choose an input method:" << endl;
				cout << "1. Through command line" << endl;
				cout << "2. Through file(polynomial.txt)" << endl;
				cin >> input_choice;
				if (input_choice == 1)
					Input(aterms, adeg, acoef);
				else if (input_choice == 2)
					FileInput(aterms, adeg, acoef);
				else
				{
					cout << "----------------------------------" << endl;
					cout << "invalid operation" << endl;
					cout << "----------------------------------" << endl;
				}
					
			}
			else if (choice == 2)
			{
				int input_choice;
				cout << "Choose an input method for first polynomial:" << endl;
				cout << "1. Through command line" << endl;
				cout << "2. Through file(polynomial.txt)" << endl;
				cin >> input_choice;
				if (input_choice == 1)
					Input(aterms, adeg, acoef);
				else if (input_choice == 2)
					FileInput(aterms, adeg, acoef);
				else
				{
					cout << "----------------------------------" << endl;
					cout << "invalid operation" << endl;
					cout << "----------------------------------" << endl;
				}
				if (aterms > 0)
				{
					cout << "Choose an input method for second polynomial:" << endl;
					cout << "1. Through command line" << endl;
					cout << "2. Through file(polynomial.txt)" << endl;
					cin >> input_choice;
					if (input_choice == 1)
						Input(bterms, bdeg, bcoef);
					else if (input_choice == 2)
						FileInput(bterms, bdeg, bcoef);
					else
					{
						cout << "----------------------------------" << endl;
						cout << "invalid operation" << endl;
						cout << "----------------------------------" << endl;
					}
				}

			}
			else if (choice != 0)
			{
				cout << "----------------------------------" << endl;
				cout << "invalid operation" << endl;
				cout << "----------------------------------" << endl;
			}
		}
		else if (aterms > 0 && bterms == 0)
		{
			cout << "0. Exit the program" << endl;
			cout << "2. Enter a second polynomial" << endl;
			cout << "3. Print the first polynomial" << endl;
			cout << "4. Solve the polynomial for a number" << endl;
			cin >> choice;
			if (choice == 2)
			{
				int input_choice;
				cout << "Choose an input method for second polynomial:" << endl;
				cout << "1. Through command line" << endl;
				cout << "2. Through file(polynomial.txt)" << endl;
				cin >> input_choice;
				if (input_choice == 1)
					Input(bterms, bdeg, bcoef);
				else if (input_choice == 2)
					FileInput(bterms, bdeg, bcoef);
				else
					cout << "invalid operation";
			}
			else if (choice == 3)
			{
				cout << "----------------------------------" << endl;
				Print(aterms, adeg, acoef);
				cout << "----------------------------------" << endl;
			}
				
			else if (choice == 4)
			{
				int variable;
				cout << "enter a value for which you want to solve the polynomial:";
				cin >> variable;
				cout << "----------------------------------" << endl;
				cout << "Answer= " << Solve(aterms, adeg, acoef, variable)<<endl;
				cout << "----------------------------------" << endl;
			}
			else if (choice != 0)
			{
				cout << "----------------------------------" << endl;
				cout << "invalid operation" << endl;
				cout << "----------------------------------" << endl;
			}
				
		}
		else if (aterms > 0 && bterms > 0)
		{
			cout << "0. Exit the program" << endl;
			cout << "1. Enter a new first polynomial" << endl;
			cout << "2. Enter two new polynomials" << endl;
			cout << "3. Print polynomials" << endl;
			cout << "4. Solve any of the polynomials for a number" << endl;
			cout << "5. Add both polynomials" << endl;
			cout << "6. Subtract second polynomial from first" << endl;
			cout << "7. Subtract first polynomail from second" << endl;
			cout << "8. MUltiply both polynomials" << endl;
			cout << "9. Check wheteher both polynomial are equal or not" << endl;
			cin >> choice;
			if (choice == 1)
			{
				int input_choice;
				cout << "Choose an input method:" << endl;
				cout << "1. Through command line" << endl;
				cout << "2. Through file(polynomial.txt)" << endl;
				cin >> input_choice;
				if (input_choice == 1)
					Input(aterms, adeg, acoef);
				else if (input_choice == 2)
					FileInput(aterms, adeg, acoef);
				else
				{
					cout << "----------------------------------" << endl;
					cout << "invalid operation" << endl;
					cout << "----------------------------------" << endl;
				}

					
			}
			else if (choice == 2)
			{
				int input_choice;
				cout << "Choose an input method for first polynomial:" << endl;
				cout << "1. Through command line" << endl;
				cout << "2. Through file(polynomial.txt)" << endl;
				cin >> input_choice;
				if (input_choice == 1)
					Input(aterms, adeg, acoef);
				else if (input_choice == 2)
					FileInput(aterms, adeg, acoef);
				else
				{
					cout << "----------------------------------" << endl;
					cout << "invalid operation" << endl;
					cout << "----------------------------------" << endl;

				}
				if (aterms > 0)
				{
					cout << "Choose an input method for second polynomial:" << endl;
					cout << "1. Through command line" << endl;
					cout << "2. Through file(polynomial.txt)" << endl;
					cin >> input_choice;
					if (input_choice == 1)
						Input(bterms, bdeg, bcoef);
					else if (input_choice == 2)
						FileInput(bterms, bdeg, bcoef);
					else
					{
						cout << "----------------------------------" << endl;
						cout << "invalid operation" << endl;
						cout << "----------------------------------" << endl;
					}
						
				}

			}
			else if (choice == 3)
			{
				int input_choice;
				cout << "Which polynomial you want to print:" << endl;
				cout << "1. First Polynomial" << endl;
				cout << "2. Second Polynomial" << endl;
				cout << "3. Both" << endl;
				cin >> input_choice;
				if (input_choice == 1)
				{
					cout << "----------------------------------" << endl;
					Print(aterms, adeg, acoef);
					cout << "----------------------------------" << endl;
				}
					
				else if (input_choice == 2)
				{
					cout << "----------------------------------" << endl;
					Print(bterms, bdeg, bcoef);
					cout << "----------------------------------" << endl;
				}
					
				else if (input_choice == 3)
				{
					cout << "----------------------------------" << endl;
					Print(aterms, adeg, acoef);
					Print(bterms, bdeg, bcoef);
					cout << "----------------------------------" << endl;
				}
				else
				{
					cout << "----------------------------------" << endl;
					cout << "invalid operation" << endl;
					cout << "----------------------------------" << endl;
				}
					

			}
			else if (choice == 4)
			{
				int input_choice;
				int variable;
				cout << "For which polynomial you want to solve:" << endl;
				cout << "1. First polynomial" << endl;
				cout << "2. Second polynomial" << endl;
				cin >> input_choice;
				cout << "Enter the value for which you want to sovle for: ";
				cin >> variable;
				if (input_choice == 1)
				{
					cout << "----------------------------------" << endl;
					cout << Solve(aterms, adeg, acoef, variable) << endl;
					cout << "----------------------------------" << endl;
				}
					
				else if (input_choice == 2)
				{
					cout << "----------------------------------" << endl;
					cout << Solve(bterms, bdeg, bcoef, variable) << endl;
					cout << "----------------------------------" << endl;
				}
					
				else
				{
					cout << "----------------------------------" << endl;
					cout << "invalid operation" << endl;
					cout << "----------------------------------" << endl;
				}
					
			}
			else if (choice == 5)
			{
			    cout << "----------------------------------" << endl;
			    Add(aterms, adeg, acoef, bterms, bdeg, bcoef, rterms, rdeg, rcoef);
				cout << "----------------------------------" << endl;
			}
				
			else if (choice == 6)
			{
			    cout << "----------------------------------" << endl;
			    Subtract(aterms, adeg, acoef, bterms, bdeg, bcoef, rterms, rdeg, rcoef);
				cout << "----------------------------------" << endl;
            }
				
			else if (choice == 7)
			{
			    cout << "----------------------------------" << endl;
			    Subtract(bterms, bdeg, bcoef, aterms, adeg, acoef, rterms, rdeg, rcoef);
				cout << "----------------------------------" << endl;
            }
				
			else if (choice == 8)
			{
			    cout << "----------------------------------" << endl;
			    Multiply(aterms, adeg, acoef, bterms, bdeg, bcoef, rterms, rdeg, rcoef);
				cout << "----------------------------------" << endl;
            }
				
			else if (choice == 9)
			{
			    if (Equal(aterms, adeg, acoef, bterms, bdeg, bcoef))
			    {
					cout << "----------------------------------" << endl;
					cout << "Both polynomials are same"<<endl;
					cout << "----------------------------------" << endl;
				}
					
				else
				{
					cout << "----------------------------------" << endl;
					cout << "Both are differnt"<<endl;
					cout << "----------------------------------" << endl;
				}
					
			}
			else if (choice != 0)
			{
			    cout << "----------------------------------" << endl;
			    cout << "invalid operation" << endl;
				cout << "----------------------------------" << endl;
            }
				
			
				
			
		}
	}
	return;
	
	
}
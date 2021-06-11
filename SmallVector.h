/*
Name: Mustafa Saðlam
ID: 150140129
20.03.17
*/
#include<iostream>
#define MAXSS 32 //Maximum Static Size

class SmallVector{
	int staticBuffer[MAXSS];
	int* dynamicBuffer;
	int size;//there isnot another way to compute it;
	public:
		SmallVector();//default costructor ###
		SmallVector(int givenArray[], int vectorSize);//constructor with an array and size parameters ###
		SmallVector(const SmallVector &toCopy);//the copy constructor ###
		~SmallVector();//the destructor ###
		
		SmallVector operator+ (const SmallVector &svAddend) const;//overloading operator + ###
		SmallVector operator* (int scalar) const;//overloading operator * ###
		const SmallVector& operator= (const SmallVector &toAssign);//overloading operator = ###
		int& operator[] (int index);//overloading operator [] for non-consts ###
		const int& operator[] (int index) const;// for consts ###
	
		int getSize() const;//the size functions ###
		int getCapacity() const;// the capacity function ###
		void push_back(const int intToAdd);//push_back with an integer ###
		void push_back(const int arrayToAdd[], const int sizeOfArray);//push_back with an int array ###
		int pop_back();//
		SmallVector reverse();//
};

SmallVector::SmallVector(){ //default constructor
	size = 0;
	dynamicBuffer = NULL;
}

SmallVector::SmallVector(int givenArray[], int vectorSize){//constructor
	size = 0;
	dynamicBuffer = NULL;
	push_back(givenArray, vectorSize);// using push_back  for a similar constructer
}

SmallVector::SmallVector(const SmallVector &toCopy){//copy constructor
	dynamicBuffer = NULL;
	(*this) = toCopy;
	size = toCopy.getSize();
}

SmallVector::~SmallVector(){//destructor
	if(dynamicBuffer) delete[] dynamicBuffer;
}

int& SmallVector::operator[](int index){
	if(index>getSize())
		return (*this)[getSize()];
	else if(index<(0-getSize()))
		return (*this)[0];
	else{
		if(index>=0){
			if(index<MAXSS) return staticBuffer[index];
			else return dynamicBuffer[index-MAXSS];
		}
		else{
			return (*this)[index+getSize()];
		}
	}	
}

const int& SmallVector::operator[](int index) const{
	if(index>getSize())
		return (*this)[getSize()];
	else if(index<(0-getSize()))
		return (*this)[0];
	else{
		if(index>=0){
			if(index<MAXSS) return staticBuffer[index];
			else return dynamicBuffer[index-MAXSS];
		}
		else{
			return (*this)[index+getSize()];//function calling itself
		}
	}	
}

const SmallVector& SmallVector::operator=(const SmallVector &toAssign){
	if(dynamicBuffer){
		if(getSize() > MAXSS+1) delete[] dynamicBuffer;
		else delete dynamicBuffer;
	}
	
	for(int i=0; (i<MAXSS && i<toAssign.getSize()); i++){
		staticBuffer[i] = toAssign.staticBuffer[i];
	}
	
	if(toAssign.getSize() > MAXSS){
		dynamicBuffer = new int[toAssign.getSize()-MAXSS];
		for(int i=0; i<toAssign.getSize()-MAXSS; i++){
			dynamicBuffer[i] = toAssign.dynamicBuffer[i];
		}
	}
	size = toAssign.getSize();
	return (*this);
}

SmallVector SmallVector::operator+(const SmallVector &svAddend) const{
	SmallVector svS(*this);//this should work since the copy constructor's implemented
	/*	for(int i=0; i<svAddend.getSize(); i++)
			svS.push_back(svAddend[i]);//using push_back to add elements to the end*/
	if(svAddend.getSize()<=MAXSS){
		svS.push_back(svAddend.staticBuffer,svAddend.getSize());
	}
	else{
		svS.push_back(svAddend.staticBuffer,MAXSS);
		svS.push_back(svAddend.dynamicBuffer,svAddend.getSize()-MAXSS);
	}
	return svS;
}

SmallVector SmallVector::operator*(int scalar) const{
	SmallVector svP;
	for(;scalar>0;scalar--)
		svP = svP + (*this);//using assignment and plus operators
	return svP;
}

int SmallVector::getSize() const{
	return size;
}

int SmallVector::getCapacity() const{
	if(size<=MAXSS) return MAXSS;
	else return size;
}

void SmallVector::push_back(const int intToAdd){
	if(getSize()<getCapacity()){
		(*this)[getSize()+1] = intToAdd;
	}
	else{
		if(dynamicBuffer){
			int sizeofdynamicbuffer = getSize()-MAXSS;
			int* tempBuffer = new int[sizeofdynamicbuffer];
			for(int i=0; i<sizeofdynamicbuffer; i++){
				tempBuffer[i] = dynamicBuffer[i];
			}
			delete[] dynamicBuffer;
			dynamicBuffer = new int[sizeofdynamicbuffer+1];
			for(int i=0; i<sizeofdynamicbuffer; i++){
				dynamicBuffer[i] = tempBuffer[i];
			}
			(*this)[getSize()+1] = intToAdd;
			delete[] tempBuffer;
		}
		else{
			dynamicBuffer = new int[getSize()-MAXSS+1];
			dynamicBuffer[0] = intToAdd;
		}
	}
	size += 1;	
}

void SmallVector::push_back(const int arrayToAdd[], const int sizeOfArray){
	if(getSize()+sizeOfArray<MAXSS){
		for(int i=0; i<sizeOfArray; i++){
			(*this)[getSize()+i] = arrayToAdd[i];
			size++;
		}
	}
	else{
		if(dynamicBuffer){
			int sizeofdynamicbuffer = getSize()-MAXSS;
			int* tempBuffer = new int[sizeofdynamicbuffer];
			for(int i=0; i<sizeofdynamicbuffer; i++){//copying dynamicBuffer to increase capacity
				tempBuffer[i] = dynamicBuffer[i];
			}
			delete[] dynamicBuffer;
			
			dynamicBuffer = new int[getSize()-MAXSS+sizeOfArray];//increasing capacity
			for(int i=0; i<getSize()-MAXSS; i++){
				dynamicBuffer[i] = tempBuffer[i];
			}
			delete[] tempBuffer; //deleting temporary copy array
			
			for(int i=0; i<sizeOfArray; i++){//adding the array 
				(*this)[getSize()+i] = arrayToAdd[i];
				size++;
			}
		}
		else{
			dynamicBuffer = new int[getSize()-MAXSS+sizeOfArray];
			for(int i=0; i<sizeOfArray; i++){//adding the array 
				(*this)[getSize()+i] = arrayToAdd[i];
				size++;
			}
		}
	}
}
int SmallVector::pop_back(){
	int toReturn = (*this)[-1];
	if(dynamicBuffer){
		int* tempBuffer = new int[getSize()-MAXSS];
		for(int i=0; i<getSize()-MAXSS-1; i++){//copying dynamicBuffer to decrease capacity
			tempBuffer[i] = dynamicBuffer[i];
		}
		delete[] dynamicBuffer;
		
		dynamicBuffer = new int[getSize()-MAXSS-1];//decreasing capacity
		for(int i=0; i<getSize()-MAXSS-1; i++){
			dynamicBuffer[i] = tempBuffer[i];
		}
		delete[] tempBuffer; //deleting temporary copy array
	}	
	size--;
	return toReturn;
}

SmallVector SmallVector::reverse(){
	SmallVector revSV(*this);//copying this to be sure that sizes are equal
	for(int i=1; i<=getSize(); i++){
		revSV[i-1] = (*this)[-i];
	}
	return revSV;
}

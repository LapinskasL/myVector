//Name:             Lukas Lapinskas
//Summary:          Vector Container Implementation  

#include <iostream>
#include <vector>
using namespace std;


class myVector {
private:
	// size of the array
	int arrCapacity = 0;
	// keeps track of number of elements in array
	int size_cnt = 0;
	// initializes an 
	int* arr = new int[arrCapacity];
	// push_back ran (because insert creates vect of same size and capacity
	// until push_back runs once).
	bool p_bRan = false;
	// pop_back ran (because insert creates vect of same size and capacity
	// until pop_back runs once).
	bool p_pRan = false;

	// multiplies arrCapacity by 1.5 by default and recopies old array elements
	// to a new one. Sometimes the default parameters need changing.
	void newArray(int addNumToCapac = 0, double multiplier = 1.5) {
		// initializes a new size (truncation due to a double is GOOD)
		// vector doesn't grow more than 50% each time with default values
		int newSize = (arrCapacity + addNumToCapac) * multiplier;

		int* tempArr = new int[newSize];
		// copies elements from arr to tempArr
		for (int i = 0; i < size_cnt; i++) {
			tempArr[i] = arr[i];
		}
		// arrCapacity variable is assigned a new size
		arrCapacity = newSize;

		delete[] arr;
		// assigns the tempArray pointer variable address to
		// arr pointer variable
		arr = tempArr;
	}

public:
	// @@@@@ ASSIGN @@@@@
	// assigns a new set of elements to the container, replacing its existing
	// elements. After the function executes, the container will have size 
	// elements, each set to value.
	void assign(int size, int value) {

		static bool assignRan = false;

		if (size > arrCapacity) {
			// checks if assign( ) ran at least once.
			// The reason for this is because in an STL array, when assign
			// runs the with array size > capacity for the first time, it creates 
			// a vector of equal capacity and size.
			if (assignRan) {
				newArray();
			}
			// if assign has never ran, with size > arrCapacity, it creates a vector
			// of equal capacity and size
			else if (!assignRan) {
				int addCapac = size - arrCapacity;
				newArray(addCapac, 1);
				// changes static boolean to true. This else if statement will never run again
				// until program is restarted.
				assignRan = true;
			}
		}
		// assigns values to every element
		for (int i = 0; i < size; i++) {
			*(arr + i) = value;
		}
		// size_cnt is updated
		size_cnt = size;
	}

	// @@@@@ AT @@@@@
	// returns a reference to the element located at the specified index
	int& at(int index) {
		return arr[index];
	}

	// @@@@@ BACK @@@@@
	// returns a reference to the last element in the container
	int& back() {
		return arr[size_cnt - 1];
	}

	// @@@@@ CAPACITY @@@@@
	// returns the number of elements that the container's
	// underlying array can hold without reallocating the array
	int capacity() {
		return arrCapacity;
	}

	// @@@@@ CLEAR @@@@@
	// erases all of the values in the container
	void clear() {
		size_cnt = 0;
	}

	// @@@@@ EMPLACE_BACK @@@@@
	// constructs a new element containing the specified value at
	// the end of the container
	// THIS FUNCTION IS INCORRECT. Could not figure out how to
	// construct a new element directly in the array.
	void emplace_back(int value) {
		push_back(value);
	}

	// @@@@@ EMPTY @@@@@
	// returns true if container is empty, or false otherwise
	bool empty() {
		if (size_cnt == 0) {
			return true;
		}
		else {
			return false;
		}
	}

	// @@@@@ FRONT @@@@@
	// returns a reference to the first element in the container
	int& front() {
		return arr[0];
	}

	// @@@@@ INSERT @@@@@
	// inserts a new element at index location with value as its value
	void insert(int index, int value) {
		// if this isn't the first update to the vector...
		if (size_cnt == arrCapacity && arrCapacity != 0) {
			// if vector capacity is not 1
			if (arrCapacity != 1) {
				newArray();
			}
			// if array capacity is 1
			else {
				// array capacity is incremented because default parameter values 
				// couldn't increase the capacity
				newArray(1, 1);
			}
		}
		// else, if array capacity is either 0 AND size is equal to capacity (if this
		// is the first update to the vector)
		else if (arrCapacity == 0 && size_cnt == arrCapacity) {
			newArray(1, 1);
		}
		// the for loop goes backwards and starts at the last element.
		// it readjusts each element to its original index + 1, until i
		// is less than parameter index (to create one space to insert
		// one new value).
		// i = last value in the array
		// loops as long as i isn't less than index parameter
		for (int i = (size_cnt - 1); i >= index; i--) {
			arr[i + 1] = arr[i];
		}
		arr[index] = value;
		size_cnt++;
	}

	// @@@@@ INSERT (with n) @@@@@
	// inserts n new elements with parameter value as their value. Consider index
	// as the starting location.
	void insert(int index, int n, int value) {
		// boolean to record if insertion occured out of range
		bool outOfRange = false;
		// if push_back or pop_back ran before... (the reason for this is because
		// that was the rule I found with inserting before pushing or popping, but
		// it is really inconsistent).
		if (p_bRan || p_pRan) {
			// holds the capacity needed for the array
			int tempCapac = arrCapacity;
			// this while statement increases efficiency. Previously, new dynamic
			// arrays would be created and deleted until arrCapacity was large enough.
			// Now, the capacity variable is multiplied until it is big enough to support
			// the new size, and only then a new dynamic array is created.
			while (size_cnt + n > tempCapac) {
				// if tempCapac is 0 or 1, tempCapac is incremented
				if (tempCapac == 0 || tempCapac == 1) {
					tempCapac++;
				}
				// else (if more than 1), it is multiplied by 1.5
				else {
					tempCapac *= 1.5;
				}
			}
			// an array with a new capacity is generated
			newArray((tempCapac - arrCapacity), 1);


			/*

			// this while loop was wrong because it kept making new arrays (I thought it didn't)
			while (size_cnt + n > tempCapac) {
				tempCapac *= 1.5;
				// if tempCapac is 0 or 1
				if (tempCapac == 0 || tempCapac == 1) {
					// increase array size by 1
					newArray(1, 1);
					tempCapac = arrCapacity;
				}
				else if (size_cnt + n <= tempCapac) {
					newArray((tempCapac - arrCapacity), 1);
				}
			}

			*/

		}
		// the reason for this else if statement is that if insert(n) is used in an STL
		// vector before push_back or pop_back (and possibly others), it creates 
		// a vector with the same size and capacity each time. But once pushback or pop_back
		// is used, the insert(n) function multiplies the last capacity by 1.5.
		else if (!p_bRan || !p_pRan) {
			// if the potential new size is larger than arrCapacity, a new array with 
			// is created with equal potential size and arrCapacity.
			if (size_cnt + n > arrCapacity) {
				newArray(n, 1);
			}
		}
		// else, and error id displayed if vector out of range
		else {
			cout << "vector out of range!" << endl;
			outOfRange = true;
		}
		// if vector NOT out of range...
		if (!outOfRange) {
			// similar to reverse loop in the other insert() function, except it recopies
			// each element to its original index + n (to create n spaces for inserting 
			// the new values).
			for (int i = (size_cnt - 1); i >= index; i--) {
				arr[i + n] = arr[i];
			}
			// inserts n amount of values into the spaces relieved by the 
			// for-loop above. Starts at index parameter and ends at index + n.
			for (int i = index; i < (index + n); i++) {
				arr[i] = value;
				size_cnt++;
			}
		}
	}

	// @@@@@ POP_BACK @@@@@
	// remove the last element of the container
	void pop_back() {
		if (size_cnt > 0) {
			size_cnt--;
		}
		// if size_cnt is 0, displays an error msg
		else {
			cout << "ERROR! Vector is empty." << endl;
		}

		p_pRan = true;
	}

	// @@@@@ PUSH_BACK @@@@@
	// adds a new element containing value to the end of the container
	void push_back(int value) {
		// if array only contains 0 or 1 elements, the default parameter
		// values of newArray are changed to 1 and 1 (the reason for this
		// is because such low size needs a little nudge due to truncation,
		// since 1*1.5=1(int) and so size would remain the same. If the size
		// is >=2, then 2*1.5=3(int).
		if (size_cnt == 0 || size_cnt == 1) {
			newArray(1, 1);
		}
		// if array is full of elements, make new array
		else if (size_cnt == arrCapacity) {
			newArray();
		}
		// place the new value at the end
		arr[size_cnt] = value;
		size_cnt++;

		p_bRan = true;
	}

	// @@@@@ SIZE @@@@@
	// returns the number of elements in the container
	int size() {
		return size_cnt;
	}

	// destructor frees up memory
	~myVector() {
		delete[] arr;
	}
};



int main() {

	vector<int> vect;
	myVector m;



	//__________________GUIDE TO QUICK TESTING_______________________
	// The two outputs MUST be identical.							|
	// Use the following two sites to check if output is identical:	|
	// 1. https://www.diffchecker.com/diff							|
	// 2. http://www.textdiff.com/									|
	// or just make/Google your own tool(s).						|
	//______________________________________________________________|

	cout << "___@STL@ vector___" << endl;

	// initial values
	cout << "size: " << vect.size() << endl;
	cout << "capacity: " << vect.capacity() << endl;
	cout << "is empty: " << vect.empty() << endl;

	// testing insert(n) IF it was the first function used multiple times in succession
	cout << "insterting (into an \"empty\" vector the number 3 into the first index five times..." << endl;
	vect.insert(vect.begin(), 5, 3);
	cout << "size: " << vect.size() << endl;
	cout << "capacity: " << vect.capacity() << endl;
	cout << "insterting (into an \"empty\" vector the number 3 into the first index 10 times..." << endl;
	vect.insert(vect.begin(), 10, 3);
	cout << "size: " << vect.size() << endl;
	cout << "capacity: " << vect.capacity() << endl;
	cout << "insterting (into an \"empty\" vector the number 3 into the first index fifteen times..." << endl;
	vect.insert(vect.begin(), 15, 3);
	cout << "size: " << vect.size() << endl;
	cout << "capacity: " << vect.capacity() << endl;

	// for some reason, it did not create a vector of equal capacity and size if used once or twice more... why?

	cout << "clearing the vector..." << endl;
	vect.clear();

	cout << "insterting (into an \"empty\" vector the number 3 into the first index fifteen times..." << endl;
	vect.insert(vect.begin(), 15, 3);
	cout << "size: " << vect.size() << endl;
	cout << "capacity: " << vect.capacity() << endl;
	cout << "popping once..." << endl;
	vect.pop_back();
	cout << "pushing once..." << endl;
	vect.push_back(3);
	cout << "size: " << vect.size() << endl;
	cout << "capacity: " << vect.capacity() << endl;

	// testing size(), capacity(), empty()
	cout << "size: " << vect.size() << endl;
	cout << "capacity: " << vect.capacity() << endl;
	cout << "is empty: " << vect.empty() << endl;

	// testing push_back()
	cout << "pushing..." << endl;
	vect.push_back(1);
	cout << "size: " << vect.size() << endl;
	cout << "capacity: " << vect.capacity() << endl;
	cout << "pushing..." << endl;
	vect.push_back(2);
	cout << "size: " << vect.size() << endl;
	cout << "capacity: " << vect.capacity() << endl;
	cout << "is empty: " << vect.empty() << endl;
	cout << "pushing..." << endl;
	vect.push_back(3);
	cout << "size: " << vect.size() << endl;
	cout << "capacity: " << vect.capacity() << endl;
	cout << "pushing..." << endl;
	vect.push_back(4);
	cout << "size: " << vect.size() << endl;
	cout << "capacity: " << vect.capacity() << endl;

	// testing front(), back(), at()
	cout << "returning front: " << vect.front() << endl;
	cout << "returning back: " << vect.back() << endl;
	cout << "returning at index 1: " << vect.at(1) << endl;

	// testing assign()
	cout << "assigning number 3 to size 2..." << endl;
	vect.assign(2, 3);
	cout << "size: " << vect.size() << endl;
	cout << "capacity: " << vect.capacity() << endl;
	cout << "returning front: " << vect.front() << endl;
	cout << "returning back: " << vect.back() << endl;
	cout << "returning at index 1: " << vect.at(1) << endl;
	cout << "assigning number 4 to size 19..." << endl;
	vect.assign(19, 4);
	cout << "size: " << vect.size() << endl;
	cout << "capacity: " << vect.capacity() << endl;
	cout << "assigning number 5 to size 16..." << endl;
	vect.assign(16, 5);
	cout << "size: " << vect.size() << endl;
	cout << "capacity: " << vect.capacity() << endl;
	cout << "returning front: " << vect.front() << endl;
	cout << "returning back: " << vect.back() << endl;
	cout << "returning at index 1: " << vect.at(1) << endl;
	cout << "assigning number 6 to size 24..." << endl;
	vect.assign(24, 6);
	cout << "size: " << vect.size() << endl;
	cout << "capacity: " << vect.capacity() << endl;

	// testing pop_back
	cout << "assigning number 7 to size 4..." << endl;
	vect.assign(4, 7);
	cout << "size: " << vect.size() << endl;
	cout << "capacity: " << vect.capacity() << endl;
	vect.pop_back();
	vect.pop_back();
	vect.pop_back();
	vect.pop_back();
	cout << "size: " << vect.size() << endl;
	cout << "capacity: " << vect.capacity() << endl;

	// testing insert(index, value)
	vect.assign(4, 7);
	cout << "inserting number 88 into index 1" << endl;
	vect.insert(vect.begin() + 1, 88);
	cout << "index 1 value: " << vect.at(1) << endl;
	cout << "size: " << vect.size() << endl;
	cout << "capacity: " << vect.capacity() << endl;
	cout << "assigning number 6 to size 28..." << endl;
	vect.assign(28, 6);
	cout << "size: " << vect.size() << endl;
	cout << "capacity: " << vect.capacity() << endl;
	cout << "inserting number 99 into index 10" << endl;
	vect.insert(vect.begin() + 10, 99);
	cout << "index 9 value: " << vect.at(9) << endl;
	cout << "index 10 value: " << vect.at(10) << endl;
	cout << "index 11 value: " << vect.at(11) << endl;
	cout << "size: " << vect.size() << endl;
	cout << "capacity: " << vect.capacity() << endl;

	// testing insert(index, n, value)
	cout << "inserting number 111 into index 12 ten times" << endl;
	vect.insert(vect.begin() + 12, 10, 111);
	cout << "index 11 value: " << vect.at(11) << endl;
	cout << "index 12 value: " << vect.at(12) << endl;
	cout << "index 21 value: " << vect.at(21) << endl;
	cout << "index 22 value: " << vect.at(22) << endl;
	cout << "size: " << vect.size() << endl;
	cout << "capacity: " << vect.capacity() << endl;

	cout << "inserting number 222 into index 39 ten times" << endl;
	vect.insert(vect.begin() + 39, 10, 222);
	cout << "index 38 value: " << vect.at(38) << endl;
	cout << "index 39 value: " << vect.at(39) << endl;
	cout << "index 48 value: " << vect.at(48) << endl;
	cout << "size: " << vect.size() << endl;
	cout << "capacity: " << vect.capacity() << endl;
	cout << "returning back: " << vect.back() << endl;

	// testing clear()
	cout << "clearing vector..." << endl;
	vect.clear();
	cout << "size: " << vect.size() << endl;
	cout << "capacity: " << vect.capacity() << endl;
	cout << "is empty: " << vect.empty() << endl;





	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	cout << "\n\n\n_________________________" << endl;
	cout << "@@@@@ NON STL BELOW @@@@@" << endl;
	cout << "output must be identical\n\n\n" << endl;
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@






	cout << "___@myVector@ vector___" << endl;

	// initial values
	cout << "size: " << m.size() << endl;
	cout << "capacity: " << m.capacity() << endl;
	cout << "is empty: " << m.empty() << endl;

	// testing insert(n)
	cout << "insterting (into an \"empty\" vector the number 3 into the first index five times..." << endl;
	m.insert(0, 5, 3);
	cout << "size: " << m.size() << endl;
	cout << "capacity: " << m.capacity() << endl;
	cout << "insterting (into an \"empty\" vector the number 3 into the first index 10 times..." << endl;
	m.insert(0, 10, 3);
	cout << "size: " << m.size() << endl;
	cout << "capacity: " << m.capacity() << endl;
	cout << "insterting (into an \"empty\" vector the number 3 into the first index fifteen times..." << endl;
	m.insert(0, 15, 3);
	cout << "size: " << m.size() << endl;
	cout << "capacity: " << m.capacity() << endl;

	cout << "clearing the vector..." << endl;
	m.clear();

	cout << "insterting (into an \"empty\" vector the number 3 into the first index fifteen times..." << endl;
	m.insert(0, 15, 3);
	cout << "size: " << m.size() << endl;
	cout << "capacity: " << m.capacity() << endl;
	cout << "popping once..." << endl;
	m.pop_back();
	cout << "pushing once..." << endl;
	m.push_back(3);
	cout << "size: " << m.size() << endl;
	cout << "capacity: " << m.capacity() << endl;

	// testing size(), capacity(), empty()
	cout << "size: " << m.size() << endl;
	cout << "capacity: " << m.capacity() << endl;
	cout << "is empty: " << m.empty() << endl;

	// testing push_back()
	cout << "pushing..." << endl;
	m.push_back(1);
	cout << "size: " << m.size() << endl;
	cout << "capacity: " << m.capacity() << endl;
	cout << "pushing..." << endl;
	m.push_back(2);
	cout << "size: " << m.size() << endl;
	cout << "capacity: " << m.capacity() << endl;
	cout << "is empty: " << m.empty() << endl;
	cout << "pushing..." << endl;
	m.push_back(3);
	cout << "size: " << m.size() << endl;
	cout << "capacity: " << m.capacity() << endl;
	cout << "pushing..." << endl;
	m.push_back(4);
	cout << "size: " << m.size() << endl;
	cout << "capacity: " << m.capacity() << endl;

	// testing front(), back(), at()
	cout << "returning front: " << m.front() << endl;
	cout << "returning back: " << m.back() << endl;
	cout << "returning at index 1: " << m.at(1) << endl;

	// testing assign()
	cout << "assigning number 3 to size 2..." << endl;
	m.assign(2, 3);
	cout << "size: " << m.size() << endl;
	cout << "capacity: " << m.capacity() << endl;
	cout << "returning front: " << m.front() << endl;
	cout << "returning back: " << m.back() << endl;
	cout << "returning at index 1: " << m.at(1) << endl;
	cout << "assigning number 4 to size 19..." << endl;
	m.assign(19, 4);
	cout << "size: " << m.size() << endl;
	cout << "capacity: " << m.capacity() << endl;
	cout << "assigning number 5 to size 16..." << endl;
	m.assign(16, 5);
	cout << "size: " << m.size() << endl;
	cout << "capacity: " << m.capacity() << endl;
	cout << "returning front: " << m.front() << endl;
	cout << "returning back: " << m.back() << endl;
	cout << "returning at index 1: " << m.at(1) << endl;
	cout << "assigning number 6 to size 24..." << endl;
	m.assign(24, 6);
	cout << "size: " << m.size() << endl;
	cout << "capacity: " << m.capacity() << endl;

	// testing pop_back
	cout << "assigning number 7 to size 4..." << endl;
	m.assign(4, 7);
	cout << "size: " << m.size() << endl;
	cout << "capacity: " << m.capacity() << endl;
	m.pop_back();
	m.pop_back();
	m.pop_back();
	m.pop_back();
	cout << "size: " << m.size() << endl;
	cout << "capacity: " << m.capacity() << endl;

	// testing insert(index, value)
	m.assign(4, 7);
	cout << "inserting number 88 into index 1" << endl;
	m.insert(1, 88);
	cout << "index 1 value: " << m.at(1) << endl;
	cout << "size: " << m.size() << endl;
	cout << "capacity: " << m.capacity() << endl;
	cout << "assigning number 6 to size 28..." << endl;
	m.assign(28, 6);
	cout << "size: " << m.size() << endl;
	cout << "capacity: " << m.capacity() << endl;
	cout << "inserting number 99 into index 10" << endl;
	m.insert(10, 99);
	cout << "index 9 value: " << m.at(9) << endl;
	cout << "index 10 value: " << m.at(10) << endl;
	cout << "index 11 value: " << m.at(11) << endl;
	cout << "size: " << m.size() << endl;
	cout << "capacity: " << m.capacity() << endl;

	// testing insert(index, n, value)
	cout << "inserting number 111 into index 12 ten times" << endl;
	m.insert(12, 10, 111);
	cout << "index 11 value: " << m.at(11) << endl;
	cout << "index 12 value: " << m.at(12) << endl;
	cout << "index 21 value: " << m.at(21) << endl;
	cout << "index 22 value: " << m.at(22) << endl;
	cout << "size: " << m.size() << endl;
	cout << "capacity: " << m.capacity() << endl;

	cout << "inserting number 222 into index 39 ten times" << endl;
	m.insert(39, 10, 222);
	cout << "index 38 value: " << m.at(38) << endl;
	cout << "index 39 value: " << m.at(39) << endl;
	cout << "index 48 value: " << m.at(48) << endl;
	cout << "size: " << m.size() << endl;
	cout << "capacity: " << m.capacity() << endl;
	cout << "returning back: " << m.back() << endl;

	// testing clear()
	cout << "clearing vector..." << endl;
	m.clear();
	cout << "size: " << m.size() << endl;
	cout << "capacity: " << m.capacity() << endl;
	cout << "is empty: " << m.empty() << endl;



	system("pause");
	return 0;
}
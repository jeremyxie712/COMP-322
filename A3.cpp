/*
    -------------------------------------
    |   Name: Jeremy Xie                |
    |   McGill ID: 260660974            |
    |   Course: COMP 322                |
    |   Instructor: Dr. Chad Zammer     |
    -------------------------------------
*/
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <type_traits>
#define NULL __null

using namespace std;

/*
Question 1:
    There are several built-in smart pointer libraries provided in C++11 and they are listed as follows:
        1. unique_ptr     smart pointer with unique object ownership semantics, this is also the new smart pointer that is designed to 
                          replace the auto_ptr. The pointer is unique, and can only be moved but not copied in any possible way. When
                          it is moved to another unique_ptr, the original data that were pointed by the original unique_ptr were lost. 

        2. shared_ptr     smart pointer with shared object ownership semantics, shared_ptr counts the references for the raw pointers. 
                          It is also possible for us to tell the ownership and have cyclic references. As their names imply, shared_ptr
                          can share owenship, this is difference from unique_ptr. 

        3. weak_ptr       weak reference to an object managed by std::shared_ptr, this pointer functions similarly with raw pointers we have
                          have ecountered in C and C++, they do have the ability to keep track of whether it is still ebing referenced and
                          if it is allocated or deallocated and providing related services with dealing pointers. Together with shared_ptr, 
                          if weak_ptr exits the scope, the pointer object still exists and will not disappear. However, it is worth mentioning
                          that weak_ptr does not affect the reference count of the associated shared_ptr though. 

        4. auto_ptr       Auto_ptr is a smart pointer that manages an object obtained via new expression and deletes that object when 
                          auto_ptr is itself destroyed. Auto_ptr's reference is unique, hence it is held by only one pointer at any time
                          and cannot share owenship amongst pointers. It can be passed but not shared or copied. Once passed, the original 
                          pointer data will become NULL. The pointer is distructed with delete when it goes out of scope. Usefult against 
                          memory leaks and dangling pointers. 
                
        5. These 4 pointers are major smart pointers since c++11, there are also intrusive_ptr and scoped_ptr exist but they function similarly
           with unique_ptr and shared_ptr respectively. 

*/

template <typename T>
class SmartPointer
{
  public:
    SmartPointer()     //Below are the constructors needed for both single value and array-like structures. 
    {
        this->smartValue = new T(0.0);
    }
    SmartPointer(T arg)
    {
        setValue(arg);
    }

    SmartPointer(T *arr, int size)
    {
        try
        {
            this->smartValue = new T[size];
        }
        catch (const std::bad_alloc &e)
        {
            std::cerr << e.what() << '\n';
        }
        this->size = size;
        for (int i = 0; i < size; i++)
        {
            try
            {
                this->setValue(i, *(arr + i));
                if (arr[i] < 0)
                    throw std::numeric_limits<int>::min();
            }
            catch (int e)
            {
                std::cerr << e << '\n';
                this->setValue(i, 0);
            }
        }
    }
    SmartPointer(T inputValue, size_t size)
    {
        try
        {
            this->smartValue = new T[size];
        }
        catch (const std::bad_alloc &e)
        {
            std::cerr << "Allocation Error" << e.what() << '\n';
        }

        this->size = size;

        for (int i = 0; i < size; i++)
        {
            this->setValue(i, inputValue);
            if (inputValue < 0)
            {
                this->setValue(i, 0);
            }
        }
    }
    T getValue(int index) //This is the getter specifically designed for the array structure such that we return a specific value with associated index.
    {
        if (index > this->size - 1)
        {
            throw "Out of bounds";
        }
        return this->smartValue[index];
    }
    void setValue(int index, T arrVal) //We set value at certain index to what we want for it. 
    {
        if (index > this->size - 1)
        {
            throw "Out of bounds";
        }
        try
        {
            if (arrVal < 0)
                throw std::numeric_limits<int>::min();
        }
        catch (int e)
        {
            std::cerr << "Error: Negative input exists " << e << '\n';
        }
        *(this->smartValue + index) = arrVal;
    }
    void printArray() //Here we use this function to print the elements of an array. 
    {
        std::cout << "Printing the array" << std::endl;
        for (int i = 0; i < this->size; i++)
        {
            if (i != this->size - 1)
            {
                std::cout << *(this->smartValue + i) << ",";
            }
            else
            {
                std::cout << *(this->smartValue + i);
            }
        }
        std::cout << std::endl;
    }

    T getValue()
    {
        return *smartValue;
    }
    void setValue(T targetVal) //This is the setter for single value edition 
    {
        this->size = 1;
        try
        {
            if (targetVal < 0)
                throw std::numeric_limits<int>::min();
            this->smartValue = new T(targetVal);
        }
        catch (const std::bad_alloc &e)
        {
            std::cerr << e.what() << '\n';
        }
        catch (int e)
        {
            std::cerr << "Error: Negative input exists " << e << '\n';
        }
    }
    friend SmartPointer<T> operator+(SmartPointer<T> &firstArg, SmartPointer<T> &secondArg) //Friend functions to overload operators.
    {
        if (firstArg.size != secondArg.size)
        {
            std::cout << "Two arrays dimensions differ" << std::endl;
            exit(0);
        }
        size_t firstSize = firstArg.size;
        SmartPointer<T> *temp = new SmartPointer<T>(0, firstSize);
        temp->size = firstArg.size;
        for (int i = 0; i < firstSize; i++)
        {
            temp->setValue(i, *(firstArg.smartValue + i) + *(secondArg.smartValue + i));
        }
        return *temp;
        // return SmartPointer<T>(firstArg.getValue() + secondArg.getValue());
    }
    friend SmartPointer<T> operator-(SmartPointer<T> &firstArg, SmartPointer<T> &secondArg)
    {
        if (firstArg.size != secondArg.size)
        {
            std::cout << "Two arrays' dimensions differ." << std::endl;
            exit(0);
        }
        size_t firstSize = firstArg.size;
        SmartPointer<T> *temp = new SmartPointer<T>(0, firstSize);
        temp->size = firstArg.size;
        for (int i = 0; i < firstSize; i++)
        {
            temp->setValue(i, *(firstArg.smartValue + i) - *(secondArg.smartValue + i));
        }
        return *temp;
    }
    friend SmartPointer<T> operator*(SmartPointer<T> &firstArg, SmartPointer<T> &secondArg)
    {
        if (firstArg.size != secondArg.size)
        {
            std::cout << "Two arrays' dimensions differ." << std::endl;
            exit(0);
        }
        size_t firstSize = firstArg.size;
        SmartPointer<T> *temp = new SmartPointer<T>(0, firstSize);
        temp->size = firstArg.size;
        for (int i = 0; i < firstSize; i++)
        {
            temp->setValue(i, *(firstArg.smartValue + i) * *(secondArg.smartValue + i));
        }
        return *temp;
    }

    ~SmartPointer() //This is the destructor for the SmartPointer class. 
    {
        while (1)
        {
            if (this->size == 1)
            {
                break;
            }
            else if (this->size < 0)
            {
                break;
            }
            else
            {
                delete[] this->smartValue;
                break;
            }
        }
    }

  private:
    T *smartValue;
    int size;
};

int main()
{
    /* Test cases provided by TA*/
    // For SmartPointer class
    cout << "Testing SmartPointer class" << endl;

    // Testing Constructors
    cout << "Creating a SmartPointer of type int with value 11" << endl;
    SmartPointer<int> SmartIntPointer1(11);
    cout << "SmartIntPointer1 = " << SmartIntPointer1.getValue() << endl;

    cout << "Creating a SmartPointer of type int with value -1" << endl;
    SmartPointer<int> SmartIntPointer(-1);

    cout << "Creating a SmartPointer of type int with no value provided" << endl;
    SmartPointer<int> SmartIntPointer2;
    cout << "SmartIntPointer2 = " << SmartIntPointer2.getValue() << endl;

    // Testing Setter & Getter
    cout << "Setting value of SmartIntPointer2 to 5" << endl;
    SmartIntPointer2.setValue(5);
    cout << "SmartIntPointer2 = " << SmartIntPointer2.getValue() << endl;

    cout << "Creating a SmartPointer of type float with no value provided" << endl;
    SmartPointer<float> SmartFloatPointer1;
    cout << "SmartFloatPointer1 = " << SmartFloatPointer1.getValue() << endl;

    cout << "Setting value of SmartFloatPointer1 to 1.5" << endl;
    SmartFloatPointer1.setValue(1.5);
    cout << "SmartFloatPointer1 = " << SmartFloatPointer1.getValue() << endl;

    cout << "Creating a SmartPointer of type float with no value provided" << endl;
    SmartPointer<float> SmartFloatPointer2;
    cout << "SmartFloatPointer2 = " << SmartFloatPointer2.getValue() << endl;

    cout << "Setting value of SmartFloatPointer2 to 2.5" << endl;
    SmartFloatPointer2.setValue(2.5);
    cout << "SmartFloatPointer2 = " << SmartFloatPointer2.getValue() << endl;

    SmartPointer<float> SmartFloatPointer3 = SmartFloatPointer1 + SmartFloatPointer2;
    cout << "SmartFloatPointer1 + SmartFloatPointer2 = " << SmartFloatPointer3.getValue() << endl;

    SmartPointer<float> SmartFloatPointer4 = SmartFloatPointer2 - SmartFloatPointer1;
    cout << "SmartFloatPointer2 - SmartFloatPointer1 = " << SmartFloatPointer4.getValue() << endl;

    SmartPointer<float> SmartFloatPointer5 = SmartFloatPointer1 * SmartFloatPointer2;
    cout << "SmartFloatPointer1 * SmartFloatPointer2 = " << SmartFloatPointer5.getValue() << endl;

    //The following are the use cases built for Question Six

    //Printing Array of size 5

    int testArr_one[5] = {37, 27, 53, 69, 31};
    SmartPointer<int> sPointerArray1(testArr_one, 5);
    std::cout << "--------------- Printing Array of size Five -------------------" << std::endl;
    sPointerArray1.printArray();
    std::cout << "---------------------------------------------------------------" << std::endl;

    //Getting the value of an element in the array by passing its index

    int testArr_two[5] = {46, 51, 21, 87, 10};
    SmartPointer<int> sPointerArray2(testArr_two, 5);
    std::cout << "------------------ Getting value out of array------------------" << std::endl;
    std::cout << sPointerArray2.getValue(1) << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;

    //Setting the value of an element in the array using its index

    SmartPointer<int> sPointerArray3(testArr_one, 5);
    std::cout << "-----------Setting value of an element in the array------------" << std::endl;
    std::cout << "Original Value: ";
    std::cout << sPointerArray3.getValue(1) << std::endl;
    std::cout << "New Value: ";
    sPointerArray3.setValue(1, 31);
    std::cout << sPointerArray3.getValue(1) << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;

    //Testing the operator overloading with arrays

    float testArr_four[4] = {88.7, 46.1, 59.9, 67.8};
    float testArr_five[4] = {23.5, 52.1, 34.7, 2.1};

    std::cout << "-------------Testing + operator overloading with array structure--------------" << std::endl;
    SmartPointer<float> sPointerArray4(testArr_four, 4);
    SmartPointer<float> sPointerArray5(testArr_five, 4);
    SmartPointer<float> sPointer_array_addition = sPointerArray4 + sPointerArray5;
    sPointer_array_addition.printArray();
    std::cout << "------------------------------------------------------------------------------" << std::endl;

    std::cout << "-------------Testing - operator overloading with array structure--------------" << std::endl;
    SmartPointer<float> sPointer_array_subtraction = sPointerArray4 - sPointerArray5;
    sPointer_array_subtraction.printArray();
    std::cout << "------------------------------------------------------------------------------" << std::endl;

    std::cout << "-------------Testing * operator overloading with array structure--------------" << std::endl;
    SmartPointer<float> sPointer_array_multiplication = sPointerArray4 * sPointerArray5;
    sPointer_array_multiplication.printArray();
    std::cout << "------------------------------------------------------------------------------" << std::endl;

    return 0;
}
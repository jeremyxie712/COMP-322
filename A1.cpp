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

using namespace std;

void countLetter()
{
    std::cout << "This is Question One" << std::endl;
    string sentence;
    char letter;
    std::cout << "Please enter a sentence: " << std::endl;
    std::getline(cin, sentence);
    std::cout << "The sentence is: " << sentence << std::endl;
    std::cout << "Please enter a letter: " << std::endl;
    cin >> letter;
    std::cout << "The letter is: " << letter << std::endl;

    int num = 0;
    for (int i = 0; i < sentence.size(); i++) //We traverse through the sentence to count the letter,
                                              //we count everything, upper or lower case letters.
    {
        if (sentence.at(i) == toupper(letter) || sentence.at(i) == tolower(letter))
        {
            num++;
        }
    }
    std::cout << "The letter " << letter << "repeated " << num << " times in your sentence. " << std::endl;
    std::cout << "---------------------------------------------------------------------" << std::endl;
    //We ignore cin at the end in order to prevent memory leak
}

void convertPhonetic()
{
    std::cout << "This is Question Two" << std::endl;
    std::vector<std::string> phoneticList(123); //We create a space of 123 since a starts at 97 on ASCII table
    phoneticList['a'] = "Alpha";
    phoneticList['b'] = "Bravo";
    phoneticList['c'] = "Charlie";
    phoneticList['d'] = "Delta";
    phoneticList['e'] = "Echo";
    phoneticList['f'] = "Foxtrot";
    phoneticList['g'] = "Golf";
    phoneticList['h'] = "Hotel";
    phoneticList['i'] = "India";
    phoneticList['j'] = "Juliett";
    phoneticList['k'] = "Kilo";
    phoneticList['l'] = "Lima";
    phoneticList['m'] = "Mike";
    phoneticList['n'] = "November";
    phoneticList['o'] = "Oscar";
    phoneticList['p'] = "Papa";
    phoneticList['q'] = "Quebec";
    phoneticList['r'] = "Romeo";
    phoneticList['s'] = "Sierra";
    phoneticList['t'] = "Tango";
    phoneticList['u'] = "Uniform";
    phoneticList['v'] = "Victor";
    phoneticList['w'] = "Whiskey";
    phoneticList['x'] = "X-ray";
    phoneticList['y'] = "Yankee";
    phoneticList['z'] = "Zulu";

    string word;
    std::cout << "Please enter a word: " << std::endl;
    cin.ignore();
    cin >> word;

    for (int i = 0; i < word.size(); i++)
    {
        int index;
        index = tolower(word.at(i));
        std::cout << phoneticList[index] << " "; //We print out corresponding phonetic label in the loop.
    }
    std::cout << " " << std::endl;
    std::cout << "---------------------------------------------------------------------" << std::endl;

}

/*
     Question Three Part One: 
            Our computers use a stack to trace all the variables and function calls that was created within the program
            and the upside of tail recursion comes in handy at this part since the normal recursion usually pushes the 
            return address of the value we want to the call stack and then directly back to the function who called it.
            This means we need a call stack whose size is linear in the depth of the recursive calls and this often takes
            a gigantic chunk of space on the memory heap. However, tail recursion does not need that amount of space since 
            it skips the process of recursive calls made by the normal recursion and return directly to the original caller. 
            This saves us space and it is relatively optimal for computers to operate. 



    Question Three Part Two:
             The answer to this question should be based on what situation we are in. It can be converted to tail recursion
             under the circumstance of using continuation passying style. One example shall be: 
                                                                def fib(n):
                                                                    if n <= 1:
                                                                        return n
                                                                    return fib(n - 1) + fib(n - 2)
             And we convert it to:
                                                                def fib_tail(n,counter):
                                                                    if n<= 1:
                                                                        return counter(n)
                                                                    return fib_tail(n - 1, lambda a: fib_tail(n - 2, lambda b: counter(a + b)))
             In this way, we can say that it became tail recursive. However, if continuation is prohibited or not applicable, 
             then we cannot convert all recursion to tail recursion. 

*/

int helper_fact(int n, int temp) //Helper function to do tail recursion
{
    if (n < 0)
    {
        return 0;
    }
    else if (n == 0)
    {
        return 1;
    }
    else if (n == 1)
    {
        return temp;
    }
    else
    {
        return helper_fact(n - 1, n * temp);
    }
}

void factorial()
{
    std::cout << "This is Question Four" << std::endl;
    int input;
    int temp = 1;
    int result;
    std::cout << "Please enter a number: " << std::endl;
    cin.ignore();
    cin >> input;
    std::cout << "The number is: " << input << std::endl;

    result = helper_fact(input, temp);

    std::cout << "The factorial of " << input << " is " << result << std::endl;
    std::cout << "---------------------------------------------------------------------" << std::endl;
}

void enhancedFactorial()
{
    std::cout << "This is Question Four" << std::endl;
    int known_fact[6] = {1, 2, 6, 24, 120, 720};
    int input;
    int result;
    std::cout << "Please enter a number: " << std::endl;
    cin.ignore();
    cin >> input;
    std::cout << "The number is: " << input << std::endl;

    if (input < 0)
    {
        result = 0;
    }
    else if (input <= 6)
    {
        result = known_fact[input - 1];
    }
    else
    {
        result = helper_fact(input, 1);
    }

    std::cout << "The factorial of " << input << " is " << result << std::endl;
    std::cout << "---------------------------------------------------------------------" << std::endl;
}

int main()
{
    //Question One
    countLetter();

    //Question Two
    convertPhonetic();

    //Question Three: See question three above.

    //Question Four
    factorial();

    //Question Five
    enhancedFactorial();

    return 0;
}
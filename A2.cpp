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
int counter;

struct ticket
{
    unsigned int numbers[6];
    ticket *next;
};

class SuperDraw
{
  public:
    SuperDraw()  //SuperDraw constuctor
    {
        ticketListHead = NULL;
        ticketListTail = NULL;
    }
    SuperDraw(int count) //This is the constructor we were instructed to implement, this will create as many lists as the user wants.
    {
        ticketListHead = NULL;
        ticketListTail = NULL;

        if (count == 0)
        {
            std::cout << "No ticket were generated since the input is 0" << std::endl;
        }
        if (count == 1)
        {
            std::cout << count << " new ticket were generated." << std::endl;
        }
        if (count > 1)
        {
            std::cout << count << " new tickets were generated. " << std::endl;
        }

        std::cout << "The numbers are: ";

        for (int i = 0; i < count; i++)
        {
            newTicket(2);
            if (i >= 0 && i < count - 1)
            {
                std::cout << " and ";
            }
            if (i == count - 1)
            {
                std::cout << std::endl;
            }
        }
    }

    SuperDraw(SuperDraw &sd) //This is another constructor wanted from the assignment documents. Here we take an object as argument. 
    {
        if (sd.ticketListHead == NULL)
        {
            ticketListHead = NULL;
            ticketListTail = NULL;
        }
        else
        {

            ticket *next = sd.ticketListHead;
            ticket *prevTicket = NULL;
            while (next)
            {
                ticket *new_ticket = new ticket();
                new_ticket->next = NULL;

                for (int i = 0; i < 6; i++)
                {
                    new_ticket->numbers[i] = next->numbers[i];
                }

                if (prevTicket != NULL)
                {
                    prevTicket->next = new_ticket;
                }
                else
                {
                    ticketListHead = new_ticket;
                }

                prevTicket = new_ticket;
                next = next->next;
            }

            ticketListTail = prevTicket;
        }
    }
    ~SuperDraw() //This is the destructor
    {
        ticket *next = ticketListHead;
        while (next)
        {
            ticket *deleteTicket = next;
            next = next->next;
            delete deleteTicket;
        }
    }

    void newTicket(int verbose = 0) //Here is the function we used to create new ticket, note that from the assignment documentation, we implement the function as void. 
    {
        ticket *new_ticket = new ticket();
        new_ticket->next = NULL;

        if (ticketListHead == NULL)
        {
            ticketListHead = new_ticket;
            ticketListTail = new_ticket;
        }
        else
        {
            ticketListTail->next = new_ticket;
            ticketListTail = new_ticket;
        }
        int newInt;
        for (int i = 0; i < 6; i++)
        {
            bool isUnique;  //Here we check if all the numbers in the ticket are unique. 
            do
            {
                newInt = rand() % 49 + 1;
                isUnique = true;
                for (int j = 0; j < 6; j++)
                {
                    if (new_ticket->numbers[j] == newInt)
                    {
                        isUnique = false;
                        break;
                    }
                }
            } while (!isUnique);
            new_ticket->numbers[i] = newInt;
        }

        int n = sizeof(new_ticket->numbers) / sizeof(new_ticket->numbers[0]);
        sort(new_ticket->numbers, new_ticket->numbers + n);

        if (verbose == 2)
        {
            for (int i = 0; i < 5; i++)
            {
                std::cout << new_ticket->numbers[i] << ", ";
            }
            std::cout << new_ticket->numbers[5];
        }

        if (verbose == 1)
        {
            std::cout << "A new ticket was successfully generated. The numbers are: ";
            for (int i = 0; i < 5; i++)
            {
                std::cout << new_ticket->numbers[i] << ", ";
            }
            std::cout << new_ticket->numbers[5] << std::endl;
        }
        counter++;
    }

    void printAllTicketNumbers() //Here we print out all the tickets we have found. 
    {
        std::cout << "We found " << counter << " generated tickets: " << std::endl;

        ticket *next = ticketListHead;
        while (next)
        {
            //prints the numbers in next
            for (int j = 0; j < 5; j++)
            {
                std::cout << next->numbers[j] << ", ";
            }
            std::cout << next->numbers[5];
            std::cout << std::endl;

            next = next->next;
        }
    }

    void verifySequence(unsigned int targetArr[]) //Here we verify whether the sequence already existed or not. 
    {
        ticket *next = ticketListHead;
        bool isEqual = false;
        sort(targetArr, targetArr + 6);
        while (next && !isEqual)
        {
            for (int k = 0; k < 6; k++)
            {
                if (next->numbers[k] != targetArr[k])
                {
                    isEqual = false;
                    break;
                }
                else
                {
                    isEqual = true;
                }
            }
            next = next->next;
        }
        if (isEqual == true)
        {
            std::cout << "The provided sequence of numbers was already generated." << std::endl;
        }
        else
        {
            std::cout << "The provided sequence of numbers was never generated before." << std::endl;
        }
    }

    void deleteSequence(unsigned int targetArr[]) //Here we delete the sequence if it's already existed. 
    {
        ticket *next = ticketListHead;
        ticket *deleteTicket = NULL;
        ticket *prevTicket = NULL;
        bool isEqual = false;
        while (next && !isEqual)
        {
            prevTicket = deleteTicket;
            deleteTicket = next;
            for (int k = 0; k < 6; k++)
            {
                if (next->numbers[k] != targetArr[k])
                {
                    isEqual = false;
                    break;
                }
                else
                {
                    isEqual = true;
                }
            }

            next = next->next;
        }

        if (isEqual == true)
        {
            std::cout << "The provided sequence of numbers was successfully deleted." << std::endl;
            if (prevTicket == NULL)
            {
                ticketListHead = deleteTicket->next;
            }
            else
            {
                prevTicket->next = deleteTicket->next;
            }

            if (deleteTicket->next == NULL)
            {
                ticketListTail = prevTicket;
            }

            delete deleteTicket;
        }
        else
        {
            std::cout << "The provided sequence of numbers was never generated before." << std::endl;
        }
    }

  private:
    ticket *ticketListHead;
    ticket *ticketListTail;
};

int main()
{
    srand(time(NULL));

    //Question One
      //Please check the detailed implementation above.

    //Question Two
    // SuperDraw sd();
    // sd.newTicket(1);


    //Question Three
    //SuperDraw sd(2)

    //Question Four
    // SuperDraw sd;
    // sd.newTicket();
    // sd.newTicket();
    // sd.newTicket();
    // sd.newTicket();
    //sd.printAllTicketNumbers();


    //Question Five
    // SuperDraw sd;
    // sd.newTicket();
    // int myNumbers[6] = {2, 4, 17, 29, 31, 34};
    // sd.verifySequence(myNumbers);


    //Question Six
    // SuperDraw sd;
    // sd.newTicket();
    // int myNumbers[6] = {2, 4, 17, 19, 31, 34};
    // sd.deleteSequence(myNumbers);

    //Question Seven
      //Please check above for the implemented destructor.

    
    //Question Eight
    // SuperDraw sd;
    // sd.newTicket();
    // SuperDraw sd2(sd);
    // sd2.printAllTicketNumbers();

    return 0;
}
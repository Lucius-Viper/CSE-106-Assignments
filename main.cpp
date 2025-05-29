#include <iostream>
#include <vector>
#include "queue.h"
using namespace std;

/********************************* RANDOM ************************************/
#define LCG_MULTIPLIER (1103515245)
#define LCG_INCREMENT (12345)
#define LCG_MODULUS ((unsigned)~0 >> 1)
static unsigned int lcg_seed = 1;
void custom_srand(unsigned int seed)
{
    lcg_seed = seed;
}
int custom_rand()
{
    lcg_seed = (LCG_MULTIPLIER * lcg_seed + LCG_INCREMENT) % (LCG_MODULUS + 1);
    return lcg_seed;
}
int randomQueue(int seed = -1)
{
    static bool initialized = false;
    if (seed != -1 && !initialized)
    {
        custom_srand(seed);
        initialized = true;
        return -1;
    }
    cout << "randomQueue() called" << endl;
    return (custom_rand() % 2) + 1;
}
/*****************************************************************************/

int main()
{
    //freopen("test_input_1.txt", "r", stdin); // Test Case 1
     freopen("test_input_2.txt", "r", stdin); // Test Case 2
    freopen("output.txt", "w", stdout);
    // Initialize the random generator with a fixed seed
    // You should set the seed only once at the beginning of your program
    // NOTE: Do not modify the following lines.
    randomQueue(42);

    Queue *Q1 = new ListQueue();
    Queue *Q2 = new ListQueue();
    Queue *Q = new ArrayQueue();

    int N;
    cin >> N;
    int timestamps[10001] = {0};

    for (int i = 1; i <= N; i++)
    {
        // TODO: Edit here to add your own logic
        int x, id;
        cin >> x;
        if (x == 1)
        {
            cin >> id;
            cin >> timestamps[id];
            cout << "Operation " << i << " ( Arrival " << id << " " << timestamps[id] << " ) :";
            if(! Q->empty()) Q->enqueue(id);
            else if (Q1->empty() and Q2->empty())
            {
                int random = randomQueue();
                if (random == 1)
                    Q1->enqueue(id);

                else
                    Q2->enqueue(id);
            }

            else if (Q1->empty())
                Q1->enqueue(id);

            else if (Q2->empty())
                Q2->enqueue(id);

            else
            {
                int q1 = Q1->back();
                int q2 = Q2->back();
                if (timestamps[q1] < timestamps[q2])
                    Q1->enqueue(id);
                else
                    Q2->enqueue(id);
            }
            cout << endl<<"Q1 : " << Q1->toString() << endl;
            cout << "Q2 : " << Q2->toString() << endl
                 << "Q : " << Q->toString() << endl;
        }
        if (x == 2)
        {
            cin >> id;
            int temp, size = Q1->size();
            if (!Q1->empty())
            {
                for (int i = 0; i < size; i++)
                {

                    temp = Q1->dequeue();
                    if (temp == id)
                        continue;
                    else
                    {
                        Q1->enqueue(temp);
                    }
                }
                // Q1->enqueue(id);
            }
            else if (!Q2->empty())
            {
                size = Q2->size();
                for (int i = 0; i < size; i++)
                {

                    temp = Q2->dequeue();
                    if (temp == id)
                        continue;
                    else
                    {
                        Q2->enqueue(temp);
                    }
                }
                // Q2->enqueue(id);
            }
            else if (!Q->empty())
            {
                size = Q->size();
                for (int i = 0; i < size; i++)
                {

                    temp = Q->dequeue();
                    if (temp == id)
                        continue;
                    else
                    {
                        Q->enqueue(temp);
                    }
                }
                // Q->enqueue(id);
            }
            cin >> timestamps[id];
            cout << "Operation " << i << " ( Leave " << id << " " << timestamps[id] << " ) :" << endl;
            cout << "Q1 : " << Q1->toString() << endl;
            cout << "Q2 : " << Q2->toString() << endl
                 << "Q : " << Q->toString() << endl;
        }
        if (x == 3)
        {
            Q->clear();
            while ((!Q1->empty()) or (!Q2->empty()))
            {
                if (Q1->empty())
                {
                    int t = Q2->dequeue();
                    Q->enqueue(t);
                }
                else if (Q2->empty())
                {
                    int t = Q1->dequeue();
                    Q->enqueue(t);
                }
                else
                {
                    if (timestamps[Q1->front()] > timestamps[Q2->front()])
                    {
                        int t = Q2->dequeue();
                        Q->enqueue(t);
                    }
                    else
                    {
                        int t = Q1->dequeue();
                        Q->enqueue(t);
                    }
                }
            }
            cout << "Operation " << i << " (Merge)" << endl;
            cout << "Q1 : " << Q1->toString() << endl;
            cout << "Q2 : " << Q2->toString() << endl
                 << "Q : " << Q->toString() << endl;
        }
        if (x == 4)
        {
            int toggle = 1;
            Q1->clear();
            Q2->clear();
            while (!Q->empty())
            {
                int temp = Q->dequeue();
                if (toggle)
                {
                    Q1->enqueue(temp);
                    toggle = 0;
                }
                else
                {
                    Q2->enqueue(temp);
                    toggle = 1;
                }
            }
            cout << "Operation " << i << " (Split)" << endl;
            cout << "Q1 : " << Q1->toString() << endl;
            cout << "Q2 : " << Q2->toString() << endl
                 << "Q : " << Q->toString() << endl;
        }
        if (x == 5)
        {
            cout << "Operation " << i << " (Departure) :"  ;
            if(! Q->empty()) Q->dequeue();
            else if ((!Q1->empty()) and (!Q2->empty()))
            {
                int random = randomQueue();
                if (random == 1)
                    Q1->dequeue();

                else
                    Q2->dequeue();
            }
            else if (!Q1->empty())
                Q1->dequeue();
            else if (!Q2->empty())
                Q2->dequeue();
            cout << "\nQ1 : " << Q1->toString() << endl;
            cout << "Q2 : " << Q2->toString() << endl
                 << "Q : " << Q->toString() << endl;
        }

        // After each operation, we will check the queue's size and capacity
        // NOTE: Do not modify the following lines.
        int capacity = ((ArrayQueue *)Q)->getCapacity();
        if ((Q->size() < capacity / 4 && capacity > 2))
        {
            cout << "Error: Queue size is less than 25% of its capacity." << endl;
        }
        else if (capacity < 2)
        {
            cout << "Error: Queue capacity is less than 2." << endl;
        }
    }

    return 0;
}
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <windows.h>
using namespace std;

class DFA
{
private:
    // 5 tuples of DFA
    int numStates;
    int initialState;
    int *finalStates;
    char *inputAlphabets;
    int transitions[100][100]; // Transition table

    int numInputAlphabets;
    int numFinalStates;

public:
    DFA()
    {
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                transitions[i][j] = -1;
            }
        }
    }

    void setNumStates(int n)
    {
        numStates = n;
    }
    void setFinalStates(int finals[], int n)
    {
        finalStates = new int[n];
        numFinalStates = n;
        for (int i = 0; i < n; ++i)
            finalStates[i] = finals[i];
    }

    void setInitialState(int initial)
    {
        initialState = initial;
    }

    void setInputAlphabets(char inputalphabets[], int n)
    {
        numInputAlphabets = n;
        inputAlphabets = new char[n];
        for (int i = 0; i < n; i++)
        {
            inputAlphabets[i] = inputalphabets[i];
        }
    }
    void addTransition(int from, char input, int to)
    {
        transitions[from][input - inputAlphabets[0]] = to;
    }

    bool checkfromAlphabets(char check)
    {
        bool exist = false;
        for (int i = 0; i < numInputAlphabets; i++)
        {
            if (check == inputAlphabets[i])
            {
                exist = true;
            }
        }
        return exist;
    }

    bool isAccepted(const string &input)
    {
        int currentState = initialState;
        bool not_alpha = false;
        for (int i = 0; i < input.length(); i++)
        {
            if (!checkfromAlphabets(input[i]))
            {
                not_alpha = true;
                break;
            }
            else
            {
                if (transitions[currentState][input[i] - inputAlphabets[0]] == -1)
                {
                    return false;
                }
                else
                {
                    currentState = transitions[currentState][input[i] - inputAlphabets[0]];
                }
            }
        }

        for (int i = 0; i < numFinalStates && not_alpha == false; ++i)
        {
            if (finalStates[i] == currentState)
            {
                return true;
            }
        }
        return false;
    }
    void simulate(string inputString)
    {
        int currState = initialState;
        string simulatedString;
        bool not_alpha = false;

        for (int i = 0; i < inputString.length(); i++)
        {
            if (!checkfromAlphabets(inputString[i]))
            {
                not_alpha = true;
                break;
            }
            else
            {
                char inputSymbol = inputString[i] - inputAlphabets[0];
                currState = transitions[currState][inputSymbol];
                simulatedString += inputString[i];
                cout << "Current State: " << currState << endl;
                cout << "Simulated String: " << simulatedString << endl;
                if (inputString[i + 1] == '\0')
                {
                    cout << "Next Input symbol: NULL\n";
                }
                else
                {
                    cout << "Next Input symbol: " << inputString[i + 1] << endl;
                }

                cout << "Press any key to continue....\n\n";
                fflush(stdin);
                getchar();
            }
        }

        cout << "String simulation Completed!\n\n";
        for (int i = 0; i < numFinalStates && not_alpha == false; ++i)
        {
            if (finalStates[i] == currState)
            {
                cout << "Result: String is accepted!\n";
                return;
            }
        }

        cout << "Result: String rejected!\n";
    }

    void displayTransitionTable(char inputAlphabet[], int numInput)
    {
        cout << "Transition Table:\n";
        cout << "-----------------\n";
        cout << "State\t|";
        for (int i = 0; i < numInput; ++i)
            cout << " " << inputAlphabet[i] << "\t|";
        cout << endl;
        cout << "-----------------\n";
        for (int i = 0; i < numStates; ++i)
        {
            cout << i << "\t|";
            for (int j = 0; j < numInput; ++j)
            {
                cout << " " << transitions[i][j] << "\t|";
            }
            cout << endl;
        }
        cout << "-----------------\n";
    }
    void AcceptanceCheck(string inputString)
    {

        if (isAccepted(inputString))
        {
            cout << "Result: Accepted\n";
        }
        else
        {
            cout << "Result: Rejected\n";
        }
    }

    void generateGraph(const string &filename, int numFinalStates, int numInput, string inputAlphabet)
    {
        ofstream outfile(filename);

        outfile << "digraph DFA {\n";
        outfile << "\trankdir=LR;\n";
        outfile << "\tsize=\"8,5\"\n";
        outfile << "\tnode [shape = doublecircle];";

        // Final states
        for (int i = 0; i < numStates; ++i)
        {
            for (int j = 0; j < numFinalStates; ++j)
            {
                if (finalStates[j] == i)
                {
                    outfile << " " << i;
                    break;
                }
            }
        }
        outfile << ";\n";
        outfile << "\tnode [shape = circle];\n";

        // Transitions
        for (int i = 0; i < numStates; ++i)
        {
            for (int j = 0; j < numInput; ++j)
            {
                int toState = transitions[i][j];
                if (toState != -1)
                {
                    outfile << "\t" << i << " -> " << toState << " [label=\"" << inputAlphabet[j] << "\"];\n";
                }
            }
        }

        outfile << "}\n";
        outfile.close();
    }
};

int main()
{
    DFA dfa;
    system("cls");
    int numStates, initialState, numFinalStates;
    cout << "\nEnter the number of states: ";
    cin >> numStates;

    cout << "Enter the initial state: ";
    cin >> initialState;

    cout << "Enter the number of final states: ";
    cin >> numFinalStates;

    cout << "Enter the final states: ";
    int finalStates[numFinalStates];
    for (int i = 0; i < numFinalStates; ++i)
        cin >> finalStates[i];

    dfa.setNumStates(numStates);
    dfa.setInitialState(initialState);
    dfa.setFinalStates(finalStates, numFinalStates);

    cout << "\nEnter the number of input alphabets: ";
    int numInput;
    cin >> numInput;

    char inputAlphabet[numInput];
    cout << "\nEnter the input alphabets: \n";
    for (int i = 0; i < numInput; ++i)
    {
        cout << "Input alphabet#0" << i + 1 << " : ";
        cin >> inputAlphabet[i];
    }
    dfa.setInputAlphabets(inputAlphabet, numInput);

    cout << "Enter transitions (from, input, to): ";
    int from, to, flag;
    char input;
    int numTransitions = 0;
    while (numTransitions < numStates * numInput)
    {
        flag = 0;
        cin >> from >> input >> to;
        if ((from < 0 || from >= numStates) || (to < 0 || to >= numStates))
        {
            cout << "Invalid Input...Please Input again.\n";
        }
        else
        {
            for (int i = 0; i < numInput; i++)
            {
                if (input == inputAlphabet[i])
                {
                    dfa.addTransition(from, input, to);
                    numTransitions++;
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                cout << "Invalid Input...Please Input again.\n";
            }
        }
    }

    dfa.displayTransitionTable(inputAlphabet, numInput);

    string inputString;
    do
    {
        cout << "\nEnter a string(Enter 'x' to exit): ";
        cin >> inputString;

        if (inputString != "x")
        {

            int choice;
            cout << "\n\n1 >> Simulate state by state\n"
                 << "2 >> Check the string acceptance\n"
                 << "3 >> Generate Graph\n"
                 << "Choose option: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                cout << endl;
                dfa.simulate(inputString);
                break;
            case 2:
                cout << endl;
                dfa.AcceptanceCheck(inputString);
                break;

            case 3:
                cout << endl;
                dfa.generateGraph("dfa_graph.dot", numFinalStates, numInput, inputAlphabet);
                cout << "Graph has been generated succesfully run \" dot -Tpng dfa_graph.dot -o dfa_graph.png \"  this command in the terminal to create a png for it";
                return 0;
                break;
            default:
                cout << "Invalid Input!\n";
                cout << "Try again..";
                break;
            }
        }
    } while (inputString != "x");

    return 0;
}

/*
Transitions for DFA that starts with "ba"
0 a 3
0 b 1
3 a 3
3 b 3
2 a 2
2 b 2
1 a 2
1 b 3


command to create a png for graph
dot -Tpng dfa_graph.dot -o dfa_graph.png
*/

/*
(does not accept substring aab)
Enter the number of states: 4
Enter the initial state: 0
Enter the number of final states: 3
Enter the final states: 0
1
2

Enter the number of input alphabets: 2

Enter the input alphabets:
Input alphabet#01 : a
Input alphabet#02 : b
Enter transitions (from, input, to):
0 a 1
0 b 0
1 a 2
1 b 0
2 a 2
2 b 3
3 a 3
3 b 3
*/
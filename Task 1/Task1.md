# Task 1 - Building a metamodel of a DFA recognizer

## Description of the metamodel of a deterministic finite state machine for recognizing a random string of characters

The metamodel is implemented in the programming language **С++**.

The metamodel of a deterministic finate automaton-recognizer consists of three classes:

* *State*

```c++
class State {
    
    private:
        std::string name;
        bool finalState;

    public:
        State() {};

        State(std::string inputName, bool inputFinalState) {
            name = inputName;
            finalState = inputFinalState;
        }

        std::string getName() { 
            return name; 
        };

        bool getFinalState() { 
            return finalState; 
        };

        ~State() {};
};
```

* *Transition*

```c++
class Transition {
    private:
        std::string sourceState;
		std::string targetState;
        char event; 

    public:
        Transition() {};

        Transition(std::string inputSourceState, std::string inputTargetState, char trigger) {
            sourceState = inputSourceState;
            targetState = inputTargetState;
            event = trigger;
        };

        std::string getSourceState() { 
            return sourceState; 
        };

        std::string getTargetState() { 
            return targetState; 
        };

        char getEvent() { 
            return event; 
        };

        ~Transition() {};
};
```

* *StateMachine*

```c++
class StateMachine {
    private:
        std::vector<State> states;
        std::vector<Transition> transitions;
        State currentState;

        bool move(char inputTrigger) {
            bool moveStatus = false;
            for(Transition transition:transitions) {
                if ((transition.getSourceState() == currentState.getName()) and (transition.getEvent() == inputTrigger)) {
                    for(State state:states) {
                        if (state.getName() == transition.getTargetState()) {
                            currentState = state;
                        };
                    };
                    moveStatus = true;
                };
            };
            return moveStatus;
        };
    
    public:
        std::vector<State> getStates() { 
            return states; 
        };

        std::vector<Transition> getTransitions() { 
            return transitions; 
        };

        State getCurrentState() { 
            return currentState; 
        };

        void addState(std::string inputName, bool inputFinalState) {
            currentState = State(inputName, inputFinalState);
            states.push_back(currentState);
        };

        void addTransition(std::string inputSourceState, std::string inputTargetState, char trigger) {
            transitions.push_back(Transition(inputSourceState, inputTargetState, trigger));
        };

        bool run(std::string trigger) {
            for(char event: trigger) {
                if (move(event) == false) {
                    return false;
                };
            };

            if (currentState.getFinalState()) {
                return true;
            }
            else {
                return false;
            };
        };
};
```


Let's use the implemented metamodels to construct a finite recognizer atom to parse a string of three symbols **a**, **b**, **c**, consisting of three states **S1**, **S2**, **S3**, and the third of which is admitting.

* ***Tabular representation of a state machine***

| Состояние | a | b | c |
| --- | --- | --- | --- |
| S1 | S1 | S2 | - |
| S2 | S1 | S2 | **S3** |
| **S3** | S1 | S2 | **S3** |

* ***Graphical representation of a finite state machine***

![StateMachineGraph](https://github.com/AlexeyPopov1997/Metamodelling/blob/master/Task%201/StateMachineGraph.PNG?raw=true)

To test the state machine, let's test it with six different input chains:

* abc — Accept
* aabbcc — Accept
* abcccccccc — Accept
* bababa — Reject
* c — Reject
* bca — Reject


## Test

```c++
int main(){
     StateMachine dfa;
     dfa.addState("S1", false);
     dfa.addState("S2", false);
     dfa.addState("S3", true);

    dfa.addTransition("S1", "S1", 'a');
    dfa.addTransition("S1", "S2", 'b');
    dfa.addTransition("S2", "S2", 'b');
    dfa.addTransition("S2", "S1", 'a');
    dfa.addTransition("S2", "S3", 'c');
    dfa.addTransition("S3", "S1", 'a');
    dfa.addTransition("S3", "S2", 'b');
    dfa.addTransition("S3", "S3", 'c');

    std::cout << "Input character string 'abc': " << (dfa.run("abc")) << std::endl;
    std::cout << "Input character string 'aabbcc': " << (dfa.run("aabbcc")) << std::endl;
    std::cout << "Input character string 'abcccccccc': " << (dfa.run("abcccccccc")) << std::endl;
    std::cout << "Input character string 'bababa': " << (dfa.run("bababa")) << std::endl;
    std::cout << "Input character string 'c': " << (dfa.run("c")) << std::endl;
    std::cout << "Input character string 'bca': " << (dfa.run("bca")) << std::endl;

    return 0;
}
```

### Results
```
Input character string 'abc': 1
Input character string 'aabbcc': 1
Input character string 'abcccccccc': 1
Input character string 'bababa': 0
Input character string 'c': 0
Input character string 'bca': 0
```

## Conclusion
The metamodel is correct.
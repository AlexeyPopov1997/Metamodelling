# Task 1 - Building a metamodel of a DFA recognizer

## Description of the metamodel of a deterministic finite state machine for recognizing a random string of characters

Реализация метамодели осуществлена на языке программирования **С++**.

Метамодель детерминированного конечного автомата-распознователя состоит из трех классов:

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


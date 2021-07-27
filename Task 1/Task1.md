# Task 1 - Building a metamodel of a DFA recognizer

## Description of the metamodel of a deterministic finite state machine for recognizing a random string of characters

Реализация метамодели осуществлена на языке программирования **С++**.

Метамодель детерминированного конечного автомата-распознователя состоит из трех классов:

* *State (Сотстояние)*

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

* *Transition (Переход)*

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
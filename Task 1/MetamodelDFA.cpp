#include <string>
#include <vector>
#include <iostream>

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
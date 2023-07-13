#ifndef CHOMUSUKE_FSM_H
#define CHOMUSUKE_FSM_H

#include <string>
#include <functional>
#include <map>

namespace cho{
    template<typename T>
    concept Hashable = requires(T a)
    {
        { std::hash<T>{}(a) } -> std::convertible_to<std::size_t>;
    };

    template<Hashable T>
    class State{
        T id;
        std::function<void()> on_enter;

        public:
        State() = default;

        State(const T& id_, const std::function<void()>& on_enter_):
            id{id_},
            on_enter{on_enter_}
        {}

        inline const T& getId() const {return id; }
        inline void onEnter() const{on_enter(); }
    };

    template<Hashable T, Hashable U>
    class Transition{
        T id;
        U fromState, toState;
        std::function<bool()> condition;
        std::function<void()> callback;

        public:
        Transition() = default;

        Transition(
            const T& id_,
            const U& fromState_,
            const U& toState_,
            const std::function<bool()>& condition_,
            const std::function<void()>& callback_):
            
            id{id_},
            fromState{ fromState_ },
            toState{ toState_ },
            condition{condition_},
            callback{callback_}
        {}

        inline const T& getId() const{return id; }
        inline const U& getFromState() const{return fromState; }
        inline const U& getToState() const {return toState; }
        inline bool canExecute() const{return condition(); }
        inline void executeCallback() const{callback(); }
    };

    template<Hashable State_type, Hashable Transition_type>
    class FSM{ 
        std::unordered_map<State_type, State<State_type>> states;
        std::unordered_map<Transition_type, Transition<Transition_type, State_type>> transitions;
        State_type current_state;

        public:
        FSM() = default;
        
        void addState(const State<State_type>& state){states[state.getId()] = state; }
        void addTransition(const Transition<Transition_type, State_type>& transition){transitions[transition.getId()] = transition; };
        bool executeTransition(const Transition_type& transition_id){
            if(transitions[transition_id].getFromState() != current_state || !transitions[transition_id].canExecute())
                return false;

            current_state = transitions[transition_id].getToState();
            transitions[transition_id].executeCallback();
            states[current_state].onEnter();

            return true;
        }
        void setState(const State_type& id){current_state = id; }
        const State_type& getCurState() const{return current_state; }
        void clear() {
            states.clear();
            transitions.clear();
            return;
        }
    };
}

#endif
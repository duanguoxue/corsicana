#ifndef CORSICANA_MATCH_HPP
#define CORSICANA_MATCH_HPP

#include "corsicana/internal/match_state.hpp"
#include "corsicana/internal/data.hpp"
#include "corsicana/basic_trie.hpp"

namespace corsicana {

template <class T>
class basic_trie;

template <class T>
class match {
public:

    friend class basic_trie<T>;

    class iterator : public std::iterator<std::forward_iterator_tag, T>
    {
        public:
            friend class corsicana::match<T>;

            iterator& operator++() {
                state.next();
                return *this;
            }
            iterator operator++(int) {
                iterator tmp(*this);
                operator++();
                return tmp;
            }

            T const& operator*() const { return state.current(); }
            bool operator==(const iterator& rhs) const { return state == rhs.state; }
            bool operator!=(const iterator& rhs) const { return state != rhs.state; }
        private:
            iterator(corsicana::internal::match_state<T> state) : state(state) {}
            corsicana::internal::match_state<T> state;
    };

    int count() const {
        int count = 0;
        auto state = corsicana::internal::match_begin(text, const_data);
        while(state.next()) { ++count; }
        return count;
    }

    std::vector<T> all() const {
        std::vector<T> output;
        auto state = corsicana::internal::match_begin(text, const_data);
        while(state.next()) {
            output.push_back(state.current());
        }
        return output;
    }

    iterator begin() const {
        auto state = corsicana::internal::match_begin(text, const_data);
        // the begin iterator needs to already be pointing to the first element
        state.next();
        return match<T>::iterator(state);
    }

    iterator end() const {
        auto state = corsicana::internal::match_end(text, const_data);
        return match<T>::iterator(state);
    }

private:
    match(T const& text, const corsicana::internal::data<T>& data) :
        text(text),
        const_data(data) {}

    T text;
    const corsicana::internal::data<T>& const_data;
};

} // namespace corsicana

#endif // CORSICANA_MATCH_HPP
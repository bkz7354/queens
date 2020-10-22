#include <iostream>
#include <type_traits>


// used to iterate over a range 0, ..., (Sz-1)
template<int Sz, int Pos = 0, typename Enable = void>
struct range{
    using next = range<Sz, Pos + 1>;
    const static bool is_end = false;
    const static int pos = Pos;
};

// partial speciliztion to detect end of range
template<int Sz, int Pos>
struct range<Sz, Pos, typename std::enable_if<(Pos >= Sz)>::type>{
	const static bool is_end = true;
};

// actually checks the layout
template<int X, int Y, int Y2, int ...List>
struct check_attack_helper;

template<int X, int Y, int Y2>
struct check_attack_helper<X, Y, Y2>{
    static const bool value = true;
};

template<int X, int Y, int Y2, int X2, int ...List>
struct check_attack_helper<X, Y, Y2, X2, List...>{
    static const bool value = !(X == X2 || Y == Y2 || Y-Y2 == X-X2 || Y-Y2 == X2-X) && check_attack_helper<X, Y, Y2+1, List...>::value;
};


// returns false if layout is imposible 
// (X, Y) - the position of the current queen
// List - x coordinates of previous queens
template<int X, int Y, int ...List>
struct check_attack{
    static const bool value = check_attack_helper<X, Y, 0, List...>::value;
};


// iterates over a row by using the range struct passed as X
// uses the B variable to check if the row ended
template<int N, bool B, typename X, typename Y, int ...XS>
struct pass_row;

// checks if the current row is the past the last (using the B variable), starts pass_row otherwise
template<int N, bool B, typename Y, int ...XS>
struct start_row;

// checks_if layout is possible (using the B variable), if it is, starts next row
template<int N, bool B, typename Y, int ...XS>
struct init_next_row;



template<int N, typename Y, int ...XS>
struct start_row<N, false, Y, XS...>{
    static const int value = 1;
};

template<int N, typename Y, int ...XS>
struct start_row<N, true, Y, XS...>{
    static const int value = pass_row<N, !range<N>::is_end, range<N>, Y, XS...>::value;
};



template<int N, typename Y, int ...XS>
struct init_next_row<N, false,Y, XS...>{
    static const int value = 0;
};

template<int N, typename Y, int ...XS>
struct init_next_row<N, true,Y, XS...>{
    static const int value = start_row<N, !Y::is_end, Y, XS...>::value;
};



template<int N, typename X, typename Y, int ...XS>
struct pass_row<N, false, X, Y, XS...>{
    static const int value = 0;
};

template<int N, typename X, typename Y, int ...XS>
struct pass_row<N, true, X, Y, XS...>{
    static const int value = 
        init_next_row<N, check_attack<X::pos, Y::pos, XS...>::value, typename Y::next, XS..., X::pos>::value + 
        pass_row<N, !X::next::is_end, typename X::next, Y, XS...>::value;
};


template<int N>
struct do_calculations{
    static const int value = start_row<N, true, range<N>>::value;
};


int main(){
    const int N = 8;
    
    std::cout << do_calculations<N>::value << std::endl;
}

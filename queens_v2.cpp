#include <iostream>



// used to iterate
template<int Sz, int Pos = 0>
struct range{
    using next = range<Sz, Pos + 1>;
    const static bool is_end = (Pos >= Sz);
    const static int pos = Pos;
};

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
template<int X, int Y, int ...List>
struct check_attack{
    static const bool value = check_attack_helper<X, Y, 0, List...>::value;
};


template<int N, bool B, typename X, typename Y, int ...XS>
struct pass_row;

template<int N, bool B, typename Y, int ...XS>
struct start_row;

template<int N, typename Y, int ...XS>
struct start_row<N, false, Y, XS...>{
    static const int value = 1;
};

template<int N, typename Y, int ...XS>
struct start_row<N, true, Y, XS...>{
    static const int value = pass_row<N, !range<N>::is_end, range<N>, Y, XS...>::value;
};


template<int N, bool B, typename Y, int ...XS>
struct init_next_row;


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

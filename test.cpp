#include <iostream>
#include <vector>

bool check(int x, std::vector<int> pxs){
	for(int y = 0; y < pxs.size(); ++y){
		if(x == pxs[y] || std::abs(x - pxs[y]) == pxs.size()-y)
			return false;
	}
	
	return true;
}

std::vector<std::vector<int>> ans;
int calc_helper(int n, int y, std::vector<int> pxs){
	if(y >= n){
		ans.push_back(pxs);
		return 1;
	}
	
	int res = 0;
	for(int x = 0; x < n; ++x){
		if(check(x, pxs)){
			auto copy = pxs;
			copy.push_back(x);
			res += calc_helper(n, y+1, copy);
		}
	}
	
	return res;
}

int calc(int n){
	return calc_helper(n, 0, {});
}

int main(){
	int n; bool b; std::cin >> n >> b;
	std::cout << calc(n) << std::endl;
	
	if(b){
		for(auto v: ans){
			for(auto x: v)
				std::cout << x+1 << " ";
			std::cout << std::endl;
		}
	}

}

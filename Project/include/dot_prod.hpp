#pragma once
#include <vector>
int dot_prod(const std::vector<bool>& S, const std::vector<bool>& P) {
	int n = static_cast<int>(S.size());
	int res = 0;
	for (int i = 0; i < n; i++) {
		res = (res + S.at(i)*P.at(i)) % 2;
	}
	return res;
}
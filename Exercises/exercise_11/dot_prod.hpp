#pragma once
#include <vector>
int dot_prod(const std::vector<bool>& S, const std::vector<bool>& P) {
	int n = S.size();
	int res = 0;
	for (int i = 0; i < n; i++) {
		res = (res + S[i]*P[i]) % 2;
	}
	return res;
}
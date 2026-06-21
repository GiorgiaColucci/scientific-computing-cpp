#pragma once
#include <vector>
std::vector<bool> binary_diff (const std::vector<bool>& minuend, const std::vector<bool>& subtrahend) {
	int n = minuend.size();
	std::vector<bool> res(n);
	for (int i = 0; i < n; i++) {
		res[i] = minuend[i] != subtrahend[i];
	}
	return res;
}
#pragma once
#include <vector>
std::vector<bool> binary_diff (const std::vector<bool>& minuend, const std::vector<bool>& subtrahend) {
	int n = static_cast<int>(minuend.size());
	std::vector<bool> res(n);
	for (int i = 0; i < n; i++) {
		res.at(i) = minuend.at(i) != subtrahend.at(i);
	}
	return res;
}
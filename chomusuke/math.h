#ifndef CHOMUSUKE_MATH_H
#define CHOMUSUKE_MATH_H


constexpr int mod(int a, int b) {
	int ret = a % b;
	while (ret < 0)
		ret += b;

	return ret;
}


#endif
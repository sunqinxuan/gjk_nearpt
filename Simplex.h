#include <vector>
#include "vector.h"
using namespace std;

class Simplex
{
public:
	Simplex();
	~Simplex();

	vector3 getLast();

private:
	vector<vector3> points;
}
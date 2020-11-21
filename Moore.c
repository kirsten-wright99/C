#include <stdio.h>
#include <math.h>

#define EPS 1e-10
#define TRUE (1<2)
#define FALSE (!TRUE)

double compute(double n);
int eq (double a, double b);
double search(double lo, double hi);

double students = 0;
double hardware = 0;

int main(void)
{
	int t = 0, i;

	scanf("%d", &t);

	for (i = 0; i < t; i++)
	{
		scanf("%lf %lf", &students, &hardware);

		double lo = 0, hi = students;

		while (compute(hi) > compute(hi * 2))
		{
			hi = hi * 2;
		}
 
    	// one more time, just to be sure we have the highest bound
    	hi = hi * 2;

    	double ans = search(lo, hi);

    	printf("%lf\n", ans);
	}

	return 0;
}

// this function computes the value of the hardware equation
// at the given double n. 
double compute(double n)
{
	double root = sqrt(n);
	double total = students / pow(hardware, root);

	return total + n;
}

// performs a ternary search on the hardware function to find a min
double search(double lo, double hi)
{
    // Check if the lo and hi value are approximately the same
	if (eq(lo, hi))
		return compute(lo);
    
    double m2 = (lo + 2 * hi) / 3;
    double m1 = (2 * lo + hi) / 3;
    
    double time1 = compute(m1);
    double time2 = compute(m2);
    
    // check if time2 is smaller
    if (time1 > time2) 
    {
        return search(m1, hi);
    }
    // time2 is better, move the bound
    else
    {
    	return search(lo, m2);
    }
}

int eq (double a, double b)
{
    // Get the difference
    double diff = a - b;
    if (diff < 0)
        diff = -diff; // absolute value of the difference

    if (diff < EPS)
        return TRUE; // ABSOLUTE ERROR CHECK PASSED

    if (a < 0)
        a = -a; // abs
    if (b < 0)
        b = -b; // abs
    if (a < b)
        a = b; // max

    // Scale the error by the magnitude of the big value
    // This will give a new relative error to check against
    if (a * EPS > diff)
        return TRUE; // RELATIVE ERROR CHECK PASSED
    
    return FALSE; // Not equal values
}
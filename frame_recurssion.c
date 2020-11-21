
#include <stdio.h>

#define EPS 1e-9
#define TRUE (1<2)
#define FALSE (!TRUE)

// The function that checks if two values are equal
int eq (double a, double b);

// The function that searchs from the lo to the hi for the max
// area
// The function return the max area found
double search(double lo, double hi, double length);

// The function that returns the area
double foo(double total, double upper);

// The main function
int main()
{
    // Read in the length
    double length;
    scanf("%lf", &length);
    
    // Initialize the lo and hi bound of the top rod of the
    // frame
    double lo = 0;
    double hi = 1;
    
    // Check if we can use a better upper bound for the length
    // of the top rod
    while (foo(length, hi) < foo(length, hi * 2))
        hi = hi * 2;
    
    // Double one last time to ensure we have the maximum
    // within our range
    hi = hi * 2;

    // Compute the answer by searching from the lo to the hi
    // bound
    double ans = search(lo, hi, length);
    
    // Print the answer
    printf("%lf\n", ans);
    
    // Return the answer
    return 0;
}

double search(double lo, double hi, double length)
{
    // Check if the lo and hi value are approximately the same
    if (eq(lo, hi))
        return foo(length, lo); // Get the area of the frame
    
    // Compute the mid points using the 2 thirds trick discussed
    // in class
    // Note this breaks the search space into 3 "equal" parts
    double m1 = (2 * lo + hi) / 3;
    double m2 = (lo + 2 * hi) / 3;
    
    // Compute the area using the first and second mid points
    // respectively
    double area1 = foo(length, m1);
    double area2 = foo(length, m2);
    
    // Check if area 1 is worse than area 2
    if (area1 < area2) {
        // Since area 1 is worse eliminate the first section of
        // the search
        // Move up the lower bound
        // lo = m1;
        return search(m1, hi, length);
    }
    
    // Area 1 is better move down the hi bound
    return search(lo, m2, length);
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

// This function computes the area of the frame given
//     1. The total length of the wooden rod
//     2. The width of the frame (upper wood piece)
double foo(double total, double upper)
{
    // Compute the remaining length after using the bottom and top
    double remainingRod = total - 2 * upper;

    // Compute the height by using the remaining rod in 6
    // different pieces
    double small = remainingRod / 6;

    // Return the area (product of the height and the width)
    return small * upper;
}

#include <thrust/for_each.h>
#include <thrust/device_vector.h>
#include <thrust/iterator/zip_iterator.h>
#include <iostream>

// This example shows how to implement a complicated transformation that
// requires 3 inputs and 1 output using for_each and zip_iterator.
// Iterators for all four vectors are combined with the zip_iterator 
// into a single sequence of tuples (i.e. they are "zipped" together).
// The complicated_functor receives a tuple that contains four elements,
// which are refrences to values in each of the four sequences.
// When we access the tuple 't' with the get() function
//      get<0>(t) returns a reference to A[i]
//      get<1>(t) returns a reference to B[i]
//      get<2>(t) returns a reference to C[i]
//      get<3>(t) returns a reference to D[i]
//
// In this example, we can implement the transformation,
//      D[i] = A[i] + B[i] * C[i];
// by invoking complicated_functor() on each of the tuples using for_each.

struct complicated_functor
{
    template <typename Tuple>
    __host__ __device__
    void operator()(Tuple t)
    {
        // D[i] = A[i] + B[i] * C[i];
        thrust::get<3>(t) = thrust::get<0>(t) + thrust::get<1>(t) * thrust::get<2>(t);
    }
};


int main(void)
{
    // allocate storage
    thrust::device_vector<float> A(5);
    thrust::device_vector<float> B(5);
    thrust::device_vector<float> C(5);
    thrust::device_vector<float> D(5);

    // initialize input vectors
    A[0] = 3;  B[0] = 6;  C[0] = 2; 
    A[1] = 4;  B[1] = 7;  C[1] = 5; 
    A[2] = 0;  B[2] = 2;  C[2] = 7; 
    A[3] = 8;  B[3] = 1;  C[3] = 4; 
    A[4] = 2;  B[4] = 8;  C[4] = 3; 

    // apply the transformation
    thrust::for_each(thrust::experimental::make_zip_iterator(thrust::make_tuple(A.begin(), B.begin(), C.begin(), D.begin())),
                     thrust::experimental::make_zip_iterator(thrust::make_tuple(A.end(),   B.end(),   C.end(),   D.end())),
                     complicated_functor());

    // print the output
    for(int i = 0; i < 5; i++)
        std::cout << A[i] << " + " << B[i] << " * " << C[i] << " = " << D[i] << std::endl;
}

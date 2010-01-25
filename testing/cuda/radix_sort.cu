#include <thrusttest/unittest.h>
#include <thrust/functional.h>
#include <thrust/sequence.h>
#include <thrust/device_malloc_allocator.h>

#include <thrust/sort.h>
#include <thrust/detail/device/cuda/detail/stable_radix_sort.h>

#if THRUST_DEVICE_BACKEND == THRUST_DEVICE_BACKEND_CUDA

using namespace thrusttest;

template <class Vector>
void InitializeSimpleKeyRadixSortTest(Vector& unsorted_keys, Vector& sorted_keys)
{
    unsorted_keys.resize(7);
    unsorted_keys[0] = 1; 
    unsorted_keys[1] = 3; 
    unsorted_keys[2] = 6;
    unsorted_keys[3] = 5;
    unsorted_keys[4] = 2;
    unsorted_keys[5] = 0;
    unsorted_keys[6] = 4;

    sorted_keys.resize(7); 
    sorted_keys[0] = 0; 
    sorted_keys[1] = 1; 
    sorted_keys[2] = 2;
    sorted_keys[3] = 3;
    sorted_keys[4] = 4;
    sorted_keys[5] = 5;
    sorted_keys[6] = 6;
}

template <class Vector>
void InitializeSimpleKeyValueRadixSortTest(Vector& unsorted_keys, Vector& unsorted_values,
                                           Vector& sorted_keys,   Vector& sorted_values)
{
    unsorted_keys.resize(7);   
    unsorted_values.resize(7);   
    unsorted_keys[0] = 1;  unsorted_values[0] = 0;
    unsorted_keys[1] = 3;  unsorted_values[1] = 1;
    unsorted_keys[2] = 6;  unsorted_values[2] = 2;
    unsorted_keys[3] = 5;  unsorted_values[3] = 3;
    unsorted_keys[4] = 2;  unsorted_values[4] = 4;
    unsorted_keys[5] = 0;  unsorted_values[5] = 5;
    unsorted_keys[6] = 4;  unsorted_values[6] = 6;
    
    sorted_keys.resize(7);
    sorted_values.resize(7);
    sorted_keys[0] = 0;  sorted_values[1] = 0;  
    sorted_keys[1] = 1;  sorted_values[3] = 1;  
    sorted_keys[2] = 2;  sorted_values[6] = 2;
    sorted_keys[3] = 3;  sorted_values[5] = 3;
    sorted_keys[4] = 4;  sorted_values[2] = 4;
    sorted_keys[5] = 5;  sorted_values[0] = 5;
    sorted_keys[6] = 6;  sorted_values[4] = 6;
}

template <class Vector>
void InitializeSimpleStableKeyRadixSortTest(Vector& unsorted_keys, Vector& sorted_keys)
{
    unsorted_keys.resize(9);   
    unsorted_keys[0] = 25; 
    unsorted_keys[1] = 14; 
    unsorted_keys[2] = 35; 
    unsorted_keys[3] = 16; 
    unsorted_keys[4] = 26; 
    unsorted_keys[5] = 34; 
    unsorted_keys[6] = 36; 
    unsorted_keys[7] = 24; 
    unsorted_keys[8] = 15; 
    
    sorted_keys.resize(9);
    sorted_keys[0] = 14; 
    sorted_keys[1] = 16; 
    sorted_keys[2] = 15; 
    sorted_keys[3] = 25; 
    sorted_keys[4] = 26; 
    sorted_keys[5] = 24; 
    sorted_keys[6] = 35; 
    sorted_keys[7] = 34; 
    sorted_keys[8] = 36; 
}


template <class Vector>
struct TestRadixSortKeySimple
{
  void operator()(const size_t dummy)
  {
    typedef typename Vector::value_type T;

    Vector unsorted_keys;
    Vector   sorted_keys;

    InitializeSimpleKeyRadixSortTest(unsorted_keys, sorted_keys);

    thrust::detail::device::cuda::detail::stable_radix_sort(unsorted_keys.begin(), unsorted_keys.end());

    ASSERT_EQUAL(unsorted_keys, sorted_keys);
  }
};
VectorUnitTest<TestRadixSortKeySimple, ThirtyTwoBitTypes, thrust::device_vector, thrust::device_malloc_allocator> TestRadixSortKeySimpleDeviceInstance;


template <class Vector>
struct TestRadixSortKeyValueSimple
{
  void operator()(const size_t dummy)
  {
    Vector unsorted_keys, unsorted_values;
    Vector   sorted_keys,   sorted_values;

    InitializeSimpleKeyValueRadixSortTest(unsorted_keys, unsorted_values, sorted_keys, sorted_values);

    thrust::detail::device::cuda::detail::stable_radix_sort_by_key(unsorted_keys.begin(), unsorted_keys.end(), unsorted_values.begin());

    ASSERT_EQUAL(unsorted_keys,   sorted_keys);
    ASSERT_EQUAL(unsorted_values, sorted_values);
  }
};
VectorUnitTest<TestRadixSortKeyValueSimple, ThirtyTwoBitTypes, thrust::device_vector, thrust::device_malloc_allocator> TestRadixSortKeyValueSimpleDeviceInstance;


//still need to do long/ulong and maybe double

typedef thrusttest::type_list<char,
                               signed char,
                               unsigned char,
                               short,
                               unsigned short,
                               int,
                               unsigned int,
                               long,
                               unsigned long,
                               long long,
                               unsigned long long,
                               double> RadixSortKeyTypes;

template <typename T>
struct TestRadixSort
{
  void operator()(const size_t n)
  {
    thrust::host_vector<T>   h_keys = thrusttest::random_integers<T>(n);
    thrust::device_vector<T> d_keys = h_keys;

    thrust::stable_sort(h_keys.begin(), h_keys.end());
    thrust::detail::device::cuda::detail::stable_radix_sort(d_keys.begin(), d_keys.end());

    ASSERT_ALMOST_EQUAL(h_keys, d_keys);
  }
};
VariableUnitTest<TestRadixSort, RadixSortKeyTypes> TestRadixSortInstance;


template <typename T>
struct TestRadixSortByKey
{
  void operator()(const size_t n)
  {
    thrust::host_vector<T>   h_keys = thrusttest::random_integers<T>(n);
    thrust::device_vector<T> d_keys = h_keys;
    
    thrust::host_vector<unsigned int>   h_values(n);
    thrust::device_vector<unsigned int> d_values(n);
    thrust::sequence(h_values.begin(), h_values.end());
    thrust::sequence(d_values.begin(), d_values.end());

    thrust::stable_sort_by_key(h_keys.begin(), h_keys.end(), h_values.begin());
    thrust::detail::device::cuda::detail::stable_radix_sort_by_key(d_keys.begin(), d_keys.end(), d_values.begin());

    ASSERT_ALMOST_EQUAL(h_keys, d_keys);
    ASSERT_ALMOST_EQUAL(h_values, d_values);
  }
};
VariableUnitTest<TestRadixSortByKey, RadixSortKeyTypes> TestRadixSortByKeyInstance;


template <typename T>
struct TestRadixSortByKeyShortValues
{
  void operator()(const size_t n)
  {
    thrust::host_vector<T>   h_keys = thrusttest::random_integers<T>(n);
    thrust::device_vector<T> d_keys = h_keys;
    
    thrust::host_vector<short>   h_values(n);
    thrust::device_vector<short> d_values(n);
    thrust::sequence(h_values.begin(), h_values.end());
    thrust::sequence(d_values.begin(), d_values.end());

    thrust::stable_sort_by_key(h_keys.begin(), h_keys.end(), h_values.begin());
    thrust::detail::device::cuda::detail::stable_radix_sort_by_key(d_keys.begin(), d_keys.end(), d_values.begin());

    ASSERT_ALMOST_EQUAL(h_keys, d_keys);
    ASSERT_ALMOST_EQUAL(h_values, d_values);
  }
};
VariableUnitTest<TestRadixSortByKeyShortValues, RadixSortKeyTypes> TestRadixSortByKeyShortValuesInstance;

template <typename T>
struct TestRadixSortByKeyFloatValues
{
  void operator()(const size_t n)
  {
    thrust::host_vector<T>   h_keys = thrusttest::random_integers<T>(n);
    thrust::device_vector<T> d_keys = h_keys;
    
    thrust::host_vector<float>   h_values(n);
    thrust::device_vector<float> d_values(n);
    thrust::sequence(h_values.begin(), h_values.end());
    thrust::sequence(d_values.begin(), d_values.end());

    thrust::stable_sort_by_key(h_keys.begin(), h_keys.end(), h_values.begin());
    thrust::detail::device::cuda::detail::stable_radix_sort_by_key(d_keys.begin(), d_keys.end(), d_values.begin());

    ASSERT_ALMOST_EQUAL(h_keys, d_keys);
    ASSERT_ALMOST_EQUAL(h_values, d_values);
  }
};
VariableUnitTest<TestRadixSortByKeyFloatValues, RadixSortKeyTypes> TestRadixSortByKeyFloatValuesInstance;


template <typename T>
struct TestRadixSortVariableBits
{
  void operator()(const size_t n)
  {
#if defined(__GNUC__) && (__GNUC__ <= 4) && (__GNUC_MINOR__ <= 1)
    // some bizzare problem with VariableUnitTest in this particular case
    // on GCC 4.1.2 (SUSE Linux)
    KNOWN_FAILURE;
#else
    for(size_t num_bits = 0; num_bits < 8 * sizeof(T); num_bits += 7){
        thrust::host_vector<T>  h_keys = thrusttest::random_integers<T>(n);
   
        size_t mask = (1 << num_bits) - 1;
        for(size_t i = 0; i < n; i++)
            h_keys[i] &= mask;

        thrust::device_vector<T> d_keys = h_keys;
    
        thrust::stable_sort(h_keys.begin(), h_keys.end());
        thrust::detail::device::cuda::detail::stable_radix_sort(d_keys.begin(), d_keys.end());
    
        ASSERT_ALMOST_EQUAL(h_keys, d_keys);
    }
#endif
  }
};
VariableUnitTest<TestRadixSortVariableBits, IntegralTypes> TestRadixSortVariableBitsInstance;


template <typename T>
struct TestRadixSortByKeyVariableBits
{
  void operator()(const size_t n)
  {
    for(size_t num_bits = 0; num_bits < 8 * sizeof(T); num_bits += 7){
        thrust::host_vector<T>   h_keys = thrusttest::random_integers<T>(n);
   
        const T mask = (1 << num_bits) - 1;
        for(size_t i = 0; i < n; i++)
            h_keys[i] &= mask;

        thrust::device_vector<T> d_keys = h_keys;
    
        thrust::host_vector<unsigned int>   h_values(n);
        thrust::device_vector<unsigned int> d_values(n);
        thrust::sequence(h_values.begin(), h_values.end());
        thrust::sequence(d_values.begin(), d_values.end());

        thrust::stable_sort_by_key(h_keys.begin(), h_keys.end(), h_values.begin());
        thrust::detail::device::cuda::detail::stable_radix_sort_by_key(d_keys.begin(), d_keys.end(), d_values.begin());

        ASSERT_ALMOST_EQUAL(h_keys, d_keys);
        ASSERT_ALMOST_EQUAL(h_values, d_values);
    }
  }
};
VariableUnitTest<TestRadixSortByKeyVariableBits, IntegralTypes> TestRadixSortByKeyVariableBitsInstance;


//void TestRadixSortMemoryLeak(void)
//{   
//    typedef unsigned long long T;
//    const size_t n = (1 << 20) + 3;
//    thrust::host_vector<T>   h_keys = thrusttest::random_integers<T>(n);
//    thrust::device_vector<T> d_keys = h_keys;
//
//    thrust::detail::device::cuda::detail::stable_radix_sort(h_keys.begin(), h_keys.end());
//
//    for (int i = 0; i < 100; i++){
//        thrust::detail::device::cuda::detail::stable_radix_sort(d_keys.begin(), d_keys.end());
//    }
//
//    ASSERT_ALMOST_EQUAL(h_keys, d_keys);
//}
//DECLARE_UNITTEST(TestRadixSortMemoryLeak);


void TestRadixSortUnalignedSimple(void)
{
    typedef thrust::device_vector<int> Vector;
    typedef typename Vector::value_type T;

    Vector unsorted_keys;
    Vector   sorted_keys;

    InitializeSimpleKeyRadixSortTest(unsorted_keys, sorted_keys);
    
    for(int offset = 1; offset < 16; offset++){
        size_t n = unsorted_keys.size() + offset;

        Vector unaligned_unsorted_keys(n, 0);
        Vector   unaligned_sorted_keys(n, 0);
        
        thrust::copy(unsorted_keys.begin(), unsorted_keys.end(), unaligned_unsorted_keys.begin() + offset);
        thrust::copy(  sorted_keys.begin(),   sorted_keys.end(),   unaligned_sorted_keys.begin() + offset);
   
        thrust::detail::device::cuda::detail::stable_radix_sort(unaligned_unsorted_keys.begin() + offset, unaligned_unsorted_keys.end());

        ASSERT_EQUAL(unaligned_unsorted_keys, unaligned_sorted_keys);
    }
}
DECLARE_UNITTEST(TestRadixSortUnalignedSimple);


void TestRadixSortByKeyUnalignedSimple(void)
{
    typedef thrust::device_vector<int> Vector;
    typedef typename Vector::value_type T;

    Vector unsorted_keys, unsorted_values;
    Vector   sorted_keys,   sorted_values;

    InitializeSimpleKeyValueRadixSortTest(unsorted_keys, unsorted_values, sorted_keys, sorted_values);

    for(int offset = 1; offset < 16; offset++){
        size_t n = unsorted_keys.size() + offset;

        Vector   unaligned_unsorted_keys(n, 0);
        Vector     unaligned_sorted_keys(n, 0);
        Vector unaligned_unsorted_values(n, 0);
        Vector   unaligned_sorted_values(n, 0);
        
        thrust::copy(  unsorted_keys.begin(),   unsorted_keys.end(),   unaligned_unsorted_keys.begin() + offset);
        thrust::copy(    sorted_keys.begin(),     sorted_keys.end(),     unaligned_sorted_keys.begin() + offset);
        thrust::copy(unsorted_values.begin(), unsorted_values.end(), unaligned_unsorted_values.begin() + offset);
        thrust::copy(  sorted_values.begin(),   sorted_values.end(),   unaligned_sorted_values.begin() + offset);
   
        thrust::detail::device::cuda::detail::stable_radix_sort_by_key(unaligned_unsorted_keys.begin() + offset, unaligned_unsorted_keys.end(), unaligned_unsorted_values.begin() + offset);

        ASSERT_EQUAL(  unaligned_unsorted_keys,   unaligned_sorted_keys);
        ASSERT_EQUAL(unaligned_unsorted_values, unaligned_sorted_values);
    }
}
DECLARE_UNITTEST(TestRadixSortByKeyUnalignedSimple);

#endif // THRUST_DEVICE_BACKEND == THRUST_DEVICE_BACKEND_CUDA


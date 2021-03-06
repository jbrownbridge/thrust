#include <unittest/unittest.h>
#include <thrust/device_malloc_allocator.h>
#include <vector>
#include <list>
#include <limits>

template <class Vector>
void TestVectorCppZeroSize(void)
{
    Vector v;
    ASSERT_EQUAL(v.size(), 0);
    ASSERT_EQUAL((v.begin() == v.end()), true);
}
DECLARE_VECTOR_UNITTEST(TestVectorCppZeroSize);


void TestVectorCppBool(void)
{
    thrust::host_vector<bool> h(3);
    thrust::device_vector<bool> d(3);

    h[0] = true; h[1] = false; h[2] = true;
    d[0] = true; d[1] = false; d[2] = true;

    ASSERT_EQUAL(h[0], true);
    ASSERT_EQUAL(h[1], false);
    ASSERT_EQUAL(h[2], true);

    ASSERT_EQUAL(d[0], true);
    ASSERT_EQUAL(d[1], false);
    ASSERT_EQUAL(d[2], true);
}
DECLARE_UNITTEST(TestVectorCppBool);


template <class Vector>
void TestVectorCppFrontBack(void)
{
    typedef typename Vector::value_type T;

    Vector v(3);
    v[0] = 0; v[1] = 1; v[2] = 2;

    ASSERT_EQUAL(v.front(), 0);
    ASSERT_EQUAL(v.back(),  2);
}
DECLARE_VECTOR_UNITTEST(TestVectorCppFrontBack);


template <class Vector>
void TestVectorCppData(void)
{
    typedef typename Vector::value_type T;

    Vector v(3);
    v[0] = 0; v[1] = 1; v[2] = 2;

    ASSERT_EQUAL(0,          *v.data());
    ASSERT_EQUAL(1,          *(v.data() + 1));
    ASSERT_EQUAL(2,          *(v.data() + 2));
    ASSERT_EQUAL(&v.front(),  v.data());
    ASSERT_EQUAL(&*v.begin(), v.data());
    ASSERT_EQUAL(&v[0],       v.data());

    const Vector &c_v = v;

    ASSERT_EQUAL(0,            *c_v.data());
    ASSERT_EQUAL(1,            *(c_v.data() + 1));
    ASSERT_EQUAL(2,            *(c_v.data() + 2));
    ASSERT_EQUAL(&c_v.front(),  c_v.data());
    ASSERT_EQUAL(&*c_v.begin(), c_v.data());
    ASSERT_EQUAL(&c_v[0],       c_v.data());
}
DECLARE_VECTOR_UNITTEST(TestVectorCppData);


template <class Vector>
void TestVectorCppElementAssignment(void)
{
    typedef typename Vector::value_type T;

    Vector v(3);

    v[0] = 0; v[1] = 1; v[2] = 2;

    ASSERT_EQUAL(v[0], 0);
    ASSERT_EQUAL(v[1], 1);
    ASSERT_EQUAL(v[2], 2);

    v[0] = 10; v[1] = 11; v[2] = 12;

    ASSERT_EQUAL(v[0], 10);
    ASSERT_EQUAL(v[1], 11);
    ASSERT_EQUAL(v[2], 12);

    Vector w(3);
    w[0] = v[0];
    w[1] = v[1];
    w[2] = v[2];

    ASSERT_EQUAL(v, w);
}
DECLARE_VECTOR_UNITTEST(TestVectorCppElementAssignment);


template <class Vector>
void TestVectorCppFromSTLVector(void)
{
    typedef typename Vector::value_type T;

    std::vector<T> stl_vector(3);
    stl_vector[0] = 0;
    stl_vector[1] = 1;
    stl_vector[2] = 2;

    thrust::host_vector<T> v(stl_vector);

    ASSERT_EQUAL(v.size(), 3);
    ASSERT_EQUAL(v[0], 0);
    ASSERT_EQUAL(v[1], 1);
    ASSERT_EQUAL(v[2], 2);

    v = stl_vector;
    
    ASSERT_EQUAL(v.size(), 3);
    ASSERT_EQUAL(v[0], 0);
    ASSERT_EQUAL(v[1], 1);
    ASSERT_EQUAL(v[2], 2);
}
DECLARE_VECTOR_UNITTEST(TestVectorCppFromSTLVector);


template <class Vector>
void TestVectorCppFillAssign(void)
{
    typedef typename Vector::value_type T;

    thrust::host_vector<T> v;
    v.assign(3, 13);

    ASSERT_EQUAL(v.size(), 3);
    ASSERT_EQUAL(v[0], 13);
    ASSERT_EQUAL(v[1], 13);
    ASSERT_EQUAL(v[2], 13);
}
DECLARE_VECTOR_UNITTEST(TestVectorCppFillAssign);


template <class Vector>
void TestVectorCppAssignFromSTLVector(void)
{
    typedef typename Vector::value_type T;

    std::vector<T> stl_vector(3);
    stl_vector[0] = 0;
    stl_vector[1] = 1;
    stl_vector[2] = 2;

    thrust::host_vector<T> v;
    v.assign(stl_vector.begin(), stl_vector.end());

    ASSERT_EQUAL(v.size(), 3);
    ASSERT_EQUAL(v[0], 0);
    ASSERT_EQUAL(v[1], 1);
    ASSERT_EQUAL(v[2], 2);
}
DECLARE_VECTOR_UNITTEST(TestVectorCppAssignFromSTLVector);


template <class Vector>
void TestVectorCppFromBiDirectionalIterator(void)
{
    typedef typename Vector::value_type T;
    
    std::list<T> stl_list;
    stl_list.push_back(0);
    stl_list.push_back(1);
    stl_list.push_back(2);

    thrust::host_vector<int> v(stl_list.begin(), stl_list.end());

    ASSERT_EQUAL(v.size(), 3);
    ASSERT_EQUAL(v[0], 0);
    ASSERT_EQUAL(v[1], 1);
    ASSERT_EQUAL(v[2], 2);
}
DECLARE_VECTOR_UNITTEST(TestVectorCppFromBiDirectionalIterator);


template <class Vector>
void TestVectorCppAssignFromBiDirectionalIterator(void)
{
    typedef typename Vector::value_type T;
    
    std::list<T> stl_list;
    stl_list.push_back(0);
    stl_list.push_back(1);
    stl_list.push_back(2);

    Vector v;
    v.assign(stl_list.begin(), stl_list.end());

    ASSERT_EQUAL(v.size(), 3);
    ASSERT_EQUAL(v[0], 0);
    ASSERT_EQUAL(v[1], 1);
    ASSERT_EQUAL(v[2], 2);
}
DECLARE_VECTOR_UNITTEST(TestVectorCppAssignFromBiDirectionalIterator);


template <class Vector>
void TestVectorCppAssignFromHostVector(void)
{
    typedef typename Vector::value_type T;

    thrust::host_vector<T> h(3);
    h[0] = 0;
    h[1] = 1;
    h[2] = 2;

    Vector v;
    v.assign(h.begin(), h.end());

    ASSERT_EQUAL(v, h);
}
DECLARE_VECTOR_UNITTEST(TestVectorCppAssignFromHostVector);


template <class Vector>
void TestVectorCppToAndFromHostVector(void)
{
    typedef typename Vector::value_type T;

    thrust::host_vector<T> h(3);
    h[0] = 0;
    h[1] = 1;
    h[2] = 2;

    Vector v(h);

    ASSERT_EQUAL(v, h);

    v = v;

    ASSERT_EQUAL(v, h);

    v[0] = 10;
    v[1] = 11;
    v[2] = 12;

    ASSERT_EQUAL(h[0], 0);  ASSERT_EQUAL(v[0], 10); 
    ASSERT_EQUAL(h[1], 1);  ASSERT_EQUAL(v[1], 11);
    ASSERT_EQUAL(h[2], 2);  ASSERT_EQUAL(v[2], 12);

    h = v;

    ASSERT_EQUAL(v, h);

    h[1] = 11;

    v = h;

    ASSERT_EQUAL(v, h);
}
DECLARE_VECTOR_UNITTEST(TestVectorCppToAndFromHostVector);


template <class Vector>
void TestVectorCppAssignFromDeviceVector(void)
{
    typedef typename Vector::value_type T;

    thrust::device_vector<T> d(3);
    d[0] = 0;
    d[1] = 1;
    d[2] = 2;

    Vector v;
    v.assign(d.begin(), d.end());

    ASSERT_EQUAL(v, d);
}
DECLARE_VECTOR_UNITTEST(TestVectorCppAssignFromDeviceVector);


template <class Vector>
void TestVectorCppToAndFromDeviceVector(void)
{
    typedef typename Vector::value_type T;

    thrust::device_vector<T> h(3);
    h[0] = 0;
    h[1] = 1;
    h[2] = 2;

    Vector v(h);

    ASSERT_EQUAL(v, h);
    
    v = v;

    ASSERT_EQUAL(v, h);

    v[0] = 10;
    v[1] = 11;
    v[2] = 12;

    ASSERT_EQUAL(h[0], 0);  ASSERT_EQUAL(v[0], 10); 
    ASSERT_EQUAL(h[1], 1);  ASSERT_EQUAL(v[1], 11);
    ASSERT_EQUAL(h[2], 2);  ASSERT_EQUAL(v[2], 12);

    h = v;

    ASSERT_EQUAL(v, h);

    h[1] = 11;

    v = h;

    ASSERT_EQUAL(v, h);
}
DECLARE_VECTOR_UNITTEST(TestVectorCppToAndFromDeviceVector);


template <class Vector>
void TestVectorCppWithInitialValue(void)
{
    typedef typename Vector::value_type T;

    const T init = 17;

    Vector v(3, init);

    ASSERT_EQUAL(v.size(), 3);
    ASSERT_EQUAL(v[0], init);
    ASSERT_EQUAL(v[1], init);
    ASSERT_EQUAL(v[2], init);
}
DECLARE_VECTOR_UNITTEST(TestVectorCppWithInitialValue);


template <class Vector>
void TestVectorCppSwap(void)
{
    typedef typename Vector::value_type T;

    Vector v(3);
    v[0] = 0; v[1] = 1; v[2] = 2;

    Vector u(3);
    u[0] = 10; u[1] = 11; u[2] = 12;

    v.swap(u);

    ASSERT_EQUAL(v[0], 10); ASSERT_EQUAL(u[0], 0);  
    ASSERT_EQUAL(v[1], 11); ASSERT_EQUAL(u[1], 1);
    ASSERT_EQUAL(v[2], 12); ASSERT_EQUAL(u[2], 2);
}
DECLARE_VECTOR_UNITTEST(TestVectorCppSwap);


template <class Vector>
void TestVectorCppErasePosition(void)
{
    typedef typename Vector::value_type T;

    Vector v(5);
    v[0] = 0; v[1] = 1; v[2] = 2; v[3] = 3; v[4] = 4;

    v.erase(v.begin() + 2);

    ASSERT_EQUAL(v.size(), 4); 
    ASSERT_EQUAL(v[0], 0); 
    ASSERT_EQUAL(v[1], 1); 
    ASSERT_EQUAL(v[2], 3); 
    ASSERT_EQUAL(v[3], 4); 
    
    v.erase(v.begin() + 0);

    ASSERT_EQUAL(v.size(), 3); 
    ASSERT_EQUAL(v[0], 1); 
    ASSERT_EQUAL(v[1], 3); 
    ASSERT_EQUAL(v[2], 4); 
    
    v.erase(v.begin() + 2);

    ASSERT_EQUAL(v.size(), 2); 
    ASSERT_EQUAL(v[0], 1); 
    ASSERT_EQUAL(v[1], 3); 
    
    v.erase(v.begin() + 1);

    ASSERT_EQUAL(v.size(), 1); 
    ASSERT_EQUAL(v[0], 1); 

    v.erase(v.begin() + 0);

    ASSERT_EQUAL(v.size(), 0); 
}
DECLARE_VECTOR_UNITTEST(TestVectorCppErasePosition);


template <class Vector>
void TestVectorCppEraseRange(void)
{
    typedef typename Vector::value_type T;

    Vector v(6);
    v[0] = 0; v[1] = 1; v[2] = 2; v[3] = 3; v[4] = 4; v[5] = 5;

    v.erase(v.begin() + 1, v.begin() + 3);

    ASSERT_EQUAL(v.size(), 4); 
    ASSERT_EQUAL(v[0], 0); 
    ASSERT_EQUAL(v[1], 3); 
    ASSERT_EQUAL(v[2], 4); 
    ASSERT_EQUAL(v[3], 5); 
    
    v.erase(v.begin() + 2, v.end());

    ASSERT_EQUAL(v.size(), 2); 
    ASSERT_EQUAL(v[0], 0); 
    ASSERT_EQUAL(v[1], 3); 
    
    v.erase(v.begin() + 0, v.begin() + 1);

    ASSERT_EQUAL(v.size(), 1); 
    ASSERT_EQUAL(v[0], 3); 
    
    v.erase(v.begin(), v.end());

    ASSERT_EQUAL(v.size(), 0); 
}
DECLARE_VECTOR_UNITTEST(TestVectorCppEraseRange);


void TestVectorCppEquality(void)
{
#if 1    
    KNOWN_FAILURE;
#else
    thrust::host_vector<int> h_a(3);
    thrust::host_vector<int> h_b(3);
    thrust::host_vector<int> h_c(3);
    h_a[0] = 0;    h_a[1] = 1;    h_a[2] = 2;
    h_b[0] = 0;    h_b[1] = 1;    h_b[2] = 3;
    h_b[0] = 0;    h_b[1] = 1;

    thrust::device_vector<int> d_a(3);
    thrust::device_vector<int> d_b(3);
    thrust::device_vector<int> d_c(3);
    d_a[0] = 0;    d_a[1] = 1;    d_a[2] = 2;
    d_b[0] = 0;    d_b[1] = 1;    d_b[2] = 3;
    d_b[0] = 0;    d_b[1] = 1;

    ASSERT_EQUAL((h_a == h_a), true); ASSERT_EQUAL((h_a == d_a), true); ASSERT_EQUAL((d_a == h_a), true);  ASSERT_EQUAL((d_a == d_a), true); 
    ASSERT_EQUAL((h_b == h_b), true); ASSERT_EQUAL((h_b == d_b), true); ASSERT_EQUAL((d_b == h_b), true);  ASSERT_EQUAL((d_b == d_b), true);
    ASSERT_EQUAL((h_c == h_c), true); ASSERT_EQUAL((h_c == d_c), true); ASSERT_EQUAL((d_c == h_c), true);  ASSERT_EQUAL((d_c == d_c), true);

    ASSERT_EQUAL((h_a == h_b), false); ASSERT_EQUAL((h_a == d_b), false); ASSERT_EQUAL((d_a == h_b), false); ASSERT_EQUAL((d_a == d_b), false); 
    ASSERT_EQUAL((h_b == h_a), false); ASSERT_EQUAL((h_b == d_a), false); ASSERT_EQUAL((d_b == h_a), false); ASSERT_EQUAL((d_b == d_a), false);
    ASSERT_EQUAL((h_a == h_c), false); ASSERT_EQUAL((h_a == d_c), false); ASSERT_EQUAL((d_a == h_c), false); ASSERT_EQUAL((d_a == d_c), false);
    ASSERT_EQUAL((h_c == h_a), false); ASSERT_EQUAL((h_c == d_a), false); ASSERT_EQUAL((d_c == h_a), false); ASSERT_EQUAL((d_c == d_a), false);
    ASSERT_EQUAL((h_b == h_c), false); ASSERT_EQUAL((h_b == d_c), false); ASSERT_EQUAL((d_b == h_c), false); ASSERT_EQUAL((d_b == d_c), false);
    ASSERT_EQUAL((h_c == h_b), false); ASSERT_EQUAL((h_c == d_b), false); ASSERT_EQUAL((d_c == h_b), false); ASSERT_EQUAL((d_c == d_b), false);
#endif    
}
DECLARE_UNITTEST(TestVectorCppEquality);


template <class Vector>
void TestVectorCppResizing(void)
{
    typedef typename Vector::value_type T;

    Vector v;

    v.resize(3);

    ASSERT_EQUAL(v.size(), 3);

    v[0] = 0; v[1] = 1; v[2] = 2;

    v.resize(5);

    ASSERT_EQUAL(v.size(), 5);

    ASSERT_EQUAL(v[0], 0);
    ASSERT_EQUAL(v[1], 1);
    ASSERT_EQUAL(v[2], 2);

    v[3] = 3; v[4] = 4;

    v.resize(4);

    ASSERT_EQUAL(v.size(), 4);

    ASSERT_EQUAL(v[0], 0);
    ASSERT_EQUAL(v[1], 1);
    ASSERT_EQUAL(v[2], 2);
    ASSERT_EQUAL(v[3], 3);

    v.resize(0);

    ASSERT_EQUAL(v.size(), 0);

// TODO remove this WAR      
#if defined(__CUDACC__) && CUDA_VERSION==3000
    // depending on sizeof(T), we will receive one
    // of two possible exceptions
    try
    {
      v.resize(std::numeric_limits<size_t>::max());
    }
    catch(std::length_error e) {}
    catch(std::bad_alloc e)
    {
      // reset the CUDA error
      cudaGetLastError();
    } // end catch
#endif // defined(__CUDACC__) && CUDA_VERSION==3000

    ASSERT_EQUAL(v.size(), 0);
}
DECLARE_VECTOR_UNITTEST(TestVectorCppResizing);



template <class Vector>
void TestVectorCppReserving(void)
{
    typedef typename Vector::value_type T;

    Vector v;

    v.reserve(3);

    ASSERT_GEQUAL(v.capacity(), 3);

    size_t old_capacity = v.capacity();

    v.reserve(0);

    ASSERT_EQUAL(v.capacity(), old_capacity);

// TODO remove this WAR      
#if defined(__CUDACC__) && CUDA_VERSION==3000
    try
    {
      v.reserve(std::numeric_limits<size_t>::max());
    }
    catch(std::length_error e) {}
    catch(std::bad_alloc e) {}
#endif // defined(__CUDACC__) && CUDA_VERSION==3000

    ASSERT_EQUAL(v.capacity(), old_capacity);
}
DECLARE_VECTOR_UNITTEST(TestVectorCppReserving)



template <class Vector>
void TestVectorCppShrinkToFit(void)
{
    typedef typename Vector::value_type T;

    Vector v;

    v.reserve(200);

    ASSERT_GEQUAL(v.capacity(), 200);

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    v.shrink_to_fit();

    ASSERT_EQUAL(1, v[0]);
    ASSERT_EQUAL(2, v[1]);
    ASSERT_EQUAL(3, v[2]);
    ASSERT_EQUAL(3, v.size());
    ASSERT_EQUAL(3, v.capacity());
}
DECLARE_VECTOR_UNITTEST(TestVectorCppShrinkToFit)



template <class Vector>
void TestVectorManipulation(size_t n)
{
    typedef typename Vector::value_type T;

    thrust::host_vector<T> src = unittest::random_samples<T>(n);
    ASSERT_EQUAL(src.size(), n);

    // basic initialization
    Vector test0(n);
    Vector test1(n, (T) 3);
    ASSERT_EQUAL(test0.size(), n);
    ASSERT_EQUAL(test1.size(), n);
    ASSERT_EQUAL((test1 == std::vector<T>(n, (T) 3)), true);
   
    // initializing from other vector
    std::vector<T> stl_vector(src.begin(), src.end());
    Vector cpy0 = src;
    Vector cpy1(stl_vector);
    Vector cpy2(stl_vector.begin(), stl_vector.end());
    ASSERT_EQUAL(cpy0, src);
    ASSERT_EQUAL(cpy1, src);
    ASSERT_EQUAL(cpy2, src);

    // resizing
    Vector vec1(src);
    vec1.resize(n + 3);
    ASSERT_EQUAL(vec1.size(), n + 3);
    vec1.resize(n);
    ASSERT_EQUAL(vec1.size(), n);
    ASSERT_EQUAL(vec1, src); 
    
    vec1.resize(n + 20, (T) 11);
    Vector tail(vec1.begin() + n, vec1.end());
    ASSERT_EQUAL( (tail == std::vector<T>(20, (T) 11)), true);

    vec1.resize(0);
    ASSERT_EQUAL(vec1.size(), 0);
    ASSERT_EQUAL(vec1.empty(), true);
    vec1.resize(10);
    ASSERT_EQUAL(vec1.size(), 10);
    vec1.clear();
    ASSERT_EQUAL(vec1.size(), 0);
    vec1.resize(5);
    ASSERT_EQUAL(vec1.size(), 5);

    // push_back
    Vector vec2;
    for(size_t i = 0; i < 10; ++i){
        ASSERT_EQUAL(vec2.size(), i);
        vec2.push_back( (T) i );
        ASSERT_EQUAL(vec2.size(), i + 1);
        for(size_t j = 0; j <= i; j++)
            ASSERT_EQUAL(vec2[j],     j);
        ASSERT_EQUAL(vec2.back(), i);
    }

    // pop_back
    for(size_t i = 10; i > 0; --i){
        ASSERT_EQUAL(vec2.size(), i);
        ASSERT_EQUAL(vec2.back(), i-1);
        vec2.pop_back();
        ASSERT_EQUAL(vec2.size(), i-1);
        for(size_t j = 0; j < i; j++)
            ASSERT_EQUAL(vec2[j], j);
    }

    //TODO test swap, erase(pos), erase(begin, end)
}

template <typename T>
void TestDeviceVectorCppManipulation(size_t n)
{
    TestVectorManipulation< thrust::device_vector<T> >(n);
}
DECLARE_VARIABLE_UNITTEST(TestDeviceVectorCppManipulation);

template <typename T>
void TestHostVectorCppManipulation(size_t n)
{
    TestVectorManipulation< thrust::host_vector<T> >(n);
}
DECLARE_VARIABLE_UNITTEST(TestHostVectorCppManipulation);

template <class Vector>
struct TestVectorCppRangeInsertSimple
{
    void operator()(size_t dummy)
    {
        Vector v1(5);
        v1[0] = 0;
        v1[1] = 1;
        v1[2] = 2;
        v1[3] = 3;
        v1[4] = 4;

        // test when insertion range fits inside capacity
        // and the size of the insertion is greater than the number
        // of displaced elements
        Vector v2(3);
        v2.reserve(10);
        v2[0] = 0;
        v2[1] = 1;
        v2[2] = 2;

        size_t new_size = v2.size() + v1.size();
        size_t insertion_size = v1.end() - v1.begin();
        size_t num_displaced = v2.end() - (v2.begin() + 1);

        ASSERT_EQUAL(true, v2.capacity()   >= new_size);
        ASSERT_EQUAL(true, insertion_size  >  num_displaced);

        v2.insert(v2.begin() + 1,
                  v1.begin(), v1.end());

        ASSERT_EQUAL(0, v2[0]);

        ASSERT_EQUAL(0, v2[1]);
        ASSERT_EQUAL(1, v2[2]);
        ASSERT_EQUAL(2, v2[3]);
        ASSERT_EQUAL(3, v2[4]);
        ASSERT_EQUAL(4, v2[5]);

        ASSERT_EQUAL(1, v2[6]);
        ASSERT_EQUAL(2, v2[7]);
        
        ASSERT_EQUAL(8,  v2.size());
        ASSERT_EQUAL(10, v2.capacity());

        // test when insertion range fits inside capacity
        // and the size of the insertion is equal to the number
        // of displaced elements
        Vector v3(5);
        v3.reserve(10);
        v3[0] = 0;
        v3[1] = 1;
        v3[2] = 2;
        v3[3] = 3;
        v3[4] = 4;

        new_size = v3.size() + v1.size();
        insertion_size = v1.end() - v1.begin();
        num_displaced = v3.end() - v3.begin();

        ASSERT_EQUAL(true, v3.capacity()   >=  new_size);
        ASSERT_EQUAL(true, insertion_size  ==  num_displaced);

        v3.insert(v3.begin(),
                  v1.begin(), v1.end());

        ASSERT_EQUAL(0, v3[0]);
        ASSERT_EQUAL(1, v3[1]);
        ASSERT_EQUAL(2, v3[2]);
        ASSERT_EQUAL(3, v3[3]);
        ASSERT_EQUAL(4, v3[4]);

        ASSERT_EQUAL(0, v3[5]);
        ASSERT_EQUAL(1, v3[6]);
        ASSERT_EQUAL(2, v3[7]);
        ASSERT_EQUAL(3, v3[8]);
        ASSERT_EQUAL(4, v3[9]);

        ASSERT_EQUAL(10, v3.size());
        ASSERT_EQUAL(10, v3.capacity());

        // test when insertion range fits inside capacity
        // and the size of the insertion is less than the
        // number of displaced elements
        Vector v4(5);
        v4.reserve(10);
        v4[0] = 0;
        v4[1] = 1;
        v4[2] = 2;
        v4[3] = 3;
        v4[4] = 4;

        new_size = v4.size() + v1.size();
        insertion_size = (v1.begin() + 3) - v1.begin();
        num_displaced = v4.end() - (v4.begin() + 1);

        ASSERT_EQUAL(true, v4.capacity()   >=  new_size);
        ASSERT_EQUAL(true, insertion_size  <   num_displaced);

        v4.insert(v4.begin() + 1,
                  v1.begin(), v1.begin() + 3);

        ASSERT_EQUAL(0, v4[0]);

        ASSERT_EQUAL(0, v4[1]);
        ASSERT_EQUAL(1, v4[2]);
        ASSERT_EQUAL(2, v4[3]);

        ASSERT_EQUAL(1, v4[4]);
        ASSERT_EQUAL(2, v4[5]);
        ASSERT_EQUAL(3, v4[6]);
        ASSERT_EQUAL(4, v4[7]);

        ASSERT_EQUAL(8, v4.size());
        ASSERT_EQUAL(10, v4.capacity());

        // test when insertion range does not fit inside capacity
        Vector v5(5);
        v5[0] = 0;
        v5[1] = 1;
        v5[2] = 2;
        v5[3] = 3;
        v5[4] = 4;

        new_size = v5.size() + v1.size();

        ASSERT_EQUAL(true, v5.capacity() < new_size);

        v5.insert(v5.begin() + 1,
                  v1.begin(), v1.end());

        ASSERT_EQUAL(0, v5[0]);

        ASSERT_EQUAL(0, v5[1]);
        ASSERT_EQUAL(1, v5[2]);
        ASSERT_EQUAL(2, v5[3]);
        ASSERT_EQUAL(3, v5[4]);
        ASSERT_EQUAL(4, v5[5]);

        ASSERT_EQUAL(1, v5[6]);
        ASSERT_EQUAL(2, v5[7]);
        ASSERT_EQUAL(3, v5[8]);
        ASSERT_EQUAL(4, v5[9]);

        ASSERT_EQUAL(10, v5.size());
    }
}; // end TestVectorCppRangeInsertSimple
VectorUnitTest<TestVectorCppRangeInsertSimple, NumericTypes, thrust::device_vector, thrust::device_malloc_allocator> TestVectorCppRangeInsertSimpleDeviceInstance;
VectorUnitTest<TestVectorCppRangeInsertSimple, NumericTypes, thrust::host_vector,   std::allocator>   TestVectorCppRangeInsertSimpleHostInstance;

template <class T>
struct TestVectorCppRangeInsert
{
    void operator()(size_t n)
    {
        thrust::host_vector<T>   h_src = unittest::random_samples<T>(n + 3);
        thrust::host_vector<T>   h_dst = unittest::random_samples<T>(n);

        thrust::device_vector<T> d_src = h_src;
        thrust::device_vector<T> d_dst = h_dst;

        // choose insertion range at random
        size_t begin = n > 0 ? (size_t)h_src[n]   % n : 0;
        size_t end   = n > 0 ? (size_t)h_src[n+1] % n : 0;
        if(end < begin) thrust::swap(begin,end);

        // choose insertion position at random
        size_t position = n > 0 ? (size_t)h_src[n+2] % n : 0;

        // insert on host
        h_dst.insert(h_dst.begin() + position,
                     h_src.begin() + begin,
                     h_src.begin() + end);

        // insert on device
        d_dst.insert(d_dst.begin() + position,
                     d_src.begin() + begin,
                     d_src.begin() + end);

        ASSERT_EQUAL(h_dst, d_dst);
    }
}; // end TestVectorCppRangeInsert
VariableUnitTest<TestVectorCppRangeInsert, IntegralTypes> TestVectorCppRangeInsertInstance;

template <class Vector>
struct TestVectorCppFillInsertSimple
{
    void operator()(size_t dummy)
    {
        // test when insertion range fits inside capacity
        // and the size of the insertion is greater than the number
        // of displaced elements
        Vector v1(3);
        v1.reserve(10);
        v1[0] = 0;
        v1[1] = 1;
        v1[2] = 2;

        size_t insertion_size = 5;
        size_t new_size = v1.size() + insertion_size;
        size_t num_displaced = v1.end() - (v1.begin() + 1);

        ASSERT_EQUAL(true, v1.capacity()   >= new_size);
        ASSERT_EQUAL(true, insertion_size  >  num_displaced);

        v1.insert(v1.begin() + 1, insertion_size, 13);

        ASSERT_EQUAL(0, v1[0]);

        ASSERT_EQUAL(13, v1[1]);
        ASSERT_EQUAL(13, v1[2]);
        ASSERT_EQUAL(13, v1[3]);
        ASSERT_EQUAL(13, v1[4]);
        ASSERT_EQUAL(13, v1[5]);

        ASSERT_EQUAL(1, v1[6]);
        ASSERT_EQUAL(2, v1[7]);
        
        ASSERT_EQUAL(8,  v1.size());
        ASSERT_EQUAL(10, v1.capacity());

        // test when insertion range fits inside capacity
        // and the size of the insertion is equal to the number
        // of displaced elements
        Vector v2(5);
        v2.reserve(10);
        v2[0] = 0;
        v2[1] = 1;
        v2[2] = 2;
        v2[3] = 3;
        v2[4] = 4;

        insertion_size = 5;
        new_size = v2.size() + insertion_size;
        num_displaced = v2.end() - v2.begin();

        ASSERT_EQUAL(true, v2.capacity()   >=  new_size);
        ASSERT_EQUAL(true, insertion_size  ==  num_displaced);

        v2.insert(v2.begin(), insertion_size, 13);

        ASSERT_EQUAL(13, v2[0]);
        ASSERT_EQUAL(13, v2[1]);
        ASSERT_EQUAL(13, v2[2]);
        ASSERT_EQUAL(13, v2[3]);
        ASSERT_EQUAL(13, v2[4]);

        ASSERT_EQUAL(0, v2[5]);
        ASSERT_EQUAL(1, v2[6]);
        ASSERT_EQUAL(2, v2[7]);
        ASSERT_EQUAL(3, v2[8]);
        ASSERT_EQUAL(4, v2[9]);

        ASSERT_EQUAL(10, v2.size());
        ASSERT_EQUAL(10, v2.capacity());

        // test when insertion range fits inside capacity
        // and the size of the insertion is less than the
        // number of displaced elements
        Vector v3(5);
        v3.reserve(10);
        v3[0] = 0;
        v3[1] = 1;
        v3[2] = 2;
        v3[3] = 3;
        v3[4] = 4;

        insertion_size = 3;
        new_size = v3.size() + insertion_size;
        num_displaced = v3.end() - (v3.begin() + 1);

        ASSERT_EQUAL(true, v3.capacity()   >=  new_size);
        ASSERT_EQUAL(true, insertion_size  <   num_displaced);

        v3.insert(v3.begin() + 1, insertion_size, 13);

        ASSERT_EQUAL(0, v3[0]);

        ASSERT_EQUAL(13, v3[1]);
        ASSERT_EQUAL(13, v3[2]);
        ASSERT_EQUAL(13, v3[3]);

        ASSERT_EQUAL(1, v3[4]);
        ASSERT_EQUAL(2, v3[5]);
        ASSERT_EQUAL(3, v3[6]);
        ASSERT_EQUAL(4, v3[7]);

        ASSERT_EQUAL(8, v3.size());
        ASSERT_EQUAL(10, v3.capacity());

        // test when insertion range does not fit inside capacity
        Vector v4(5);
        v4[0] = 0;
        v4[1] = 1;
        v4[2] = 2;
        v4[3] = 3;
        v4[4] = 4;

        insertion_size = 5;
        new_size = v4.size() + insertion_size;

        ASSERT_EQUAL(true, v4.capacity() < new_size);

        v4.insert(v4.begin() + 1, insertion_size, 13);

        ASSERT_EQUAL(0, v4[0]);

        ASSERT_EQUAL(13, v4[1]);
        ASSERT_EQUAL(13, v4[2]);
        ASSERT_EQUAL(13, v4[3]);
        ASSERT_EQUAL(13, v4[4]);
        ASSERT_EQUAL(13, v4[5]);

        ASSERT_EQUAL(1, v4[6]);
        ASSERT_EQUAL(2, v4[7]);
        ASSERT_EQUAL(3, v4[8]);
        ASSERT_EQUAL(4, v4[9]);

        ASSERT_EQUAL(10, v4.size());
    }
}; // end TestVectorCppFillInsertSimple
VectorUnitTest<TestVectorCppFillInsertSimple, NumericTypes, thrust::device_vector, thrust::device_malloc_allocator> TestVectorCppFillInsertSimpleDeviceInstance;
VectorUnitTest<TestVectorCppFillInsertSimple, NumericTypes, thrust::host_vector,   std::allocator>   TestVectorCppFillInsertSimpleHostInstance;

template <class T>
struct TestVectorCppFillInsert
{
    void operator()(size_t n)
    {
        thrust::host_vector<T>   h_dst = unittest::random_samples<T>(n + 2);

        thrust::device_vector<T> d_dst = h_dst;

        // choose insertion position at random
        size_t position = n > 0 ? (size_t)h_dst[n] % n : 0;

        // choose insertion size at random
        size_t insertion_size = n > 0 ? (size_t)h_dst[n] % n : 13;

        // insert on host
        h_dst.insert(h_dst.begin() + position,
                     insertion_size,
                     13);

        // insert on device
        d_dst.insert(d_dst.begin() + position,
                     insertion_size,
                     13);

        ASSERT_EQUAL(h_dst, d_dst);
    }
}; // end TestVectorCppFillInsert
VariableUnitTest<TestVectorCppFillInsert, IntegralTypes> TestVectorCppFillInsertInstance;



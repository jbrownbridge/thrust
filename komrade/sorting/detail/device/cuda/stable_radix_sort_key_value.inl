/*
 *  Copyright 2008-2009 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

// do not attempt to compile this file with any other compiler
#ifdef __CUDACC__


#include <limits>
#include <komrade/detail/util/static.h>
#include <komrade/sorting/detail/device/cuda/stable_radix_sort_bits.h>

namespace komrade
{

namespace sorting
{

namespace detail
{

namespace device
{

namespace cuda
{

//////////////////////
// Common Functions //
//////////////////////

template <typename KeyType, typename ValueType>
void stable_radix_sort_key_value_permute_dev(KeyType * keys, ValueType * values, unsigned int num_elements)
{
    // When sizeof(ValueType) != 4 use a permutation to sort the values
    komrade::device_ptr<unsigned int> permutation = komrade::device_malloc<unsigned int>(num_elements);
    komrade::range(permutation, permutation + num_elements);

    stable_radix_sort_key_value_dev(keys, (&permutation[0]).get(), num_elements);
    
    // copy values into temp vector and then permute
    komrade::device_ptr<ValueType> temp_values = komrade::device_malloc<ValueType>(num_elements);
    komrade::copy(komrade::device_ptr<ValueType>(values), 
                  komrade::device_ptr<ValueType>(values + num_elements),
                  temp_values);

    komrade::gather(komrade::device_ptr<ValueType>(values), 
                    komrade::device_ptr<ValueType>(values + num_elements),
                    permutation,
                    temp_values);

    // free temp buffers
    komrade::device_free(permutation);
    komrade::device_free(temp_values);
}

template <typename KeyType, typename ValueType>
void stable_radix_sort_key_value_small_dev(KeyType * keys, ValueType * values, unsigned int num_elements)
{
    // When sizeof(ValueType) == 4 just pretend the ValueType is unsigned int

    // encode the small types in 32-bit unsigned ints
    komrade::device_ptr<unsigned int> full_keys = komrade::device_malloc<unsigned int>(num_elements);
    komrade::transform(komrade::device_ptr<KeyType>(keys), 
                       komrade::device_ptr<KeyType>(keys + num_elements),
                       full_keys,
                       encode_uint<KeyType>());
    
    // sort the 32-bit unsigned ints
    stable_radix_sort_key_value_dev(full_keys.get(), (unsigned int *) values, num_elements);
    
    // decode the 32-bit unsigned ints
    komrade::transform(full_keys,
                       full_keys + num_elements,
                       komrade::device_ptr<KeyType>(keys),
                       decode_uint<KeyType>());

    // free temp buffers
    komrade::device_free(full_keys);
}


/////////////////
// 8 BIT TYPES //
/////////////////

template <typename KeyType, typename ValueType>
void stable_radix_sort_key_value_dev(KeyType * keys, ValueType * values, unsigned int num_elements,
                                     komrade::detail::util::Int2Type<1>)
{
    if (sizeof(ValueType) == 4){
        stable_radix_sort_key_value_small_dev(keys, values, num_elements);
    } else {
        stable_radix_sort_key_value_permute_dev(keys, values, num_elements);
    }
}

//////////////////
// 16 BIT TYPES //
//////////////////

template <typename KeyType, typename ValueType>
void stable_radix_sort_key_value_dev(KeyType * keys, ValueType * values, unsigned int num_elements,
                                     komrade::detail::util::Int2Type<2>)
{
    if (sizeof(ValueType) == 4){
        stable_radix_sort_key_value_small_dev(keys, values, num_elements);
    } else {
        stable_radix_sort_key_value_permute_dev(keys, values, num_elements);
    }
}


//////////////////
// 32 BIT TYPES //
//////////////////

template <typename KeyType, typename ValueType> 
void stable_radix_sort_key_value_dev(KeyType * keys, ValueType * values, unsigned int num_elements,
                                     komrade::detail::util::Int2Type<4>,
                                     komrade::detail::util::Int2Type<4>,
                                     komrade::detail::util::Bool2Type<true>,   
                                     komrade::detail::util::Bool2Type<false>)  // uint32
{
    radix_sort_by_key((unsigned int*) keys, (unsigned int *) values, num_elements, encode_uint<KeyType>(), decode_uint<KeyType>());
}

template <typename KeyType, typename ValueType>
void stable_radix_sort_key_value_dev(KeyType * keys, ValueType * values, unsigned int num_elements,
                                     komrade::detail::util::Int2Type<4>,
                                     komrade::detail::util::Int2Type<4>,
                                     komrade::detail::util::Bool2Type<true>,
                                     komrade::detail::util::Bool2Type<true>)   // int32
{
    // find the smallest value in the array
    KeyType min_val = komrade::reduce(komrade::device_ptr<KeyType>(keys),
                                      komrade::device_ptr<KeyType>(keys + num_elements),
                                      (KeyType) 0,
                                      komrade::minimum<KeyType>());

    if(min_val < 0)
        // negatives present, sort all 32 bits
        radix_sort_by_key((unsigned int*) keys, (unsigned int*) values, num_elements, encode_uint<KeyType>(), decode_uint<KeyType>(), 32);
    else
        // all keys are positive, treat keys as unsigned ints
        radix_sort_by_key((unsigned int*) keys, (unsigned int*) values, num_elements, encode_uint<KeyType>(), decode_uint<KeyType>());
}

template <typename KeyType, typename ValueType>
void stable_radix_sort_key_value_dev(KeyType * keys, ValueType * values, unsigned int num_elements,
                                     komrade::detail::util::Int2Type<4>,
                                     komrade::detail::util::Int2Type<4>,
                                     komrade::detail::util::Bool2Type<false>,
                                     komrade::detail::util::Bool2Type<true>)  // float32
{
    // sort all 32 bits
    radix_sort_by_key((unsigned int*) keys, (unsigned int*) values, num_elements, encode_uint<KeyType>(), decode_uint<KeyType>(), 32);
}

template <typename KeyType, typename ValueType>
void stable_radix_sort_key_value_dev(KeyType * keys, ValueType * values, unsigned int num_elements,
                                     komrade::detail::util::Int2Type<4>)
{
    if (sizeof(ValueType) == 4){
        stable_radix_sort_key_value_dev(keys, values, num_elements,
                                        komrade::detail::util::Int2Type<4>(),
                                        komrade::detail::util::Int2Type<4>(),
                                        komrade::detail::util::Bool2Type<std::numeric_limits<KeyType>::is_exact>(),
                                        komrade::detail::util::Bool2Type<std::numeric_limits<KeyType>::is_signed>());
    } else {
        stable_radix_sort_key_value_permute_dev(keys, values, num_elements);
    }
}

//////////////////
// 64 BIT TYPES //
//////////////////

template <typename KeyType, typename ValueType,
          typename LowerBits, typename UpperBits, 
          typename LowerBitsExtractor, typename UpperBitsExtractor>
void stable_radix_sort_key_value_large_dev(KeyType * keys, ValueType * values, unsigned int num_elements,
                                           LowerBitsExtractor extract_lower_bits,
                                           UpperBitsExtractor extract_upper_bits)
{
    // first sort on the lower 32-bits of the keys
    komrade::device_ptr<unsigned int> partial_keys = komrade::device_malloc<unsigned int>(num_elements);
    komrade::transform(komrade::device_ptr<KeyType>(keys), 
                       komrade::device_ptr<KeyType>(keys + num_elements),
                       partial_keys,
                       extract_lower_bits);

    komrade::device_ptr<unsigned int> permutation = komrade::device_malloc<unsigned int>(num_elements);
    komrade::range(permutation, permutation + num_elements);
    
    stable_radix_sort_key_value_dev((LowerBits *) partial_keys.get(), permutation.get(), num_elements);

    // permute full keys and values so lower bits are sorted
    komrade::device_ptr<KeyType> permuted_keys = komrade::device_malloc<KeyType>(num_elements);
    komrade::gather(permuted_keys, 
                    permuted_keys + num_elements, 
                    permutation,
                    komrade::device_ptr<KeyType>(keys));
    
    komrade::device_ptr<ValueType> permuted_values = komrade::device_malloc<ValueType>(num_elements);
    komrade::gather(permuted_values, 
                    permuted_values + num_elements, 
                    permutation,
                    komrade::device_ptr<ValueType>(values));

    // now sort on the upper 32 bits of the keys
    komrade::transform(permuted_keys, 
                       permuted_keys + num_elements,
                       partial_keys,
                       extract_upper_bits);
    komrade::range(permutation, permutation + num_elements);
    
    stable_radix_sort_key_value_dev((UpperBits *) partial_keys.get(), permutation.get(), num_elements);

    // store sorted keys and values
    komrade::gather(komrade::device_ptr<KeyType>(keys), 
                    komrade::device_ptr<KeyType>(keys + num_elements),
                    permutation,
                    permuted_keys);
    komrade::gather(komrade::device_ptr<ValueType>(values), 
                    komrade::device_ptr<ValueType>(values + num_elements),
                    permutation,
                    permuted_values);

    komrade::device_free(partial_keys);
    komrade::device_free(permutation);
    komrade::device_free(permuted_keys);
    komrade::device_free(permuted_values);
}

    
template <typename KeyType, typename ValueType>
void stable_radix_sort_key_value_dev(KeyType * keys, ValueType * values, unsigned int num_elements,
                                     komrade::detail::util::Int2Type<8>,
                                     komrade::detail::util::Bool2Type<true>,
                                     komrade::detail::util::Bool2Type<false>)  // uint64
{
    stable_radix_sort_key_value_large_dev<KeyType, ValueType, unsigned int, unsigned int, lower_32_bits<KeyType>, upper_32_bits<KeyType> > 
        (keys, values, num_elements, lower_32_bits<KeyType>(), upper_32_bits<KeyType>());
}

template <typename KeyType, typename ValueType>
void stable_radix_sort_key_value_dev(KeyType * keys, ValueType * values, unsigned int num_elements,
                                     komrade::detail::util::Int2Type<8>,
                                     komrade::detail::util::Bool2Type<true>,
                                     komrade::detail::util::Bool2Type<true>)   // int64
{
    stable_radix_sort_key_value_large_dev<KeyType, ValueType, unsigned int, int, lower_32_bits<KeyType>, upper_32_bits<KeyType> > 
        (keys, values, num_elements, lower_32_bits<KeyType>(), upper_32_bits<KeyType>());
}

template <typename KeyType, typename ValueType>
void stable_radix_sort_key_value_dev(KeyType * keys, ValueType * values, unsigned int num_elements,
                                     komrade::detail::util::Int2Type<8>,
                                     komrade::detail::util::Bool2Type<false>,
                                     komrade::detail::util::Bool2Type<true>)  // float64
{
    typedef unsigned long long uint64;
    stable_radix_sort_key_value_large_dev<uint64, ValueType, unsigned int, unsigned int, lower_32_bits<KeyType>, upper_32_bits<KeyType> >
        (reinterpret_cast<uint64 *>(keys), values, num_elements, lower_32_bits<KeyType>(), upper_32_bits<KeyType>());
}

template <typename KeyType, typename ValueType>
void stable_radix_sort_key_value_dev(KeyType * keys, ValueType * values, unsigned int num_elements,
                                     komrade::detail::util::Int2Type<8>)
{
    stable_radix_sort_key_value_dev(keys, values, num_elements,
                                    komrade::detail::util::Int2Type<8>(),
                                    komrade::detail::util::Bool2Type<std::numeric_limits<KeyType>::is_exact>(),
                                    komrade::detail::util::Bool2Type<std::numeric_limits<KeyType>::is_signed>());
}

////////////////
// Dispatcher //
////////////////
template <typename KeyType, typename ValueType> 
void stable_radix_sort_key_value_dev(KeyType * keys, ValueType * values, unsigned int num_elements)
{
    // TODO statically assert is_pod<KeyType>
    stable_radix_sort_key_value_dev(keys, values, num_elements, komrade::detail::util::Int2Type<sizeof(KeyType)>());
}


} // end namespace cuda

} // end namespace device

} // end namespace detail

} // end namespace sorting

} // end namespace komrade

#endif // __CUDACC__


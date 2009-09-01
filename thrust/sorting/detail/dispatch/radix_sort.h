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


/*! \file radix_sort.h
 *  \brief Dispatches radix_sort based on iterator_category.
 */


#include <thrust/iterator/iterator_traits.h>

#include <thrust/sort.h>
#include <thrust/sorting/detail/device/stable_radix_sort.h>

namespace thrust
{

namespace sorting
{

namespace detail
{

namespace dispatch
{

//////////////////
/// HOST PATHS ///
//////////////////

template<typename RandomAccessIterator>
  void stable_radix_sort(RandomAccessIterator begin,
                         RandomAccessIterator end,
                         thrust::host_space_tag)
{
    // no host path, just use stable_sort
    thrust::stable_sort(begin, end);
}

template<typename RandomAccessIterator1,
         typename RandomAccessIterator2>
  void stable_radix_sort_by_key(RandomAccessIterator1 keys_begin,
                                RandomAccessIterator1 keys_end,
                                RandomAccessIterator2 values_begin,
                                thrust::host_space_tag,
                                thrust::host_space_tag)
{
    // no host path, just use stable_sort_by_key
    thrust::stable_sort_by_key(keys_begin, keys_end, values_begin);
} 


////////////////////
/// DEVICE PATHS ///
////////////////////

template<typename RandomAccessIterator>
  void stable_radix_sort(RandomAccessIterator begin,
                         RandomAccessIterator end,
                         thrust::device_space_tag)
{
    thrust::sorting::detail::device::stable_radix_sort(begin, end);
}

template<typename RandomAccessIterator1,
         typename RandomAccessIterator2>
  void stable_radix_sort_by_key(RandomAccessIterator1 keys_begin,
                                RandomAccessIterator1 keys_end,
                                RandomAccessIterator2 values_begin,
                                thrust::device_space_tag,
                                thrust::device_space_tag)
{
    thrust::sorting::detail::device::stable_radix_sort_by_key(keys_begin, keys_end, values_begin);
}

} // end namespace dispatch

} // end namespace detail

} // end namespace sorting

} // end namespace thrust


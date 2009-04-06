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


/*! \file merge_sort.h
 *  \brief Dispatches merge_sort based on iterator_category.
 */

#include <algorithm>

#include <komrade/iterator/iterator_categories.h>
#include <komrade/iterator/iterator_traits.h>
#include <komrade/detail/type_traits.h>

#include <komrade/sorting/detail/host/stable_merge_sort.h>
#include <komrade/sorting/detail/device/cuda/stable_merge_sort.h>


namespace komrade
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

template<typename RandomAccessIterator,
         typename StrictWeakOrdering>
  void stable_merge_sort(RandomAccessIterator begin,
                         RandomAccessIterator end,
                         StrictWeakOrdering comp,
                         komrade::random_access_host_iterator_tag)
{
    komrade::sorting::detail::host::stable_merge_sort(begin, end, comp);
}

template<typename RandomAccessKeyIterator,
         typename RandomAccessValueIterator,
         typename StrictWeakOrdering>
  void stable_merge_sort_by_key(RandomAccessKeyIterator keys_begin,
                                RandomAccessKeyIterator keys_end,
                                RandomAccessValueIterator values_begin,
                                StrictWeakOrdering comp,
                                komrade::random_access_host_iterator_tag,
                                komrade::random_access_host_iterator_tag)
{
    komrade::sorting::detail::host::stable_merge_sort_by_key(keys_begin, keys_end, values_begin, comp);
}


////////////////////
/// DEVICE PATHS ///
////////////////////

template<typename RandomAccessIterator,
         typename StrictWeakOrdering>
  void stable_merge_sort(RandomAccessIterator begin,
                         RandomAccessIterator end,
                         StrictWeakOrdering comp,
                         komrade::random_access_device_iterator_tag)
{
    // implement with merge_sort_by_key_dev for now
    size_t n = end - begin;
    typedef typename komrade::iterator_traits<RandomAccessIterator>::value_type KeyType;

    // XXX it's potentially unsafe to pass the same array for keys & values
    //     implement a legit merge_sort_dev function later
    // XXX use make_device_dereferenceable here instead of assuming &*begin is device_ptr
    return komrade::sorting::detail::device::cuda::stable_merge_sort_by_key_dev<KeyType,KeyType,StrictWeakOrdering>((&*begin).get(), (&*begin).get(), comp, n);
}

template<typename RandomAccessKeyIterator,
         typename RandomAccessValueIterator,
         typename StrictWeakOrdering>
  void stable_merge_sort_by_key(RandomAccessKeyIterator keys_begin,
                            RandomAccessKeyIterator keys_end,
                            RandomAccessValueIterator values_begin,
                            StrictWeakOrdering comp,
                            komrade::random_access_device_iterator_tag,
                            komrade::random_access_device_iterator_tag)
{
    size_t n = keys_end - keys_begin;
    typedef typename komrade::iterator_traits<RandomAccessKeyIterator>::value_type KeyType;
    typedef typename komrade::iterator_traits<RandomAccessValueIterator>::value_type ValueType;

    // XXX use make_device_dereferenceable here instead of assuming &*keys_begin & &*values_begin is device_ptr
    return komrade::sorting::detail::device::cuda::stable_merge_sort_by_key_dev<KeyType,ValueType,StrictWeakOrdering>((&*keys_begin).get(), (&*values_begin).get(), comp, n);
} 


} // end namespace dispatch

} // end namespace detail

} // end namespace sorting

} // end namespace komrade


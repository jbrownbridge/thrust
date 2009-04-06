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


/*! \file uninitialized_copy.inl
 *  \brief Inline file for uninitialized_copy.h.
 */

#include <komrade/uninitialized_copy.h>
#include <komrade/iterator/iterator_traits.h>
#include <komrade/detail/dispatch/uninitialized_copy.h>
#include <komrade/detail/type_traits.h>

namespace komrade
{

template<typename InputIterator,
         typename ForwardIterator>
  ForwardIterator uninitialized_copy(InputIterator first,
                                     InputIterator last,
                                     ForwardIterator result)
{
  typedef typename iterator_traits<ForwardIterator>::value_type ResultType;

  return detail::dispatch::uninitialized_copy(first, last, result,
           typename detail::has_trivial_copy_constructor<ResultType>());
} // end uninitialized_copy()

} // end komrade


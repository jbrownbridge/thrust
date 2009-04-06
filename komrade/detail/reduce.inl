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


/*! \file reduce.inl
 *  \brief Inline file for reduce.h.
 */

#include <komrade/reduce.h>
#include <komrade/functional.h>
#include <komrade/transform_reduce.h>
#include <komrade/iterator/iterator_traits.h>

namespace komrade
{

//////////////////
// Entry Points //
//////////////////

template<typename InputIterator>
typename komrade::iterator_traits<InputIterator>::value_type
  reduce(InputIterator begin,
         InputIterator end)
{
  typedef typename komrade::iterator_traits<InputIterator>::value_type InputType;

  // use InputType(0) as init by default
  return komrade::reduce(begin, end, InputType(0));
} // end reduce()

template<typename InputIterator,
         typename T>
   T reduce(InputIterator begin,
            InputIterator end,
            T init)
{
  // use plus<T> by default
  return komrade::reduce(begin, end, init, komrade::plus<T>());
} // end reduce()


template<typename InputIterator,
         typename T,
         typename BinaryFunction>
   T reduce(InputIterator begin,
            InputIterator end,
            T init,
            BinaryFunction binary_op)
{
  typedef typename komrade::iterator_traits<InputIterator>::value_type InputType;

  // use transform_reduce with identity transformation
  return komrade::transform_reduce(begin, end, komrade::identity<InputType>(), init, binary_op);
} // end reduce()


} // namespace end komrade


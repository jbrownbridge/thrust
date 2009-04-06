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


/*! \file scan.inl
 *  \brief Inline file for scan.h.
 */

#include <komrade/scan.h>
#include <komrade/transform_scan.h>
#include <komrade/iterator/iterator_traits.h>
#include <komrade/functional.h>

namespace komrade
{

//////////////////
// Entry Points //
//////////////////
template<typename InputIterator,
         typename OutputIterator>
  void inclusive_scan(InputIterator first,
                      InputIterator last,
                      OutputIterator result)
{
    typedef typename komrade::iterator_traits<OutputIterator>::value_type OutputType;

    // assume plus as the associative operator
    komrade::inclusive_scan(first, last, result, komrade::plus<OutputType>());
} 

template<typename InputIterator,
         typename OutputIterator,
         typename AssociativeOperator>
  void inclusive_scan(InputIterator first,
                      InputIterator last,
                      OutputIterator result,
                      AssociativeOperator binary_op)
{
    typedef typename komrade::iterator_traits<InputIterator>::value_type InputType;

    // forward to transform_scan with identity transformation
    komrade::transform_inclusive_scan(first, last, result, komrade::identity<InputType>(), binary_op);
}

template<typename InputIterator,
         typename OutputIterator>
  void exclusive_scan(InputIterator first,
                      InputIterator last,
                      OutputIterator result)
{
    typedef typename komrade::iterator_traits<OutputIterator>::value_type OutputType;

    // assume 0 as the initialization value
    komrade::exclusive_scan(first, last, result, OutputType(0));
}

template<typename InputIterator,
         typename OutputIterator,
         typename T>
  void exclusive_scan(InputIterator first,
                      InputIterator last,
                      OutputIterator result,
                      const T init)
{
    typedef typename komrade::iterator_traits<OutputIterator>::value_type OutputType;

    // assume plus as the associative operator
    komrade::exclusive_scan(first, last, result, init, komrade::plus<OutputType>());
} 

template<typename InputIterator,
         typename OutputIterator,
         typename T,
         typename AssociativeOperator>
  void exclusive_scan(InputIterator first,
                      InputIterator last,
                      OutputIterator result,
                      const T init,
                      AssociativeOperator binary_op)
{
    typedef typename komrade::iterator_traits<InputIterator>::value_type InputType;

    // forward to transform_scan with identity transformation
    komrade::transform_exclusive_scan(first, last, result, komrade::identity<InputType>(), init, binary_op);
}

} // end namespace komrade

